char* VGA_MEMORY = (char*) (0xb8000);

/* Calculation of the addresses with this formula
 * destination_address = 0xb8000 + 2 * (row * 80 + col)
 * where row and col counting start at 0
 * Rows: 10, 12, 14
 * Cols: 35, 38, 41
 */
char* FIELD_ADDRESSES[9] = {(char*) (0xb8686), (char*) (0xb868c), (char*) (0xb8692), (char*) (0xb87c6), (char*) (0xb87cc), (char*) (0xb87d2), (char*) (0xb8906), (char*) (0xb890c), (char*) (0xb8912)};

void print(char *msg, int msg_len)
{
	int i;
	for (i = 0; i < msg_len; i++) {
		VGA_MEMORY[i*2] = msg[i];
		VGA_MEMORY[i*2+1] = 0xf; // white color
	}
}

void main()
{
	print("Hi", 2);
	while(1);
}
