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
#include <random.h> // for seeding random number generator
#include <candy.h>

int is_game_running = 0; // FALSE

void reset_game_state()
{
  score = 0;
  key_down_code = 0; // prevent previous arrow key presses to make snake start moving
  key_up_code = 0;
  clear_screen();
  init_snake_ui();
  init_snake();
  spawn_candy();
  is_game_running = 1;
}

void main(int mem_map_entry_count, mem_map_entry_t* mem_map)
{
  init_mem_management(mem_map_entry_count, mem_map);

  init_idt();
  pic_setup_with_irq_remap();

  init_keyboard();
  init_timer();
  rtc_time_rand_seed();

  start_screen();
  while(! (key_up_code == ENTER_SCANCODE) ); // wait for ENTER key to be released 
  reset_game_state();

  u64 last_frame = 0;
  while (1) { // MAIN game loop
    if ((ticks - last_frame) > (FREQ/FPS)) { // update game with frame rate "FPS"
      last_frame = ticks;

      if (is_game_running) {
        redraw_background();

        move_snake();

        draw_snake();
        draw_candy();
      } else { // GAME OVER
        // in the game over screen wait for ENTER key release to restart the game
        if (key_up_code == ENTER_SCANCODE)
          reset_game_state();
      }
    }
  }
}
