#include <mm/heap.h>

void kheap_init(uint32_t start, uint32_t end)
{
	heap_start = start;
	heap_end = end;
	heap_size = heap_end - heap_size;

	first = (struct mem_block*)heap_start;
	first->used = 0;
	first->prev = NULL;
	first->next = NULL;
	first->size = heap_size - sizeof(struct mem_block);
}

void *kmalloc(size_t size)
{
	struct mem_block *tmp = first;

	struct mem_block *result = NULL;

	for (tmp; tmp != NULL && result == NULL; tmp = tmp->next)
	{
		if (tmp->used == false && tmp->size >= size)
			result = tmp;
	}

	if (result->size >= size + sizeof(struct mem_block) + 1)
	{
		tmp = (struct mem_block*)((size_t)result + sizeof(struct mem_block) + size);
		tmp->used = false;
		tmp->size = result->size - size - sizeof(struct mem_block);
		tmp->prev = result;
		tmp->next = result->next;
		if(tmp->next != 0)
			tmp->next->prev = tmp;

		result->size = size;
		result->next = tmp;
	}

	result->used = true;
	return (void*)(((size_t)result) + sizeof(struct mem_block));
}

void kfree(void *ptr)
{
	struct mem_block *tmp = (struct mem_block*)((size_t)ptr - sizeof(struct mem_block));

	tmp->used = false;

	if (tmp->prev != NULL && tmp->prev->used == false)
	{
		tmp->prev->size += sizeof(struct mem_block) + tmp->size;
		tmp->prev->next = tmp->next;

		if (tmp->next != NULL)
			tmp->next->prev = tmp->prev;
		tmp = tmp->prev;
	}

	if (tmp->next != NULL && tmp->next->used == false)
	{
		tmp->size += sizeof(struct mem_block) + tmp->next->size;
		tmp->next = tmp->next->next;
		if (tmp->next != NULL)
			tmp->next->prev = tmp;
	}
}
