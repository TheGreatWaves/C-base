#include <stdio.h> // Will remove this later.
#include "base.h"
#include "mem.h"

#define EvalPrint(x)    printf("%s = %d\n", #x, (S32)(x))
#define EvalPrintLL(x)  printf("%s = %ld\n", #x, (S64)(x))
#define EvalPrintU(x)   printf("%s = %u\n", #x, (U32)(x))
#define EvalPrintULL(x) printf("%s = %lu\n", #x, (U64)(x))

int main()
{
  printf("[Context]\n");
  printf("COMPILER_CL    %d\n", COMPILER_CL   );
  printf("COMPILER_CLANG %d\n", COMPILER_CLANG);
  printf("COMPILER_GCC   %d\n", COMPILER_GCC  );
  printf("OS_WINDOWS     %d\n", OS_WINDOWS    );
  printf("OS_LINUX       %d\n", OS_LINUX      );
  printf("OS_MAC         %d\n", OS_MAC        );
  printf("ARCH_X64       %d\n", ARCH_X64      );
  printf("ARCH_X86       %d\n", ARCH_X86      );
  printf("ARCH_ARM       %d\n", ARCH_ARM      );
  printf("ARCH_ARM64     %d\n", ARCH_ARM64    );
  printf("CPP            %d\n", LANG_CPP      );
  Assert(1 > 100);


  printf("\n[Limit Constants]\n");
  // Minimum Limits (Signed)
  EvalPrint(min_S8);
  EvalPrint(min_S16);
  EvalPrint(min_S32);
  EvalPrintLL(min_S64);

  // Maximum Limits (Signed)
  EvalPrint(max_S8);
  EvalPrint(max_S16);
  EvalPrint(max_S32);
  EvalPrintLL(max_S64);

  // Maxmimum Limits (Unsigned)
  EvalPrintU(max_U8);
  EvalPrintU(max_U16);
  EvalPrintU(max_U32);
  EvalPrintULL(max_U64);


  // Generic printing
  gprint("\n[Generic Printing]");
  gprint(42);
  gprint("Hello world");
  gprint((float)23123.3);
  gprint((double)123123.61321232);

  // Creating a memory arena
  MemoryArena arena = makeArena();
  freeArena(&arena);
  return 0; 
}
