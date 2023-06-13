#pragma once
#ifndef BASE_ASSERT
#define BASE_ASSERT

// NOTE: Defauled to disabled
#if !defined(ENABLE_ASSERT)
#define ENABLE_ASSERT 0
#endif

//////////////////////////////////
// NOTE: Helper Macros

// This is placed here just for this file to work.
#define _stmnt(s)                                                                                  \
    do                                                                                             \
    {                                                                                              \
        s                                                                                          \
    } while (0)

// NOTE: Not great can be overidden later
#if !defined(assert_break)
#define assert_break() *(( int* ) 0) = 0;
#endif

#if ENABLE_ASSERT
#define assert(c) _stmnt(if (!(c)) { assert_break(); })
#else
#define assert(c)
#endif

#endif // BASE_ASSERT
