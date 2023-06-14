#pragma once
#ifndef BASE_HASHTABLE
#define BASE_HASHTABLE

#include "types.h"
#include "utils.h"

typedef struct {
  size_t count;
	size_t capacity;
} Table_Impl;

// Note: Evil anonymous struct
#define TableType(key_type, val_type) \
	struct                              \
	{                                   \
		Table_Impl impl;                  \
		struct {                          \
			key_type keys;                  \
			val_type values;                \
		}* entries;                       \
	}

#define TableInit(table) stmnt( \
	init_table_impl(&((table)->impl)); \
	(table)->entries = NULL;        \
)

#define free_table(table) stmnt(         \
	FREE_ARRAY(void*, (table)->entries, 0) \
	init_table_impl(&table.impl);          \
)	

void init_table_impl(Table_Impl* table_impl);

#endif /* BASE_HASHTABLE */
