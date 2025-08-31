#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__


#include <stddef.h> /* for size_t */

typedef struct node node_t;
typedef struct list list_t;
typedef node_t* iterator_t;

typedef enum
{
	OPERATION_FAIL = -1,
	SUCCESS
} status_t;


/*
	Description: the function will allocate a list, with a dummy end, and return it to the user.
	Args: None
	Return Value: pointer to the 
	Time Complexity: O(1)
	Space Complexity:O(1)
*/
list_t* SllCreate(void);

/*
	Description: the funtion will destroy the list, and remove and free each element in the list.
				every element or iterator will be freed.
	Args:poiter to the list.
	Return Value: void
	Time Complexity: O(n)
	Space Complexity: O(1)
*/
void SllDestroy(list_t* list);
/*
	Description: The function will insert an elemnt with the data given as argment to the list.
				 The element will be inserted before the iterator.
	Args: pointer to the list, iterator that the new element will be inserted before it, and pointer to data.
	
	Return Value: iterator to the element inserted
	Time Complexity:  O(1)
	Space Complexity: O(1)
*/
iterator_t SllInsert(list_t* list, iterator_t iterator, void* data);
/*
	Description: the fuction will remove the iterator recieved from the user, 
	and free the iterator pointed by the iterator recieved as an argument.
	 
	Args: iterator wished to be removed.
	Return Value: the next iterator.
	Time Complexity: O(1)
	Space Complexity: O(1)
*/
iterator_t SllRemove(iterator_t iterator);
/*
	Description: the function will iterate over the elements between "from" to "to" (excluding "to"),
	 and will return the first iterator holding the data that equals to the data recieved as an argument, using is_match.
	 if the function couldnt find such element, th function will return "to".
	Args: poiter to the beggining and pointer to the end of the search bounds, data to look for, and function pointer to matching function.
	Return Value: iterator holding the data looked for, or "to"
	Time Complexity:, O(n)
	Space Complexity:O(1)
*/
iterator_t SllFind(iterator_t from, iterator_t to, void* data, int (*is_match)(void*, void*));
/*
	Description: The function will return the size of the list, the amount of elements in the lit.
	Args: pointet to a const list.
	Return Value: the size of the list
	Time Complexity: O(n)
	Space Complexity:O(1)
*/
size_t SllSize(const list_t* list);
/*
	Description: the fuction will return whether the list is empty
	Args: pointer to const list
	Return Value: 1 if the list is empty, 0 otherwise.
	Time Complexity: O(1)
	Space Complexity: O(1)
*/
int SllIsEmpty(const list_t* list);
/*
	Description:the function will return the data held by the iterator
	Args: const iterator
	Return Value: pointer to the data held by the iterator
	Time Complexity: O(1)
	Space Complexity: O(1)
*/
void* SllGetData(const iterator_t iterator);
/*
	Description: the function will set the data held by the iterator to the data recieved as an arguement.
				the data will be saved by ref.
	Args: iterator, and data to set as the iterator's data
	Return Value: void
	Time Complexity: O(1)
	Space Complexity: O(1)
*/
void SllSetData(iterator_t iterator, void* data);
/*
	Description: The fuction will return the next iterator.
	Args: const iterator
	Return Value: iterator which is the next of the iterator recieved as an arguement
	Time Complexity: O(1)
	Space Complexity: O(1)
*/
iterator_t SllGetNext(const iterator_t iterator);
/*
	Description: the function will return an iteratorto the beggining of the list
	Args: cost list pointer
	Return Value: iterator to the beggining of the list
	Time Complexity:, O(1)
	Space Complexity: O(1)
*/
iterator_t SllBegin(const list_t* list);

/*
	Description: the function will return an iteratorto the end of the list
	Args: cost list pointer
	Return Value: iterator to the end of the list
	Time Complexity:, O(1)
	Space Complexity: O(1)
*/
iterator_t SllEnd(const list_t* list);
/*
	Description: The function will iterate over the list and will invoke the operation_func on each of the elements in the bounds,
				the function will be called with each element data and args.
				if operation func has failed for an element, the funtion will stop and return a status accordingly.
	Args: iterators to the beggining and end of th bounds, function pointer to invoke, and extra arguments to the functon.
	Return Value: status indicating if every operation func has succeeded.
	Time Complexity: O(n * operation_func) 
	Space Complexity:O(operation_func)
*/
status_t SllForEach(iterator_t from, iterator_t to, int (*operation_func)(void*, void*), void* args);
/*
	Description: the functon will return whether two iterators are equal by comparing addresses.
	Args: two iterators to compare
	Return Value: 1 if the iterators are equal, 0 otherwise
	Time Complexity: O(1)
	Space Complexity:O(1)
*/
int SllIsEqual(iterator_t iterator1, iterator_t iterator2);


void SllAppend(list_t* sll1, list_t* sll2);











#endif /* end of header guard __SINGLY_LINKED_LIST_H__ */
