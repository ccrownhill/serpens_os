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

int is_game_running = 0; // FALSE

void main(int mem_map_entry_count, mem_map_entry_t* mem_map)
{
  init_mem_management(mem_map_entry_count, mem_map);

  init_idt();
  pic_setup_with_irq_remap();

  init_keyboard();
  init_timer();
  start_screen();
}

void game_main_loop()
{
  if (is_game_running) {
    redraw_background();
    move_snake();
    draw_snake();
  } else {
    // in the game over screen wait for a key release to restart the game
    if (key_down_code && key_up_code == key_down_code)
      start_game();
  }
}
