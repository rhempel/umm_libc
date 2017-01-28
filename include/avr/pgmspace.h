#ifndef __PGMSPACE_H_
#define __PGMSPACE_H_ 1

// RHempel - Added stuff here to get us going on the ARM

#define pgm_read_byte(fmt) (*fmt)
#define strlen_P(p) strlen((p))
#define strnlen_P(p,s) strnlen((p),(s))                              

#endif /* __PGMSPACE_H_ */
