/**
 * Display driver *
 *
 * Note: The functions that deal with the setting or reading the VGA text mode
 * cursor are not really necessary so that everything works properly. They are
 * only needed for the kprint() function. I added them because I wanted to learn
 * how dealing with the cursor works.
 */

#include <display.h>
#include <ports_io.h>

void print_char(char c, u32 col, u32 row, u8 appearance_byte)
{
  u16 offset = GET_OFFSET(col, row);
  char* dest_address = (char*)VGA_BUFFER + offset;
  dest_address[0] = c;
  dest_address[1] = appearance_byte;

  // this was commented out because it is not necessary for the game
  // however setting the cursor is necessary for the "kprint" function
  //set_cursor_offset(offset + 2); // set cursor to next character field
}

/**
 * Print at current cursor position
 * with appearance byte set to 0xf for white color
 */
void kprint(char* msg)
{
  u16 offset = get_cursor_offset();
  kprint_at(msg, GET_COL_FROM_OFFSET(offset), GET_ROW_FROM_OFFSET(offset), WHITE); 
}

void kprint_at(char* msg, u32 col, u32 row, u8 appearance_byte)
{
  char* c;
  for (c = msg; *c != '\0'; c++) {
    print_char(*c, col, row, appearance_byte);
    col++;
    if (col >= NUM_COLS) {
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
void kprint_centered(char* msg, u32 msg_len, u32 col, u32 row, u8 appearance_byte)
{
  col -= msg_len/2;
  kprint_at(msg, col, row, appearance_byte);
}

/**
 * Fill all fields with 0 char and black color 0x0
 */
void clear_screen()
{
  int col, row;
  for (col = 0; col <= NUM_COLS; col++)
    for (row = 0; row <= NUM_ROWS; row++)
      print_char('\0', col, row, 0x0);
  set_cursor_offset(0);
}

u16 get_cursor_offset()
{
  u16 offset;

  // Get higher 8 bits (0xe register) of cursor offset
  port_byte_out(VGA_CTRL_REG, CURSOR_OFFSET_HIGH_BYTE_REG);
  offset = port_byte_in(VGA_DATA_REG) << 8; // assign register val to higher byte

  // Get lower 8 bits (0xf register)
  port_byte_out(VGA_CTRL_REG, CURSOR_OFFSET_LOW_BYTE_REG);
  offset += port_byte_in(VGA_DATA_REG);

  return offset*2; // because the normal offset uses 2 bytes per character field
}

void set_cursor_offset(u16 offset)
{
  offset /= 2; // because cursor offset does not include 2 bytes per field
  port_byte_out(VGA_CTRL_REG, CURSOR_OFFSET_HIGH_BYTE_REG); // higher byte (0xe register)
  port_byte_out(VGA_DATA_REG, (u8)(offset >> 8)); // only write higher byte with '>> 8'
  port_byte_out(VGA_CTRL_REG, CURSOR_OFFSET_LOW_BYTE_REG); // lower byte (0xf register)
  port_byte_out(VGA_DATA_REG, (u8)(offset & 0xff)); // only write lower byte
}
