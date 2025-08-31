#include <stdlib.h>		 /* malloc and free*/
#include <assert.h>		 /* assert */

#include "singly_linked_list.h"

typedef enum 
{
	FALSE,
	TRUE
}bool_t;

struct node
{
	void* data;
	node_t* next;
};

struct list
{
	node_t* head;
	node_t* tail;
};

static iterator_t CreateNode(void);
static int SizeCounter(void* data, void* args);


list_t* SllCreate(void)
{
	iterator_t dummy = NULL;	
	list_t* list = malloc(sizeof(list_t));
	if (NULL == list)
	{
		return NULL;
	}
	
	dummy = malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		free(list);
		return NULL;
	}
	dummy->data = list;
	dummy->next = NULL;
	list->head = dummy;
	list->tail = dummy;
	
	return list;
}


void SllDestroy(list_t* list)
{
	iterator_t iter = NULL;
	assert (NULL != list);
	
	iter = SllBegin(list);
	
	while (NULL	!= SllGetNext(iter))
	{
		iter = SllRemove(iter);
	}
	
	iter->data = NULL;
	iter->next = NULL;
	list->head = NULL;
	list->tail = NULL;
	
	free(iter);
	free(list);
}


iterator_t SllInsert(list_t* list, iterator_t iterator, void* data)
{
	iterator_t new_node = NULL;
	assert(NULL != list);
	assert(NULL != iterator);
	
	new_node = CreateNode();
	if (NULL == new_node)
	{
		return NULL;
	}

	
	SllSetData(new_node, iterator->data);
	new_node->next = iterator->next;
	
	SllSetData(iterator, data);
	iterator->next = new_node;
	
	if (iterator == list->tail)
	{
		list->tail = iterator->next;
	}
	
	return iterator;
}


iterator_t SllRemove(iterator_t iterator)
{
	iterator_t temp = NULL;
	assert(NULL != iterator);
	
	if (NULL == SllGetNext(iterator))
	{
		return iterator;
	}
	temp = SllGetNext(iterator);
	
	SllSetData(iterator, SllGetData(temp));
	iterator->next = SllGetNext(temp);
	
	if (NULL == SllGetNext(temp))
	{
		((list_t*)temp->data)->tail = iterator;
	}
	temp->data = NULL;
	temp->next = NULL;
	free(temp);
	
	return iterator;
}


iterator_t SllFind(iterator_t from, iterator_t to, void* data, int (*is_match)(void*, void*))
{
	assert(NULL != from);
	assert(NULL != to);
	
	while (FALSE == SllIsEqual(from, to))
	{
		if (TRUE == is_match(SllGetData(from), data))
		{
			return from;
		}
		from = SllGetNext(from);
	}
	return to;
}



size_t SllSize(const list_t* list)
{
	size_t counter = 0;
	assert(NULL != list);
	
	SllForEach(SllBegin(list), SllEnd(list), SizeCounter, &counter);
	
	return counter;
}


int SllIsEmpty(const list_t* list)
{
	assert(NULL != list);
	
	return (SllBegin(list) == SllEnd(list));
}



void* SllGetData(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->data;
}


void SllSetData(iterator_t iterator, void* data)
{
	assert(NULL != iterator);
	
	iterator->data = data;
}


iterator_t SllGetNext(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->next;
}


iterator_t SllBegin(const list_t* list)
{
	assert(NULL != list);
	
	return list->head;
}


iterator_t SllEnd(const list_t* list)
{
	assert(NULL != list);
	
	return list->tail;
}


status_t SllForEach(iterator_t from, iterator_t to, int (*operation_func)(void*, void*), void* args)
{
	assert(NULL != from);
	assert(NULL != to);
	
	while (FALSE == SllIsEqual(from, to))
	{
		if (SUCCESS != operation_func(from->data, args))
		{
			return OPERATION_FAIL;
		}
		from = SllGetNext(from);
	}
	
	return SUCCESS;
}


int SllIsEqual(iterator_t iterator1, iterator_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	
	return iterator1 == iterator2;	
}


static iterator_t CreateNode(void)
{
	iterator_t node = malloc(sizeof(node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = NULL;
	node->next = NULL;
	
	return node;
}


void SllAppend(list_t* sll1, list_t* sll2)
{
	assert(NULL != sll1);
	assert(NULL != sll2);
	
	sll1->tail->data = sll2->head->data;
	sll1->tail->next = sll2->head->next;
	sll1->tail = sll2->tail;
	
	sll2->head->data = sll2;
	sll2->head->next = NULL;
	sll2->tail = sll2->head;
	
	sll1->tail->data = sll1;
}


static int SizeCounter(void* data, void* args)
{
	data = (void*)data;
	++(*(size_t*)args);
	return SUCCESS;
}




