#ifndef ISR_H
#define ISR_H

#include <types.h>

/**
 * Structure containing everything that will be pushed onto the stack
 * before calling the isr_handler function
 * That's why this will be used as its argument so all this pushed
 * data can be accessed by isr_handler
 */
struct registers {
	u32 ds;               // data segment selector
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusehd by pusha
	u32 int_no, err_code; // Interrupt number and error code from isr[n] fn
	u32 eip, cs, eflags, useresp, ss; // pushed by processor automatically
};

void isr_exception_handler(struct registers);

#endif
