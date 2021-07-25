#include <game_ui.h>
#include <display.h>
#include <util.h>
#include <snake.h> // for score extern declaration (if this will be the only thing needed remove this include statement later)

static void draw_field_borders()
{
  int i;
  for (i = 0; i < FIELD_COLS+2; i++) {
    print_char('#', FIELD_X_OFFSET + i, FIELD_Y_OFFSET, LIGHT_BLUE); // upper border
    print_char('#', FIELD_X_OFFSET + i, FIELD_Y_OFFSET + FIELD_ROWS+1, LIGHT_BLUE); // lower border
  }
  for (i = 0; i < FIELD_ROWS+2; i++) {
    print_char('#', FIELD_X_OFFSET, FIELD_Y_OFFSET + i, LIGHT_BLUE); // left border
    print_char('#', FIELD_X_OFFSET + FIELD_COLS+1, FIELD_Y_OFFSET + i, LIGHT_BLUE); // right border
  }
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

  kprint_centered(score_text, 11, 70, 9, WHITE);
}

void init_snake_ui()
{
  clear_screen();
  draw_field_borders();
  init_info_text();
  show_score(); // maybe show this only in every updated frame so that it can be left out here
}
