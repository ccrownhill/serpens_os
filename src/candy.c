#include <stdint.h>
#include <candy.h>
#include <game_ui.h> // for field dimensions and other info
#include <random.h> // for spawning at random location
#include <snake.h>

// in main.c
extern int is_game_running;

candy_t candy;

void spawn_candy()
{
  // put candy at random new position
  // and choose a different position if it is where the head is
  do {
    candy.x_pos = FIELD_X_OFFSET + (uint8_t)(rand() % FIELD_COLS) + 1;
    candy.y_pos = FIELD_Y_OFFSET + (uint8_t)(rand() % FIELD_ROWS) + 1;
  } while (candy.x_pos == snake_head->x_pos && candy.y_pos == snake_head->y_pos);
}

void draw_candy()
{
  if (!is_game_running)
    return;

  print_char(CANDY_CHAR, candy.x_pos, candy.y_pos, CANDY_COLOR);
}
