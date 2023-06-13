#pragma once
#ifndef BASE_MEM_MALLOC
#define BASE_MEM_MALLOC

#include "mem.h"
#include "types.h"
#include "utils.h"

void*         m_malloc_reserve(void* ctx, u64 size);
void          m_malloc_commit(void* ctx, void* ptr, u64 size);
void          m_malloc_decommit(void* ctx, void* ptr, u64 size);
void          m_malloc_release(void* ctx, void* ptr, u64 size);
M_BaseMemory* m_malloc_base_memory(void);

#endif // BASE_MEM_MALLOC