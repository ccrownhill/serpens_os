/* Kernel of TicTacToe OS */

#include <types.h>
#include <display.h>
#include <keyboard.h>
#include <game_ui.h>
#include <snake.h>
#include <util.h>
#include <idt.h>
#include <irq.h>
#include <memory.h>
#include <timer.h>

#define START_SCREEN_TITLE "Snake Operating System"
#define START_SCREEN_TITLE_LEN 22
#define START_SCREEN_SUBTITLE "Press any key to begin playing"
#define START_SCREEN_SUBTITLE_LEN 30

int is_game_running = 0; // FALSE

void start_screen()
{
  clear_screen();
  kprint_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11, WHITE);
  kprint_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);

  // wait for key press
  while (!keyboard_input.is_key_down);

  is_game_running = 1;
}

void main(int mem_map_entry_count, mem_map_entry_t* mem_map)
{
  init_mem_management(mem_map_entry_count, mem_map);

  init_idt();
  pic_setup_with_irq_remap();

  init_keyboard();
  start_screen();

  init_snake_ui();
  init_snake();
  init_timer();
}

void game_main_loop()
{
  if (!is_game_running);
  move_snake();
  draw_snake();
}
