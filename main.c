/* Kernel of TicTacToe OS */

#include "main.h"
#include "display.h"
#include "field.h"

void start_screen()
{
	clear_screen();
	print_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11);
	print_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15);
}

void main()
{
	start_screen();
	//print_centered("Tic-Tac-Toe Time!", 17, TITLE_COL, TITLE_ROW);
	//init_field();
	//insert_mark(PLAYER_X_MARK, 4);
	while(1);
}
