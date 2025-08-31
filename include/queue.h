#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>

/* #include "singly_linked_list.h"
 */#include "heap.h"

typedef struct queue queue_t;


queue_t* QueueCreate(void);

void QueueDestroy(queue_t* queue);

status_t Enqueue(queue_t* queue, void* data);

void Dequeue(queue_t* queue);

size_t QueueSize(const queue_t* queue);

void* QueuePeek(const queue_t* queue);

void QueueAppend(queue_t* queue1, queue_t* queue2);


#endif /* End of the header guard QUEUE */

