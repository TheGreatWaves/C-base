#pragma once
#ifndef BASE_ARRAY
#define BASE_ARRAY

#include "types.h"
#include "utils.h"
#include "mem.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t count;
  size_t capacity;
  size_t elemsize;
} Array_Impl;

#define ArrayType(type) struct { Array_Impl impl; type *data; }
#define ArrayInit(arr) init_array(&arr.impl, sizeof(*arr.data))
void init_array(Array_Impl *impl, size_t elem_size);

#define free_array(pointer) \
  FREE_ARRAY(void*, (pointer)->data, 0); (pointer)->data = NULL

#define write_array(arr, type, entry) stmnt(                                         \
	if ((arr)->impl.capacity < ((arr)->impl.capacity+1))                               \
	{                                                                                  \
		size_t old_capacity = (arr)->impl.capacity;                                      \
		(arr)->impl.capacity = GROW_CAPACITY(old_capacity);                              \
		(arr)->data = GROW_ARRAY(type, (arr)->data, old_capacity, (arr)->impl.capacity); \
	}                                                                                  \
	(arr)->data[(arr)->impl.count] = (entry);                                          \
	(arr)->impl.count++;                                                               \
)


#endif /* BASE_ARRAY */

