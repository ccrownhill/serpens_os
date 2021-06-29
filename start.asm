[bits 32]
[extern main]

section .bss
align 16
stack_bottom:
resb 0x4000
stack_top:

global _start
_start:
	cli ; disable interrupts
	cld ; clear direction flag

	;mov ax, 0x10
	;mov ds, ax
	;mov es, ax
	;mov fs, ax
	;mov gs, ax
	;mov ss, ax

	mov esp, stack_top

	call main
