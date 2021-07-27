/* Kernel of TicTacToe OS */

#include <types.h>
#include <display.h>
#include <keyboard.h>
#include <game_ui.h>
#include <snake.h>
#include <util.h>
#include <idt.h>
#include <irq.h>

#define START_SCREEN_TITLE "Snake Operating System"
#define START_SCREEN_TITLE_LEN 22
#define START_SCREEN_SUBTITLE "Press any key to begin playing"
#define START_SCREEN_SUBTITLE_LEN 30

// in link.ld
extern u32 _kernelend;

void start_screen()
{
  clear_screen();
  kprint_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11, WHITE);
  kprint_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);
}

u32 get_kernel_end()
{
  return (u32)&_kernelend;
}

void main()
{
  char kernel_end_string[5];
  int_to_ascii(get_kernel_end(), kernel_end_string);
  kprint_at(kernel_end_string, 3, 21, WHITE);

  while(1);


  init_idt();
  pic_setup_with_irq_remap();

  init_keyboard();
  start_screen();
  while (!keyboard_input.is_key_pressed);

  init_snake_ui();
  init_snake();
  draw_snake();

  while(1);
}
