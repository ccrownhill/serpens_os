#include <irq.h>
#include <display.h> // for printing
#include <util.h> // for int_to_ascii
#include <ports_io.h>

void pic_setup_with_irq_remap()
{
  // save masks (for later restoration)
  u8 mask1 = port_byte_in(PIC1_DATA);
  u8 mask2 = port_byte_in(PIC2_DATA);

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
  port_byte_out(PIC1_DATA, mask1);
  port_byte_out(PIC2_DATA, mask2);
}

void irq_handler(struct registers regs)
{
  char ascii_interrupt[4];
  int_to_ascii(regs.int_no-32, ascii_interrupt);
  kprint_at("Received interrupt: ", 0, 23, WHITE);
  kprint(ascii_interrupt);
}
