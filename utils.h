#pragma once
#ifndef BASE_UTILS
#define BASE_UTILS

#include "context.h"
#include "types.h"
#include <stdio.h>

//////////////////////////////////
// NOTE: Useful utilites

#define stmnt(s) do { s } while(0)

// Typing casting
#define     cast(t,v) ((t)(v))
#define  cast_void(v) cast(void,(v)) 
#define cast_voidp(v) cast(void*,(v)) 


#if LANG_CPP
#include <iostream>
// TODO: Need to fix precision error.
template <typename T>
inline void gprint(T t)  { std::cout << t << '\n'; }

#else // C

// Primitive types generic printing
void print_s32(s32 x);
void print_u32(u32 x);
void print_f32(f32 x);
void print_f64(f64 x);
void print_s64(s64 x);
void print_u64(u64 x);
void print_charp(char* x);
void print_char(char x);
void print_unknown();

#define gprint(x) _Generic((x), \
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
  char*: print_charp, \
  char: print_char, \
  default: print_unknown \
)(x)

#endif // gprint 


#endif // BASE_UTILS