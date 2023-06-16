#pragma once
#ifndef BASE_HASHTABLE
#define BASE_HASHTABLE

#include "types.h"
#include "utils.h"

#define TABLE_MAX_LOAD 0.75

typedef struct
{
    size_t count;
    size_t capacity;
} Table_Impl;

#define DECLARE_MAKE_TABLE(name, val_type)                                                         \
    name glue(name, _make)()                                                                       \
    {                                                                                              \
        name t;                                                                                    \
        TABLE_INIT(&t);                                                                            \
        return t;                                                                                  \
    }

#define DECLARE_FIND_TABLE(name, val_type)                                                         \
    glue(name, _entry) * glue(name, _find)(name * table, char* key)                                \
    {                                                                                              \
        u32 index = hash_string(key) % table->impl.capacity;                                       \
        for (;;)                                                                                   \
        {                                                                                          \
            glue(name, _entry)* entry = &table->entries[index];                                    \
            if (entry->key == NULL || strcmp(entry->key, key) == 0)                                \
            {                                                                                      \
                return entry;                                                                      \
            }                                                                                      \
            index = (index + 1) % table->impl.capacity;                                            \
        }                                                                                          \
    }

#define DECLARE_GET_TABLE(name, val_type)                                                          \
    bool glue(name, _get)(name * table, char* key, val_type* value)                                \
    {                                                                                              \
        if (table->impl.count == 0)                                                                \
            return false;                                                                          \
        glue(name, _entry)* entry = glue(name, _find)(table, key);                                 \
        if (entry->key == NULL)                                                                    \
            return false;                                                                          \
        *value = entry->value;                                                                     \
        return true;                                                                               \
    }

#define DECLARE_ADJUST_CAPACITY_TABLE(name, val_type)                                              \
    void glue(name, _adjust_capacity)(name * table, size_t capacity)                               \
    {                                                                                              \
        glue(name, _entry)* entries = ALLOCATE(glue(name, _entry), capacity);                      \
        for (int i = 0; i < capacity; i++)                                                         \
        {                                                                                          \
            entries[i].key = NULL;                                                                 \
        }                                                                                          \
                                                                                                   \
        for (int i = 0; i < table->impl.capacity; i++)                                             \
        {                                                                                          \
            glue(name, _entry)* entry = &table->entries[i];                                        \
            if (entry->key == NULL)                                                                \
                continue;                                                                          \
            glue(name, _entry)* dest = glue(name, _find)(table, entry->key);                       \
            dest->key                = entry->key;                                                 \
            dest->value              = entry->value;                                               \
        }                                                                                          \
                                                                                                   \
        FREE_ARRAY(void*, table->entries, table->impl.capacity);                                   \
        table->entries       = entries;                                                            \
        table->impl.capacity = capacity;                                                           \
    }

#define DECLARE_SET_TABLE(name, val_type)                                                          \
    bool glue(name, _set)(name * table, char* key, val_type val)                                   \
    {                                                                                              \
        if (table->impl.count + 1 > table->impl.capacity * TABLE_MAX_LOAD)                         \
        {                                                                                          \
            size_t capacity = GROW_CAPACITY(table->impl.capacity);                                 \
            glue(name, _adjust_capacity)(table, capacity);                                         \
        }                                                                                          \
        glue(name, _entry)* entry = glue(name, _find)(table, key);                                 \
        bool is_new_key           = entry->key == NULL;                                            \
        if (is_new_key)                                                                            \
            table->impl.count++;                                                                   \
        entry->key   = key;                                                                        \
        entry->value = val;                                                                        \
        return is_new_key;                                                                         \
    }

// Note: Evil anonymous struct
#define DECLARE_TABLE(name, val_type)                                                              \
    typedef struct                                                                                 \
    {                                                                                              \
        char*    key;                                                                              \
        val_type value;                                                                            \
    } glue(name, _entry);                                                                          \
                                                                                                   \
    typedef struct                                                                                 \
    {                                                                                              \
        Table_Impl impl;                                                                           \
        glue(name, _entry) * entries;                                                              \
    } name;                                                                                        \
    DECLARE_MAKE_TABLE(name, val_type)                                                             \
    DECLARE_FIND_TABLE(name, val_type)                                                             \
    DECLARE_ADJUST_CAPACITY_TABLE(name, val_type)                                                  \
    DECLARE_SET_TABLE(name, val_type)                                                              \
    DECLARE_GET_TABLE(name, val_type)

#define TABLE_INIT(table) stmnt(init_table_impl(&((table)->impl)); (table)->entries = NULL;)

#define FREE_TABLE(table)                                                                          \
    stmnt(FREE_ARRAY(void*, (table)->entries, 0) init_table_impl(&table.impl);)

void init_table_impl(Table_Impl* table_impl);

#endif /* BASE_HASHTABLE */
