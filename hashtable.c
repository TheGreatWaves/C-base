#include "hashtable.h"

void init_table_impl(Table_Impl* table_impl)
{
    table_impl->count    = 0;
    table_impl->capacity = 0;
}
