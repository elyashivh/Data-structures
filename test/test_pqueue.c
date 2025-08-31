#include <stdio.h>		/*printf*/
#include <stddef.h>		/*size_t*/
#include <assert.h>


#include "pqueue.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define ANSI_STYLE_BOLD "\x1b[1m"
#define ANSI_RESET_ALL  "\x1b[0m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define NUM (5)

int Is_MatchIf(void* arg1, void* arg2);
static int Comparator(void* a, void* b);
void TestPQCreateAndDestroy(void);
void TestPQBasicOperation(void);
void TestPQIsEmptyAndSize(void);
void TestPQErase(void);
void TestPQClear(void);

static int num_of_failurs = 0;

int main ()
{
	TestPQCreateAndDestroy();
	TestPQBasicOperation();
	TestPQIsEmptyAndSize();
	TestPQErase();
	TestPQClear();
	
	if (!num_of_failurs)
	{
		printf(ANSI_COLOR_MAGENTA ANSI_STYLE_BOLD"----All tests passed successfully----\n"ANSI_RESET_ALL);
	}

	
	return 0;
}


void TestPQCreateAndDestroy(void)
{
	pqueue_t* pqueue = PQCreate(Comparator);
	if (NULL == pqueue)
	{
		printf("%s%d: Test PQ-Create failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	
	printf("%s --Test PQ-Create done--\n%s", GREEN, RESET);
	
	PQDestroy(pqueue);
	
	printf("%s --Test PQ-Destroy done--\n%s", GREEN, RESET);
}


void TestPQBasicOperation(void)
{
	pqueue_t* pqueue = PQCreate(Comparator);
	int arr[NUM] = {5, 3, 4, 2, 1};
	int arr2[NUM] = {5,4,3,2,1};
	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		if (ALLOCATION_FAIL == PQEnqueue(pqueue, arr+i))
		{
			printf("%s%d: Test PQ-Enqueue failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 	
		}
	}
	
		printf("%s --Test PQ-Enqueue done--\n%s", GREEN, RESET);
		
	for(i = 0; i < NUM; ++i)
	{
		if (arr2[i] != *(int*)PQPeek(pqueue))
		{
			printf("%s%d: Test PQ-Dequeue failed, iter %ld\n%s", RED, __LINE__,i, RESET);
			++num_of_failurs; 	
		}
		PQDequeue(pqueue);
	}
	
	printf("%s --Test PQ-Peek done--\n%s", GREEN, RESET);
	printf("%s --Test PQ-Dequeue done--\n%s", GREEN, RESET);
	PQDestroy(pqueue);
}


void TestPQIsEmptyAndSize(void)
{
	pqueue_t* pqueue = PQCreate(Comparator);
	int arr[NUM] = {5, 3, 4, 2, 1};

	size_t i = 0;
	
	if (!PQIsEmpty(pqueue))
		{
			printf("%s%d: Test PQ-Is-Empty failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 	
		}
	printf("%s --Test PQ-Is-Empty done--\n%s", GREEN, RESET);
	
	for(i = 0; i < NUM; ++i)
	{
		PQEnqueue(pqueue, &arr[i]);
		if (i+1 != PQSize(pqueue))
		{
			printf("%s%d: Test PQ-Size failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 	
		}
	}
	
	printf("%s --Test PQ-Size done--\n%s", GREEN, RESET);
	
	PQDestroy(pqueue);

}


void TestPQErase(void)
{
	pqueue_t* pqueue = PQCreate(Comparator);
	int arr[NUM] = {5, 3, 4, 2, 1};

	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		PQEnqueue(pqueue, &arr[i]);
	}
	
	PQErase(pqueue, &arr[1], Is_MatchIf);
	PQDequeue(pqueue);
	PQDequeue(pqueue);
	if (arr[3] != *(int*)PQPeek(pqueue))
	{
		printf("%s%d: Test PQ-Erase failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	printf("%s --Test PQ-Erase done--\n%s", GREEN, RESET);
	PQDestroy(pqueue);
}

void TestPQClear(void)
{
	pqueue_t* pqueue = PQCreate(Comparator);
	int arr[NUM] = {5, 3, 4, 2, 1};

	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		PQEnqueue(pqueue, &arr[i]);
	}
	assert((size_t)5 == PQSize(pqueue));
	
	PQClear(pqueue);
	if (!PQIsEmpty(pqueue))
	{
		printf("%s%d: Test PQ-Clear failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	printf("%s --Test PQ-Clear done--\n%s", GREEN, RESET);
	PQDestroy(pqueue);	
}


static int Comparator(void* a, void* b)
{
    return *(int*)b - *(int*)a;
}

int Is_MatchIf(void* arg1, void* arg2)
{
	return ((*(int*)arg1) == (*(int*)arg2));
}

