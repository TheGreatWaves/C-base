#include "mem_malloc.h"

void* m_malloc_reserve(void *ctx, u64 size) { return malloc(size); }
void  m_malloc_commit(void *ctx, void *ptr, u64 size) {}
void  m_malloc_decommit(void *ctx, void *ptr, u64 size) {}
void  m_malloc_release(void *ctx, void *ptr, u64 size) { free(ptr); }

M_BaseMemory* m_malloc_base_memory(void) 
{
	local M_BaseMemory mem = {};
	if (mem.reserve == 0)
	{
		// Aassign function pointers
		mem.reserve  = m_malloc_reserve;
		mem.commit   = m_change_memory_no_op;
		mem.decommit = m_change_memory_no_op;
		mem.release  = m_malloc_release;
	}
	return (&mem);
}
