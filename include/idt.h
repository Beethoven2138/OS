#ifndef IDT_H
#define IDT_H

#include <common.h>
#include <gdt.h>
#include <irq.h>
#include <mm/paging.h>

/* Defines an IDT entry */
struct idt_entry {
	uint16_t base_lo;
	uint16_t sel;        /* kernel segment goes here */
	uint8_t always0;     /* This will ALWAYS be set to 0 */
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

void idt_install();

extern void idt_load();

#endif
