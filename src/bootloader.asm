[org 0x7c00]
[bits 16]

entry:
  ; disable interrupts
  cli

  xor ax, ax
  mov es, ax
  mov ds, ax

  ; init stack by setting stack pointer to some empty memory region
  mov sp, 0x3000

  ; get drive number to load kernel later
  mov [drive_num], dl

  ; text mode 80x25 EGA, VGA
  mov ah, 0x0
  mov al, 0x3
  int 0x10

; get a memory map using int 0x15 with EAX=0xe820
; if this interrupt is not supported or any other error happens while
; getting the memory map it will just be ignored and the kernel will use
; some default memory address for where allocations can take place
mem_map_acquisition:
  xor bp, bp ; use bp as counter of memory map entries that were read
  xor ebx, ebx ; ebx 0 to start at beginning of map
  mov es, bx ; set es (the segment selector of the buffer address es:di) to 0
  mov di, mem_map_start ; make es:di point to memory at address "mem_map_start"
  mov edx, smap_magic_num ; magic number ("SMAP" in ascii)
read_next_mem_map_entry:
  mov eax, 0xe820 ; the memory map function of int 0x15
  mov ecx, mem_map_entry_size
  int 0x15

  jc mem_map_acquisition_err ; carry flag is set on error
  mov edx, smap_magic_num ; sometimes it does not persist in edx
  cmp eax, edx ; on success eax should be set to SMAP
  jne mem_map_acquisition_err
  inc bp ; increment entry counter
  cmp ebx, 0 ; this means that all entries were read
  je mem_map_acquisition_done

  add di, mem_map_entry_size ; make di point to next entry location
  jmp read_next_mem_map_entry ; read next entry

mem_map_acquisition_err:
  mov bp, 0x0 ; just make sure that the kernel can't read any entries if there was an error

mem_map_acquisition_done:
  mov [mem_map_entry_count], bp ; store entry count in memory to pass it to kernel later

; Try Extended LBA read first and fall back to CHS if this does not succeed
lba_disk_read:
  mov di, max_disk_read_tries ; for every sector use these max tries to read it

lba_read_sector:
  mov ah, 0x42 ; Extended read with LBA addressing
  mov dl, [drive_num] ; drive number
  mov si, disk_address_packet
  int 0x13
  jnc lba_next_sector ; if the read succeeded
  jmp lba_try_again

lba_next_sector:
  inc byte [sectors_read]
  cmp byte [sectors_read], total_sectors_num
  je switch_to_pm ; check if all desired sectors were read

  add word [offset], sector_size 
  inc dword [sector]

  jmp lba_disk_read ; now read that next sector

lba_try_again:
  dec di
  jnz lba_read_sector
  ;jmp disk_error


chs_disk_info:
  ; get info about disk parameters like maximum number of tracks, heads, cylinders
  ; this will be necessary only for CHS read because with this data I can
  ; determine if the next sector is on the next head or cylinder and
  ; switch to the next head/cylinder
  mov ah, 0x8
  mov dl, [drive_num]
  int 0x13
  mov byte [sectors_per_track], cl
  and byte [sectors_per_track], 0x3f ; only look at bits 5-0
  mov byte [max_head_num], dh
  mov byte [max_cylinder_num], cl
  and word [max_cylinder_num], 0xc0 ; only look at bits 7-6
  shl word [max_cylinder_num], 2 ; these 2 bits are the bits 9-8 of the cylinder num
  or byte [max_cylinder_num], ch

chs_disk_read:
  mov di, max_disk_read_tries ; for every sector use these max tries to read it

chs_read_sector:
  mov ah, 0x2 ; CHS reading mode
  mov al, byte [num_sectors]
  mov ch, byte [chs_cylinder]
  mov dh, byte [chs_head]
  mov cl, byte [chs_sector]
  mov dl, [drive_num]

  ; load the next sectors at memory address es:bx 0x1000:0x0000 --> kernel at 0x10000
  mov bx, [mem_segment] ; es can't be set directly
  mov es, bx
  mov bx, [offset]
  int 0x13

  jnc chs_next_sector ; carry flag is set on error
  jmp  chs_try_again

chs_next_sector:
  inc byte [sectors_read]
  cmp byte [sectors_read], total_sectors_num
  je switch_to_pm ; check if all desired sectors were read

  add word [offset], sector_size
  inc byte [chs_sector]
  mov byte bl, [sectors_per_track] ; can't compare the two variables directly
  cmp byte [chs_sector], bl ; compare chs_sector with sectors_per_track
  jg chs_next_head
  jmp chs_disk_read

chs_next_head:
  mov byte [chs_sector], 0x1 ; first sector always 1
  inc byte [chs_head]
  mov byte bl, [max_head_num]
  cmp byte [chs_head], bl
  jg chs_next_cylinder
  jmp chs_disk_read

