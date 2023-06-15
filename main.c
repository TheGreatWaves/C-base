#include "array.h"
#include "base.h"
#include "hashtable.h"
#include "mem_malloc.h"
#include "utils.h"
#include <stdio.h> // Will remove this later.

#define eval_print(x)     printf("%s = %d\n", #x, ( s32 ) (x))
#define eval_print_ll(x)  printf("%s = %ld\n", #x, ( s64 ) (x))
#define eval_print_u(x)   printf("%s = %u\n", #x, ( u32 ) (x))
#define eval_print_ull(x) printf("%s = %lu\n", #x, ( u64 ) (x))

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
    eval_print(min_s8);
    eval_print(min_s16);
    eval_print(min_s32);
    eval_print_ll(min_s64);

    // Maximum Limits (Signed)
    eval_print(max_s8);
    eval_print(max_s16);
    eval_print(max_s32);
    eval_print_ll(max_s64);

    // Maxmimum Limits (Unsigned)
    eval_print_u(max_u8);
    eval_print_u(max_u16);
    eval_print_u(max_u32);
    eval_print_ull(max_u64);

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
        int* arr = push_array(&arena, int, 5);
        for (int i = 0; i < 5; i++)
        {
            arr[i] = 1 + i;
            gprint(arr[i]);
        }

        // Revert arena state to prior to action
        m_end_temp(temp);
    }
    m_arena_release(&arena);

    gprint("\n========== ARRAY =========\n");

    ArrayType(int) int_array;
    ArrayInit(&int_array);

    for (int i = 0; i < 10; i++)
    {
        write_array(&int_array, int, i);
    }

    for (int i = 0; i < 10; i++)
    {
        gprint(int_array.data[i]);
    }

    free_array(&int_array);

    gprint("\n========== TABLE  =========\n");


    CharTable table = CharTable_make();

    bool new_set = CharTable_set(&table, "karan", 69);

    if (new_set) gprint(CharTable_find(&table, "karan")->value);

    CharTable_set(&table, "karan", 269);
    gprint(CharTable_find(&table, "karan")->value);
    return 0;
}
