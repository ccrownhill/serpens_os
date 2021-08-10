#include <stdint.h>
#include <irq.h>
#include <display.h> // for printing
#include <util.h> // for int_to_ascii
#include <ports_io.h>

void (*irq_handlers[16])() = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void pic_setup_with_irq_remap()
{
  // save masks (for later restoration)
  uint8_t mask1 = port_byte_in(PIC1_DATA);
  uint8_t mask2 = port_byte_in(PIC2_DATA);

  port_byte_out(PIC1_COMMAND, PIC_INIT_COMMAND); // starts the initialization sequence (in cascade mode)
  io_wait();
  port_byte_out(PIC2_COMMAND, PIC_INIT_COMMAND);
  io_wait();
  port_byte_out(PIC1_DATA, PIC1_OFFSET); // 0x20 offset = 32 for IRQs 0-7 on master PIC
  io_wait();
  port_byte_out(PIC2_DATA, PIC2_OFFSET); // 0x28 offset = 40 for IRQs 8-15 on slave PIC
  io_wait();
  port_byte_out(PIC1_DATA, 4); //tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  io_wait();
  port_byte_out(PIC2_DATA, 2); //tell Slave PIC its cascade identity (0000 0010)
  io_wait();

  port_byte_out(PIC1_DATA, PIC_8086_MODE);
  io_wait();
  port_byte_out(PIC2_DATA, PIC_8086_MODE);
  io_wait();

  // restore saved masks
  // hopefully all interrupts are 0 (enabled) and not 1 (disabled)
  port_byte_out(PIC1_DATA, mask1);
  port_byte_out(PIC2_DATA, mask2);

  __asm__("sti"); // enable interrupts (sets interrupt flag)
}

void irq_handler(struct registers* regs)
{
  void (*handler)();
  handler = irq_handlers[regs->int_no - FIRST_IRQ];

  if (handler)
    handler();

  // Send End Of Interrupt to master (and maybe slave) PIC
  if (regs->int_no >= FIRST_IRQ+8) // check if IRQ is from the Slave PIC (IRQ 8-15)
    port_byte_out(PIC2_COMMAND, PIC_EOI_COMMAND); // send EOI to Slave PIC

  port_byte_out(PIC1_COMMAND, PIC_EOI_COMMAND); // send EOI to Master PIC
}

void install_irq_handler(int irq_num, void (*handler)())
{
  irq_handlers[irq_num] = handler;
}
