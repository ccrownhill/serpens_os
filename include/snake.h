#ifndef SNAKE_H
#define SNAKE_H

#include <game_ui.h> // for the offsets and columns and rows
#include <display.h> // for the colors

// place snake in the center
#define SNAKE_INIT_X (FIELD_X_OFFSET + (FIELD_COLS / 2))
#define SNAKE_INIT_Y (FIELD_Y_OFFSET + (FIELD_ROWS / 2))

#define SNAKE_HEAD_CHAR 2 // smiley in Code Page 437
#define SNAKE_BODY_CHAR 15 // sun character

#define SNAKE_BODY_COLOR GREEN
#define SNAKE_HEAD_COLOR LIGHT_GREEN

extern int score;

typedef struct snake_part {
  u8 x_pos;
  u8 y_pos;
  struct snake_part* next; // this always points from the part closer to the rear to the one closer to the head
} snake_part;

void init_snake();
void move_snake();
void draw_snake();
void detect_boder_collisions();

#endif
