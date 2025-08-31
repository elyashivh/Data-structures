#include <stdio.h>
#include <stddef.h>		
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "bst.h"


#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define STYLE_BOLD "\x1b[1m"
#define COLOR_MAGENTA "\x1b[35m"
#define RESET_ALL "\x1b[0m"
#define NUM (5)

int comp(void* a, void* b);
void TestBSTCreateAndDestroy(void);
void TestBSTCInsert(void);
void TestBSTRemove(void);
void TestBSTSizeAndIsEmpty(void);
void TestBSTNext(void);
void TestBSTPrev(void);
void TestBSTBegin(void);
void TestBSTEnd(void);
void TestBSTGetData(void);
void TestBSTFind(void);
void TestBSTIsEqual(void);
void TestBSTForEach(void);
static int IncByOne(void* x, void* args);

static int num_of_failurs = 0;


int main ()
{
	TestBSTCreateAndDestroy();
	TestBSTCInsert();
	TestBSTRemove();
	TestBSTSizeAndIsEmpty();
	TestBSTNext();
	TestBSTPrev();
	TestBSTBegin();
	TestBSTEnd();
	TestBSTGetData();
	TestBSTIsEqual();
	TestBSTFind();
	TestBSTForEach();


	if (!num_of_failurs)
	{
		printf(COLOR_MAGENTA STYLE_BOLD "----All tests passed successfully----\n" RESET_ALL);
	}

	return 0;
}

