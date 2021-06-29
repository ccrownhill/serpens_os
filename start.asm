[bits 32]
[extern main]

section .data
align 16
stack_bottom:
resb 0x4000 ; 16 KiB
stack_top:

global _start
_start:
	cli ; disable interrupts
	cld ; clear direction flag

	mov esp, stack_top ; init stack

	call main ; call main function in kernel

; hang if main returns (this will not happen)
_hang:
	hlt
	jmp _hang
