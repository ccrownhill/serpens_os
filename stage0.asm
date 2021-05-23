[org 0x7c00]
[bits 16]

entry:
	mov si, greetings
	call print

	; video mode: 320x200 @ 16 colors
	;mov ah, 0x0
	;mov al, 0x13
	;int 0x10

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

	; load gdt
	lgdt [gdt_desc]

	; enable protected mode
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; transition to 32 bit code in code segment
	jmp 0x8:pm_entry


[bits 32]

pm_entry:
	; setup all data selectors
	mov ax, (gdt_data_segment - gdt_start)
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	; set stack offset with esp
	mov esp, 0x90000

	; print P character
	mov eax, 0xb8000
	mov byte [eax], 'P'
	mov byte [eax + 1], 0x1b ; cyan with blue background

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

greetings: db "Tic-Tac-Toe Time!!!", 0xd, 0xa, 0x0 ; 0xd is \r and 0xa is \n
greetings_len: equ $-greetings

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
	dw 0b10010010
	dw 0b11001111
	db 0
gdt_end:

; gdt descriptor
gdt_desc:
	dw gdt_end - gdt_start - 1 ; GDT size - 1
	dd gdt_start ; gdt base


; MBR boot signature
times 510-($-$$) db 0
dw 0xaa55
