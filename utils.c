#include "utils.h"

#if LANG_CPP
#else
void print_s32(s32 x)
{
    printf("%d\n", ( s32 ) (x));
}
void print_u32(u32 x)
{
    printf("%u\n", ( u32 ) (x));
}
void print_f32(f32 x)
{
    printf("%lf\n", ( f32 ) (x));
}
void print_f64(f64 x)
{
    printf("%f\n", ( f64 ) (x));
}
void print_s64(s64 x)
{
    printf("%ld\n", ( s64 ) (x));
}
void print_u64(u64 x)
{
    printf("%lu\n", ( u64 ) (x));
}
void print_charp(char* x)
{
    printf("%s\n", (x));
}
void print_char(char x)
{
    print_charp(&x);
}
void print_unknown()
{
    print_charp("Unknown type");
}
#endif // LANG_CPP
