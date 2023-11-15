#ifndef SDCARD_HW_H_
#define SDCARD_HW_H_

#include "alt_types.h"

void sdcard_io_init(void);
inline unsigned char sdcard_read(void);
inline void sdcard_write(unsigned char data);
unsigned char sdcard_assert(void);
void sdcard_deassert(void);
unsigned char sdcard_block_read(unsigned char *buff, alt_u16 cnt);
unsigned char sdcard_block_write(const unsigned char *buff, unsigned char cmd);

#endif /*SDCARD_HW_H_*/
