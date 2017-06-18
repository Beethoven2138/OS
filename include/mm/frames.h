#ifndef __MM__FRAMES_H
#define __MM__FRAMES_H

#include <common.h>

extern uint32_t endkernel;

/*Used to keep track of allocated and free frames
*1 == used, 0 == free
*/
uint32_t *bitmap;

//Number of frames used
uint32_t nframes;

void page_frame_init(uint32_t mem_size);
/*
Allocates a single frame
returns the physical address of the frame
*/
uint32_t alloc_frame_int();

void free_frame_int(uint32_t frame_adr);

#endif
