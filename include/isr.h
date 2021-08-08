#ifndef ISR_H
#define ISR_H

/**
 * Structure containing everything that will be pushed onto the stack
 * before calling the isr_handler function
 * That's why this will be used as its argument so all this pushed
 * data can be accessed by isr_handler
 */
struct registers {
  uint32_t gs, fs, es, ds;               // data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusehd by pusha
  uint32_t int_no, err_code; // Interrupt number and error code from isr[n] fn
  uint32_t eip, cs, eflags, useresp, ss; // pushed by processor automatically
};

void isr_exception_handler(struct registers*);

#endif
