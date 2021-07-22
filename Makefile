# Note that I use a cross compiler for "i686-elf"
# which is why the compilation will only work if such a cross compiler is present

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
	i686-elf-ld -o $@ -Tlink.ld $^ --oformat binary

boot.img: src/stage0.bin kernel.bin
	#dd if=/dev/zero of=boot.img bs=512 count=70
	#dd if=bootsect.bin of=boot.img conv=notrunc bs=512 seek=0 count=1
	#dd if=main.bin of=boot.img conv=notrunc bs=512 seek=1 count=69
	cat $^ > $@

boot: boot.img
	qemu-system-i386 -drive format=raw,file=$< -d cpu_reset

clean:
	rm -f *.o *.bin *.img *.iso
	rm -f src/*.o src/*.bin

.PHONY: all boot clean
