#include "array.h"

void init_array(Array_Impl* impl, size_t elem_size)
{
    impl->count    = 0;
    impl->capacity = 0;
    impl->elemsize = elem_size;
}
