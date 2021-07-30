#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <types.h>
#include <isr.h> // for `struct registers`

// copied from jdah/tetris-os -> keyboard.h
// maybe not perfectly correct
#define KEY_NULL 0
#define KEY_ESC 27
#define KEY_BACKSPACE '\b'
#define KEY_TAB '\t'
#define KEY_ENTER '\n'
#define KEY_RETURN '\r'

#define KEY_INSERT 0x90
#define KEY_DELETE 0x91
#define KEY_HOME 0x92
#define KEY_END 0x93
#define KEY_PAGE_UP 0x94
#define KEY_PAGE_DOWN 0x95
#define KEY_LEFT 0x4B
#define KEY_UP 0x48
#define KEY_RIGHT 0x4D
#define KEY_DOWN 0x50

#define KEY_F1 0x80
#define KEY_F2 (KEY_F1 + 1)
#define KEY_F3 (KEY_F1 + 2)
#define KEY_F4 (KEY_F1 + 3)
#define KEY_F5 (KEY_F1 + 4)
#define KEY_F6 (KEY_F1 + 5)
#define KEY_F7 (KEY_F1 + 6)
#define KEY_F8 (KEY_F1 + 7)
#define KEY_F9 (KEY_F1 + 8)
#define KEY_F10 (KEY_F1 + 9)
#define KEY_F11 (KEY_F1 + 10)
#define KEY_F12 (KEY_F1 + 11)

#define KEY_LCTRL 0x1D
#define KEY_RCTRL 0x1D

#define KEY_LALT 0x38
#define KEY_RALT 0x38

#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36

#define KEY_CAPS_LOCK 0x3A
#define KEY_SCROLL_LOCK 0x46
#define KEY_NUM_LOCK 0x45

#define KEY_MOD_ALT 0x0200
#define KEY_MOD_CTRL 0x0400
#define KEY_MOD_SHIFT 0x0800
#define KEY_MOD_CAPS_LOCK 0x1000
#define KEY_MOD_NUM_LOCK 0x2000
#define KEY_MOD_SCROLL_LOCK 0x4000

/**
 * scancodes will be "anded" with these values (scancode & _AND_VAL)
 * if the resulting number of this and operation is non zero
 * the condition expressed by the Macro name is correct
 */
#define ANY_CHECK_AND_VAL 0xff
#define IS_KEY_UP(scancode) (scancode & 0x80)
#define IS_KEY_DOWN(scancode) (!IS_KEY_UP(scancode))

/**
 * clear the keyboard output buffer as long as it is not empty
 * (i.e. the first bit of the 0x64 status register is set)
 */
#define CLEAR_KEYBOARD_OUT_BUF() ({\
    while(port_byte_in(0x64) & 0x1) {\
      port_byte_in(0x60);\
    }\
  })
 
typedef struct keyboard_input {
  u8 is_key_down; // true or false value whether any key is pressed

  // the keycode of the pressed key
  // (the ASCII code for all alphabetical keys and the defined scancode values
  // from above for all other keys)
  u8 key_code;
} keyboard_input_t;

// defined in keyboard.c
extern keyboard_input_t keyboard_input;

void init_keyboard();
void keyboard_irq_handler();
void send_command(u8 command);
u8 get_scancode();
u8 get_key(u8 type_specifying_and_val);
u8 get_scancode_set();

#endif
