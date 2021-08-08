#include <stdint.h>
#include <isr.h>
#include <idt.h>
#include <display.h>
#include <util.h>

void isr_exception_handler(struct registers* regs)
{
  char ascii_interrupt[5];
  int_to_ascii(regs->int_no, ascii_interrupt);
  kprint_at("Received exception: ", 0, 23, WHITE);
  kprint(ascii_interrupt); // kprint just prints right after the last print output
}
