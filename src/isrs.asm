; macro for ISRs without an error code
; because some interrupts push an error code
; here 0 is pushed as a dummy error code
%macro ISR_NO_ERRCODE 1  ; define a macro, taking one parameter
	[global isr%1]        ; %1 accesses the first parameter.
	isr%1:
		cli
		push byte 0 ; push dummy error code
		push byte %1
		jmp isr_common
%endmacro

; macro for ISRs with error code
%macro ISR_ERRCODE 1
	[global isr%1]
	isr%1:
		cli
		push byte %1
		jmp isr_common
%endmacro

; using the macros to get the global functions isr0() to isr47()
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
ISR_NO_ERRCODE 32
ISR_NO_ERRCODE 33
ISR_NO_ERRCODE 34
ISR_NO_ERRCODE 35
ISR_NO_ERRCODE 36
ISR_NO_ERRCODE 37
ISR_NO_ERRCODE 38
ISR_NO_ERRCODE 39
ISR_NO_ERRCODE 40
ISR_NO_ERRCODE 41
ISR_NO_ERRCODE 42
ISR_NO_ERRCODE 43
ISR_NO_ERRCODE 44
ISR_NO_ERRCODE 45
ISR_NO_ERRCODE 46
ISR_NO_ERRCODE 47

; in isr.c
[extern isr_handler]
; isr_common: save processor state and calls C-level handler
; before restoring the stack frame
isr_common:
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
	call isr_handler

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
