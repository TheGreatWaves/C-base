#pragma once
#ifndef BASE_MEMORY
#define BASE_MEMORY

#include "assert.h"
#include "types.h"
#include "utils.h"
#include <stdlib.h>

typedef void* _m_reserve_func(void* ctx, u64 size);
typedef void  _m_change_memory_func(void* ctx, void* ptr, u64 size);

typedef struct M_BaseMemory
{
    _m_reserve_func*       reserve;
    _m_change_memory_func* commit;
    _m_change_memory_func* decommit;
    _m_change_memory_func* release;
    void*                  ctx;
} M_BaseMemory;

// Dummy change memory function
void m_change_memory_no_op(void* ctx, void* ptr, u64 size);

//////////////////////////////////
// NOTE: Memory arena types

/**
 * Memory arena.
 */
typedef struct _memory_arena
{
    M_BaseMemory* base;
    u8*           memory;
    u64           cap;
    u64           pos;
    u64           commit_pos;
} M_Arena;

/**
 * Temporary block, deallocates the chunk
 * taken from arena once out of scope.
 */
typedef struct M_Temp
{
    M_Arena* arena;
    u64      pos;
} M_Temp;

//////////////////////////////////
// NOTE: Arena functions
#define M_DEFAULT_RESERVE_SIZE GB(1)
#define M_COMMIT_BLOCK_SIZE    MB(64)

M_Arena m_make_arena_reserve(M_BaseMemory* base, u64 reserve_size);
M_Arena m_make_arena(M_BaseMemory* base);

void m_arena_release(M_Arena* arena);

void* m_arena_push(M_Arena* arena, u64 size);
void  m_arena_pop_to(M_Arena* arena, u64 pos);

void  m_arena_align(M_Arena* arena, u64 pow_2_align);
void* m_arena_push_zero(M_Arena* arena, u64 size);
void  m_arena_align_zero(M_Arena* arena, u64 pow_2_align);

#define push_array(a, T, c)      ( T* ) m_arena_push((a), sizeof(T) * (c))
#define push_array_zero(a, T, c) ( T* ) m_arena_push_zero((a), sizeof(T) * (c))

M_Temp m_begin_temp(M_Arena* arena);
void   m_end_temp(M_Temp temp);

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
	((type*) reallocate((pointer), sizeof(type) * (old_count), sizeof(type) * (new_count)))

#define FREE_ARRAY(type, pointer, old_count) \
	reallocate(pointer, sizeof(type) * (old_count), 0)

void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif // BASE_MEMORY
