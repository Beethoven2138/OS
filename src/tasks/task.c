#include <tasks/task.h>

static Task *current_task;
static Task *head;
static Task otherTask;
//static uint32_t task_count;

static void test()
{
	while(1)
	{
		terminal_writestring("aaaaaaaaaaa");
		for (int i = 0; i < 100000000; i++);
		preempt();
	}
}

void init_tasking()
{
	asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(head->regs.cr3)::"%eax");
	
	asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(head->regs.eflags)::"%eax");
	//terminal_printhex32(head->regs.eflags);for(;;);
	//head->next = (Task *)kmalloc(sizeof(struct Task));


}

void create_task(Task *task, void (*main)(), uint32_t flags, uint32_t *pagedir) {
	
	task->regs.eax = 0;
	task->regs.ebx = 0;
	task->regs.ecx = 0;
	task->regs.edx = 0;
	task->regs.esi = 0;
	task->regs.edi = 0;
	task->regs.eflags = flags;
	task->regs.eip = (uint32_t) main;
	task->regs.cr3 = (uint32_t) pagedir;
	task->regs.esp = alloc_frame_int() + 0x1000;

	task->next = 0;
}

void preempt()
{
	Task *last = current_task;
	current_task = current_task->next;

	switch_task(&(last->regs), &(current_task->regs));
}
