#include "mem.h"
#include "utils.h"

void m_change_memory_no_op(void *ctx, void *ptr, u64 size) {}

//////////////////////////////////
// NOTE: Arena functions

M_Arena m_make_arena_reserve(M_BaseMemory *base, u64 reserve_size)
{
	M_Arena arena = {};	
	arena.base = base;
	arena.memory = cast(u8*, base->reserve(base->ctx, reserve_size));
	arena.cap = reserve_size;
	return arena;
}

M_Arena m_make_arena(M_BaseMemory* base)
{
	M_Arena arena = m_make_arena_reserve(base, M_DEFAULT_RESERVE_SIZE);
	return arena;
}

void m_arena_release(M_Arena* arena)
{
	M_BaseMemory* base = arena->base;
	base->release(base->ctx, arena->memory, arena->cap);
}

void* m_arena_push(M_Arena* arena, u64 size)
{
	// Null pointer is returned if failed.
	void* result = 0;

	// Check that the new push will fit within the chunk.
	if (arena->pos + size <= arena->cap)
	{
		// The result will be the beginning of the newly segmented block.
		result = arena->memory + arena->pos;

		// Increment the position of the arena next segment.
		arena->pos += size;

		u64 pos = arena->pos;
		u64 commit_pos = arena->commit_pos;

		// Double check the commit size, check bytes prior to pos
		// Check if the position has exceeded the amount we've committed so far,
		// if it has then we need to commit more.
		if (pos > commit_pos) {

			// Obtain the next commit position.
			u64 pos_aligned = AlignUpPow2(pos, M_COMMIT_BLOCK_SIZE);

			// Make sure it fits within the arena.
			u64 next_commit_pos = ClampTop(pos_aligned, arena->cap);

			// Now we can find the commit size.
			u64 commit_size = next_commit_pos - commit_pos;

			// Apply the commit and update the position.
			M_BaseMemory* base = arena->base;
			base->commit(base->ctx, arena->memory + arena->commit_pos, commit_size);
			arena->commit_pos = next_commit_pos;
		}
	}
	return result;
}

void m_arena_pop_to(M_Arena* arena, u64 pos)
{
	// Check valid pop position
	if (pos < arena->pos)
	{
		// Reset arena pos, everything 
		// onwards (LHS) will now be popped
		arena->pos = pos;

		u64 pos = arena->pos;

		// Find out the next block we could commit
		u64 pos_aligned = AlignUpPow2(pos, M_COMMIT_BLOCK_SIZE);
		u64 next_commit_pos = ClampTop(pos_aligned, arena->cap);
		
		u64 commit_pos = arena->commit_pos;

		// Check if the calculated next commit position is behind
		// our actual current commit position, if so then we must
		// decommit and reset our commit position.
		if (next_commit_pos < commit_pos) 
		{
			u64 decommit_size = commit_pos - next_commit_pos;
			M_BaseMemory* base = arena->base;
			base->decommit(base->ctx, arena->memory + next_commit_pos, decommit_size);
			arena->commit_pos = next_commit_pos;
		}
	}
}
