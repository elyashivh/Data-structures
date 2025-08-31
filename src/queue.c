#include <stddef.h>		/*size_t*/
#include <assert.h>		/*assert*/
#include <stdlib.h>		/*malloc & free*/

#include "queue.h"
#include "singly_linked_list.h"

/* 
* Author: Elyashiv Horden 
* Date: 13-12-2024
* Reviewer: Or Elyahu
*/


struct queue
{
	list_t* list;
};


queue_t* QueueCreate(void)
{
	queue_t* queue = malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	queue->list= SllCreate();
	
	if (NULL == queue->list)
	{
		free(queue);
		return NULL;
	}
	
	return queue;
}

void QueueDestroy(queue_t* queue)
{
	assert(NULL != queue);
	
	SllDestroy(queue->list);
	free(queue);
}

status_t Enqueue(queue_t* queue, void* data)
{
	assert(NULL != queue);
	
	if (SllInsert(queue->list, SllEnd(queue->list), data) == SllEnd(queue->list))
	{
		return OPERATION_FAIL;
	}
	return SUCCESS;
}

void Dequeue(queue_t* queue)
{
	assert(NULL != queue);
	
	SllRemove(SllBegin(queue->list));
}

size_t QueueSize(const queue_t* queue)
{
	assert(NULL != queue);
	
	return SllSize(queue->list);
}

void* QueuePeek(const queue_t* queue)
{
	assert(NULL != queue);
	
	return SllGetData(SllBegin(queue->list));
}

void QueueAppend(queue_t* queue1, queue_t* queue2)
{
	assert(NULL != queue1);
	assert(NULL != queue2);
		
	SllAppend(queue1->list, queue2->list);
}


























