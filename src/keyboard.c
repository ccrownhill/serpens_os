#include <keyboard.h>
#include <ports_io.h>

void init_keyboard()
{
	// activate keyboard by enabling scanning
	send_command(0xf4);

	// clear the keyboard output buffer as long as it is not empty
	// (i.e. the first bit of the 0x64 status register is set)
	while (port_byte_in(0x64) & 0x1)
	port_byte_in(0x60);
}

void send_command(u8 command)
{
	// wait until command input buffer is empty
	// by checking if the second bit of the status register is set
	while (port_byte_in(0x64) & 0x2) {}
	port_byte_out(0x60, command);
}

/**
 * Waits until a key is pressed and returns the scancode
 */
u8 get_scancode()
{
	// wait until output buffer is full
	while (!(port_byte_in(0x64) & 0x1)) {}
	return port_byte_in(0x60);
}

/**
 * Get scancode set which is either 1, 2 (default) or 3 (given in set)
 * If translation from set 2 to 1 is enable in the KBC
 * the sets 1, 2 and 3 will be returned as 0x43, 0x41 and 0x3f
 */
u8 get_scancode_set()
{
	u8 result;
	send_command(0xf0);

	while (!(port_byte_in(0x60) & 0xfa)) {} // wait for ACK response

	// 0x0 is the parameter which causes the command 0xf0
	// to return the current scancode set
	port_byte_out(0x60, 0x0);

	while (!(port_byte_in(0x60) & 0xfa)) {}
	result = port_byte_in(0x60);
	return result;
}
