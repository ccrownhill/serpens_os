/* Display driver */

#include <display.h>

char* VGA_MEMORY = (char*) (0xb8000);

void print_char(char c, int col, int row, u8 appearance_byte)
{
	char* dest_address = VGA_MEMORY + 2 * (row * 80 + col);
	dest_address[0] = c;
	dest_address[1] = appearance_byte;
}

void print_left(char* msg, int col, int row, u8 appearance_byte)
{
	char* c;
	for (c = msg; *c != '\0'; c++) {
		print_char(*c, col, row, appearance_byte);
		col++;
		if (col >= 80) {
			col = 0;
			row++;
		}
	}
}

/**
 * Be careful with this function
 * it only works if the text fits centered onto the specified location
 * into 1 row
 */
void print_centered(char* msg, int msg_len, int col, int row, u8 appearance_byte)
{
	col -= msg_len/2;
	print_left(msg, col, row, appearance_byte);
}

void clear_screen()
{
	int col, row;
	for (col = 0; col <= MAX_COLS; col++)
		for (row = 0; row <= MAX_ROWS; row++)
			print_char('\0', col, row, 0x0);
}
