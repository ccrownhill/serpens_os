#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <types.h>

void send_command(u8 command);
void init_keyboard();
u8 get_scancode();

#endif