[org 0x7c00]
[bits 16]

jmp short entry

greetings: db "Tic-Tac-Toe Time!!!", 0xd, 0xa ; 0xd is \r and 0xa is \n
greetings_end: ; just a label for the address of the string end
greetings_len: equ $-greetings

entry:
	mov si, greetings
	mov di, greetings_end
	call print

key_input:
	; just type in characters and put them on the screen
	mov ah, 0x0
	int 0x16
	mov ah, 0xe
	int 0x10
	jmp key_input ; hang with infinite loop

print:
	; print the string with first character address stored in si
	; and end address stored in di
	mov ah, 0xe
	print_next_char:
		mov al, [si]
		int 0x10
		inc si
	cmp si, di;greetings_end
	jne print_next_char
	ret

; MBR boot signature
times 510-($-$$) db 0
dw 0xaa55
