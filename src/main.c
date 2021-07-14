/* Kernel of TicTacToe OS */

#include <main.h>
#include <display.h>
#include <field.h>
#include <keyboard.h>
#include <util.h>
#include <idt.h>

void main()
{
	init_keyboard();
	start_screen();
	get_key(UP_CHECK_AND_VAL); // wait for release of any key
	clear_screen();

	init_idt();
	__asm__("int $0x4"); // test interrupt handler

	kprint_centered("Your turn! You have the X marks!", 32, TITLE_COL, TITLE_ROW - 2, WHITE);
	kprint_centered("Enter a number from 1-9 to put your mark in the desired field!", 62, TITLE_COL, TITLE_ROW, WHITE);
  kprint("test");
	init_field();

	while(1);
}

void player_turn()
{
}

void start_screen()
{
	clear_screen();
	kprint_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11, WHITE);
	kprint_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);
}