chs_next_cylinder:
  mov byte [chs_head], 0x0
  inc byte [chs_cylinder]
  jmp chs_disk_read

chs_try_again:
  dec di
  jnz chs_read_sector
  jmp disk_error

switch_to_pm:
  ; Set the A20 line
  in al, 0x92
  or al, 2
  out 0x92, al

  ; load GDT descriptor table
  lgdt [gdt_desc]
  
  ; enable protected mode
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  ; transition to 32 bit code in code segment
  ; and flush the GDT
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

  ; note that the start of the memory map is just 4 bytes after mem_map_entry_count
  ; before calling the kernel main function in the bootstrap assembly of the kernel
  ; this should be pushed so that the kernel main function can read it as its
  ; parameter
  mov ebx, mem_map_entry_count

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
    jne print_next_char
  ret

; for debugging (uncomment it to use it and also uncomment the line with "hexdigits")
;print_hex:
;    ; print hexadecimal value stored in dx
;    ; this is needed for debugging
;
;    ; setup new stackframe
;    push bp
;    mov bp, sp
;    
;    push byte 0x0
;    
;    xor bx, bx
;  draw_nibble:
;    mov bx, dx
;    and bx, 0xf ; only consider last 4 bits
;    mov bx, [hexdigits + bx] ; get the character corresponding to the number
;    
;    ; push current digit character on stack
;    dec sp
;    mov byte [esp], bl
;
;    shr dx, 4 ; >> 4
;    cmp dx, 0
;    jne draw_nibble
;
;    ; print the digit with "0x" prepended
;    push word "0x"
;    mov si, sp
;    call print
;
;    ; clean up
;    mov sp, bp
;    pop bp
;    ret
  
disk_error:
  mov si, DISK_ERR_MSG
  call print
  jmp $

; UNCOMMENT this for using the print_hex function:
;hexdigits: db "0123456789ABCDEF" ; used for printing hex values

DISK_ERR_MSG: db "DISK ERR", 0xd, 0xa, 0x0
;MEM_INFO_ERR_MSG: db "MEMINFO ERR", 0xd, 0xa, 0x0

; store entry count at this address after the bootsector and before the kernel
smap_magic_num equ 0x0534D4150
mem_map_entry_count equ 0x8000
mem_map_start equ mem_map_entry_count + 4 ; place it after the 4 bytes for the count variable
mem_map_entry_size equ 20 ; 2 uint64_ts (base and len) and 1 uint32_t (type)

; parameters for reading from disk
drive_num: db 0x0 ; boot drive; this will be set automatically at beginning of bootloader
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
; used for Extended LBA Read from disk
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
; setup a basic flat memory model
; where code and data segment both span the whole address space (0x00000000-0xffffffff)
; that way the OS has access to a continuous, unsegmented address space
align 8
gdt_start:
gdt_null_segment:
  dq 0
; A separate code segment is needed because it must reference a descriptor
; that is set as a 'code segment' in the Access flags below
gdt_code_segment:
  dw 0xffff ; lower 16 bits of limit
  dw 0 ; lower 16 bits of the base
  db 0 ; next 8 bits of base
  db 0b10011010 ; Access flags; What ring can this segment be used in?
  db 0b11001111 ; granularity (the lower 2 bytes are the higher 16 bits of the limit)
  db 0 ; last 8 bits of base
gdt_data_segment:
  dw 0xffff
  dw 0
  db 0
  db 0b10010010 ; the data segments need the segment type access flag set to 0 (indicating a data segment)
  db 0b11001111
  db 0
gdt_end:

; gdt descriptor
gdt_desc:
  dw gdt_end - gdt_start - 1 ; GDT size - 1
  dd gdt_start ; gdt base

; MBR partition table starting at byte 446
times 446-($-$$) db 0

; partition 1 (contains the kernel code)
boot_indicator: db 0x80 ; mark as bootable
starting_head: db 0x0
starting_sector: db 0x1 ; bits 5-0 for sector and bits 7-6 are upper bits of cylinder
starting_cylinder: db 0x0
system_id: db 0x7f ; just some ID that has not been used for anything else by standard
; the last sector of the partition should be 2880
ending_head: db 45 ; here I assume the maximum number of heads as 255
ending_sector: db 45
ending_cylinder: db 0x0
first_sector_lba: dd 0x1 ; first sector after the bootsector
total_sectors_in_partition: dd 2879 ; 2880-1 because first sector is bootsector

; partitions 2-4 are unused and therefore set to 0
times 16 db 0
times 16 db 0
times 16 db 0

; MBR boot signature
dw 0xaa55
