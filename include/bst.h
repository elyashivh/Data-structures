#ifndef __BST_H__
#define __BST_H__


#include <stddef.h>

typedef int (*bst_comp_t)(void*, void*);
typedef int (*bst_operation_t)(void*, void*);

typedef struct node* iterator_t;
typedef struct bst bst_t;

typedef enum status
{
	OPERATION_FAILED = -1,
	SUCCESS = 0
} status_t;


/*
	Description: 	Create and init the tree DB. 		
	Args:			comparator - A function to sort the tree.
	Return Value:	Pointer to the new tree DS.
	Time Complexity:	O(1).
	Space Complexity:	O(1).
*/
bst_t* BSTCreate(bst_comp_t comparator);

/*
	Description: 		Destroy tree DB.	
	Args:				Pointer to tree to be destroied.	
	Return Value:		None.
	Time Complexity:	O(?).
	Space Complexity:	O(1).
*/
void BSTDestroy(bst_t* tree);

/*
	Description:   		Insert new element to the tree.
	Args:		  		Pointer to a tree and pointer to data to be insert.
	Return Value:  		Pointer to the added element.
	Time Complexity:	O(logN).
	Space Complexity:	O(1).
*/
iterator_t BSTInsert(bst_t* tree, void* data);

/*
	Description: 		Remove an element from the tree
	Args:				Pointer to the element to remove.
	Return Value:	    None.
	Time Complexity:	O(logN).
	Space Complexity:	O(1).
*/
void BSTRemove(iterator_t iterator);

/*
	Description: 		Get the stored data in some element.	
	Args:				Pointer to the element.
	Return Value:	    Pointer fot the data.
	Time Complexity:	O(1).
	Space Complexity:	O(1).
*/
void* BSTGetData(const iterator_t iterator);

/*
	Description: 		Find an element which contain a specific data.	
	Args:				Pointer to the tree and Pointer for the data to look for
	Return Value:	    Pointer to an element which the same data
	Time Complexity:	O(logN).
	Space Complexity:	O(1).
*/
iterator_t BSTFind(const bst_t* tree, void* data);

/*
	Description: 		Make some operation for range of elemetns
	Args:				Pointers to start and to the end of the range.
						Pointers to function operation.
						Pointers to args fot the function.
	Return Value:	    Status function execution.
	Time Complexity:	O(NlogN).
	Space Complexity:	O(1).
*/
status_t BSTForEach(iterator_t from, iterator_t to, bst_operation_t operation, void* args);

/*
	Description: 		Get the tree size.
	Args:				Pointer to the tree.
	Return Value:	    The tree size.
	Time Complexity:	O(NlogN).
	Space Complexity:	O(1).
*/
size_t BSTSize(const bst_t* tree);

/*
	Description: 		Check if the tree is empty.
	Args:				Pointer to the tree.
	Return Value:	    1 if is empty, 0 otherwise.
	Time Complexity:	O(1).
	Space Complexity:	O(1).
*/
int BSTIsEmpty(const bst_t* tree);

/*
	Description: 		Check if 2 elements is equal.
	Args:				Pointer to 2 elements.
	Return Value:	    1 if equal, 0 otherwise.
	Time Complexity:	O(N^2).
	Space Complexity:	O(1).
*/
int BSTIsEqual(const iterator_t iter1, const iterator_t iter2);

/*
	Description: 		Get the prev element in the tree.	
	Args:				Pointer to an element.
	Return Value:	    pointer to the ptev element.
	Time Complexity:	O(logN).
	Space Complexity:	O(1).
*/
iterator_t BSTPrev(const iterator_t iterator);

/*
	Description: 		Get the next iterator	
	Args:				Pointer to an element.
	Return Value:	    Pointer to the next iterator in the Tree
	Time Complexity:	O(logN).
	Space Complexity:	O(1).
*/
iterator_t BSTNext(const iterator_t iterator);

/*
	Description: 		Get the first element in the tree.
	Args:				Pointer to the tree.
	Return Value:	    Pointer to the first element.
	Time Complexity:	O(1).
	Space Complexity:	O(1).
*/
iterator_t BSTBegin(const bst_t* tree);

/*
	Description: 		Get the last element in the tree (dummy-root)
	Args:				Pointer to the tree.
	Return Value:	    Pointer to the last element.
	Time Complexity:	O(1).
	Space Complexity:	O(1).
*/
iterator_t BSTEnd(const bst_t* tree);

#endif /* end of header guard*/
