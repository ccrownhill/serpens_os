; macro for ISRs without an error code
; because some interrupts push an error code
; here 0 is pushed as a dummy error code
%macro ISR_NO_ERRCODE 1  ; define a macro, taking one parameter
	[global isr%1]        ; %1 accesses the first parameter.
	isr%1:
		cli
		push byte 0 ; push dummy error code
		push byte %1
		jmp isr_exception_common
%endmacro

; macro for ISRs with error code
%macro ISR_ERRCODE 1
	[global isr%1]
	isr%1:
		cli
		push byte %1
		jmp isr_exception_common
%endmacro

; macro for ISRs for interrupts and not exceptions
%macro ISR_INTERRUPT 1
  [global isr%1]
  isr%1:
    cli
    push byte 0 ; dummy error code
    push byte %1
    jmp isr_interrupt_common
%endmacro

; using the macros to get the global functions isr0() to isr47()
; 32 Intel protected mode exceptions:
ISR_NO_ERRCODE 0
ISR_NO_ERRCODE 1
ISR_NO_ERRCODE 2
ISR_NO_ERRCODE 3
ISR_NO_ERRCODE 4
ISR_NO_ERRCODE 5
ISR_NO_ERRCODE 6
ISR_NO_ERRCODE 7
ISR_ERRCODE 8
ISR_NO_ERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NO_ERRCODE 15
ISR_NO_ERRCODE 16
ISR_NO_ERRCODE 17
ISR_NO_ERRCODE 18
ISR_NO_ERRCODE 19
ISR_NO_ERRCODE 20
ISR_NO_ERRCODE 21
ISR_NO_ERRCODE 22
ISR_NO_ERRCODE 23
ISR_NO_ERRCODE 24
ISR_NO_ERRCODE 25
ISR_NO_ERRCODE 26
ISR_NO_ERRCODE 27
ISR_NO_ERRCODE 28
ISR_NO_ERRCODE 29
ISR_NO_ERRCODE 30
ISR_NO_ERRCODE 31

; 16 PIC interrupts:
ISR_INTERRUPT 32
ISR_INTERRUPT 33
ISR_INTERRUPT 34
ISR_INTERRUPT 35
ISR_INTERRUPT 36
ISR_INTERRUPT 37
ISR_INTERRUPT 38
ISR_INTERRUPT 39
ISR_INTERRUPT 40
ISR_INTERRUPT 41
ISR_INTERRUPT 42
ISR_INTERRUPT 43
ISR_INTERRUPT 44
ISR_INTERRUPT 45
ISR_INTERRUPT 46
ISR_INTERRUPT 47

; in isr.c
[extern isr_exception_handler]
; isr_exception_common: save processor state and calls C-level handler
; before restoring the stack frame
; for all exceptions 0-31
isr_exception_common:
	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds
	push eax

	; setup segment registers
	mov ax, 0x10 ; 0x10 is the data segment
	mov ds, ax
	mov es, ax,
	mov fs, ax
	mov gs, ax

	; call C-level handler function
	call isr_exception_handler

	pop eax ; reload original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax

	; reset stack to what it was
	; before isr[n]() function pushed err code and isr number
	add esp, 8
	sti ; reenable interrupts

	; pop CS, EIP, EFLAGS, SS, and ESP
	; this was automatically pushed by the processor back when the interrupt
	; first happened
	iret

; in irq.c
[extern irq_handler]
; isr_interrupt_common: save processor state and calls C-level handler
; before restoring the stack frame
; for all interrupts 32-47
isr_interrupt_common:
	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds
	push eax

	; setup segment registers
	mov ax, 0x10 ; 0x10 is the data segment
	mov ds, ax
	mov es, ax,
	mov fs, ax
	mov gs, ax

	; call C-level handler function
	call irq_handler

	pop eax ; reload original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax

	; reset stack to what it was
	; before isr[n]() function pushed err code and isr number
	add esp, 8
	sti ; reenable interrupts

	; pop CS, EIP, EFLAGS, SS, and ESP
	; this was automatically pushed by the processor back when the interrupt
	; first happened
	iret
