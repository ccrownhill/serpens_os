/* Kernel of TicTacToe OS */

#include <types.h>
#include <display.h>
#include <keyboard.h>
#include <game_ui.h>
#include <snake.h>
#include <util.h>
#include <idt.h>
#include <irq.h>

#define START_SCREEN_TITLE "Snake Operating System"
#define START_SCREEN_TITLE_LEN 22
#define START_SCREEN_SUBTITLE "Press any key to begin playing"
#define START_SCREEN_SUBTITLE_LEN 30

// in link.ld
extern u32 _kernelend;

typedef struct {
  u64 base_addr;
  u64 length;
  u32 type;
} mem_map_entry_t;

void start_screen()
{
  clear_screen();
  kprint_centered(START_SCREEN_TITLE, START_SCREEN_TITLE_LEN, 38, 11, WHITE);
  kprint_centered(START_SCREEN_SUBTITLE, START_SCREEN_SUBTITLE_LEN, 38, 15, WHITE);
}

u32 get_kernel_end()
{
  return (u32)&_kernelend;
}

void main(int mem_map_entry_count, mem_map_entry_t* mem_map)
{
  char kernel_end_string[5];
  int_to_hexascii(get_kernel_end(), kernel_end_string);
  kprint_at(kernel_end_string, 3, 21, WHITE);

  char mmap_string[5];
  int i;
  for (i = 0; i < mem_map_entry_count; i++) {
    memset(mmap_string, 0, 5);
    int_to_hexascii(mem_map[i].base_addr, mmap_string);
    kprint_at(mmap_string, i*2, i*3, WHITE);
    memset(mmap_string, 0, 5);
    int_to_hexascii(mem_map[i].length, mmap_string);
    kprint_at(mmap_string, i*2, i*3+1, WHITE);
    memset(mmap_string, 0, 5);
    //int_to_hexascii(0b10000000000000000100000000000000, mmap_string);
    int_to_hexascii(mem_map[i].type, mmap_string);
    kprint_at(mmap_string, i*2, i*3+2, WHITE);
  }

  while(1);


  init_idt();
  pic_setup_with_irq_remap();

  init_keyboard();
  start_screen();
  while (!keyboard_input.is_key_pressed);

  init_snake_ui();
  init_snake();
  draw_snake();

  while(1);
}
