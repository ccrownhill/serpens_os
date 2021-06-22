[org 0x7c00]
[bits 16]

; TODO: FINISH PRINT_HEX FN
; TODO: LOAD NEXT DISK SECTORS WITH KERNEL
; TODO: CONTINUE CODE EXECUTION AT THE KERNEL

entry:
	mov si, greetings
	call print

	; text mode 80x25 EGA, VGA
	mov ah, 0x0
	mov al, 0x3
	int 0x10

	; video mode: 320x200 @ 16 colors
	;mov ah, 0x0
	;mov al, 0xd
	;int 0x10

	mov dx, 0x1fb6
	call print_hex

	; disable interrupts
	cli
	; clear direction flag
	;cld

	; Set the A20 line
	in al, 0x92
	or al, 2
	out 0x92, al

	; clear DS register
	xor ax, ax
	mov ds, ax

	; load GDT
	lgdt [gdt_desc]
	
	; load IDT
	lidt [idt_desc]

	; enable protected mode
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; transition to 32 bit code in code segment
	jmp 0x8:pm_entry


[bits 32]

pm_entry:
	; setup all data selectors
	mov ax, (gdt_data_segment - gdt_start) ; 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; init stack by setting stack pointer to some empty memory region
	; kernel will be loaded here
	mov esp, 0x10000 ; 0x10000 because there is a lot of free memory

	; print P character with VGA text mode buffer on 3rd line
	mov byte [0xb8140], 'H'
	mov byte [0xb8141], 0xf ; white on black
	mov byte [0xb8142], 'i'
	mov byte [0xb8143], 0xf

_hang:
	jmp _hang

[bits 16]
print:
	; print the string with first character address stored in si
	; and end address stored in di
	mov ah, 0xe
	print_next_char:
		mov al, [si]
		int 0x10
		inc si
		cmp byte [si], 0x0
		jnz print_next_char
	ret

print_hex:
	; print hexadecimal value stored in dx
	; NOT DONE
	mov dx, bx
	and bx, 0x9
	add bx, 48
	mov si, bx
	call print
	ret

greetings: db "Tic-Tac-Toe Time!!!", 0xd, 0xa, 0x0 ; 0xd is \r and 0xa is \n

; GDT
align 8
gdt_start:
gdt_null_segment:
	dq 0
gdt_code_segment:
	dw 0xffff
	dw 0
	db 0
	db 0b10011010
	db 0b11001111
	db 0
gdt_data_segment:
	dw 0xffff
	dw 0
	db 0
	db 0b10010010
	db 0b11001111
	db 0
gdt_end:

; gdt descriptor
gdt_desc:
	dw gdt_end - gdt_start - 1 ; GDT size - 1
	dd gdt_start ; gdt base

; empty IDT
idt_desc:
	dw 0
	dd 0

; MBR boot signature
times 510-($-$$) db 0
dw 0xaa55
