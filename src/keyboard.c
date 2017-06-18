#include <keyboard.h>

#define DATA_PORT 0x60
#define COMMAND_PORT 0x6A
#define COMMAND_ACK 0xFA
#define COMMAND_RESEND 0xFE

void terminal_putchar(char);

uint8_t keyboard_table_uk[128] = {
	    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}

void set_typematic(uint8_t typematic)
{
	do {
		outb(COMMAND_PORT, 0xF3);
		outb(DATA_PORT, typematic);
	} while (inb(DATA_PORT) == COMMAND_RESEND);
	
	terminal_putchar('y');
}

void keyboard_uninstall()
{
	irq_uninstall_handler(1);
}

void keyboard_handler(struct regs *r)
{
	uint8_t scancode = 0;

	do {
		if (inb(0x60)!= scancode)
		{
			scancode = inb(0x60);
			if (scancode > 0)
			        break;
		}
	} while(1);

	if (!(scancode & 0x80))
		terminal_putchar(keyboard_table_uk[scancode]);
}
