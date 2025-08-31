#include <stdio.h>
#include <stddef.h>		
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "avl.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define STYLE_BOLD "\x1b[1m"
#define COLOR_MAGENTA "\x1b[35m"
#define RESET_ALL "\x1b[0m"
#define SIZE (5)
#define SUCCESS (0)
#define FAILED (1)

typedef struct
{
    int arr[10];
    int j;
}for_tests_t;

static int Comparator(const void* data, const void* key);
static int CheckTree(void* data, void* args);

void TestTestCreateAndDestroy(void);
void TestInsert(void);
void TestRemove(void);
void TestFind(void);
void TestForEach(void);
void TestIsEmpty(void);
void TestSize(void);
void TestHeight(void);
void TestInsertWithHeight(void);

static int num_of_failurs = 0;


int main ()
{
	TestTestCreateAndDestroy();
	TestInsert();
	TestRemove();
	TestFind();
	TestForEach();
	TestIsEmpty();
	TestSize();
	TestHeight();
	TestInsertWithHeight();

	
	if (!num_of_failurs)
	{
		printf(COLOR_MAGENTA STYLE_BOLD "----All tests passed successfully----\n" RESET_ALL);
	}

	return 0;
}


void TestTestCreateAndDestroy(void)
{
	avl_t* avl = AVLCreate(Comparator);

    if (avl == NULL)
	{
		printf(COLOR_RED"%d: Test AVL-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (AVLSize(avl) != 0)
	{
		printf(COLOR_RED"%d: Test AVL-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	if (!AVLIsEmpty(avl))
	{
		printf(COLOR_RED"%d: Test AVL-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
	}
	
	AVLDestroy(avl);
    printf(COLOR_GREEN "--Test AVL-Create done--\n" RESET_ALL);
	printf(COLOR_GREEN "--Test AVL-Destroy done--\n" RESET_ALL);
}


void TestInsert(void)
{
	avl_t* avl = AVLCreate(Comparator);
	size_t i = 0;
	int arr[NUM_OF_DICT] = {1,2,3,4,5};
	for_tests_t ans = {{1,2,3,4,5}, 0};

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		if (AVLInsert(avl, arr+i, arr+i) != SUCCESS)
		{
			printf(COLOR_RED"%d: Test AVL-Insert failed \n"RESET_ALL, __LINE__);
			++num_of_failurs; 	
		}
	}

    if (AVLSize(avl) != 5)
	{
		printf(COLOR_RED"%d: Test AVL-Insert failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	if (AVLForeach(avl, CheckTree, &ans, IN_ORDER) != SUCCESS)
	{
		printf(COLOR_RED"%d: Test AVL-Insert failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	
	AVLDestroy(avl);
    printf(COLOR_GREEN "--Test AVL-Insert done--\n" RESET_ALL);
}


void TestRemove(void)
{
	avl_t* avl = AVLCreate(Comparator);
	size_t i = 0;
	int arr[NUM_OF_DICT*2] = {1,2,3,4,5,6,7,8,9};
	for_tests_t ans = {{2,3,5,6,7,8,9}, 0};
	int remove1 = 1;
	int remove4 = 4;

	for (i = 0; i < NUM_OF_DICT+4; ++i)
	{
		AVLInsert(avl, arr+i, arr+i);
	}

	AVLRemove(avl, &remove1);
    AVLRemove(avl, &remove4);

    if (AVLSize(avl) != 7)
	{
		printf(COLOR_RED"%d: Test AVL-Removert failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	if (AVLForeach(avl, CheckTree, &ans, IN_ORDER) != SUCCESS)
	{
		printf(COLOR_RED"%d: Test AVL-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	
	AVLDestroy(avl);
    printf(COLOR_GREEN "--Test AVL-Remove done--\n" RESET_ALL);
}

void TestFind(void)
{
	return;
}
void TestForEach(void)
{
	avl_t* avl = AVLCreate(Comparator);
	size_t i = 0;
	int arr[] = { 1, 2 ,3 ,4 ,5};
    for_tests_t ans_in_order = { {1,2,3,4,5}, 0};
	for_tests_t ans_pre_order = { {2,1,4,3,5}, 0};
	for_tests_t ans_post_order = { {1,3,5,4,2}, 0};

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		AVLInsert(avl, arr+i, arr+i);
	}

	if (AVLForeach(avl, CheckTree, &ans_in_order, IN_ORDER) != SUCCESS)
	{
		printf(COLOR_RED"%d: Test AVL-For-Each failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (AVLForeach(avl, CheckTree, &ans_pre_order, PRE_ORDER) != SUCCESS)
	{
		printf(COLOR_RED"%d: Test AVL-For-Each failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (AVLForeach(avl, CheckTree, &ans_post_order, POST_ORDER) != SUCCESS)
	{
		printf(COLOR_RED"%d: Test AVL-For-Each failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	AVLDestroy(avl);
    printf(COLOR_GREEN "--Test AVL-For-Each done--\n" RESET_ALL);
}
void TestIsEmpty(void)
{
	return;
}
void TestSize(void)
{
	return;
}
void TestHeight(void)
{
	return;
}
void TestInsertWithHeight(void)
{
	return;
}

static int Comparator(const void* data, const void* key)
{
    return *(int*)data - *(int*)key;
}

static int CheckTree(void* data, void* args)
{
    for_tests_t* temp = (for_tests_t*)args; 

    if( temp->arr[temp->j] != *(int*)data)
    {
        return FAILED;
    }
    temp->j += 1;
    return SUCCESS;
}