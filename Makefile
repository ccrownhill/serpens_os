CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -Wall -Wextra -ffreestanding
INCS = -Iinclude

SRC = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)
OBJ = $(SRC:.c=.o)

all: boot.img

%.bin: %.asm
	nasm -f bin -o $@ $<

%.o: %.asm
	nasm -f elf32 -o $@ $<

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

kernel.bin: src/start.o src/isrs.o $(OBJ)
	$(LD) -o $@ -Tlink.ld $^ --oformat binary

boot.img: src/stage0.bin kernel.bin
	dd if=/dev/zero of=boot.img bs=512 count=2880
	dd if=src/stage0.bin of=boot.img conv=notrunc bs=512 seek=0 count=1
	dd if=kernel.bin of=boot.img conv=notrunc bs=512 seek=1 count=2048

boot.iso: boot.img
	mkdir tmpisodir
	cp $< tmpisodir
	mkisofs -o $@ -eltorito-boot $< tmpisodir
	rm -rf tmpisodir

# this boots from a hard drive
boot: boot.img
	qemu-system-i386 -drive format=raw,file=$< -d cpu_reset

boot-floppy: boot.img
	qemu-system-i386 -fda $<

boot-cdrom: boot.iso
	qemu-system-i386 -cdrom $<

qemu-debug: boot.img
	qemu-system-i386 -s -S -drive format=raw,file=$< -d cpu_reset

clean:
	rm -f *.o *.bin *.img *.iso
	rm -f src/*.o src/*.bin

.PHONY: all boot boot-floppy boot-cdrom clean
