#include "utils.h"

void  printd(S32 x)  { printf("%d\n",  (S32)(x)); }
void  printu(U32 x)  { printf("%u\n",  (U32)(x)); }
void printld(S64 x)  { printf("%ld\n", (S64)(x)); }
void printlu(U64 x)  { printf("%lu\n", (U64)(x)); }
void printcp(char* x){ printf("%s\n", x); }
void printc(char x)  { printcp(&x); }
