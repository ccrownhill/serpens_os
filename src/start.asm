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

  ; ebx contains the address to the count of memory map entries and the entries themselves
  ; these were obtained in the bootloader stage0.asm using int 0x15 (eax=0xe820)
  mov eax, ebx
  add eax, 4 ; memory map is stored 4 bytes after the entry count integer
  push eax ; address of first memory map entry (second pointer argument for main)
  push dword [ebx] ; value of entry count (first integer argument for main)

  call main ; call main function in kernel

; hang if main returns (this will not happen)
_hang:
  hlt
  jmp _hang
