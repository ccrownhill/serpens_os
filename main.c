void main()
{
	char* VGA_MEMORY = (char*) (0xb8000);
	VGA_MEMORY[0] = 'X';
	while(1);
}
