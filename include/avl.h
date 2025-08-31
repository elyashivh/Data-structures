#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>
/*
    Version 1.0.0
*/

/*
    Description: This comperator compares the data with the unique key.
                 Key must be unique.
*/
typedef int(*avl_comp_t)(const void* data, const void* key);
/*
    Description: Operation function that is performed on the data.
                Args could be uses as another param to Operation function.
                Args could be NULL if not in use.
*/
typedef int(*avl_operation_t)(void* data, void* args);

typedef enum traversal_type
{
    IN_ORDER = 0,
    POST_ORDER,
    PRE_ORDER
} traversal_type_t;

typedef struct avl avl_t;


/*
    Description:        Creation of the AVL ds. 
						This function allocates & 
						initiates the AVL tree in memory.
					    Root is set to NULL.
    Args:               Comperator for use in insertion and searching.
    Return value:       Pointer to the allocated struct on success, NULL on failure.
    Time complexity:    O(1).
    Space complexity:   O(1).
*/
avl_t* AVLCreate(avl_comp_t comparator);

/*
    Description:        Destroys the AVL and frees all allocated memory.
    Args:               A pointer to the AVL to destroy.
    Return value:       None.
    Time complexity:    O(n)/O(nlogn).
    Space complexity:   O(1).
*/
void AVLDestroy(avl_t* tree);

/*
    Description:        Adds a new element to the tree.
    Args:               Tree - The AVL a new element is added to.
                        Data - The data of the new element added.
                        Key - unique identifier of the data. 
    Return value:       0 if insertion succeed or non zero value if failed.
    Time complexity:    O(log(n)).
    Space complexity:   O(1).
*/
int AVLInsert(avl_t* tree, void* data, void* key); /* balance func */

/*
    Description:        Removes a node from the tree.
    Args:               A pointer to the AVL tree.
                        Key - unique identifier of the data to be removed.
    Return value:       None.
    Time complexity:    O(log(n)).
    Space complexity:   O(1).
*/
void AVLRemove(avl_t* tree, void* key); /* balance func */

/*
    Description:        Find the node according to data supplied within the AVL tree.
						This function using the Comparator function to compare. (reffer AVLCreate)
						Case not found - NULL is returned.
    Args:               Pointer to the AVL ds, data to find.
                        Key - unique identifier of the data to find.
    Return value:       A pointer to the data.
    Time complexity:    O(log(n)).
    Space complexity:   O(log(n)).
*/
void* AVLFind(avl_t* tree, void* key);

/*
    Description:        Performs an operation for each node in the tree. 
    Args:               A pointer to the AVL tree, 
                        a pointer to an operation function,
                        a pointer to args to use in the operation function.
    Return value:       Status of operation execution, either success or fail. 
    Time complexity:    O(operation) * O(n)
    Space complexity:   
*/
int AVLForeach(avl_t* tree, avl_operation_t operation, void* args, traversal_type_t traversal_type);

/*
    Description:        Checks if the tree has no nodes.
    Args:               A pointer to the AVL tree.
    Return value:       1 if empty, 0 otherwise. 
    Time complexity:    O(1).
    Space complexity:   O(1).
*/
int AVLIsEmpty(const avl_t* tree);

/*
    Description:        Gets the size of nodes within the tree.
    Args:               A pointer to the AVL tree. 
    Return value:       The number of nodes in the tree.
    Time complexity:    O(n)/O(nlogn).
    Space complexity:   O(1).
*/
size_t AVLSize(const avl_t* tree);

/*
    Description:        Gets the height of the tree, which is the max size of nodes
                        from the root to the any leaf.
    Args:               A pointer to the AVL tree.
    Return value:       The height of the tree.
    Time complexity:    O(1).
    Space complexity:   O(1).
*/
size_t AVLHeight(const avl_t* tree);

#endif  /* __AVL_H__ */