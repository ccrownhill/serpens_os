[org 0x7c00]
[bits 16]

jmp short entry

greetings db "Tic-Tac-Toe Time!!!", 0xa
greetings_end ; just a label for the address of the string end
greetings_len equ $-greetings

entry:

print:
	mov si, greetings
	mov ah, 0xe

	print_next_char:
	mov al, [si]
	int 0x10
	inc si
	cmp si, greetings_end
	jne print_next_char

hang:
	; hang with infinite loop
	jmp $

; MBR boot signature
times 510-($-$$) db 0
dw 0xaa55
