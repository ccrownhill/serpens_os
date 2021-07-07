#include <keyboard.h>
#include <ports_io.h>

void init_keyboard()
{
	/* clear the keyboard output buffer as long as it is not empty
	 * (i.e. the first bit of the 0x64 status register is set) */
	while (port_byte_in(0x64) & 0x1)
		port_byte_in(0x60);

	/* activate keyboard by enabling scanning */
	send_command(0xf4);
}

void send_command(u8 command)
{
	/* wait until command input buffer is empty
	 * by checking if the second bit of the status register is set */
	while ((port_byte_in(0x64) & 0x2)) {}
	port_byte_out(0x60, command);
}

/**
 * Waits until a key is pressed and returns the scancode
 */
u8 get_scancode()
{
}
