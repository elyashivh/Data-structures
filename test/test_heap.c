#include <stdio.h>
#include <stddef.h>		
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "heap.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define STYLE_BOLD "\x1b[1m"
#define COLOR_MAGENTA "\x1b[35m"
#define RESET_ALL "\x1b[0m"
#define FAIL (1)
#define SIZE (10)
#define SIZE2 (7)


static int Comparator(void* a, void* b);
static int IsMatchInt(void* a, void* b);

void TestHeapCreateAndDestroy(void);
void TestHeapPush(void);
void TestHeapPeekAndPop(void);
void TestHeapPop(void);
void TestHeapRemove(void);
void TestHeapIsEmptyAndSize(void);

static int num_of_failurs = 0;

int main ()
{
	TestHeapCreateAndDestroy();
	TestHeapPush();
	TestHeapPeekAndPop();
	TestHeapRemove();
	TestHeapIsEmptyAndSize();

	if (!num_of_failurs)
	{
		printf(COLOR_MAGENTA STYLE_BOLD "----All tests passed successfully----\n" RESET_ALL);
	}

	return 0;
}


void TestHeapCreateAndDestroy(void)
{
	heap_t* heap = HeapCreate(Comparator);

	if (heap == NULL)
	{
		printf(COLOR_RED"%d: Test Heap-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (0 != HeapSize(heap))
	{
		printf(COLOR_RED"%d: Test Heap-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (!HeapIsEmpty(heap))
	{
		printf(COLOR_RED"%d: Test Heap-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}


	HeapDestroy(heap);

    printf(COLOR_GREEN "--Test Heap Create done--\n" RESET_ALL);
	printf(COLOR_GREEN "--Test Heap Destroy done--\n" RESET_ALL);
}

void TestHeapPush(void)
{
	heap_t* heap = HeapCreate(Comparator);
	int arr[NUM_OF_DICT] = {8, 41, 71, 21, 13, 12, 10, 11, 16, 48};
	size_t i = 0;

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		if (HeapPush(heap, arr+i) == FAIL)
		{
			printf(COLOR_RED"%d: Test Heap-Push failed \n"RESET_ALL, __LINE__);
			++num_of_failurs; 	
		}
	}
	if (HeapSize(heap) != NUM_OF_DICT)
	{
		printf(COLOR_RED"%d: Test Heap-Push failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}

	HeapDestroy(heap);

    printf(COLOR_GREEN "--Test Heap-Push done--\n" RESET_ALL);
}

void TestHeapPeekAndPop(void)
{
	heap_t* heap = HeapCreate(Comparator);
	int arr[SIZE2] = {10, 20, 50, 30, 80, 60, 70};
	size_t i = 0;

	for (i = 0; i < SIZE2; ++i)
	{
		HeapPush(heap, arr+i);
	}
	
	if (*(int*)HeapPeek(heap) != arr[0])
	{
		printf(COLOR_RED"%d: Test Heap-Peek failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}

	HeapPop(heap);
	if (*(int*)HeapPeek(heap) != arr[1])
	{
		printf(COLOR_RED"%d: Test Heap-Peek failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	HeapPop(heap);
	if (*(int*)HeapPeek(heap) != arr[3])
	{
		printf(COLOR_RED"%d: Test Heap-Peek failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	HeapPop(heap);

	if (HeapSize(heap) != SIZE2-3)
	{
		printf(COLOR_RED"%d: Test Heap-Pop failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}

	HeapPop(heap);
	HeapPop(heap);

	if (HeapSize(heap) != SIZE2-5)
	{
		printf(COLOR_RED"%d: Test Heap-Pop failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}

	HeapDestroy(heap);

    printf(COLOR_GREEN "--Test Heap-Pop done--\n" RESET_ALL);
}

void TestHeapRemove(void)
{
	heap_t* heap = HeapCreate(Comparator);
	int arr[SIZE2] = {20, 10, 50, 30, 80, 60, 70};
/* 	int ptr0 = arr[0];
	int ptr1 = arr[1];
	int ptr2 = arr[2];
	int ptr3 = arr[3];
	int ptr4 = arr[4];
	int ptr5 = arr[5];
	int ptr6 = arr[6];  */

	HeapPush(heap, arr+0);
	HeapPush(heap, arr+1);
	HeapPush(heap, arr+2);
	HeapPush(heap, arr+3);
	HeapPush(heap, arr+4);
	HeapPush(heap, arr+5);
	HeapPush(heap, arr+6);
	if (*(int*)HeapRemove(heap, IsMatchInt, arr+6) != arr[6])
	{
		printf(COLOR_RED"%d: Test Heap-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	if (*(int*)HeapRemove(heap, IsMatchInt, arr+2) != arr[2])
	{
		printf(COLOR_RED"%d: Test Heap-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	if (*(int*)HeapRemove(heap, IsMatchInt, arr) != arr[0])
	{
		printf(COLOR_RED"%d: Test Heap-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	
	if (HeapSize(heap) != SIZE2-3)
	{
		printf(COLOR_RED"%d: Test Heap-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}

	HeapDestroy(heap);

    printf(COLOR_GREEN "--Test Heap-Remove done--\n" RESET_ALL);

}

void TestHeapIsEmptyAndSize(void)
{
	heap_t* heap = HeapCreate(Comparator);
	int arr[SIZE2] = {10, 20, 50, 30, 80, 60, 70};
	size_t i = 0;

	if (HeapSize(heap) != 0)
	{
		printf(COLOR_RED"%d: Test Heap-Size failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	if (!HeapIsEmpty(heap))
	{
		printf(COLOR_RED"%d: Test Heap-Is-Empty failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}

	for (i = 0; i < SIZE2; ++i)
	{
		HeapPush(heap, arr+i);
		if (HeapSize(heap) != i+1)
		{
			printf(COLOR_RED"%d: Test Heap-Size failed \n"RESET_ALL, __LINE__);
			++num_of_failurs;
		}
	}
	if (HeapIsEmpty(heap))
	{
		printf(COLOR_RED"%d: Test Heap-Is-Empty failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	for (i = 0; i < SIZE2; ++i)
	{
		HeapPop(heap);
		if (HeapSize(heap) != SIZE2-i-1)
		{
			printf(COLOR_RED"%d: Test Heap-Size failed \n"RESET_ALL, __LINE__);
			++num_of_failurs;
		}
	}

	HeapDestroy(heap);

	printf(COLOR_GREEN "--Test Heap-Is-Empty done--\n" RESET_ALL);
    printf(COLOR_GREEN "--Test Heap-Size done--\n" RESET_ALL);
}


static int Comparator(void* a, void* b)
{
    return *(int*)a - *(int*)b;
}

static int IsMatchInt(void* a, void* b)
{
    return *(int*)a == *(int*)b;
}