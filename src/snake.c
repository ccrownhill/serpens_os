#include <snake.h>
#include <keyboard.h> // for user input
#include <display.h>
#include <game_ui.h> // definitions of game field border coordinates
#include <memory.h>
#include <candy.h> // for collision detection
#include <util.h> // for memset

typedef enum { NONE, LEFT, RIGHT, UP, DOWN } moving_dir;

extern int is_game_running; // in main.c

moving_dir snake_dir;

int score = 0;

snake_part* snake_head;
snake_part* snake_rear;
snake_part prev_rear;

void init_snake()
{
  snake_head = (snake_part*)kalloc(sizeof(snake_part));
  memset((char*)snake_head, 0, sizeof(snake_part));
  snake_head->x_pos = SNAKE_INIT_X;
  snake_head->y_pos = SNAKE_INIT_Y;
  snake_head->next = NULL;
  snake_rear = snake_head;
  snake_dir = NONE;
}

void add_body_part()
{
  snake_part* new_part = (snake_part*)kalloc(sizeof(snake_part));
  memset((char*)new_part, 0, sizeof(snake_part));
  new_part->x_pos = prev_rear.x_pos;
  new_part->y_pos = prev_rear.y_pos;
  new_part->next = snake_rear;
  snake_rear = new_part;
}

void continue_moving_in_current_dir()
{
  switch (snake_dir) { // just continue moving in the same direction
    case LEFT:
      snake_head->x_pos -= 1;
      break;
    case RIGHT:
      snake_head->x_pos += 1;
      break;
    case UP:
      snake_head->y_pos -= 1;
      break;
    case DOWN:
      snake_head->y_pos += 1;
      break;
  }
}

void move_snake()
{
  if (!is_game_running)
    return;

  prev_rear = *snake_rear;
  // advance all body parts to the position of the next body part
  snake_part* snake_p;
  // NOTE: rear parts always point to next part closer to head
  for (snake_p = snake_rear; snake_p->next != NULL; snake_p = snake_p->next) {
    snake_p->x_pos = snake_p->next->x_pos;
    snake_p->y_pos = snake_p->next->y_pos;
  }

  // move the snake head according to user input
  // Note that it can not be moved in the opposite direction of the one it is
  // currently moving in
  if (key_down_code == KEY_LEFT && snake_dir != RIGHT) {
    snake_head->x_pos -= 1;
    snake_dir = LEFT;
  } else if (key_down_code == KEY_RIGHT && snake_dir != LEFT) {
    snake_head->x_pos += 1;
    snake_dir = RIGHT;
  } else if (key_down_code == KEY_UP && snake_dir != DOWN) {
    snake_head->y_pos -= 1;
    snake_dir = UP;
  } else if (key_down_code == KEY_DOWN && snake_dir != UP) {
    snake_head->y_pos += 1;
    snake_dir = DOWN;
  } else {
    continue_moving_in_current_dir(); 
  }

  detect_border_collisions();
  detect_candy_collisions();
  detect_body_collisions();
}

void draw_snake()
{
  if (!is_game_running)
    return;

  snake_part* snake_p = snake_rear;
  // draw the body parts
  for (; snake_p->next != NULL; snake_p = snake_p->next) {
    print_char(SNAKE_BODY_CHAR, snake_p->x_pos, snake_p->y_pos, SNAKE_BODY_COLOR);
  }
  // draw the head
  print_char(SNAKE_HEAD_CHAR, snake_head->x_pos, snake_head->y_pos, SNAKE_BODY_COLOR);
}

void destroy_snake()
{
  snake_part* snake_p;
  snake_part* next;
  for (snake_p = snake_rear; snake_p != NULL; snake_p = next) {
    next = snake_p->next;
    kfree(snake_p);
  }
}

void detect_border_collisions()
{
  if (snake_head->x_pos <= FIELD_X_OFFSET || snake_head->x_pos > FIELD_X_OFFSET + FIELD_COLS ||
      snake_head->y_pos <= FIELD_Y_OFFSET || snake_head->y_pos > FIELD_Y_OFFSET + FIELD_ROWS) {
    destroy_snake();
    game_over_screen();
  }
}

void detect_candy_collisions()
{
  if (snake_head->x_pos == candy.x_pos && snake_head->y_pos == candy.y_pos) {
    score++;
    show_score();
    spawn_candy();
    add_body_part();
  }
}

void detect_body_collisions()
{
  snake_part* snake_p;
  for (snake_p = snake_rear; snake_p != snake_head; snake_p = snake_p->next) {
    if (snake_head->x_pos == snake_p->x_pos && snake_head->y_pos == snake_p->y_pos) {
      destroy_snake();
      game_over_screen();
      return;
    }
  }
}
