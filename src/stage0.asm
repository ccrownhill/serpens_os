[org 0x7c00]
[bits 16]

entry:
  ; disable interrupts
  cli
  ; clear direction flag
  cld

  xor ax, ax
  mov es, ax
  mov ds, ax

  ; init stack by setting stack pointer to some empty memory region
  ; See where it is empty: https://wiki.osdev.org/Memory_Map_(x86)
  mov sp, 0x3000
  mov bp, sp ; init base pointer

  ; text mode 80x25 EGA, VGA
  mov ah, 0x0
  mov al, 0x3
  int 0x10

chs_disk_info:
  ; get info about disk parameters like maximum number of tracks, heads, cylinders
  ; this will be necessary only for CHS read because with this data I can
  ; determine if the next sector is on the next head or cylinder and
  ; switch to the next head/cylinder
  mov ah, 0x8
  mov dl, drive_num
  int 0x13
  mov byte [sectors_per_track], cl
  and byte [sectors_per_track], 0x3f ; only look at bits 5-0
  mov byte [max_head_num], dh
  mov byte [max_cylinder_num], cl
  and word [max_cylinder_num], 0xc0 ; only look at bits 7-6
  shl word [max_cylinder_num], 2 ; these 2 bits are the bits 9-8 of the cylinder num
  or byte [max_cylinder_num], ch

read_disk:
  mov di, max_disk_read_tries ; for every sector use these max tries to read it

lba_read_sector:
  ; Extended read with LBA addressing
  mov ah, 0x42
  mov dl, drive_num ; drive number
  mov si, disk_address_packet
  int 0x13
  jnc lba_next_sector ; if the read succeeded
  jmp try_disk_read_again

lba_next_sector:
  inc byte [sectors_read]
  cmp byte [sectors_read], total_sectors_num
  je switch_to_pm ; check if all desired sectors were read

  add word [offset], sector_size 
  inc dword [sector]

  jmp read_disk ; now read that next sector

;chs_read_sector:
;  mov ah, 0x2 ; read disk sectors into memory
;  mov al, byte [num_sectors]
;  mov ch, byte [chs_cylinder]
;  mov dh, byte [chs_head]
;  mov cl, byte [chs_sector]
;  mov dl, drive_num
;
;  ; load the next sectors at memory address es:bx 0x1000:0x0000 --> kernel at 0x10000
;  mov bx, [mem_segment] ; es can't be set directly
;  mov es, bx
;  mov bx, [offset]
;  int 0x13
;
;  jnc chs_next_sector ; carry flag is set on error
;  jmp try_disk_read_again 
;
;chs_next_sector:
;  inc byte [sectors_read]
;  cmp byte [sectors_read], total_sectors_num
;  je switch_to_pm ; check if all desired sectors were read
;
;  add word [offset], sector_size
;  inc byte [chs_sector]
;  mov byte bl, [sectors_per_track] ; can't compare the two variables directly
;  cmp byte [chs_sector], bl ; compare chs_sector with sectors_per_track
;  jg chs_next_head
;  jmp read_disk
;
;chs_next_head:
;  mov byte [chs_sector], 0x0
;  inc byte [chs_head]
;  mov byte bl, [max_head_num]
;  cmp byte [chs_head], bl
;  jg chs_next_cylinder
;  jmp read_disk
;
;chs_next_cylinder:
;  mov byte [chs_head], 0x0
;  inc byte [chs_cylinder]
;  jmp read_disk

try_disk_read_again:
  mov ah, 0x0 ; reset the disk
  int 0x13
  dec di
  ;jnz chs_read_sector ; UNCOMMENT THIS FOR CHS READ
  jnz lba_read_sector
  jmp disk_error

switch_to_pm:
  ; Set the A20 line
  in al, 0x92
  or al, 2
  out 0x92, al

  ; clear DS register
  xor ax, ax
  mov ds, ax

  ; load GDT
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
  mov ax, (gdt_data_segment - gdt_start) ; 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  mov esp, 0x3000

  ; continue execution in kernel with jump
  jmp 0x10000 ; this address was set to 0x1000:0x0 when loading the kernel from disk

[bits 16]
print:
  ; print the string with first character address stored in si
  ; until a '\0' character
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
    ; this is needed for debugging

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

; parameters for reading from disk
drive_num equ 0x80 ; boot drive: 0x80 for first Hard disk (0x0 for first floppy not working)
max_disk_read_tries equ 5

; for CHS
chs_sector: db 0x2 ; sector 2 (the one after the bootsector)
chs_head: db 0x0
chs_cylinder: db 0x0

; these values are set above when using the disk info interrupt
; (int 0x13 with ah=0x8)
sectors_per_track: db 0x0
max_head_num: db 0x0
max_cylinder_num: dw 0x0

total_sectors_num equ 0x20
sector_size equ 512 ; in bytes
sectors_read: db 0

align 8
; used for Extended Read from disk
disk_address_packet:
  db 0x10 ; size of DAP
  db 0x0 ; unused
num_sectors:
  dw 0x1 ; read one sector after the other
offset:
  dw 0x0
mem_segment:
  dw 0x1000
sector:
  dd 0x1 ; start reading from second sector
  dd 0x0 ; upper bits

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

; MBR boot signature
times 510-($-$$) db 0
dw 0xaa55
