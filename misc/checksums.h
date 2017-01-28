
#ifndef __CHECKSUMS_H__
#define __CHECKSUMS_H__

#include "stdconst.h"

extern UWORD crc_xmodem(const unsigned char *buffer, int size);
extern ULONG sum_bytes( const unsigned char *buffer, int size);

#endif
