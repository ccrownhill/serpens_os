#include <ports_io.h>

u8 port_byte_in(u16 port)
{
  // "d" to load dx with port
  // "=a" for assigning the value of al to result after the instruction
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void port_byte_out(u16 port, u8 data)
{
  // "d" to load dx with port
  // "a" to load al with data
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

u16 port_word_in(u16 port)
{
  unsigned short result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void port_word_out(u16 port, u8 data)
{
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

/**
 * Wait for one I/O operation to complete
 * by writing a byte to I/O port 0x80 (unused)
 */
void io_wait()
{
  asm volatile ( "out %%al, $0x80" : : "a" (0) );
}
