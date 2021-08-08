#include <stdint.h>
#include <idt.h>
#include <util.h>

// irq handlers for all 256 interrupts
idt_entry_t idt_entries[256];
idt_desc_t idt_desc;

void init_idt()
{
  idt_desc.limit = sizeof(idt_entry_t) * 256 -1;
  idt_desc.base  = (uint32_t)&idt_entries;

  memset((char*)&idt_entries, 0, sizeof(idt_entry_t)*256);

  // set all 48 ISRs by passing the function pointers as 32 bit numbers
  idt_set_gate( 0, (uint32_t)isr0 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 1, (uint32_t)isr1 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 2, (uint32_t)isr2 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 3, (uint32_t)isr3 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 4, (uint32_t)isr4 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 5, (uint32_t)isr5 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 6, (uint32_t)isr6 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 7, (uint32_t)isr7 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 8, (uint32_t)isr8 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 9, (uint32_t)isr9 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(10, (uint32_t)isr10, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(11, (uint32_t)isr11, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(12, (uint32_t)isr12, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(13, (uint32_t)isr13, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(14, (uint32_t)isr14, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(15, (uint32_t)isr15, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(16, (uint32_t)isr16, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(17, (uint32_t)isr17, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(18, (uint32_t)isr18, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(19, (uint32_t)isr19, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(20, (uint32_t)isr20, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(21, (uint32_t)isr21, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(22, (uint32_t)isr22, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(23, (uint32_t)isr23, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(24, (uint32_t)isr24, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(25, (uint32_t)isr25, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(26, (uint32_t)isr26, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(27, (uint32_t)isr27, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(28, (uint32_t)isr28, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(29, (uint32_t)isr29, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(30, (uint32_t)isr30, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(31, (uint32_t)isr31, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(32, (uint32_t)isr32, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(33, (uint32_t)isr33, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(34, (uint32_t)isr34, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(35, (uint32_t)isr35, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(36, (uint32_t)isr36, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(37, (uint32_t)isr37, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(38, (uint32_t)isr38, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(39, (uint32_t)isr39, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(39, (uint32_t)isr39, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(40, (uint32_t)isr40, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(41, (uint32_t)isr41, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(42, (uint32_t)isr42, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(43, (uint32_t)isr43, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(44, (uint32_t)isr44, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(45, (uint32_t)isr45, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(46, (uint32_t)isr46, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(47, (uint32_t)isr47, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);

  flush_idt((uint32_t)&idt_desc);
}

/**
 * Assign the irq handler to the irq specified by irq_num
 * The irq handler is given as a function pointer that is casted to uint32_t
 * which is better for doing the following assignments and calculations
 */
void idt_set_gate(uint8_t irq_num, uint32_t isr_fn_ptr, uint16_t kernel_cs, uint8_t type_attr)
{
  idt_entries[irq_num].isr_low = isr_fn_ptr & 0xFFFF;          // lowest 16 bits
  idt_entries[irq_num].isr_high = (isr_fn_ptr >> 16) & 0xFFFF;  // highest 16 bits

  idt_entries[irq_num].kernel_cs = kernel_cs;
  idt_entries[irq_num].reserved = 0;
  idt_entries[irq_num].type_attr = type_attr;
}

/**
 * Load idt descriptor into idtr register with lidt
 * idt_desc_ptr should be cast to uint32_t
 */
void flush_idt(uint32_t idt_desc_ptr)
{
  __asm__("lidtl (%0)" : : "r" (idt_desc_ptr));
}
