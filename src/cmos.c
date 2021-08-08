#include <cmos.h>
#include <ports_io.h>

u8 read_cmos_reg(u8 reg)
{
  // select the register by sending it to I/O port 0x70
  port_byte_out(0x70, (NMI_DISABLE_BIT << 7) | reg);
  // read the register value from port 0x71
  return port_byte_in(0x71);
}

void write_cmos_reg(u8 reg, u8 val)
{
  // select the register by sending it to I/O port 0x70
  port_byte_out(0x70, (NMI_DISABLE_BIT << 7) | reg);
  // write the register value by sending it to port 0x71
  return port_byte_out(0x71, val);
}
