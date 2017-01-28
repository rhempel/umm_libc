/*! \file xmodem.c \brief XModem Transmit/Receive Implementation with CRC and 1K support. */
//*****************************************************************************
//
// File Name  : 'xmodem.c'
// Title    : XModem Transmit/Receive Implementation with CRC and 1K support
// Author     : Pascal Stang - Copyright (C) 2006
// Created    : 4/22/2006
// Revised    : 7/22/2006
// Version    : 0.1
// Target MCU   : AVR processors
// Editor Tabs  : 4
//
// This code is distributed under the GNU Public License
//    which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
// Modified by BogdanM for the eLua project
// Modified by rhempel for the pbLua project
//*****************************************************************************

#include <string.h>
#include <stdlib.h>

#include "stdconst.h"

#include "xmodem.h"
#include "checksums.h"

#include "console.h"
#include "SysISRHandler.h"

static int xmodem_out( unsigned char c )
{
   return( nxt_putc( c ) ); 
}

static int xmodem_in( void )
{
   return( nxt_getc( 0 ) );
}

static int xmodem_crc_check( const unsigned char *buffer, int size )
{
    // check checksum against packet
     if(crc_xmodem( buffer, size) == ((buffer[size]<<8)+buffer[size+1]))
       return 1;
     else
       return 0;
 }
 
static xmodem_state *pXMstate;

static int xmodem_init( UBYTE state )
{
  pXMstate = malloc( sizeof( xmodem_state ) );

  // If we still don't have a state structure allocated, there's an
  // error...
 
  if( NULL == pXMstate ) {
    return( XMODEM_ERROR_NOMEMORY );
  }
 
  // Now we can set up the receive state for the first time..

  pXMstate->ready      = XMODEM_READY_IDLE;
  pXMstate->flush      = 0;

  pXMstate->seqNum     = 1;      // Sequence number starts at 1
  pXMstate->response   = 'C';    // Solicit a connection with CRC

  pXMstate->retries    = XMODEM_RETRIES;
  pXMstate->expiry     = ISRTicks + XMODEM_TIMEOUT;
  pXMstate->pktBytes   = 0;
  pXMstate->state      = state;

  return( XMODEM_ERROR_NONE );
}

static int xmodem_done( void )
{
  free( pXMstate );
  pXMstate = NULL;
}  

static UBYTE xmodem_updateretry( UBYTE newState )
{
  pXMstate->state = newState;
    
  if( pXMstate->retries ) {
    pXMstate->retries--;

    if( (0 == pXMstate->retries) && (pXMstate->state != XMODEM_SEND_ACK) ) {
      pXMstate->state   = XMODEM_ABORT;
      pXMstate->retries = 4;
    }
  }
} 

static int xmodem_processinput( void )
{
  if( NULL == pXMstate ) {
    return( 0 );
  }

  pXMstate->process = 0;

  if( EOF != (pXMstate->input = xmodem_in()) ) {
  // We have a character, process it if we're not flushing the input stream

    if( !pXMstate->flush ) {
      pXMstate->expiry = ISRTicks + XMODEM_TIMEINC;
      pXMstate->process = 1;
    }
  } else {
  // We have no character, check to see if we've timed out

    if( pXMstate->expiry <= ISRTicks ) {
      // We have timed out, so update the next timeout, unconditionally clear
      // the flush state, set the timeout state, and update the retry counter

      pXMstate->expiry += XMODEM_TIMEINC;
      pXMstate->flush   = 0;

      pXMstate->process = 1;

      xmodem_updateretry( pXMstate->state );
    } 
  }

  return( pXMstate->process || (pXMstate->state & XMODEM_FORCE) );
}

