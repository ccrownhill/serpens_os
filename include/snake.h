#ifndef SNAKE_H
#define SNAKE_H

#include <game_ui.h> // for the offsets and columns and rows
#include <display.h> // for the colors

// place snake in the center
#define SNAKE_INIT_X (FIELD_X_OFFSET + (FIELD_COLS / 2) + 1)
#define SNAKE_INIT_Y (FIELD_Y_OFFSET + (FIELD_ROWS / 2) + 1)

#define SNAKE_HEAD_CHAR 2 // smiley in Code Page 437
#define SNAKE_BODY_CHAR 15 // sun character

#define SNAKE_BODY_COLOR GREEN
#define SNAKE_HEAD_COLOR LIGHT_GREEN

#define SNAKE_SPEED 12 // in fields/second

#define MAX_INPT_QUEUE_LEN 3

extern int score;

typedef enum { NONE, LEFT, RIGHT, UP, DOWN } moving_dir;

typedef struct snake_part {
  uint8_t x_pos;
  uint8_t y_pos;
  struct snake_part* next; // this always points from the part closer to the rear to the one closer to the head
} snake_part;

typedef struct inpt_queue_item {
  moving_dir dir;
  struct inpt_queue_item* next;
  struct inpt_queue_item* prev;
} inpt_queue_item;

extern snake_part* snake_head;

void init_snake();
void add_body_part();
void move_snake();
void continue_moving_in_currrent_dir();
void draw_snake();
void destroy_snake();
void detect_border_collisions();
void detect_candy_collisions();
void detect_body_collisions();
void game_over();
void process_input();
void enqueue_input();
moving_dir dequeue_input();
void destroy_input_queue();
int are_dirs_opposite(moving_dir, moving_dir);

#endif
