[bits 32]
[extern main] ; in main.c

section .bss
align 32
stack_bottom:
resb 0x4000 ; 16 KiB
stack_top:

section .text
global _start
_start:
	cli ; disable interrupts
	cld ; clear direction flag

	; init segment registers
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov esp, stack_top ; init stack

	call main ; call main function in kernel

; hang if main returns (this will not happen)
_hang:
	hlt
	jmp _hang
