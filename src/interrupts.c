#include <interrupts.h>

// irq handlers for all 256 interrupts
struct idt_entry idt_entries[256];
struct idt_descriptor idt_desc;

void init_idt()
{
	int i;
	idt_desc.limit = sizeof(struct idt_entry) * 256 -1;
	idt_desc.base  = (u32)&idt_entries;

	memset(&idt_entries, 0, sizeof(struct idt_entry)*256);

	idt_set_gate( 0, (u32int)isr0 , 0x08, 0x8E);
	idt_set_gate( 1, (u32int)isr1 , 0x08, 0x8E);
	idt_set_gate( 2, (u32int)isr2 , 0x08, 0x8E);
	idt_set_gate( 3, (u32int)isr3 , 0x08, 0x8E);
	idt_set_gate( 4, (u32int)isr4 , 0x08, 0x8E);
	idt_set_gate( 5, (u32int)isr5 , 0x08, 0x8E);
	idt_set_gate( 6, (u32int)isr6 , 0x08, 0x8E);
	idt_set_gate( 7, (u32int)isr7 , 0x08, 0x8E);
	idt_set_gate( 8, (u32int)isr8 , 0x08, 0x8E);
	idt_set_gate( 9, (u32int)isr9 , 0x08, 0x8E);
	idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
	idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
	idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
	idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
	idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
	idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
	idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
	idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
	idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
	idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
	idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
	idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
	idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
	idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
	idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
	idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
	idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
	idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
	idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
	idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
	idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
	idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);
	idt_set_gate(32, (u32int)isr32, 0x08, 0x8E);
	idt_set_gate(33, (u32int)isr33, 0x08, 0x8E);
	idt_set_gate(34, (u32int)isr34, 0x08, 0x8E);
	idt_set_gate(35, (u32int)isr35, 0x08, 0x8E);
	idt_set_gate(36, (u32int)isr36, 0x08, 0x8E);
	idt_set_gate(37, (u32int)isr37, 0x08, 0x8E);
	idt_set_gate(38, (u32int)isr38, 0x08, 0x8E);
	idt_set_gate(39, (u32int)isr39, 0x08, 0x8E);
	idt_set_gate(39, (u32int)isr39, 0x08, 0x8E);
	idt_set_gate(40, (u32int)isr40, 0x08, 0x8E);
	idt_set_gate(41, (u32int)isr41, 0x08, 0x8E);
	idt_set_gate(42, (u32int)isr42, 0x08, 0x8E);
	idt_set_gate(43, (u32int)isr43, 0x08, 0x8E);
	idt_set_gate(44, (u32int)isr44, 0x08, 0x8E);
	idt_set_gate(45, (u32int)isr45, 0x08, 0x8E);
	idt_set_gate(46, (u32int)isr46, 0x08, 0x8E);
	idt_set_gate(47, (u32int)isr47, 0x08, 0x8E);

	idt_flush((u32)&idt_desc);
}

/**
 * Assign the irq handler to the irq specified by irq_num
 */
void idt_set_gate(u8 irq_num, u32 irq_handler_fn_ptr, u16 segment_selector, u8 flags)
{
}

/**
 * Load idt descriptor into idtr register with lidt
 */
void flush_idt(struct idt_descriptor *idt_desc)
{
	__asm__("lidt (%%eax)" : : "a" (idt_desc));
}
