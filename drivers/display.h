#ifndef DISPLAY_H
#define DISPLAY_H

#define MAX_COLS 80
#define MAX_ROWS 25

void print_char(char c, int col, int row, char attribute_byte);
void print_left(char* msg, int col, int row);
void print_centered(char* msg, int msg_len, int col, int row);
void clear_screen();
#endif
