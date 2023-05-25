#include "mem.h"

void* mMallocReserve(void *ctx, U64 size) { return malloc(size); }
void  mMallocCommit(void *ctx, void *ptr, U64 size) {}
void  mMallocDecommit(void *ctx, void *ptr, U64 size) {}
void  mMallocRelease(void *ctx, void *ptr, U64 size) { free(ctx); }

M_BaseMemory
mMallocBaseMemory(void) 
{
	M_BaseMemory mem = {};
	if (mem.reserve == 0)
	{
		// Aassign function pointers
		mem.reserve  = mMallocReserve;
		mem.commit   = mChangeMemoryNoOp;
		mem.decommit = mChangeMemoryNoOp;
		mem.release  = mMallocRelease;
	}
	return mem;
}

MemoryArena _makeArena(struct _arena_in_args in_args) 
{
	size_t blockSize = (in_args.blockSize > 0) ?  in_args.blockSize : DEFAULT_BLOCK_SIZE;
  MemoryArena arena = {blockSize, 0, 0, 0};
	arena.currentBlock = malloc( arena.blockSize );
  return arena;
}

void freeArena(MemoryArena* arena) { free(arena->currentBlock); } 