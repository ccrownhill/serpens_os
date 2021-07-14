#include <isr.h>
#include <display.h>
#include <util.h>

void isr_handler(struct registers regs)
{
	char ascii_interrupt[5];
	int_to_ascii(regs.int_no, ascii_interrupt);
	kprint_at("received interrupt: ", 0, 23, WHITE);
	kprint(ascii_interrupt);
}
