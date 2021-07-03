/* Kernel of TicTacToe OS */

#include "display.h"
#include "field.h"

void main()
{
	clear_screen(); // removes the blinking cursor from the screen
	print_centered("Tic-Tac-Toe Time!", 17, TITLE_COL, TITLE_ROW);
	init_field();
	insert_mark(PLAYER_X_MARK, 4);
	while(1);
}
