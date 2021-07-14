#ifndef IDT_H
#define IDT_H

#include <types.h>

// structure of interrupt gate
struct idt_entry {
	u16 base_lo;
	u16 selector;
	u8 always0;
	u8 flags;
	u16 base_hi;
} __attribute__((packed)); // prevent compiler optimization

// structure of IDT descriptor pointing to an array of interrupt handlers
struct idt_descriptor {
	u16 limit; // the size of the array with all 256 interrupt handlers
	u32 base;
} __attribute__((packed)); // prevent compiler optimization

// ISRs from isr.asm
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();

void init_idt();
void idt_set_gate(u8 irq_num, u32 irq_handler_fn_ptr, u16 selector, u8 flags);
void flush_idt(u32 idt_desc_ptr);

#endif
