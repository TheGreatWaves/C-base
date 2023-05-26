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

#ifndef DEFAULT_BLOCK_SIZE
# define DEFAULT_BLOCK_SIZE ((256)*(1024))
#endif

typedef struct _memory_arena {
  const size_t blockSize;
  size_t currentBlockPos;
  size_t currentAllocSize;
  uint8_t* currentBlock;
} MemoryArena;

struct _arena_in_args { size_t blockSize; };
MemoryArena _make_arena(struct _arena_in_args in_args);
void free_arena(MemoryArena* arena);


#define make_arena(...) _make_arena((struct _arena_in_args){__VA_ARGS__});
#endif // BASE_MEMORY
