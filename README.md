# TicTacToe in an OS

Current state: 

1. Got Hello World bootloader to work.
1. Enabled user to type anything and see output on text (pressing enter will be like using a carriage return)
1. Got into 32 bit protected mode and printed Hi on third line with VGA text mode buffer at 0xb8000 to confirm that the switch was successful
1. Got VGA screen driver to work for displaying basic text.
1. Got keyboard polling driver to work.
1. Setup idt and successfully tested it with a test interrupt.

TODO: Check if direction flag should be finally set or not (cld and std)
