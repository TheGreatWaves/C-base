#pragma once
#ifndef BASE_UTILS
#define BASE_UTILS

#include "types.h"
#include <stdio.h>

//////////////////////////////////
// NOTE: Useful utilites

#define Stmnt(s) do { s } while(0)

// Typing casting
#define     cast(t,v) ((t)(v))
#define  cast_void(v) cast(void,(v)) 
#define cast_voidp(v) cast(void*,(v)) 

// Primitive types generic printing
void  printd(S32 x);
void  printu(U32 x);
void printld(S64 x);
void printlu(U64 x);
void printc(char x);
void printcp(char* x);
void printWhatever();

#define gprint(x) _Generic((x), \
  int : printd, \
  char*: printcp, \
  char: printc, \
  default: printWhatever \
)(x)

#endif // BASE_UTILS