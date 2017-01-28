#include "stdconst.h"

// XMODEM constants

#define XMODEM_RETRIES (8)
#define XMODEM_TIMEOUT (8000)
#define XMODEM_TIMEINC (2000)
#define XMODEM_PKTSIZE (128)
#define XMODEM_CRCFLAG (1)

typedef struct xmodem_state_t {
  UBYTE  state;
  UBYTE  ready;

  UBYTE  response;
  int    input;

  UBYTE  flush;
  UBYTE  process;
  UBYTE  done;

  UBYTE  retries;
  ULONG  expiry;

  UBYTE  seqNum;
  UBYTE  pktBytes;
  UBYTE  buffer[XMODEM_PKTSIZE+6];
} xmodem_state;

extern int xmodem_recv( const char **        );
extern int xmodem_send( const char *, size_t );

// xmodem control characters
#define SOH       (0x01)
#define STX       (0x02)
#define EOT       (0x04)
#define ACK       (0x06)
#define NAK       (0x15)
#define CAN       (0x18)
#define CTRLZ     (0x1A)

#define XMODEM_READY_DONE  (0)
#define XMODEM_READY_IDLE  (1)
#define XMODEM_READY_NEWRX (2)
#define XMODEM_READY_NEWTX (3)
#define XMODEM_READY_TX    (4)

// error return codes

#define XMODEM_ERROR_NONE          ( 0)
#define XMODEM_ERROR_REMOTECANCEL  (-1)
#define XMODEM_ERROR_EXCEEDEDRETRY (-2)
#define XMODEM_ERROR_OUTOFSYNC     (-3)
#define XMODEM_ERROR_NOMEMORY      (-4)
#define XMODEM_ERROR_ALREADYTX     (-5)
#define XMODEM_ERROR_ALREADYRX     (-6)

// state masks

#define XMODEM_STATE_MASK          (0x0F)
#define XMODEM_DIR                 (0x10)
#define XMODEM_FORCE               (0x20)

#define XMODEM_IDLE                (0x00)

#define XMODEM_ABORT               (XMODEM_FORCE | 0x0F)

// receive states

#define XMODEM_RECV_QUERY          (XMODEM_FORCE | 0x01)
#define XMODEM_RECV_REPLY          (               0x02)
#define XMODEM_RECV_PART           (               0x03)
#define XMODEM_RECV_PACKET         (XMODEM_FORCE | 0x04)
#define XMODEM_RECV_CANCEL         (               0x05)
#define XMODEM_RECV_DONE           (XMODEM_FORCE | 0x07)

// send states

#define XMODEM_SEND_QUERY          (               0x11)
#define XMODEM_SEND_PACKET         (XMODEM_FORCE | 0x12)
#define XMODEM_SEND_WAIT           (               0x13)
#define XMODEM_SEND_CANCEL         (               0x14)
#define XMODEM_SEND_CLOSE          (XMODEM_FORCE | 0x15)
#define XMODEM_SEND_ACK            (               0x16)

// #define XMODEM_ERROR_REMOTECANCEL (-1)
// #define XMODEM_ERROR_OUTOFSYNC    (-2)
// #define XMODEM_ERROR_RETRYEXCEED  (-3)
// #define XMODEM_ERROR_OUTOFMEM     (-4)

