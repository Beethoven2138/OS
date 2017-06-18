#include <mm/paging.h>

void init_paging(uint32_t mem_size)
{
	page_frame_init(mem_size);

	uint32_t heap_start = alloc_frame_int();

        kheap_init(heap_start, heap_start + 0x1000);

	page_directory = alloc_frame_int();

        //set each entry to not present
	for (uint32_t i = 0; i < 1024; i++)
	{
		// This sets the following flags to the pages:
		//   Supervisor: Only kernel-mode can access them
		//   Write Enabled: It can be both read from and written to
		//   Not Present: The page table is not present
		page_directory[i] = 0x00000002;
	}

	first_page_table = alloc_frame_int();
	// holds the physical address where we want to start mapping these pages to.
// in this case, we want to map these pages to the very beginning of memory.

//we will fill all 1024 entries in the table, mapping 4 megabytes
	for (uint32_t i = 0; i < 1024; i++)
	{
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
	}

	page_directory[0] = ((unsigned int)first_page_table) | 3;

	loadPageDir(page_directory);
	enablePaging();
}
