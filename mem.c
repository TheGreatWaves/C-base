#include "mem.h"

void m_change_memory_no_op(void *ctx, void *ptr, u64 size) {}

MemoryArena _make_arena(struct _arena_in_args in_args) 
{
	size_t blockSize = (in_args.blockSize > 0) ?  in_args.blockSize : DEFAULT_BLOCK_SIZE;
  MemoryArena arena = {blockSize, 0, 0, 0};
	arena.currentBlock = malloc( arena.blockSize );
  return arena;
}

void free_arena(MemoryArena* arena) { free(arena->currentBlock); } 