int xmodem_recv( const char **string )
{
  if( NULL == pXMstate ) {
     xmodem_init( XMODEM_RECV_QUERY );
  }

  if( NULL == string ) {
    xmodem_out( CAN );
    xmodem_out( CAN );
    xmodem_done();
  }

  while( xmodem_processinput() ) {

    // Check for input and process only if we have a character or a timeout...

    switch( pXMstate->state ) {
  
      case XMODEM_RECV_QUERY:   xmodem_out( pXMstate->response );
                                pXMstate->state = XMODEM_RECV_REPLY;
                                break;
    
      case XMODEM_RECV_REPLY:   switch( pXMstate->input ) {
                              
                                case EOF: pXMstate->state   = XMODEM_RECV_QUERY;
                                          break;
    
                                case SOH: pXMstate->buffer[0] = SOH; 
                                          pXMstate->pktBytes  = 1;
                                          pXMstate->state     = XMODEM_RECV_PART;
                                          break;
    
                                case EOT: pXMstate->flush     = 1;
                                          pXMstate->response  = ACK; 
                                          pXMstate->state     = XMODEM_RECV_DONE;
                                          break;
    
                                case CAN: pXMstate->state     = XMODEM_RECV_CANCEL;
                                          break;
    
                                default:  break;
                                }
    
                                break;
    
      case XMODEM_RECV_PART:    switch( pXMstate->input ) {
    
                                case EOF: pXMstate->response = NAK;
                                          pXMstate->state    = XMODEM_RECV_QUERY;
                                          break;
    
                                default: // We've got a character - add it to the packet received
                                         // so far...
    
                                         do {
                                           pXMstate->buffer[pXMstate->pktBytes++] = (unsigned char)(pXMstate->input);
    
                                           if( (XMODEM_PKTSIZE+XMODEM_CRCFLAG+4) == pXMstate->pktBytes ) {
                                             pXMstate->state = XMODEM_RECV_PACKET;
                                           } else {
                                             pXMstate->input = xmodem_in();
                                           }
                                         } while( (EOF != pXMstate->input) && (XMODEM_RECV_PACKET != pXMstate->state ) );
                                         break;
                                }
                                break;  
    
      case XMODEM_RECV_PACKET:  // We've got a full packet, so do a consistency check on the sequence number
                                //  and the CRC
                                
                                if( (pXMstate->buffer[1] == (unsigned char)(~pXMstate->buffer[2]) ) &&
                                    xmodem_crc_check( &pXMstate->buffer[3], XMODEM_PKTSIZE ) ) {
   
                                  if( pXMstate->buffer[1] == pXMstate->seqNum ) {
                                    // Is this the packet we are waiting for?
  
                                    pXMstate->seqNum++;
                                    pXMstate->ready    = XMODEM_READY_NEWRX;
                                    pXMstate->retries  = XMODEM_RETRIES;
                                    pXMstate->response = ACK;
                                    pXMstate->state    = XMODEM_RECV_QUERY;

                                    *string = &pXMstate->buffer[3];

                                  } else if( pXMstate->buffer[1] == (unsigned char)(pXMstate->seqNum - 1) ) {
                                    // Retry of previous packet, acknowledge and move on...
     
                                    pXMstate->response = ACK;
                                    pXMstate->state    = XMODEM_RECV_QUERY;
  
                                  } else {
                                    // We're totally out of sync - abort!
  
                                    pXMstate->state    = XMODEM_ABORT;
                                  }
                                } else {
                                  // Packet was corrupt - NAK it, flush the input stream for one timeout
                                  // period and try again
     
                                  pXMstate->response   = NAK;
                                  pXMstate->flush      = 1;

                                  xmodem_updateretry( XMODEM_RECV_QUERY );
                                }
                                break;
    
      case XMODEM_RECV_CANCEL:  switch( pXMstate->input ) { 
    
                                case EOF: // No character recieved, ignore for now
                                          break;
    
                                case CAN: // This is two CAN bytes in a row - ACK it, flush the input
                                          // stream
                                          
                                          pXMstate->flush    = 1;
                                          pXMstate->response = ACK;
                                          pXMstate->state    = XMODEM_RECV_DONE;
                                          break;
    
                                default:  // Some other character was received, reset the machine

                                          pXMstate->flush    = 1;
                                          pXMstate->response = NAK;
                                          pXMstate->state    = XMODEM_RECV_QUERY;
                                          break;
                                }
                                break;
    
      case XMODEM_ABORT:        pXMstate->flush = 1;
                                xmodem_out( CAN );
                                xmodem_out( CAN );
                                pXMstate->response = CAN;
                                pXMstate->state    = XMODEM_RECV_DONE;
                                break;
  
      case XMODEM_RECV_DONE:    xmodem_out( pXMstate->response );
                                xmodem_done();
                                break;
    
      default:                  break;            
      }
  
  }
  return( (NULL == pXMstate) ? XMODEM_READY_DONE : pXMstate->ready );
}

