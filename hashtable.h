#pragma once
#ifndef BASE_HASHTABLE
#define BASE_HASHTABLE

#include "types.h"
#include "utils.h"

#define TABLE_MAX_LOAD 0.75

typedef struct {
  size_t count;
	size_t capacity;
} Table_Impl;

// Note: Evil anonymous struct
#define DECLARE_TABLE(name, val_type)                                   \
	typedef struct                                                        \
	{                                                                     \
			char* key;                                                        \
			val_type value;                                                   \
	} name##_entry;                                                       \
                                                                        \
  typedef struct                                                        \
	{                                                                     \
		Table_Impl impl;                                                    \
		name##_entry* entries;                                              \
	} name;                                                               \
                                                                        \
	name name##_make()                                                    \
{                                                                       \
	name t;                                                               \
	TableInit(&t);                                                        \
return t;                                                               \
}                                                                       \
                                                                        \
	name##_entry* name##_find(name* table, char* key)                     \
	{                                                                     \
		u32 index = hash_string(key) % table->impl.capacity;                \
		for (;;)                                                            \
		{                                                                   \
			name##_entry* entry = &table->entries[index];                     \
			if (entry->key==NULL || strcmp(entry->key, key)==0)               \
			{                                                                 \
				return entry;                                                   \
			}                                                                 \
			index = (index + 1) % table->impl.capacity;                       \
		}                                                                   \
	}                                                                     \
	void name##_adjust_capacity(name* table, size_t capacity)             \
	{                                                                     \
	  name##_entry* entries = ALLOCATE(name##_entry, capacity);           \
		for (int i=0; i<capacity; i++)                                      \
		{                                                                   \
		  entries[i].key = NULL;                                            \
		}                                                                   \
                                                                        \
	  for (int i = 0; i < table->impl.capacity; i++)                      \
		{                                                                   \
	    name##_entry* entry = &table->entries[i];                         \
	    if (entry->key == NULL) continue;                                 \
	    name##_entry* dest = name##_find(table, entry->key);              \
	    dest->key = entry->key;                                           \
	    dest->value = entry->value;                                       \
	  }                                                                   \
                                                                  			\
		FREE_ARRAY(void*, table->entries, table->impl.capacity);            \
		table->entries = entries;                                           \
		table->impl.capacity = capacity;                                    \
	}                                                                     \
                                                                        \
	bool name##_set(name* table, char* key, val_type val)                 \
	{                                                                     \
	  if (table->impl.count + 1 > table->impl.capacity * TABLE_MAX_LOAD)  \
		{                                                                   \
	    size_t capacity = GROW_CAPACITY(table->impl.capacity);            \
	    name##_adjust_capacity(table, capacity);                          \
	  }                                                                   \
		name##_entry* entry = name##_find(table, key);                      \
		bool is_new_key = entry->key==NULL;                                 \
		if (is_new_key) table->impl.count++;                                \
		entry->key = key;                                                   \
		entry->value = val;                                                 \
		return is_new_key;                                                  \
	}


#define TableInit(table) stmnt(      \
	init_table_impl(&((table)->impl)); \
	(table)->entries = NULL;           \
)

#define free_table(table) stmnt(         \
	FREE_ARRAY(void*, (table)->entries, 0) \
	init_table_impl(&table.impl);          \
)	

#define table_set(table, k, v) stmnt(                              \
	if (table.impl.count + 1 > table.impl.capacity * TABLE_MAX_LOAD) \
	{                                                                \
		size_t capacity = GROW_CAPACITY(table.impl.capacity);          \
		adjustCapacity(table, capacity);                               \
	}                                                                \
  u32 index = hash_string(k) % table.impl.capacity;                \
	for (;;)                                                         \
  {                                                                \
		int key_not_found = (table.entries[index].key == NULL);        \
		int key_found = strcmp(table.entries[index].key, k)==0;        \
		if (key_found || key_not_found)                                \
		{                                                              \
			if (key_not_found)                                           \
		  {                                                            \
			  table.impl.count++;                                        \
      }                                                            \
			table.entries[index].key = k;                                \
			table.entries[index].value = v;                              \
			break;                                                       \
		}                                                              \
		index = (index + 1) % table.impl.capacity;                     \
	}                                                                \
)

void init_table_impl(Table_Impl* table_impl);

#endif /* BASE_HASHTABLE */
