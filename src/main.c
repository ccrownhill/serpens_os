/* Kernel of TicTacToe OS */

#include <main.h>
#include <display.h>
#include <field.h>
#include <keyboard.h>
#include <util.h>

void main()
{
	init_keyboard();
	start_screen();
	get_key(UP_CHECK_AND_VAL); // wait for release of any key
	clear_screen();

	print_centered("Your turn! You have the X marks!", 32, TITLE_COL, TITLE_ROW - 2, WHITE);
	print_centered("Enter a number from 1-9 to put your mark in the desired field!", 62, TITLE_COL, TITLE_ROW, WHITE);
	init_field();

	while(1);
}

void player_turn()
{
}

void start_screen()
{
	clear_screen();
	print_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11, WHITE);
	print_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);
}

