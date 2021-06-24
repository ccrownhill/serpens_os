[org 0x7c00]
[bits 16]

; TODO: FIX PROBLEM THAT THIS BINARY IS GREATER THAN 512 BYTES
; TODO: LOAD NEXT DISK SECTORS WITH KERNEL
; TODO: CONTINUE CODE EXECUTION AT THE KERNEL

entry:

	; init stack by setting stack pointer to some empty memory region
	; See where it is empty: https://wiki.osdev.org/Memory_Map_(x86)
	mov sp, 0x3000
	; next you could also init all segment registers
	; this is not necessary since they have the desired 0x0 value already
	mov bp, sp ; init base pointer

	; text mode 80x25 EGA, VGA
	mov ah, 0x0
	mov al, 0x3
	int 0x10

	; video mode: 320x200 @ 16 colors
	;mov ah, 0x0
	;mov al, 0xd
	;int 0x10

read_disk:
	; CHS read (not used here):
	; load next 0x0 sectors with the kernel into memory at 0x1000
	; using CHS (cylinder head sector) read
	;mov ah, 0x2 ; read disk sectors into memory
	;mov al, 0x1 ; read 1 sector
	;mov ch, 0x0 ; cylinder 0x0
	;mov dh, 0x0 ; head 0x0
	;mov cl, 0x2 ; sector 2 (the one after the bootsector)
	;mov dl, 0x0 ; boot drive

  ;; load the next sectors at memory address es:bx 0x1000:0x0000 --> kernel at 0x10000
	;mov bx, 0x1000 ; es can't be set directly
	;mov es, bx

	;mov bx, 0x0
	;int 0x13

	; Extended read
	mov ah, 0x42
	mov dl, 0x0 ; drive number
	mov si, disk_address_packet
	int 0x13

	jc disk_error ; carry flag is set on error

switch_to_pm:
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

	; continue execution in kernel
	jmp 0x10000 ; this address was set with es:bx when loading the kernel from disk
	jmp $

	; print P character with VGA text mode buffer on 3rd line
	;mov byte [0xb8140], 'H'
	;mov byte [0xb8141], 0xf ; white on black
	;mov byte [0xb8142], 'i'
	;mov byte [0xb8143], 0xf

[bits 16]
print:
	; print the string with first character address stored in si
	; and end address stored in di
	mov ah, 0xe
	print_next_char:
		mov byte al, [si]
		int 0x10
		inc si
		
		; check if '\0' character at the end is reached
		cmp byte [si], 0x0
		jnz print_next_char
	ret

print_hex:
		; print hexadecimal value stored in dx
		; this might be needed for debugging

		; setup new stackframe
		push bp
		mov bp, sp
		
		push byte 0x0
		
		xor bx, bx
	draw_nibble:
		mov bx, dx
		and bx, 0xf ; only consider last 4 bits
		mov bx, [hexdigits + bx] ; get the character corresponding to the number
		
		; push current digit character on stack
		dec sp
		mov byte [esp], bl

		shr dx, 4 ; >> 4
		cmp dx, 0
		jne draw_nibble

		; print the digit with "0x" prepended
		push word "0x"
		mov si, sp
		call print

		; clean up
		mov sp, bp
		pop bp
		ret
	
disk_error:
	mov si, DISK_ERR_MSG
	call print
	jmp $

greetings: db "Tic-Tac-Toe Time!!!", 0xd, 0xa, 0x0 ; 0xd is \r and 0xa is \n
hexdigits: db "0123456789ABCDEF" ; used for printing hex values
DISK_ERR_MSG: db "Error reading from disk", 0xd, 0xa, 0x0

; used for Extended Read from disk
disk_address_packet:
	db 0x10 ; size of DAP
	db 0x0 ; unused
num_sectors:
	dw 0x40
offset:
	dw 0x0
segment:
	dw 0x1000


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
