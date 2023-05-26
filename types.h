#pragma once
#ifndef BASE_TYPES
#define BASE_TYPES

//////////////////////////////////
// NOTE: Basic Types

#include <stdint.h>

typedef        int8_t     s8;
typedef       int16_t    s16;
typedef       int32_t    s32;
typedef       int64_t    s64;
typedef       uint8_t     u8;
typedef      uint16_t    u16;
typedef      uint32_t    u32;
typedef      uint64_t    u64;
typedef            s8     b8;
typedef           s16    b16;
typedef           s32    b32;
typedef           s64    b64;
typedef         float    f32;
typedef        double    f64;
typedef unsigned long size_t;

//////////////////////////////////
// NOTE: Basic Helpers

#define Min(a,b) (((a)<(b))?(a):(b))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Clamp(a,x,b) (((x)<(a))?(a):\
  ((b)<(x))?(b):(x))
#define ClampTop(a,bound) Min(a,bound)
#define ClampBot(a,bound) Max(a,bound)

#define AlignUpPow2(x, p) (((x) + (p) - 1)&~((p) - 1))
#define AlignDownPow2(x, p) ((x)&~((p) - 1))

//////////////////////////////////
// NOTE: File sizes
#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((x) << 40)

#define c_linkage_begin extern "C" {
#define c_linkage_end }
#define c_linkage extern "C"

#endif // BASE_TYPES
