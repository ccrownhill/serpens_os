#ifndef DISPLAY_H
#define DISPLAY_H

#include <types.h>

#define MAX_COLS 80
#define MAX_ROWS 25

/**
 * 16 VGA colors for VGA text mode 0x3
 * for printing text in different colors
 */
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xa
#define LIGHT_CYAN 0xb
#define LIGHT_RED 0xc
#define LIGHT_MAGENTA 0xd
#define LIGHT_BROWN 0xe
#define WHITE 0xf

void print_char(char c, int col, int row, u8 appearance_byte);
void print_left(char* msg, int col, int row, u8 appearance_byte);
void print_centered(char* msg, int msg_len, int col, int row, u8 appearance_byte);
void clear_screen();

#endif
