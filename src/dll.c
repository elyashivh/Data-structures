#include <stddef.h>		/*size_t*/
#include <assert.h>		/*assert*/
#include <stdlib.h>		 /* malloc and free*/

#include "dll.h"

typedef enum 
{
	FALSE,
	TRUE
}bool_t;

struct node
{
	void* data;
	dll_node_t* next;
	dll_node_t* prev;
};

struct list
{
	dll_node_t head;
	dll_node_t tail;
};

static void DllSetNext(dll_iterator_t iterator1, dll_iterator_t iterator2);
static void DllSetPrev(dll_iterator_t iterator1, dll_iterator_t iterator2);
static dll_iterator_t CreateNode(void* data);
static int SizeCounter(void* data, void* args);

dll_t* DllCreate(void)
{
	dll_t* dlist = NULL;
	
	dlist = (dll_t*)malloc(sizeof(dll_t));
	if (NULL == dlist)
	{
		return NULL;
	}

	dlist->head.prev = NULL;
	dlist->head.data = NULL;
	dlist->head.next = &dlist->tail;
	
	dlist->tail.prev = &dlist->head;
	dlist->tail.data = NULL;
	dlist->tail.next = NULL;
	
	return dlist;
}	

void DllDestroy(dll_t* list)
{
	dll_iterator_t temp = NULL;
	assert(NULL != list);
	
	temp = DllBegin(list);
	while (NULL != DllGetNext(temp))
	{
		temp = DllRemove(temp);
	}
	
	list->head.prev = NULL;
	list->head.next = NULL;
	list->tail.prev = NULL;
	list->tail.next = NULL;	
	
	free(list);
}


dll_iterator_t DllPushFront(dll_t* list, void* data)
{
	assert(NULL != list);
	
	return DllInsert(list, DllBegin(list), data);
}


dll_iterator_t DllPushBack(dll_t* list, void* data)
{
	assert(NULL != list);
	
	return DllInsert(list, DllEnd(list), data);
}


void* DllPopBack(dll_t* list)
{
	void* ans = NULL;
	assert(NULL != list);
	
	ans = DllGetData(DllGetPrev(DllEnd(list)));
	DllRemove(DllGetPrev(DllEnd(list)));
	
	return ans;
}


void* DllPopFront(dll_t* list)
{
	void* ans = NULL;
	assert(NULL != list);
	
	ans = DllGetData(DllBegin(list));
	DllRemove(DllBegin(list));
	
	return ans;
}   

dll_iterator_t DllInsert(dll_t* list, dll_iterator_t iterator, void* data) /* Inserts before */
{
	dll_iterator_t new_node = NULL;
	assert(NULL != list);
	assert(NULL != iterator);
	
	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return DllEnd(list);
	}
	new_node->next = iterator;
	new_node->prev = iterator->prev;
	
	new_node->prev->next = new_node;
	iterator->prev = new_node;	
	
	return new_node;
}

dll_iterator_t DllRemove(dll_iterator_t iterator)
{
	dll_iterator_t temp = NULL;
	assert(NULL != iterator);
	
	temp = DllGetNext(iterator);

	
	DllSetNext(DllGetPrev(iterator), DllGetNext(iterator));
	DllSetPrev(DllGetNext(iterator), DllGetPrev(iterator));
	
	DllSetNext(iterator, NULL);
	DllSetPrev(iterator, NULL);
	
	free(iterator);
	return temp;
}

dll_iterator_t DllFind(dll_iterator_t from, dll_iterator_t to, void* data, int (*Is_Match)(void*, void*))
{

	assert(NULL != from);
	assert(NULL != to);
	
	while(FALSE == DllIsEqual(from, to))
	{
		if (Is_Match(DllGetData(from), data))
		{
			return from;
		}
		from = DllGetNext(from);
	}
	
	return to;
}

status_t DllMultiFind(dll_t* out_params, dll_iterator_t from, dll_iterator_t to, void* data, int (*Is_Match)(void*, void*))
{
/*	dll_iterator_t temp = NULL;*/
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != out_params);
	
	from = DllFind(from, to, data, Is_Match);
	
	
	while (FALSE == DllIsEqual(from, to))
	{
		DllPushBack(out_params, DllGetData(from));
		from = DllGetNext(from);
		from = DllFind(from, to, data, Is_Match);
	}

	return SUCCESS;
}


size_t DllSize(const dll_t* list)
{
	size_t counter = 0;
	assert(NULL != list);
	
	DllForEach(DllBegin(list), DllEnd(list), SizeCounter, &counter);
	
	return counter;
}


int DllIsEmpty(const dll_t* list)
{
	assert(NULL != list);
	
	return DllIsEqual(DllBegin(list), DllEnd(list));
}


void* DllGetData(const dll_iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->data;
}


void DllSetData(dll_iterator_t iterator, void* data)
{
	assert(NULL != iterator);
	
	iterator->data = data;
}


dll_iterator_t DllGetNext(const dll_iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->next;
}


dll_iterator_t DllGetPrev(const dll_iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->prev;
}


dll_iterator_t DllBegin(const dll_t* list)
{
	assert(NULL != list);
	
	return DllGetNext((const dll_iterator_t)&list->head);
}


dll_iterator_t DllEnd(const dll_t* list)
{
	return (const dll_iterator_t)&list->tail;
}


status_t DllForEach(dll_iterator_t from, dll_iterator_t to, int (*operation_func)(void*, void*), void* args)
{
	status_t ans = SUCCESS;
	
	assert(NULL != from);
	assert(NULL != to);
	
	while (FALSE == DllIsEqual(from, to))
	{
		ans = operation_func(DllGetData(from), args);
		if (SUCCESS != ans)
		{
			return ans;
		}
		from = DllGetNext(from);
	}
	
	return ans;

}


int DllIsEqual(dll_iterator_t iterator1, dll_iterator_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	
	return iterator1 == iterator2;
}


void DllSplice(dll_iterator_t iterator, dll_iterator_t from, dll_iterator_t to)
{
	dll_iterator_t temp = NULL;
	
	assert(NULL != iterator);
	assert(NULL != free);
	assert(NULL != to);
	
	iterator = DllGetPrev(iterator);
	temp = DllGetPrev(from);
	
	DllSetNext(DllGetPrev(from), to);
	
	DllSetPrev(from, iterator);
	DllSetNext(DllGetPrev(to), DllGetNext(iterator));
	DllSetNext(iterator, from);
	DllSetPrev(to, temp);
}


static void DllSetNext(dll_iterator_t iterator1, dll_iterator_t iterator2)
{
	iterator1->next = iterator2;
}


static void DllSetPrev(dll_iterator_t iterator1, dll_iterator_t iterator2)
{
	iterator1->prev = iterator2;
}


static dll_iterator_t CreateNode(void* data)
{
	dll_iterator_t new_node = (dll_iterator_t)malloc(sizeof(dll_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	return new_node;
}

static int SizeCounter(void* data, void* args)
{
	data = (void*)data;
	++(*(size_t*)args);
	
	return SUCCESS;
}













