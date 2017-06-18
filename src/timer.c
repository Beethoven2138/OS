#include <timer.h>

void terminal_writestring(const char*);

void timer_handler(struct regs *r)
{
	static uint32_t timer_ticks = 0;
	if (++timer_ticks % 18 == 0)
	        terminal_writestring("A second passed");
}

void timer_install()
{
	irq_install_handler(0, timer_handler);
}
