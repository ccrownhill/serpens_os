char* VGA_MEMORY = (char*) (0xb8000);

void main()
{
	print("Hi", 2);
	while(1);
}

void print(char *msg, int msg_len)
{
	int i;
	for (i = 0; i < msg_len; i++) {
		VGA_MEMORY[i*2] = msg[i];
		VGA_MEMORY[i*2+1] = 0xf; // white color
	}
}
