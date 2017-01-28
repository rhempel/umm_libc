// These are the variables and includes needed by the NXT

#include "stdconst.h"

#include "checksums.h"


ULONG sum_bytes( const unsigned char *buffer, int size)
{
  ULONG sum = 0;
  
  while( size-- )
    sum += (UBYTE)(buffer[size]);

  return( sum );
}


UWORD crc_xmodem(const unsigned char *buffer, int size)
{
  UWORD crc = 0;
  
    while(size--) {
      crc =  (crc>>8) | (crc<<8);
      crc ^= *buffer++;
      crc ^= (crc&0xFF) >>  4;
      crc ^= (crc     ) << 12;
      crc ^= (crc&0xff) <<  5;
    }

  return crc;
}
