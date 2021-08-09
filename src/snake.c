#include <stdint.h>
#include <snake.h>
#include <keyboard.h> // for user input
#include <display.h>
#include <game_ui.h> // definitions of game field border coordinates
#include <memory.h>
#include <candy.h> // for collision detection
#include <util.h> // for memset
#include <timer.h> // for wait_seconds

#define NULL 0

extern int is_game_running; // in main.c

moving_dir snake_dir;

int score = 0;

snake_part* snake_head;
snake_part* snake_rear;
snake_part prev_rear;

int inpt_queue_len = 0;
inpt_queue_item* inpt_queue_first;
inpt_queue_item* inpt_queue_last;

void init_snake()
{
  snake_head = (snake_part*)kalloc(sizeof(snake_part));
  memset((char*)snake_head, 0, sizeof(snake_part));
  snake_head->x_pos = SNAKE_INIT_X;
  snake_head->y_pos = SNAKE_INIT_Y;
  snake_head->next = NULL;
  snake_rear = snake_head;
  snake_dir = NONE;

  inpt_queue_first = NULL;
  inpt_queue_last = NULL;
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
  // currently moving in (this is checked when before enqueuing the directions)
  moving_dir dir_inpt = dequeue_input();
  switch (dir_inpt) {
    case LEFT:
      snake_head->x_pos -= 1;
      snake_dir = LEFT;
      break;
    case RIGHT:
      snake_head->x_pos += 1;
      snake_dir = RIGHT;
      break;
    case UP:
      snake_head->y_pos -= 1;
      snake_dir = UP;
      break;
    case DOWN:
      snake_head->y_pos += 1;
      snake_dir = DOWN;
      break;
    default:
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
  snake_part *snake_p, *next;
  for (snake_p = snake_rear; snake_p != NULL; snake_p = next) {
    next = snake_p->next;
    kfree(snake_p);
  }
  destroy_input_queue();
}

void detect_border_collisions()
{
  if (snake_head->x_pos <= FIELD_X_OFFSET || snake_head->x_pos > FIELD_X_OFFSET + FIELD_COLS ||
      snake_head->y_pos <= FIELD_Y_OFFSET || snake_head->y_pos > FIELD_Y_OFFSET + FIELD_ROWS) {
    game_over();
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
      game_over();
      return;
    }
  }
}

void game_over()
{
  destroy_snake();
  wait_seconds(1);
  game_over_screen();
}

void process_input()
{
  // if any arrow key was pressed add the implied moving direction to the
  // snake movement input queue
  switch (key_down_code) {
    case KEY_LEFT:
      enqueue_input(LEFT);
      break;
    case KEY_RIGHT:
      enqueue_input(RIGHT);
      break;
    case KEY_UP:
      enqueue_input(UP);
      break;
    case KEY_DOWN:
      enqueue_input(DOWN);
      break;
  }
}

void enqueue_input(moving_dir dir)
{
  // ignore the direction if it is opposite or equal to the one before
  // the one before is the snake_dir if the queue is empty or
  // the next queue item
  if ((inpt_queue_len && (dir == inpt_queue_last->dir || are_dirs_opposite(dir, inpt_queue_last->dir))) ||
      (!inpt_queue_len && (dir == snake_dir || are_dirs_opposite(dir, snake_dir))))
    return;

  if (inpt_queue_len == MAX_INPT_QUEUE_LEN)
    dequeue_input();

  inpt_queue_item* new_item = (inpt_queue_item*)kalloc(sizeof(inpt_queue_item));
  memset((char*)new_item, 0, sizeof(inpt_queue_item));
  new_item->dir = dir;
  new_item->next = inpt_queue_last;
  new_item->prev = NULL;
  if (inpt_queue_last)
    inpt_queue_last->prev = new_item;
  inpt_queue_last = new_item;
  if (!inpt_queue_first) // check if this is the first item inserted
    inpt_queue_first = inpt_queue_last;
  inpt_queue_len++;
}

moving_dir dequeue_input()
{
  if (inpt_queue_first) {
    moving_dir ret_dir = inpt_queue_first->dir;
    inpt_queue_item* tmp = inpt_queue_first;
    inpt_queue_first = inpt_queue_first->prev;
    kfree(tmp);
    if (!inpt_queue_first) // if queue has become empty
      inpt_queue_last = NULL;
    else
      inpt_queue_first->next = NULL;
    inpt_queue_len--;
    return ret_dir;
  } else {
    return NONE;
  }
}

void destroy_input_queue()
{
  inpt_queue_item *item, *next;
  for (item = inpt_queue_last; item != NULL; item = next) {
    next = item->next;
    kfree(item);
  }
  inpt_queue_len = 0;
}

int are_dirs_opposite(moving_dir d1, moving_dir d2)
{
  return ( (d1 == LEFT && d2 == RIGHT) || (d1 == RIGHT && d2 == LEFT) ||
           (d1 == UP && d2 == DOWN) || (d1 == DOWN && d2 == UP) );
}
