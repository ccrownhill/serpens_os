#include <game_ui.h>
#include <display.h>
#include <util.h>
#include <keyboard.h>
#include <snake.h> // for score extern declaration (if this will be the only thing needed remove this include statement later)

#define BORDER_CHAR 177 // this uses code page 437 encoding

extern int is_game_running; // in main.c

static void draw_field_borders()
{
  int i;
  for (i = 0; i < FIELD_COLS+2; i++) {
    print_char(BORDER_CHAR, FIELD_X_OFFSET + i, FIELD_Y_OFFSET, LIGHT_BLUE); // upper border
    print_char(BORDER_CHAR, FIELD_X_OFFSET + i, FIELD_Y_OFFSET + FIELD_ROWS+1, LIGHT_BLUE); // lower border
  }
  for (i = 0; i < FIELD_ROWS+2; i++) {
    print_char(BORDER_CHAR, FIELD_X_OFFSET, FIELD_Y_OFFSET + i, LIGHT_BLUE); // left border
    print_char(BORDER_CHAR, FIELD_X_OFFSET + FIELD_COLS+1, FIELD_Y_OFFSET + i, LIGHT_BLUE); // right border
  }
}

void start_screen()
{
  is_game_running = 0;
  clear_screen();
  kprint_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11, WHITE);
  kprint_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);

  key_down_code = 0; // ignore all previous key presses
  wait_for_key_release();
  //key_up_code = 0; // ignore all previous key releases
  //while (!key_up_code);
  key_up_code = 0; // clear code of key release just detected

  start_game();
}

// TODO: Make the computer poweroff if ESC was pressed
void game_over_screen()
{
  is_game_running = 0;
  clear_screen();
  show_score();
  kprint_centered(GAME_OVER_SCREEN_TITLE, GAME_OVER_SCREEN_TITLE_LEN, 38, 11, WHITE);
  kprint_centered(GAME_OVER_SCREEN_SUBTITLE, GAME_OVER_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);

  // get scancodes and print them for testing
  //char test[5];
  //u8 test_code = get_scancode();
  //int_to_hexascii(test_code, test);
  //kprint_at(test, 0, 20, GREEN);
  //test_code = get_scancode();
  //int_to_hexascii(test_code, test);
  //kprint_at(test, 6, 20, GREEN);

  key_down_code = 0; // ignore all previous key presses
  wait_for_key_release();
  //key_up_code = 0; // ignore all previous key releases
  //while (!key_up_code);
  key_up_code = 0; // clear code of key release just detected
  
  start_game();
}

void start_game()
{
  score = 0;
  key_down_code = 0; // prevent previous arrow key presses to make snake start moving
  clear_screen();
  init_snake_ui();
  init_snake();
  is_game_running = 1;
}

static void init_info_text()
{
  kprint_centered("Use the arrow keys", 18, 70, 16, LIGHT_GREY);
  kprint_centered("to move the snake", 17, 70, 17, LIGHT_GREY);
  kprint_centered("and eat the candy", 17, 70, 18, LIGHT_GREY);
}

/**
 * Display "Score: 0000" where the score is always padded with 0s to a 4 digit
 * number
 * It will be called every time the snake its a candy
 */
void show_score()
{
  char score_text[12] = "Score: 0000";
  int i = 0;
  int n = score;

  // set the score text digit by digit from the back so that
  // the 0s stay at the beginning
  do {
    score_text[10-i] = n%10 + '0';
    i++;
  } while ((n /= 10) > 0);

  kprint_centered(score_text, 11, SCORE_COL, SCORE_ROW, WHITE);
}

void init_snake_ui()
{
  draw_field_borders();
  init_info_text();
  show_score();
}

/**
 * Just make all fields of the snake playing field black again
 * this will be used at the beginning of every frame
 */
void redraw_background()
{
  int col, row;
  for (col = FIELD_X_OFFSET+1; col < FIELD_X_OFFSET + FIELD_COLS + 1; col++)
    for (row = FIELD_Y_OFFSET+1; row < FIELD_Y_OFFSET + FIELD_ROWS + 1; row++)
      print_char('\0', col, row, BLACK);
}
