CC = gcc
CFLAGS = -elf_i386 -m32 -Wall -Wextra -ffreestanding -fno-pie -nostdlib -nostdinc -fno-builtin -fno-stack-protector

all: boot.img

bootsect.bin: stage0.asm
	nasm -f bin -o bootsect.bin stage0.asm

start.o: start.asm
	nasm -f elf -o start.o start.asm

# freestanding tells gcc that no standard library may exist
# and that startup may not be at "main"
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# "-Ttext 0x10000" because that's where the kernel will be loaded in memory
kernel.bin: start.o main.o
	ld -m elf_i386 -o kernel.bin -Tlink.ld start.o main.o --oformat binary

boot.img: bootsect.bin kernel.bin
	#dd if=/dev/zero of=boot.img bs=512 count=70
	#dd if=bootsect.bin of=boot.img conv=notrunc bs=512 seek=0 count=1
	#dd if=main.bin of=boot.img conv=notrunc bs=512 seek=1 count=69
	cat bootsect.bin kernel.bin > boot.img

boot: boot.img
	qemu-system-i386 -drive format=raw,file=boot.img -d cpu_reset

clean:
	rm -f *.o *.bin *.img *.iso

.PHONY: all boot clean
