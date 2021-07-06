unsigned char port_byte_in(unsigned short port)
{
	// "d" to load dx with port
	// "=a" for assigning the value of al to result after the instruction
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port, unsigned char data)
{
	// "d" to load dx with port
	// "a" to load al with data
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