void TestBSTCreateAndDestroy(void)
{
	bst_t* tree = BSTCreate(comp);
	if (!tree)
	{
		printf(COLOR_RED"%d: Test BST-Create failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (!BSTIsEmpty(tree))
	{
		printf(COLOR_RED"%d: Test BST-Create failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	
	printf(COLOR_GREEN "--Test BST-Create & Destroy done--\n" RESET_ALL);
}

void TestBSTCInsert(void)
{
	size_t i = 0;
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};

	assert(tree);
	for(i = 0; i < NUM; ++i)
	{
		if (!BSTInsert(tree, &arr[i]))
		{
			printf(COLOR_RED"%d: Test BST-Insert failed iteration: %ld\n"RESET_ALL, __LINE__, i);
			++num_of_failurs; 	
		}
	}

	if (BSTIsEmpty(tree))
	{
		printf(COLOR_RED"%d: Test BST-Insert failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	
	BSTDestroy(tree);
	
	printf(COLOR_GREEN "--Test BST-Insert done--\n" RESET_ALL);
}

void TestBSTRemove(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter_a = NULL;
	iterator_t iter_b = NULL;
	iterator_t iter_c = NULL;
	iterator_t iter_d = NULL;
	iterator_t iter_e = NULL;

	iter_a = BSTInsert(tree, &arr[0]);
	iter_b = BSTInsert(tree, &arr[1]);
	iter_c = BSTInsert(tree, &arr[2]);
	iter_d = BSTInsert(tree, &arr[3]);
	iter_e = BSTInsert(tree, &arr[4]);

	BSTRemove(iter_a);
	BSTRemove(iter_b);
	BSTRemove(iter_c);
	BSTRemove(iter_d);
	BSTRemove(iter_e);
	
	if (!BSTIsEmpty(tree))
	{
		printf(COLOR_RED"%d: Test BST-Remove failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Remove done--\n" RESET_ALL);
}

void TestBSTSizeAndIsEmpty(void)
{
	size_t i = 0;
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};

	assert(tree);
	if (!BSTIsEmpty(tree))
	{
		printf(COLOR_RED"%d: Test BST-Is-Empty failed iteration: %ld\n"RESET_ALL, __LINE__, i);
		++num_of_failurs; 	
	}
	for(i = 0; i < NUM; ++i)
	{
		assert(BSTInsert(tree, &arr[i]));
		if (i+1 != BSTSize(tree))
		{
			printf(COLOR_RED"%d: Test BST-Size failed iteration: %ld\n"RESET_ALL, __LINE__, i);
			++num_of_failurs; 	
		}
	}

	for(i = 0; i < NUM-1; ++i)
	{
		BSTRemove(BSTBegin(tree));
		if ((size_t)(NUM-1-i) != BSTSize(tree))
		{
			printf(COLOR_RED"%d: Test BST-Size failed iteration: %ld\n"RESET_ALL, __LINE__, i);
			++num_of_failurs; 	
		}
	}

	BSTRemove(BSTBegin(tree));
	if (!BSTIsEmpty(tree))
	{
		printf(COLOR_RED"%d: Test BST-Is-Empty failed iteration\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Is-Empty done--\n" RESET_ALL);
	printf(COLOR_GREEN "--Test BST-Size done--\n" RESET_ALL);
}

void TestBSTGetData(void)
{
	size_t i = 0;
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	int ans[NUM] = {10, 25, 40, 50, 75};

	for(i = 0; i < NUM; ++i)
	{
		BSTInsert(tree, &arr[i]);
	}

	for(i = 0; i < NUM; ++i)
	{
		if (ans[i] != *(int*)BSTGetData(BSTBegin(tree)))
		{
			printf(COLOR_RED"%d: Test BST-Size failed iteration: %ld\n"RESET_ALL, __LINE__, i);
			++num_of_failurs; 	
		}
		BSTRemove(BSTBegin(tree));
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Is-Empty done--\n" RESET_ALL);
}

void TestBSTFind(void)
{	
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter_a = NULL;
	iterator_t iter_b = NULL;
	iterator_t iter_c = NULL;
	iterator_t iter_d = NULL;
	iterator_t iter_e = NULL;

	iter_a = BSTInsert(tree, &arr[0]);
	iter_b = BSTInsert(tree, &arr[1]);
	iter_c = BSTInsert(tree, &arr[2]);
	iter_d = BSTInsert(tree, &arr[3]);
	iter_e = BSTInsert(tree, &arr[4]);

	
	if (!BSTIsEqual(BSTFind(tree, &arr[0]), iter_a))
	{
		printf(COLOR_RED "%d: Test BST-Find failed\n" RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (!BSTIsEqual(BSTFind(tree, &arr[1]), iter_b))
	{
		printf(COLOR_RED "%d: Test BST-Find failed\n" RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (!BSTIsEqual(BSTFind(tree, &arr[2]), iter_c))
	{
		printf(COLOR_RED "%d: Test BST-Find failed\n" RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (!BSTIsEqual(BSTFind(tree, &arr[3]), iter_d))
	{
		printf(COLOR_RED "%d: Test BST-Find failed\n" RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (!BSTIsEqual(BSTFind(tree, &arr[4]), iter_e))
	{
		printf(COLOR_RED "%d: Test BST-Find failed\n" RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Find done--\n" RESET_ALL);
}

void TestBSTForEach(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};

	BSTInsert(tree, &arr[0]);
	BSTInsert(tree, &arr[1]);
	BSTInsert(tree, &arr[2]);
	BSTInsert(tree, &arr[3]);
	BSTInsert(tree, &arr[4]);

	if (BSTForEach(BSTBegin(tree), BSTEnd(tree), IncByOne, tree) == OPERATION_FAILED)
	{
		printf(COLOR_RED "%d: Test BST-For-Each failed\n" RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	
	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-For-Each done--\n" RESET_ALL);
}

void TestBSTIsEqual(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter_a = NULL;
	iterator_t iter_b = NULL;
	iterator_t iter_c = NULL;
	iterator_t iter_d = NULL;
	iterator_t iter_e = NULL;

	iter_a = BSTInsert(tree, &arr[0]);
	iter_b = BSTInsert(tree, &arr[1]);
	iter_c = BSTInsert(tree, &arr[2]);
	iter_d = BSTInsert(tree, &arr[3]);
	iter_e = BSTInsert(tree, &arr[4]);

	if (!BSTIsEqual(BSTBegin(tree), iter_d))
	{
		printf(COLOR_RED"%d: Test BST-Is-Equal failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	BSTRemove(iter_d);
	if (!BSTIsEqual(BSTBegin(tree), iter_b))
	{
		printf(COLOR_RED"%d: Test BST-Is-Equal failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	BSTRemove(iter_b);
	if (!BSTIsEqual(BSTBegin(tree), iter_e))
	{
		printf(COLOR_RED"%d: Test BST-Is-Equal failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	BSTRemove(iter_e);
	if (!BSTIsEqual(BSTBegin(tree), iter_a))
	{
		printf(COLOR_RED"%d: Test BST-Is-Equal failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}BSTRemove(iter_a);
	if (!BSTIsEqual(BSTBegin(tree), iter_c))
	{
		printf(COLOR_RED"%d: Test BST-Is-Equal failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Is-Equal done--\n" RESET_ALL);
}

void TestBSTPrev(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter_a = NULL;
	iterator_t iter_b = NULL;
	iterator_t iter_c = NULL;
	iterator_t iter_d = NULL;
	iterator_t iter_e = NULL;

	iter_a = BSTInsert(tree, &arr[0]);
	iter_b = BSTInsert(tree, &arr[1]);
	iter_c = BSTInsert(tree, &arr[2]);
	iter_d = BSTInsert(tree, &arr[3]);
	iter_e = BSTInsert(tree, &arr[4]);

	if (BSTPrev(iter_c) != iter_a)
	{
		printf(COLOR_RED"%d: Test BST-Prev failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTPrev(iter_a) != iter_e)
	{
		printf(COLOR_RED"%d: Test BST-Prev failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTPrev(iter_e) != iter_b)
	{
		printf(COLOR_RED"%d: Test BST-Prev failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTPrev(iter_b) != iter_d)
	{
		printf(COLOR_RED"%d: Test BST-Prev failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Prev done--\n" RESET_ALL);
}

void TestBSTNext(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter_a = NULL;
	iterator_t iter_b = NULL;
	iterator_t iter_c = NULL;
	iterator_t iter_d = NULL;
	iterator_t iter_e = NULL;

	iter_a = BSTInsert(tree, &arr[0]);
	iter_b = BSTInsert(tree, &arr[1]);
	iter_c = BSTInsert(tree, &arr[2]);
	iter_d = BSTInsert(tree, &arr[3]);
	iter_e = BSTInsert(tree, &arr[4]);

	if (BSTNext(iter_a) != iter_c)
	{
		printf(COLOR_RED"%d: Test BST-Next failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTNext(iter_b) != iter_e)
	{
		printf(COLOR_RED"%d: Test BST-Next failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTNext(iter_c) != BSTEnd(tree))
	{
		printf(COLOR_RED"%d: Test BST-Next failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTNext(iter_d) != iter_b)
	{
		printf(COLOR_RED"%d: Test BST-Next failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (BSTNext(iter_e) != iter_a)
	{
		printf(COLOR_RED"%d: Test BST-Next failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Next done--\n" RESET_ALL);
}

void TestBSTEnd(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter = NULL;
	assert(tree);

	BSTInsert(tree, &arr[0]);
	BSTInsert(tree, &arr[1]);
	iter = BSTInsert(tree, &arr[2]);
	BSTInsert(tree, &arr[3]);
	BSTInsert(tree, &arr[4]);

	if (iter != BSTPrev(BSTEnd(tree)))
	{
		printf(COLOR_RED"%d: Test BST-End failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-End done--\n" RESET_ALL);
}


void TestBSTBegin(void)
{
	bst_t* tree = BSTCreate(comp);
	int arr[NUM] = {50, 25, 75, 10, 40};
	iterator_t iter_b = NULL;
	iterator_t iter_d = NULL;

	assert(tree);

	BSTInsert(tree, &arr[0]);
	iter_b = BSTInsert(tree, &arr[1]);
	BSTInsert(tree, &arr[2]);
	iter_d = BSTInsert(tree, &arr[3]);
	BSTInsert(tree, &arr[4]);

	if (iter_d != BSTBegin(tree))
	{
		printf(COLOR_RED"%d: Test BST-Begin failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	BSTRemove(iter_d);
	if (iter_b != BSTBegin(tree))
	{
		printf(COLOR_RED"%d: Test BST-Begin failed\n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	BSTDestroy(tree);
	printf(COLOR_GREEN "--Test BST-Begin done--\n" RESET_ALL);
}


int comp(void* a, void* b)
{
    return *(int*)a - *(int*)b;
}

static int IncByOne(void* x, void* args)
{
	++(*(int*)x);
	args = (void*)args;
	
	return SUCCESS;
} 

