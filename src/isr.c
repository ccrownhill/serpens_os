#include <isr.h>
#include <display.h>
#include <util.h>

void isr_handler(struct registers regs)
{
	char ascii_interrupt[1];
	int_to_ascii(regs.int_no, ascii_interrupt);
	print_left("received interrupt: ", 0, 23, WHITE);
	print_left(ascii_interrupt, 30, 23, WHITE);
}
