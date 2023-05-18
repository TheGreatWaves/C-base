#pragma once
#ifndef BASE_UTILS
#define BASE_UTILS

#include "context.h"
#include "types.h"
#include <stdio.h>

//////////////////////////////////
// NOTE: Useful utilites

#define Stmnt(s) do { s } while(0)

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
void printS32(S32 x);
void printU32(U32 x);
void printF32(F32 x);
void printF64(F64 x);
void printS64(S64 x);
void printU64(U64 x);
void printcharp(char* x);
void printchar(char x);
void printUnknown();

#define gprint(x) _Generic((x), \
  S8: printS32,\
  S16: printS32,\
  S32: printS32,\
  S64: printS64,\
  U8: printU32, \
  U16: printU32, \
  U32: printU32, \
  U64: printU64, \
  F32: printF32, \
  F64: printF64, \
  char*: printcharp, \
  char: printchar, \
  default: printUnknown \
)(x)

#endif // gprint 

#endif // BASE_UTILS