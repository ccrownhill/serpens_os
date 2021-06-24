all: boot.img

bootsect.bin: stage0.asm
	nasm -f bin -o bootsect.bin stage0.asm

main.o: main.c
	# freestanding tells gcc that no standard library may exist
	# and that startup may not be at "main"
	gcc -ffreestanding -c main.c -o main.o

main.bin: main.o
	# "-Ttext 0x1000" because that's where the kernel will be loaded in memory
	ld -o main.bin -Ttext 0x1000 main.o --oformat binary

boot.img: bootsect.bin main.bin
	dd if=/dev/zero of=boot.img bs=512 count=2880
	dd if=bootsect.bin of=boot.img conv=notrunc bs=512 seek=0 count=1
	dd if=main.bin of=boot.img conv=notrunc bs=512 seek=1 count=2048
	# maybe just use: cat bootsect.bin main.bin > boot.img

boot: boot.img
	qemu-system-i386 -drive format=raw,file=boot.img -d cpu_reset

clean:
	rm -f *.o *.bin *.img *.iso

.PHONY: all boot clean
