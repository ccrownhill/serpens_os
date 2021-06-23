[org 0x7c00]
[bits 16]

; TODO: MAKE PRINT_HEX PRINT IN CORRECT ORDER BY ALLOCATING MEMORY ON THE STACK
				AND WRITING THE CHARACTERS THERE
				THEN A POINTER TO THIS MEMORY WILL BE PUT INTO SI SO THAT THE STRING
				CAN BE PRINTED WITH THE PRINT FUNCTION
; TODO: LOAD NEXT DISK SECTORS WITH KERNEL
; TODO: CONTINUE CODE EXECUTION AT THE KERNEL

entry:
	; init stack by setting stack pointer to some empty memory region
	; See where it is empty: https://wiki.osdev.org/Memory_Map_(x86)
	mov sp, 0x3000

	mov bp, sp ; init base pointer

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

	mov esp, 0x3000

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
		push bp
		mov bp, sp
		sub sp, byte 0x10 ; allocate 16 bytes on stack
		xor cx, cx ; set counter to 0
		
		mov ah, 0xe
		mov al, '0'
		int 0x10
		mov al, 'x'
		int 0x10
		xor bx, bx
	draw_nibble:
		mov bx, dx
		cmp bx, 0
		je done
		and bx, 0xf
		cmp bx, 0x9
		jg greater_than_9
	less_than_9:
		add bx, 48 ; because '0' is 48 in code page 437 encoding
		jmp print_num
	greater_than_9:
		add bx, 55 ; 55 because that way 0xa will become 'A' in Code page 437
	print_num:
		mov byte [bp - 0x1], bl ; TODO:	CORRECT THIS
		mov al, bl
		int 0x10
		shr dx, 4
		inc cx
		jmp draw_nibble
	done:
		mov sp, bp
		pop bp
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
