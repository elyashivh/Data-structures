#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>		/*size_t*/

typedef struct node dll_node_t;
typedef struct list dll_t;
typedef dll_node_t* dll_iterator_t;

typedef enum
{
	OPERATION_FAIL = -1,
	SUCCESS
} status_t;


dll_t* DllCreate(void);


void DllDestroy(dll_t* list);


dll_iterator_t DllPushFront(dll_t* list, void* data);


dll_iterator_t DllPushBack(dll_t* list, void* data);

void* DllPopBack(dll_t* list); 

void* DllPopFront(dll_t* list);   

dll_iterator_t DllInsert(dll_t* list, dll_iterator_t iterator, void* data); /* Inserts before */

dll_iterator_t DllRemove(dll_iterator_t iterator);

dll_iterator_t DllFind(dll_iterator_t from, dll_iterator_t to, void* data, int (*Is_Match)(void*, void*));

status_t DllMultiFind(dll_t* out_params, dll_iterator_t from, dll_iterator_t to, void* data, int (*Is_Match)(void*, void*));

size_t DllSize(const dll_t* list);

int DllIsEmpty(const dll_t* list);

void* DllGetData(const dll_iterator_t iterator);

void DllSetData(dll_iterator_t iterator, void* data);

dll_iterator_t DllGetNext(const dll_iterator_t iterator);

dll_iterator_t DllGetPrev(const dll_iterator_t iterator);

dll_iterator_t DllBegin(const dll_t* list);

dll_iterator_t DllEnd(const dll_t* list);

status_t DllForEach(dll_iterator_t from, dll_iterator_t to, int (*operation_func)(void*, void*), void* args);

int DllIsEqual(dll_iterator_t iterator1, dll_iterator_t iterator2);

void DllSplice(dll_iterator_t iterator, dll_iterator_t from, dll_iterator_t to);

#endif /* end of header guard __DLL_H__ */
