#ifndef CANDY_H
#define CANDY_H

#include <display.h> // for the color definitions

#define CANDY_CHAR 4 // see a code page 437 table
#define CANDY_COLOR RED

typedef struct {
  u8 x_pos;
  u8 y_pos;
} candy_t;

extern candy_t candy;

void spawn_candy();
void draw_candy();

#endif
