#ifndef IRQ_H
#define IRQ_H

#include <types.h>
#include <isr.h> // for "struct registers"

#define PIC1    0x20    // IO base address for master PIC
#define PIC2    0xA0    // IO base address for slave PIC
#define PIC1_COMMAND  PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA (PIC2+1)
#define PIC_8086_MODE 0x1    // 8086/88 (MCS-80/85) mode

#define PIC_INIT_COMMAND 0x11
#define PIC1_OFFSET 0x20 // Master PIC interrupts should start at 0x20 = 32
#define PIC2_OFFSET 0x28 // Slave PIC interrupts should start at 0x28 = 40

#define PIC_EOI_COMMAND 0x20 // End of Interrupt command

#define FIRST_IRQ 0x20 // 32

#define TIMER_IRQ 0
#define KEYBOARD_IRQ 1

void pic_setup_with_irq_remap();
void irq_handler(struct registers);
void install_irq_handler(int, void (*)());

#endif
