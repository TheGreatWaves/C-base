#pragma once
#ifndef BASE_LIMITS
#define BASE_LIMITS
#define global static

//////////////////////////////////
// NOTE: Limit Constants

#include "types.h"

const global S8  min_S8  = (S8)  0x80;
const global S16 min_S16 = (S16) 0x8000;
const global S32 min_S32 = (S32) 0x80000000;
const global S64 min_S64 = (S64) 0x8000000000000000llu;

const global S8  max_S8  = (S8)  0x7f;
const global S16 max_S16 = (S16) 0x7fff;
const global S32 max_S32 = (S32) 0x7fffffff;
const global S64 max_S64 = (S64) 0x7fffffffffffffffllu;

const global U8  max_U8  = 0xff;
const global U16 max_U16 = 0xffff;
const global U32 max_U32 = 0xffffffff;
const global U64 max_U64 = 0xffffffffffffffffllu;

global uint8_t  min_U8;
global uint16_t min_U16;
global uint32_t min_U32;
global uint64_t min_U64;

#endif // BASE_LIMITS
