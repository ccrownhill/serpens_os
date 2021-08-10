# Snake in an OS

This is an Operating System that boots up and starts a game of Snake. 

(One could also say that it is not really an operating system (if OS is defined as an environment to run other programs in)  but rather a Snake game that runs **without** an operating system on bare metal.)

Note that this has only been tested in QEMU and not on real hardware.

## Compilation

To be able to compile this OS and run it using the Makefile included here you need to create an `i686-elf` cross compiler.

See [this](https://wiki.osdev.org/GCC_Cross-Compiler) article from the osdev.org Wiki on how to compile `binutils` and `gcc` for `i686-elf`.

In addition to that `nasm` needs to be installed (just use the standard package from your distribution package manager).
