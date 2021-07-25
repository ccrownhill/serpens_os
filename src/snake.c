#include <snake.h>
#include <keyboard.h> // for user input
#include <display.h>

typedef enum { LEFT, RIGHT, UP, DOWN } moving_dir;

moving_dir snake_dir;

int score = 0;

snake_part* snake_head;
snake_part* snake_rear;

void init_snake()
{
  snake_head = (snake_part*)malloc(sizeof(snake_part));
  snake_head->x_pos = SNAKE_INIT_X;
  snake_head->y_pos = SNAKE_INIT_Y;
  snake_head->next = NULL;
  snake_rear = snake_head;
}

void move_snake()
{
  // advance all body parts to the position of the next body part
  snake_part* snake_p = snake_rear;
  // NOTE: rear parts always point to next part closer to head
  for (; snake_p->next != NULL; snake_p = snake_p->next) {
    snake_p->x_pos = snake_p->next->x_pos;
    snake_p->y_pos = snake_p->next->y_pos;
  }

  // move the snake head according to user input
  if (keyboard_input.is_key_pressed) {
    switch (keyboard_input.key_code) {
      case KEY_LEFT:
        snake_head->x_pos -= 1;
        snake_dir = LEFT;
        break;
      case KEY_RIGHT:
        snake_head->x_pos += 1;
        snake_dir = RIGHT;
        break;
      case KEY_UP:
        snake_head->y_pos -= 1;
        snake_dir = UP;
        break;
      case KEY_DOWN:
        snake_head->y_pos += 1;
        snake_dir = DOWN;
        break;
    }
  } else { // if there is no new user input
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
    } // end switch
  } // end if
}

void draw_snake()
{
  snake_part* snake_p = snake_rear;
  // draw the body parts
  for (; snake_p->next != NULL; snake_p = snake_p->next) {
    print_char(SNAKE_BODY_CHAR, snake_p->x_pos, snake_p->y_pos, SNAKE_BODY_COLOR);
  }
  // draw the head
  print_char(SNAKE_HEAD_CHAR, snake_head->x_pos, snake_head->y_pos, SNAKE_BODY_COLOR);
}

void detect_border_collisions()
{
}
