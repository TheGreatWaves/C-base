#pragma once
#ifndef BASE_UTILS
#define BASE_UTILS

#include "context.h"
#include "types.h"
#include <stdio.h>

//////////////////////////////////
// NOTE: Useful utilites.

#define stmnt(s)                                                                                   \
    do                                                                                             \
    {                                                                                              \
        s                                                                                          \
    } while (0)

// Typing casting
#define cast(t, v)    (( t ) (v))
#define cast_void(v)  cast(void, (v))
#define cast_voidp(v) cast(void*, (v))

#define str(x)            #x
#define join_helper(a, b) a##b
#define join(a, b)        join_helper(str(a), str(b))
#define glue(a, b)        join_helper(a, b)

// Primitive types generic printing.
void print_s32(s32 x);
void print_u32(u32 x);
void print_f32(f32 x);
void print_f64(f64 x);
void print_s64(s64 x);
void print_u64(u64 x);
void print_charp(char* x);
void print_char(char x);
void print_unknown(void*);

#define gprint(x)                                                                                  \
    _Generic((x), \
  s8: print_s32,\
  s16: print_s32,\
  s32: print_s32,\
  s64: print_s64,\
  u8: print_u32, \
  u16: print_u32, \
  u32: print_u32, \
  u64: print_u64, \
  f32: print_f32, \
  f64: print_f64, \
  const char*: print_charp, \
  char*: print_charp, \
  char: print_char, \
  default: print_unknown \
)(x)

#include <string.h>
#define MemoryZero(p, z)    memset((p), 0, (z))
#define MemoryZeroStruct(p) memset((p), sizeof(*(p)))

// Creates a mask of n 1s.
#define MASK(n) (~((~(( uint32_t ) 0)) << n))

// Creates a mask of n 1s followed by p 0s.
#define MASK1(n, p) ((MASK(n)) << (p))

// Creates a mask of n 0s followed by p 1s.
#define MASK0(n, p) (~(MASK1(n, p)))

#endif // BASE_UTILS