#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <common.h>
#include <irq.h>

/* Control Port: 0x64
   Data Port: 0x60
*/

uint8_t keyboard_table_uk[128];

uint8_t key_status;

void keyboard_handler(struct regs *r);

void keyboard_install();
void keyboard_uninstall();

void set_typematic(uint8_t typematic);

#endif
