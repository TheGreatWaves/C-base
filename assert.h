#pragma once
#ifndef BASE_ASSERT
#define BASE_ASSERT

// NOTE: Defauled to disabled
#if !defined(ENABLE_ASSERT)
# define ENABLE_ASSERT 0
#endif

//////////////////////////////////
// NOTE: Helper Macros

// This is placed here just for this file to work.
#define _Stmnt(s) do { s } while(0)

// NOTE: Not great can be overidden later
#if !defined(AssertBreak)
# define AssertBreak() *((int*)0) = 0;
#endif

#if ENABLE_ASSERT
# define Assert(c) _Stmnt( if (!(c)){ AssertBreak(); } )
#else 
# define Assert(c)
#endif

#endif // BASE_ASSERT
