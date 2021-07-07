#include <display.h>

int FIELD_ROWS[3] = {10, 12, 14};
int FIELD_COLS[3] = {35, 38, 41};

void init_field()
{
	int row_i, col_i;
	for (row_i = 0; row_i < 3; row_i++)
		for (col_i = 0; col_i < 3; col_i++)
			print_char('-', FIELD_COLS[col_i], FIELD_ROWS[row_i], 0xf);
}

/* Insert the mark mark ('X' or 'O') on the position field_pos
 * which is a number between 0 and 8
 */
void insert_mark(char mark, short field_pos)
{
	int row = field_pos/3;
	int col = field_pos%3;
	print_char(mark, FIELD_COLS[col], FIELD_ROWS[row], 0xf);
}
