#pragma once
#ifndef BASE_MEMORY
#define BASE_MEMORY

#include <stdlib.h>
#include "types.h"

typedef void* M_ReserveFunc(void *ctx, U64 size);
typedef void  M_ChangeMemoryFunc(void *ctx, void *ptr, U64 size);

typedef struct M_BaseMemory
{
  M_ReserveFunc      * reserve; 
  M_ChangeMemoryFunc * commit;
  M_ChangeMemoryFunc * decommit;
  M_ChangeMemoryFunc * release;
} M_BaseMemory;

// Unspecified
void mChangeMemoryNoOp(void *ctx, void *ptr, U64 size);

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
MemoryArena _makeArena(struct _arena_in_args in_args);
void freeArena(MemoryArena* arena);


#define makeArena(...) _makeArena((struct _arena_in_args){__VA_ARGS__});
#endif // BASE_MEMORY
