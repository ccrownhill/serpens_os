#ifndef CMOS_H
#define CMOS_H

#include <types.h>

#define NMI_DISABLE_BIT 0 // don't disable NMIs (Non Maskable Interrupts)

u8 read_cmos_reg(u8);
void write_cmos_reg(u8, u8);

#endif
