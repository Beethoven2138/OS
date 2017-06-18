#ifndef __MM__PAGING_H
#define __MM__PAGING_H

#include <common.h>
#include <mm/frames.h>
#include <mm/heap.h>

uint32_t *page_directory;

uint32_t *first_page_table;

void init_paging(uint32_t mem_size);

void handle_page_fault(struct regs *r);

extern void loadPageDir(unsigned int *);
extern void enablePaging();

#endif
