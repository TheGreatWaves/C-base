#pragma once
#ifndef BASE_MEMORY
#define BASE_MEMORY

#include <stdlib.h>
#include "types.h"
#include "utils.h"

typedef void* _m_reserve_func(void *ctx, u64 size);
typedef void  _m_change_memory_func(void *ctx, void *ptr, u64 size);

typedef struct M_BaseMemory
{
  _m_reserve_func      * reserve; 
  _m_change_memory_func * commit;
  _m_change_memory_func * decommit;
  _m_change_memory_func * release;
  void* ctx;
} M_BaseMemory;

// Dummy change memory function
void m_change_memory_no_op(void *ctx, void *ptr, u64 size);


//////////////////////////////////
// NOTE: Memory arena

typedef struct _memory_arena {
  M_BaseMemory* base;
  u8* memory;
  u64 cap;
  u64 pos;
  u64 commit_pos;
} M_Arena;

//////////////////////////////////
// NOTE: Arena functions
#define M_DEFAULT_RESERVE_SIZE GB(1)
#define M_COMMIT_BLOCK_SIZE MB(64)

M_Arena m_make_arena_reserve(M_BaseMemory *base, u64 reserve_size);
M_Arena m_make_arena(M_BaseMemory* base);

void m_arena_release(M_Arena* arena);
void* m_arena_push(M_Arena* arena, u64 size);
void m_arena_pop_to(M_Arena* arena, u64 pos);

// struct _arena_in_args { size_t blockSize; };
// MemoryArena _make_arena(struct _arena_in_args in_args);
// void free_arena(MemoryArena* arena);
 

#define make_arena(...) _make_arena((struct _arena_in_args){__VA_ARGS__});
#endif // BASE_MEMORY
