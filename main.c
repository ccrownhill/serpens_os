/* Kernel of TicTacToe OS */

#define FIELD_TITLE_CENTER_ADDRESS 0xb84ac

char* VGA_MEMORY = (char*) (0xb8000);

/* Calculation of the addresses with this formula
 * destination_address = 0xb8000 + 2 * (row * 80 + col)
 * where row and col counting start at 0
 * Rows: 10, 12, 14
 */
char* FIELD_ADDRESSES[9] = {(char*) (0xb8686), (char*) (0xb868c), (char*) (0xb8692), (char*) (0xb87c6), (char*) (0xb87cc), (char*) (0xb87d2), (char*) (0xb8906), (char*) (0xb890c), (char*) (0xb8912)};

/* Write the text centered above the TicTacToe field
 * It should not be longer than 80 characters in order to fit on this one line
 */
void field_title(char *text, int text_len)
{
	char* start = (char*)FIELD_TITLE_CENTER_ADDRESS - (text_len / 2);
	int i;
	for (i = 0; i < text_len; i++) {
		start[i*2] = text[i];
		start[i*2+1] = 0xf; /* white */
	}
}

void init_field()
{
	int i;
	for (i = 0; i < 9; i++) {
		FIELD_ADDRESSES[i][0] = '-';
		FIELD_ADDRESSES[i][1] = 0xf; /* white */
	}
}

void main()
{
	field_title("Hello!", 6);
	init_field();
	while(1);
}
