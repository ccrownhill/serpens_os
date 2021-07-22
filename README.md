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
