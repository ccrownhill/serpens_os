#ifndef CMOS_H
#define CMOS_H

#define NMI_DISABLE_BIT 0 // don't disable NMIs (Non Maskable Interrupts)

uint8_t read_cmos_reg(uint8_t);
void write_cmos_reg(uint8_t, uint8_t);

#endif