int xmodem_send( const char *string, size_t len )
{
  // First, check if we're sending for the first time, and set up
  // accordingly...
 
  if( NULL == pXMstate ) {
     xmodem_init( XMODEM_SEND_QUERY );
  }

  if( xmodem_processinput() ) {

    switch( pXMstate->state ) {
  
      case XMODEM_SEND_QUERY:   switch( pXMstate->input ) {
                              
                                case 'C': pXMstate->state = XMODEM_SEND_PACKET;
                                          pXMstate->ready = XMODEM_READY_NEWTX;
                                          break;
    
                                case CAN: pXMstate->state = XMODEM_SEND_CANCEL;
                                          break;
    
                                default:  // Should we flush if we get a garbage character here?
                                          break;
                                }
    
                                break;
 
      case XMODEM_SEND_PACKET:  if( pXMstate->ready == XMODEM_READY_TX) {
                                  // Ready to send or retry a packet
                                  
                                  UWORD crc = 0;  
                                 
                                  xmodem_out(  SOH              );
                                  xmodem_out(  pXMstate->seqNum );
                                  xmodem_out( ~pXMstate->seqNum );
  
                                  for( pXMstate->pktBytes = 3; pXMstate->pktBytes < XMODEM_PKTSIZE+3; pXMstate->pktBytes++ ) {
                                    xmodem_out( pXMstate->buffer[pXMstate->pktBytes] );
                                  }
  
                                  crc = crc_xmodem(&(pXMstate->buffer[3]),XMODEM_PKTSIZE);
                                  
                                  xmodem_out( (crc>>8) & 0xFF );
                                  xmodem_out( (crc   ) & 0xFF );
  
                                  pXMstate->state = XMODEM_SEND_WAIT;

                                } else if( (XMODEM_READY_NEWTX == pXMstate->ready) && string ) {
                                  // New packet is ready to be copied into the local buffer

                                  memset( pXMstate->buffer, 0, sizeof( pXMstate->buffer ) );

                                  len = (len > XMODEM_PKTSIZE) ? XMODEM_PKTSIZE : len;

                                  for( pXMstate->pktBytes = 3; pXMstate->pktBytes < len+3; pXMstate->pktBytes++ ) {
                                    pXMstate->buffer[pXMstate->pktBytes] = *string++;
                                  }

                                  pXMstate->ready = XMODEM_READY_TX;

                                } else {
                                  // No more data from application

                                  pXMstate->state = XMODEM_SEND_CLOSE;
                                }

                                break;
  
      case XMODEM_SEND_WAIT:    switch( pXMstate->input ) {
                              
                                case ACK: pXMstate->seqNum++;
                                          pXMstate->retries = XMODEM_RETRIES;
                                          pXMstate->state   = XMODEM_SEND_PACKET;
                                          pXMstate->ready   = XMODEM_READY_NEWTX;
                                          break;
  
                                case NAK: xmodem_updateretry( XMODEM_SEND_PACKET );
                                          break;
    
                                case CAN: pXMstate->state   = XMODEM_SEND_CANCEL;
                                          break;
    
                                default:  // Should we flush if we get a garbage character here?
                                          xmodem_updateretry( XMODEM_SEND_PACKET );
                                          break;
                                }
  
                                break;
  
      case XMODEM_SEND_CANCEL:  switch( pXMstate->input ) { 
    
                                case EOF: // No character recieved, ignore for now
                                          break;
    
                                case CAN: // This is two CAN bytes in a row - cancel by receiver
                                          xmodem_out( ACK );
                                          xmodem_done ();
                                          break;
    
                                default:  // Should we flush if we get a garbage character here?
                                          // Some other character was received, look for correct response
                                          pXMstate->state    = XMODEM_SEND_WAIT;
                                          break;
                                }
  
                                break;
  
      case XMODEM_ABORT:        pXMstate->response = CAN;
                                
                                xmodem_out( pXMstate->response );
                                xmodem_out( pXMstate->response );

                                pXMstate->state = XMODEM_SEND_ACK;
                                break;
  
      case XMODEM_SEND_CLOSE:   pXMstate->response = EOT;
                                
                                xmodem_out( pXMstate->response );
                                
                                pXMstate->state = XMODEM_SEND_ACK;
                                break;

      case XMODEM_SEND_ACK:     switch( pXMstate->input ) { 
                                    
                                case ACK: xmodem_done();
                                          break;
    
                                default:  xmodem_out( pXMstate->response );
                                          xmodem_out( pXMstate->response );

                                          if( 0 == pXMstate->retries ) {
                                            xmodem_done();
                                          }
                                }
                                break;
   }
  }

  return( (NULL == pXMstate) ? XMODEM_READY_DONE : pXMstate->ready );
}


