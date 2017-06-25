#ifndef __TASKS__TASK_H
#define __TASKS__TASK_H

#include <mm/paging.h>
#include <mm/heap.h>
#include <mm/frames.h>//Later in paging.h

extern void init_tasking();

typedef struct {
	uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct Task {
	Registers regs;
	struct Task *next;
} Task;

extern void create_task(Task*, void(*)(), uint32_t, uint32_t*);

extern void preempt(); // Switch task frontend
extern void switch_task(Registers *old, Registers *new); // The function which actually switches

#endif
