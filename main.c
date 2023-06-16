#include "array.h"
#include "base.h"
#include "hashtable.h"
#include "mem_malloc.h"
#include "utils.h"
#include <stdio.h> // Will remove this later.

#define EVAL_PRINT(x)     printf("%s = %d\n", #x, ( s32 ) (x))
#define EVAL_PRINT_LL(x)  printf("%s = %ld\n", #x, ( s64 ) (x))
#define EVAL_PRINT_u(x)   printf("%s = %u\n", #x, ( u32 ) (x))
#define EVAL_PRINT_ull(x) printf("%s = %lu\n", #x, ( u64 ) (x))

DECLARE_TABLE(CharTable, int)

int main()
{
    printf("[Context]\n");
    printf("COMPILER_CL    %d\n", COMPILER_CL);
    printf("COMPILER_CLANG %d\n", COMPILER_CLANG);
    printf("COMPILER_GCC   %d\n", COMPILER_GCC);
    printf("OS_WINDOWS     %d\n", OS_WINDOWS);
    printf("OS_LINUX       %d\n", OS_LINUX);
    printf("OS_MAC         %d\n", OS_MAC);
    printf("ARCH_X64       %d\n", ARCH_X64);
    printf("ARCH_X86       %d\n", ARCH_X86);
    printf("ARCH_ARM       %d\n", ARCH_ARM);
    printf("ARCH_ARM64     %d\n", ARCH_ARM64);
    printf("CPP            %d\n", LANG_CPP);
    assert(1 > 100);

    printf("\n[Limit Constants]\n");
    // Minimum Limits (Signed)
    EVAL_PRINT(min_s8);
    EVAL_PRINT(min_s16);
    EVAL_PRINT(min_s32);
    EVAL_PRINT_LL(min_s64);

    // Maximum Limits (Signed)
    EVAL_PRINT(max_s8);
    EVAL_PRINT(max_s16);
    EVAL_PRINT(max_s32);
    EVAL_PRINT_LL(max_s64);

    // Maxmimum Limits (Unsigned)
    EVAL_PRINT_u(max_u8);
    EVAL_PRINT_u(max_u16);
    EVAL_PRINT_u(max_u32);
    EVAL_PRINT_ull(max_u64);

    // Generic printing
    gprint("\n[Generic Printing]");
    gprint(42);
    gprint("Hello world");
    gprint(( float ) 23123.3);
    gprint(( double ) 123123.61321232);

    // Base mem interface style malloc
    M_Arena arena = m_make_arena(m_malloc_base_memory());
    {
        // Take snapshop of current arena state
        M_Temp temp = m_begin_temp(&arena);

        // Action...
        int* arr = PUSH_ARRAY(&arena, int, 5);
        for (int i = 0; i < 5; i++)
        {
            arr[i] = 1 + i;
            gprint(arr[i]);
        }

        // Revert arena state to prior to action
        m_end_temp(temp);
    }

    gprint("\n========== ARRAY =========\n");

    ARRAY_TYPE(int) int_array;
    ARRAY_INIT(&int_array);

    for (int i = 0; i < 10; i++)
    {
        WRITE_ARRAY(&int_array, int, i);
    }

    for (int i = 0; i < 10; i++)
    {
        gprint(int_array.data[i]);
    }

    RELEASE_ARRAY(&int_array);

    gprint("\n========== TABLE  =========\n");

    CharTable table   = CharTable_make();
    bool      new_set = CharTable_set(&table, "foo", 100);
    if (new_set)
        gprint(CharTable_find(&table, "foo")->value);
    CharTable_set(&table, "foo", 200);
    gprint(CharTable_find(&table, "foo")->value);

    int* entry = PUSH_ARRAY(&arena, int, 1);
    bool found = CharTable_get(&table, "foo", entry);
    if (found)
    {
        gprint("Found");
        gprint(*entry);
    }
    else
        gprint("Not found");

    m_arena_release(&arena);
    return 0;
}
