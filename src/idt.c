#include <util.h>
#include <idt.h>

// irq handlers for all 256 interrupts
idt_entry_t idt_entries[256];
idt_desc_t idt_desc;

void init_idt()
{
  idt_desc.limit = sizeof(idt_entry_t) * 256 -1;
  idt_desc.base  = (u32)&idt_entries;

  memset((char*)&idt_entries, 0, sizeof(idt_entry_t)*256);

  // set all 48 ISRs by passing the function pointers as 32 bit numbers
  idt_set_gate( 0, (u32)isr0 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 1, (u32)isr1 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 2, (u32)isr2 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 3, (u32)isr3 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 4, (u32)isr4 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 5, (u32)isr5 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 6, (u32)isr6 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 7, (u32)isr7 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 8, (u32)isr8 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate( 9, (u32)isr9 , KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(10, (u32)isr10, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(11, (u32)isr11, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(12, (u32)isr12, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(13, (u32)isr13, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(14, (u32)isr14, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(15, (u32)isr15, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(16, (u32)isr16, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(17, (u32)isr17, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(18, (u32)isr18, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(19, (u32)isr19, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(20, (u32)isr20, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(21, (u32)isr21, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(22, (u32)isr22, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(23, (u32)isr23, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(24, (u32)isr24, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(25, (u32)isr25, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(26, (u32)isr26, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(27, (u32)isr27, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(28, (u32)isr28, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(29, (u32)isr29, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(30, (u32)isr30, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(31, (u32)isr31, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(32, (u32)isr32, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(33, (u32)isr33, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(34, (u32)isr34, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(35, (u32)isr35, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(36, (u32)isr36, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(37, (u32)isr37, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(38, (u32)isr38, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(39, (u32)isr39, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(39, (u32)isr39, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(40, (u32)isr40, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(41, (u32)isr41, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(42, (u32)isr42, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(43, (u32)isr43, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(44, (u32)isr44, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(45, (u32)isr45, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(46, (u32)isr46, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);
  idt_set_gate(47, (u32)isr47, KERNEL_CS, PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR);

  flush_idt((u32)&idt_desc);
}

/**
 * Assign the irq handler to the irq specified by irq_num
 * The irq handler is given as a function pointer that is casted to u32
 * which is better for doing the following assignments and calculations
 */
void idt_set_gate(u8 irq_num, u32 isr_fn_ptr, u16 kernel_cs, u8 type_attr)
{
  idt_entries[irq_num].isr_low = isr_fn_ptr & 0xFFFF;          // lowest 16 bits
  idt_entries[irq_num].isr_high = (isr_fn_ptr >> 16) & 0xFFFF;  // highest 16 bits

  idt_entries[irq_num].kernel_cs = kernel_cs;
  idt_entries[irq_num].reserved = 0;
  idt_entries[irq_num].type_attr = type_attr;
}

/**
 * Load idt descriptor into idtr register with lidt
 * idt_desc_ptr should be cast to u32
 */
void flush_idt(u32 idt_desc_ptr)
{
  __asm__("lidtl (%0)" : : "r" (idt_desc_ptr));
}
