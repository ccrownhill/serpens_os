#include <stdint.h>
#include <cmos.h>
#include <ports_io.h>

uint8_t read_cmos_reg(uint8_t reg)
{
  // select the register by sending it to I/O port 0x70
  port_byte_out(0x70, (NMI_DISABLE_BIT << 7) | reg);
  // read the register value from port 0x71
  return port_byte_in(0x71);
}

void write_cmos_reg(uint8_t reg, uint8_t val)
{
  // select the register by sending it to I/O port 0x70
  port_byte_out(0x70, (NMI_DISABLE_BIT << 7) | reg);
  // write the register value by sending it to port 0x71
  return port_byte_out(0x71, val);
}
