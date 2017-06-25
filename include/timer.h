#ifndef TIMER_H
#define TIMER_H

#include <common.h>
#include <irq.h>
#include <tasks/task.h>

void timer_handler(struct regs *r);
void timer_install();

#endif
