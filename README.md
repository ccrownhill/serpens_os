# TicTacToe in an OS

Current state: 

1. Got Hello World bootloader to work.
1. Enabled user to type anything and see output on text (pressing enter will be like using a carriage return)
1. Got into 32 bit protected mode and printed Hi on third line with VGA text mode buffer at 0xb8000 to confirm that the switch was successful
1. Got VGA screen driver to work for displaying basic text.
1. Got keyboard polling driver to work.
1. Setup idt and successfully tested it with a test interrupt.

## Compilation

To be able to compile this OS and run it using the Makefile included here you need to create an `i686-elf` cross compiler.

See [this](https://wiki.osdev.org/GCC_Cross-Compiler) article from the osdev.org Wiki on how to compile `binutils` and `gcc` for `i686-elf`.

In addition to that `nasm` needs to be installed (just use the standard package from your distribution package manager).

## Note on reading from disk

By default the bootloader `src/stage0.asm` uses LBA addressing to read from disk.

However, when running on something older than a pentium processor (**very unlikely**), this will not work. In this case you need CHS (Cylinder Head Sector) addressing.

The CHS code is also in `src/stage0.asm` but it is commented out. To use it just uncomment all code underneath labels containing `chs` like `chs_read_sector:` and comment out the parts for LBA reading (all those that have `lba` in the code labels i.e. `lba_read_sector:` and `lba_next_sector`). Last you need to uncomment the one jump statement in `try_read_disk_again:` that is for CHS: `jnz chs_read_sector`.
