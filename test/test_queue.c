#include <stdio.h>

#include "queue.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
/*#define NUM_OF_TESTS (5)*/
#define NUM (5)


void TestCreateAndDestroyQueue(void);
void TestEnqueueAndDequeue(void);
void TestAppendAndPeek(void);

static int num_of_failurs = 0;
int main ()
{
	TestCreateAndDestroyQueue();
	TestEnqueueAndDequeue();
	TestAppendAndPeek();
	
	printf("%d Tests failed\n", num_of_failurs);
	if (!num_of_failurs)
	{
		printf("----All tests passed successfully----\n");
	}
	
	return 0;
}


void TestCreateAndDestroyQueue(void)
{
	queue_t* queue = QueueCreate();

	if (NULL == queue)
	{
		printf("%s%d: Test Queue-Create failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	printf("%s --Test Create Queue done--\n%s", GREEN, RESET);
	
	if (0 != QueueSize(queue))
	{
		printf("%s%d: Test Queue Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	
	QueueDestroy(queue);
	printf("%s --Test Destroy Queue done--\n%s", GREEN, RESET);
}


void TestEnqueueAndDequeue(void)
{
	queue_t* queue = QueueCreate();
	int arr[NUM] = {1,2,3,4,5};
	int i = 0;

	for (i = 0; i < NUM; ++i)
	{
		if (OPERATION_FAIL == Enqueue(queue, &arr[i]))
		{
			printf("%s%d: Test Queue Enqueue failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		
		if ((size_t)(i+1) != QueueSize(queue))
		{
			printf("%s%d: Test Queue Size failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
	}
	printf("%s --Test Enqueue done--\n%s", GREEN, RESET);
	
	for (i = 0; i < NUM; ++i)
	{
		Dequeue(queue);
		if ((size_t)(NUM-i-1) != QueueSize(queue))
		{
			printf("%s%d: Test Queue Enqueue failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
	}
	printf("%s --Test Dequeue done--\n%s", GREEN, RESET);
	
	QueueDestroy(queue);
}


void TestAppendAndPeek(void)
{
	queue_t* queue1 = QueueCreate();
	queue_t* queue2 = QueueCreate();
	int arr1[NUM] = {1,2,3,4,5};
	int arr2[NUM] = {6,7,8,9,10};
	int i = 0;

	for (i = 0; i < NUM; ++i)
	{
		 Enqueue(queue1, &arr1[i]);
	}
	for (i = 0; i < NUM; ++i)
	{
		 Enqueue(queue2, &arr2[i]);
	}
	
	QueueAppend(queue1, queue2);
	if ((size_t)(NUM*2) != QueueSize(queue1))
	{
		printf("%s%d: Test Queue Append failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Append done--\n%s", GREEN, RESET);
	
	for (i = 0; i < NUM*2; ++i)
	{
		if (i+1 != *(int*)QueuePeek(queue1))
		{
			printf("%s%d: Test Queue Peek failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		Dequeue(queue1);
	}
	printf("%s --Test Queue Peek done--\n%s", GREEN, RESET);
	printf("%s --Test Queue Size done--\n%s", GREEN, RESET);
	
	
	QueueDestroy(queue1);
	QueueDestroy(queue2);
}







