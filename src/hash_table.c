/*
Author:     Elyashiv Horden  
Date:		15-1-2024	    
CR: 	    Yehonatan Ailon
*/

#include <assert.h>         /*assert*/
#include <stdlib.h>         /*malloc & free*/

#include "hash_table.h"     /*hash*/
#include "dll.h"            /*dll functionlity*/

#define SUCCESS (0)
#define FAIL (1)
#define FALSE (0)
#define TRUE (1)


struct hash_table
{
    dll_t** hash;
    size_t num_of_buckets;
    hash_function_t hash_function;
    is_same_key_t is_same_key;
};



/*                       FORWARD DECLARATION                          */
/******************************************************************** */
static dll_t** InitHashTable(dll_t** table, size_t num_of_buckets);
static void DestroyHashTable(dll_t** table, size_t num_of_buckets);
static int FreeList(void* data, void* arg);

/********************************************************************* */



/*                           API FUNCTION                               */
/********************************************************************** */
hash_table_t* HashCreate(size_t num_of_buckets, 
    hash_function_t hash_function, is_same_key_t is_same_key)
    {   
        hash_table_t* table = NULL;
        dll_t** hash = NULL;
        assert(hash_function);
        assert(is_same_key);

        table = (hash_table_t*)malloc(sizeof(hash_table_t));
        if (NULL == table)
        {
            return NULL;
        }

        hash = InitHashTable(hash, num_of_buckets);
        if (NULL == hash)
        {
            free (table);
            return NULL;
        }
        table->hash = hash;
        table->hash_function = hash_function;
        table->is_same_key = is_same_key;
        table->num_of_buckets = num_of_buckets;
        return table;
    }

void HashDestroy(hash_table_t* table)
{
    assert(table);

    DestroyHashTable(table->hash, table->num_of_buckets);
    free(table->hash);
    free(table);
}

int HashInsert(hash_table_t* table, void* key, void* value)
{
    size_t i = 0;
    dll_t* list = NULL;
    entry_t* new_entry = NULL;

    assert(table);
    assert(key);

    new_entry = (entry_t*)malloc(sizeof(entry_t));
    if (NULL == new_entry)
    {
        return FAIL;
    }

    new_entry->key = key;
    new_entry->value = value;

    i = table->hash_function(key);
    list = table->hash[i];

    if (NULL == DllInsert(list, DllBegin(list), new_entry))
    {
        free(new_entry);
        return FAIL;
    }

    return SUCCESS;
}

void HashRemove(hash_table_t* table, void* key)
{
    size_t i = 0;
    dll_t* list = NULL;
    dll_iterator_t element_to_remove = NULL;

    assert(table);
    assert(key);

    i = table->hash_function(key);
    list = table->hash[i];
    element_to_remove = DllFind(DllBegin(list), DllEnd(list), key, table->is_same_key);
    if (DllIsEqual(DllEnd(list), element_to_remove) == FALSE)
    {
        free(DllGetData(element_to_remove));
        DllRemove(element_to_remove);
    }
}

void* HashFind(const hash_table_t* table, void* key)
{
    size_t i = 0;
    dll_t* list = NULL;
    dll_iterator_t iter = NULL;

    assert(table);
    assert(key);

    i = table->hash_function(key);
    list = table->hash[i];
    iter = DllFind(DllBegin(list), DllEnd(list), key, table->is_same_key);
    if (DllIsEqual(DllEnd(list), iter))
    {
        return NULL;
    }
    
    return DllGetData(iter);
}

int HashForEach(hash_table_t* table, hash_operation_t function, void* args)
{
    size_t i = 0;
    int status = SUCCESS;
    dll_t* list = NULL;

    assert(table);
    assert(function);

    for (i = 0; i < table->num_of_buckets; ++i)
    {
        list = table->hash[i];
        if (NULL != list)
        {
            status = DllForEach(DllBegin(list), DllEnd(list), function, args);
        }
        if (SUCCESS != status)
        {
            return status;
        }
    }
    return status;
}

int HashIsEmpty(const hash_table_t* table)
{
    size_t i = 0;
    dll_t* list = NULL;

    assert(table);

    for (i = 0; i < table->num_of_buckets; ++i)
    {
        list = table->hash[i];
        if (NULL != list)
        {
            if (FALSE == DllIsEmpty(list))
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

size_t HashCount(const hash_table_t* table)
{
    size_t i = 0;
    size_t counter = 0;
    dll_t* list = NULL;

    assert(table);

    for (i = 0; i < table->num_of_buckets; ++i)
    {
        list = table->hash[i];
        if (NULL != list)
        {
            counter += DllSize(list);
        }
    }
    return counter;
}


/*                         STATIC FUNCTION                             */
/********************************************************************** */
static dll_t** InitHashTable(dll_t** table, size_t num_of_buckets)
{
    size_t i = 0;
    table = (dll_t**)malloc(sizeof(dll_t*) * num_of_buckets);

    if (NULL == table)
    {
        return NULL;
    }

    for (i = 0; i < num_of_buckets; ++i)
    {
        table[i] = DllCreate();
        if (NULL == table[i])
        {
            DestroyHashTable(table, i);
            return NULL;
        }
    }

    return table;
}
 
static void DestroyHashTable(dll_t** table, size_t num_of_buckets)
{
    size_t i = 0;
    for (i = 0; i < num_of_buckets; ++i)
    {
        DllForEach(DllBegin(table[i]), DllEnd(table[i]), FreeList, NULL);
        DllDestroy(table[i]);
    }
}

static int FreeList(void* data, void* arg)
{
    (void)arg;
    free(data);
    return SUCCESS;
}