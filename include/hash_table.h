/*
    Version 1.0.1
*/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>
#include "dll.h"

typedef size_t (*hash_function_t)(void* key);
typedef int (*hash_operation_t)(void* data, void* args);
typedef int (*is_same_key_t)(void* entry, void* key);

typedef struct hash_table hash_table_t;

typedef struct entry
{
    void* key;
    void* value;
}entry_t;

/*
    Description:        This function creates the HashTable ds.
                        It uses hash_function and is_same_key functions (refer typedefs).
    Args:               Size - the size of the table.
                        Hash_function - function that returns the index within the table,
                                        according to the key.
                        Is_same_key - function that comapres between two entries' keys.
    Return value:       Pointer to the ds created on success, NULL otherwise.
    Time complexity:    O(1).
    Space complexity:   O(size).
*/
hash_table_t* HashCreate(size_t num_of_buckets, 
    hash_function_t hash_function, is_same_key_t is_same_key);

/*
    Description:        This function destroys the HashTable ds.
    Args:               Table - pointer to the ds.
    Return value:       None.
    Time complexity:    O(Count). (refer HashCount)
    Space complexity:   O(1).
*/
void HashDestroy(hash_table_t* table);

/*
    Description:        Insert key,value entry in the correct position,
                        according to the HashFunction. 
                        *NOTE* case key already existed - undefined behaviour.
    Args:               Table - pointer to the ds.
                        Key - the unique identifier.
                        Value - the value to insert.
    Return value:       0 on success, 1 otherwise.
    Time complexity:    O(1).
    Space complexity:   O(1).
*/
int HashInsert(hash_table_t* table, void* key, void* value); /* O(1) */ 

/*
    Description:        Removes an entry from the HashTable according to
                        the key. (refer is_same_key)
    Args:               Table - pointer to the ds.
                        Key - the unique identifier.
    Return value:       None.
    Time complexity:    O(1).
    Space complexity:   O(1).
*/
void HashRemove(hash_table_t* table, void* key);  /* O(1) */

/*
    Description:        Checks if an element with a given key is exists in the hash table.    
    Args:               table - A pointer to the checked table.
    Return value:       If found - A pointer to the data matches the given key.
                        If not found - NULL.
    Time complexity:    O(1) in average case.
                        O(num of elements) in worst case.
    Space complexity:   O(1)
*/
void* HashFind(const hash_table_t* table, void* key);/* O(1) */

/*
    Description:        Performs an operation function on each element in the
                        hash table.
    Args:               table- pointer to the hash table.
                        function- pointer to function to be performed.
                        args- additional arguments for the operation function.
    Return value:       Returns 0 if all operations were successfull, 
                        1 otherwise.
    Time complexity:    O(1)
    Space complexity:   O(1)
*/
int HashForEach(hash_table_t* table, hash_operation_t function, void* args);

/*
    Description:        Checks if the hash table has no elements.       
    Args:               Table - pointer to the ds.
    Return value:       Non zero value if the hash table is empty, zero otherwise.    
    Time complexity:    O(num of buckets).
    Space complexity:   O(1).
*/
int HashIsEmpty(const hash_table_t* table);

/*
    Description:        Counts the numbers of elements within the HashTable.
    Args:               Table- pointer to the hash_table.               
    Return value:       The number of elements counted.
    Time complexity:    O(num of buckets + number of elements).
    Space complexity:   O(1)
*/
size_t HashCount(const hash_table_t* table);



/* advanced
HashLoadBalance
HashSD 
*/
#endif /* __HASH_TABLE_H__ */


 