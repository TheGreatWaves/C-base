#pragma once
#ifndef BASE_LIMITS
#define BASE_LIMITS
#define _global static

//////////////////////////////////
// NOTE: Limit Constants

#include "types.h"

const _global s8  min_s8  = (s8)  0x80;
const _global s16 min_s16 = (s16) 0x8000;
const _global s32 min_s32 = (s32) 0x80000000;
const _global s64 min_s64 = (s64) 0x8000000000000000llu;

const _global s8  max_s8  = (s8)  0x7f;
const _global s16 max_s16 = (s16) 0x7fff;
const _global s32 max_s32 = (s32) 0x7fffffff;
const _global s64 max_s64 = (s64) 0x7fffffffffffffffllu;

const _global u8  max_u8  = 0xff;
const _global u16 max_u16 = 0xffff;
const _global u32 max_u32 = 0xffffffff;
const _global u64 max_u64 = 0xffffffffffffffffllu;

#endif // BASE_LIMITS
