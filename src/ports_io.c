#include <stdint.h>
#include <ports_io.h>

uint8_t port_byte_in(uint16_t port)
{
  // "d" to load dx with port
  // "=a" for assigning the value of al to result after the instruction
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void port_byte_out(uint16_t port, uint8_t data)
{
  // "d" to load dx with port
  // "a" to load al with data
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t port_word_in(uint16_t port)
{
  unsigned short result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void port_word_out(uint16_t port, uint8_t data)
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
