#include <keyboard.h>
#include <ports_io.h>
#include <irq.h>
#include <display.h> // for printing

/**
 * All ASCII characters for their corresponding scancodes
 * Use the scancode as the index to get the right character
 * Note: Non-ASCII characters like the F. keys get values greater than 0x7f
 */
u8 scancode_set1_chars[128] = {
  KEY_NULL, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  '-', '=', KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u',
  'i', 'o', 'p', '[', ']', KEY_ENTER, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',
  'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
  ',', '.', '/', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
  KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
  KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
  KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12
};

u8 key_down_code = 0;

void init_keyboard()
{
  // activate keyboard by enabling scanning
  send_command(0xf4);

  // clear the keyboard output buffer as long as it is not empty
  // (i.e. the first bit of the 0x64 status register is set)
  CLEAR_KEYBOARD_OUT_BUF();

  key_down_code = 0;

  // install keyboard IRQ handler on IRQ1
  install_irq_handler(KEYBOARD_IRQ, keyboard_irq_handler);
}

/**
 * This function is called every time IRQ1 is encountered
 * which happens every time a key is pressed
 * That's why then this function can read the keyboard output buffer
 * immediately without checking whether it is full
 */
void keyboard_irq_handler()
{
  kprint("key");
  u8 scancode = port_byte_in(0x60);
  if (IS_KEY_UP(scancode)) {
    if (key_down_code == scancode) // no key currently pressed
      key_down_code = 0;
  } else {
    key_down_code = scancode;
  }
}

void send_command(u8 command)
{
  // wait until command input buffer is empty
  // by checking if the second bit of the status register is set
  while (port_byte_in(0x64) & 0x2) {}
  port_byte_out(0x60, command);
}

/**
 * Get scancode as soon as one is in the keyboard output buffer
 */
u8 get_scancode()
{
  // wait until output buffer is full
  while (!(port_byte_in(0x64) & 0x1)) {}
  return port_byte_in(0x60);
}

/**
 * Get scancode set which is either 1, 2 (default) or 3 (given in set)
 * If translation from set 2 to 1 is enable in the KBC
 * the sets 1, 2 and 3 will be returned as 0x43, 0x41 and 0x3f
 */
u8 get_scancode_set()
{
  u8 result;
  send_command(0xf0);

  while (!(port_byte_in(0x60) & 0xfa)) {} // wait for ACK response

  // 0x0 is the parameter which causes the command 0xf0
  // to return the current scancode set
  port_byte_out(0x60, 0x0);

  while (!(port_byte_in(0x60) & 0xfa)) {}
  result = port_byte_in(0x60);
  return result;
}
