#include <util.h>
#include <idt.h>

// irq handlers for all 256 interrupts
struct idt_entry idt_entries[256];
struct idt_descriptor idt_desc;

void init_idt()
{
	idt_desc.limit = sizeof(struct idt_entry) * 256 -1;
	idt_desc.base  = (u32)&idt_entries;

	memset((u8*)&idt_entries, 0, sizeof(struct idt_entry)*256);

	// set all 48 ISRs by passing the function pointers as 32 bit numbers
	// TODO: WHY IS IT FLAG 0x8e
	idt_set_gate( 0, (u32)isr0 , 0x08, 0x8E);
	idt_set_gate( 1, (u32)isr1 , 0x08, 0x8E);
	idt_set_gate( 2, (u32)isr2 , 0x08, 0x8E);
	idt_set_gate( 3, (u32)isr3 , 0x08, 0x8E);
	idt_set_gate( 4, (u32)isr4 , 0x08, 0x8E);
	idt_set_gate( 5, (u32)isr5 , 0x08, 0x8E);
	idt_set_gate( 6, (u32)isr6 , 0x08, 0x8E);
	idt_set_gate( 7, (u32)isr7 , 0x08, 0x8E);
	idt_set_gate( 8, (u32)isr8 , 0x08, 0x8E);
	idt_set_gate( 9, (u32)isr9 , 0x08, 0x8E);
	idt_set_gate(10, (u32)isr10, 0x08, 0x8E);
	idt_set_gate(11, (u32)isr11, 0x08, 0x8E);
	idt_set_gate(12, (u32)isr12, 0x08, 0x8E);
	idt_set_gate(13, (u32)isr13, 0x08, 0x8E);
	idt_set_gate(14, (u32)isr14, 0x08, 0x8E);
	idt_set_gate(15, (u32)isr15, 0x08, 0x8E);
	idt_set_gate(16, (u32)isr16, 0x08, 0x8E);
	idt_set_gate(17, (u32)isr17, 0x08, 0x8E);
	idt_set_gate(18, (u32)isr18, 0x08, 0x8E);
	idt_set_gate(19, (u32)isr19, 0x08, 0x8E);
	idt_set_gate(20, (u32)isr20, 0x08, 0x8E);
	idt_set_gate(21, (u32)isr21, 0x08, 0x8E);
	idt_set_gate(22, (u32)isr22, 0x08, 0x8E);
	idt_set_gate(23, (u32)isr23, 0x08, 0x8E);
	idt_set_gate(24, (u32)isr24, 0x08, 0x8E);
	idt_set_gate(25, (u32)isr25, 0x08, 0x8E);
	idt_set_gate(26, (u32)isr26, 0x08, 0x8E);
	idt_set_gate(27, (u32)isr27, 0x08, 0x8E);
	idt_set_gate(28, (u32)isr28, 0x08, 0x8E);
	idt_set_gate(29, (u32)isr29, 0x08, 0x8E);
	idt_set_gate(30, (u32)isr30, 0x08, 0x8E);
	idt_set_gate(31, (u32)isr31, 0x08, 0x8E);
	idt_set_gate(32, (u32)isr32, 0x08, 0x8E);
	idt_set_gate(33, (u32)isr33, 0x08, 0x8E);
	idt_set_gate(34, (u32)isr34, 0x08, 0x8E);
	idt_set_gate(35, (u32)isr35, 0x08, 0x8E);
	idt_set_gate(36, (u32)isr36, 0x08, 0x8E);
	idt_set_gate(37, (u32)isr37, 0x08, 0x8E);
	idt_set_gate(38, (u32)isr38, 0x08, 0x8E);
	idt_set_gate(39, (u32)isr39, 0x08, 0x8E);
	idt_set_gate(39, (u32)isr39, 0x08, 0x8E);
	idt_set_gate(40, (u32)isr40, 0x08, 0x8E);
	idt_set_gate(41, (u32)isr41, 0x08, 0x8E);
	idt_set_gate(42, (u32)isr42, 0x08, 0x8E);
	idt_set_gate(43, (u32)isr43, 0x08, 0x8E);
	idt_set_gate(44, (u32)isr44, 0x08, 0x8E);
	idt_set_gate(45, (u32)isr45, 0x08, 0x8E);
	idt_set_gate(46, (u32)isr46, 0x08, 0x8E);
	idt_set_gate(47, (u32)isr47, 0x08, 0x8E);

	flush_idt((u32)&idt_desc);
}

/**
 * Assign the irq handler to the irq specified by irq_num
 * The irq handler is given as a function pointer that is casted to u32
 * which is better for doing the following assignments and calculations
 */
void idt_set_gate(u8 irq_num, u32 isr_fn_ptr, u16 selector, u8 flags)
{
	idt_entries[irq_num].base_lo = isr_fn_ptr & 0xFFFF;          // lowest 16 bits
	idt_entries[irq_num].base_hi = (isr_fn_ptr >> 16) & 0xFFFF;  // highest 16 bits

	idt_entries[irq_num].selector = selector;
	idt_entries[irq_num].always0 = 0;
	idt_entries[irq_num].flags   = flags;
}

/**
 * Load idt descriptor into idtr register with lidt
 * idt_desc_ptr should be cast to u32
 */
void flush_idt(u32 idt_desc_ptr)
{
	__asm__("lidtl (%0)" : : "r" (idt_desc_ptr));
}
