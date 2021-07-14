#ifndef DISPLAY_H
#define DISPLAY_H

#include <types.h>

#define VGA_BUFFER 0xb8000

#define NUM_COLS 80
#define NUM_ROWS 25

#define GET_OFFSET(col, row) (2*(row*NUM_COLS + col))
#define GET_COL_FROM_OFFSET(offset) ((offset % (NUM_COLS*2)) / 2)
#define GET_ROW_FROM_OFFSET(offset) (offset / (NUM_COLS*2))

#define VGA_CTRL_REG 0x3d4
#define VGA_DATA_REG 0x3d5

#define CURSOR_OFFSET_HIGH_BYTE_REG 0xe
#define CURSOR_OFFSET_LOW_BYTE_REG 0xf

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
void kprint(char* msg);
void kprint_at(char* msg, int col, int row, u8 appearance_byte);
void kprint_centered(char* msg, int msg_len, int col, int row, u8 appearance_byte);
void clear_screen();
u16 get_cursor_offset();
void set_cursor_offset(u16 offset);

#endif
