[bits 32]
[extern main]

section .bss
align 16
stack_bottom:
resb 0x4000
stack_top:

global _start
_start:
	mov esp, stack_top
	call main
