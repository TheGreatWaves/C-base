#include "utils.h"

#if LANG_CPP
#else
void printS32   (S32   x) { printf     ("%d\n" , (S32)(x)) ;}
void printU32   (U32   x) { printf     ("%u\n" , (U32)(x)) ;}
void printF32   (F32   x) { printf     ("%lf\n", (F32)(x)) ;}
void printF64   (F64   x) { printf     ("%f\n" , (F64)(x)) ;}
void printS64   (S64   x) { printf     ("%ld\n", (S64)(x)) ;}
void printU64   (U64   x) { printf     ("%lu\n", (U64)(x)) ;}
void printcharp (char* x) { printf     ("%s\n" ,      (x)) ;}
void printchar  (char  x) { printcharp (&x)                ;}
void printUnknown ()      { printcharp ("Unknown type")    ;}
#endif // LANG_CPP
