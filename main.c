void main()
{
	const unsigned char* VGA_MEMORY = (const unsigned char*) (0xb8000);
	VGA_MEMORY[0] = 'X';
}
