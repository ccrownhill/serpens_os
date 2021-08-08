#ifndef GAME_UI_H
#define GAME_UI_H

// text for start screen
#define START_SCREEN_TITLE "Snake Operating System"
#define START_SCREEN_TITLE_LEN 22
#define START_SCREEN_SUBTITLE "Press ENTER to begin playing"
#define START_SCREEN_SUBTITLE_LEN 28

// text for game over screen
#define GAME_OVER_SCREEN_TITLE "Game Over"
#define GAME_OVER_SCREEN_TITLE_LEN 9
#define GAME_OVER_SCREEN_SUBTITLE "Press ENTER to play again"
#define GAME_OVER_SCREEN_SUBTITLE_LEN 25

// dimensions of the snake playing field
#define FIELD_COLS 50
#define FIELD_ROWS 23

#define FIELD_X_OFFSET 5
#define FIELD_Y_OFFSET 0

#define SCORE_COL 70
#define SCORE_ROW 9

void start_screen();
void game_over_screen();
void init_snake_ui();
void show_score();
void redraw_background();

#endif
