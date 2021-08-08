#ifndef IDT_H
#define IDT_H

// structure of interrupt gate
typedef struct idt_entry {
  uint16_t isr_low;
  uint16_t kernel_cs;
  uint8_t reserved; // always 0
  uint8_t type_attr;
  uint16_t isr_high;
} __attribute__((packed)) idt_entry_t; // prevent compiler optimization

// structure of IDT descriptor pointing to an array of interrupt handlers
typedef struct idt_descriptor {
  uint16_t limit; // the size of the array with all 256 interrupt handlers
  uint32_t base;
} __attribute__((packed)) idt_desc_t; // prevent compiler optimization

// Code segment
#define KERNEL_CS 0x8

// 0x8e: type_attr value consists of
//     P = 0b1 (interrupt is used)
//     DPL = 0b00 (descriptor privilege level; 0 for highest level)
//     S = 0b0 (storage segment; 0 because interrupt gate is used)
//     Type = 0b1110 (for a 32 bit interrupt gate)
// ==> type_attr = 1000 1110 = 0x8e
#define PRIVILEGED_INTERRUPT_GATE_TYPE_ATTR 0x8e

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
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void flush_idt(uint32_t);

#endif
