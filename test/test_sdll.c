#include <stdio.h>		/*printf*/
#include <stddef.h>		/*size_t*/

#include "sdll.h"


#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define NUM (5)


int Compare(void* arg1, void* arg2);
void TestBasicFuncSdll(void);
void TesSdllPop(void);
void TesSdllGets(void);
void TesSdllFinfIf(void);
static int Is_MatchIf(void* arg1, void* arg2);
static int IncByOne(void* x, void* args);
void TesSdllForEach(void);
void TestIsEqual(void);
void TestMerge(void);
void TestFind(void);

static int num_of_failurs = 0;

int main ()
{
	TestBasicFuncSdll();
	TesSdllPop();
	TesSdllGets();
	TesSdllFinfIf();
	TesSdllForEach();
	TestIsEqual();
	TestMerge();
	TestFind();
	
	printf("%d Tests failed\n", num_of_failurs);
	
	if (!num_of_failurs)
	{
		printf("----All tests passed successfully----\n");
	}
	return 0;
}


void TestBasicFuncSdll(void)
{
	
	sdll_t* list = SdllCreate(&Compare); 
	sdll_iterator_t iter;
	int arr[NUM] = {1,2,3,4,5};
	size_t i = 0;
	
	
	/*Test Dll create*/
	if (NULL == list)
	{
		printf("%s%d: Test Sdll-Create failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	
	/*Test Is-Empty*/
	if (1 != SdllIsEmpty(list))
	{
		printf("%s%d: Test Sdll Is-Empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sdll create done--\n%s", GREEN, RESET);
	printf("%s --Test Sdll Is-Empty done--\n%s", GREEN, RESET);
	
	/*Test Insert & size*/
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
		if (i+1 != SdllSize(list))
		{
			printf("%s%d: Test Sdll Size failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
	}
	printf("%s --Test Sdll Size done--\n%s", GREEN, RESET);
	
	iter = SdllBegin(list);
	for(i = 0; i < NUM; ++i)
	{
		SdllRemove(iter);
		iter = SdllBegin(list);
	}
	
	if (0 != SdllSize(list))
	{
		printf("%s%d: Test Sdll Remove failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sdll Remove done--\n%s", GREEN, RESET);
	
	
	SdllDestroy(list);
	printf("%s --Test Sdll Destroy done--\n%s", GREEN, RESET);
}


void TesSdllPop(void)
{
	sdll_t* list = SdllCreate(&Compare); 
	int arr[NUM] = {4,3,2,5,1};
	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
	}
	
	/*Test Pop-Front*/
	for(i = 0; i < NUM; ++i)
	{
		if ((int)(i+1) != *(int*)SdllPopFront(list))
		{
			printf("%s%d: Test Sdll Pop-Front failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
	}
	printf("%s --Test Sdll Pop-Front done--\n%s", GREEN, RESET);
	
	
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
	}
	
	/*Test Pop-Back*/
	for(i = 0; i < NUM; ++i)
	{
		if ((int)(NUM - i) != *(int*)SdllPopBack(list))
		{
			printf("%s%d: Test Sdll Pop-Front failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
	}
	printf("%s --Test Sdll Pop-Front done--\n%s", GREEN, RESET);
	
	SdllDestroy(list);
}


void TesSdllGets(void)
{
	sdll_t* list = SdllCreate(&Compare); 
	sdll_iterator_t iter;
	int arr[NUM] = {4,3,2,5,1};
	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
	}
	
	iter = SdllBegin(list);
	for(i = 0; i < NUM; ++i)
	{
		if ((int)(i+1) != *(int*)SdllGetData(iter))
		{
			printf("%s%d: Test Sdll Get-Data failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = SdllGetNext(iter);
	}
	printf("%s --Test Sdll Get-Data done--\n%s", GREEN, RESET);
	printf("%s --Test Sdll Get-Next done--\n%s", GREEN, RESET);
	
	iter = SdllEnd(list);
	iter = SdllGetPrev(iter);

	for(i = 0; i < NUM; ++i)
	{
		if ((int)(NUM-i) != *(int*)SdllGetData(iter))
		{
			printf("%s%d: Test Sdll Get-Data failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = SdllGetPrev(iter);
	}
	printf("%s --Test Sdll Get-Prev done--\n%s", GREEN, RESET);
	printf("%s --Test Sdll Begin done--\n%s", GREEN, RESET);
	printf("%s --Test Sdll End done--\n%s", GREEN, RESET);
	
	SdllDestroy(list);
}


void TesSdllFinfIf(void)
{
	sdll_t* list = SdllCreate(&Compare); 
	sdll_iterator_t iter = {0};
	int arr[NUM] = {4,3,2,5,1};
	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
	}
	
	iter = SdllFindIf(SdllBegin(list), SdllEnd(list), NULL, Is_MatchIf);
	if (3 != *(int*)SdllGetData(iter))
	{
		printf("%s%d: Test Sdll Find-If failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sdll Find-If done--\n%s", GREEN, RESET);
	
	SdllDestroy(list);
}


void TesSdllForEach(void)
{
	sdll_t* list = SdllCreate(&Compare); 
	sdll_iterator_t iter;
	int arr[NUM] = {4,3,2,5,1};
	size_t i = 0;
	size_t j = 2;
	
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
	}
	
	SdllForEach(SdllBegin(list), SdllEnd(list), IncByOne, list);
	iter = SdllBegin(list);
	for (i = 0; i < NUM; ++i)
	{
		if((int)(j+i) != *(int*)SdllGetData(iter))
		{
			printf("%s%d: Test Sdll For-Each failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = SdllGetNext(iter);
	}
	printf("%s --Test Sdll For-Each done--\n%s", GREEN, RESET);

	SdllDestroy(list);
}

void TestIsEqual(void)
{
	sdll_t* list = SdllCreate(&Compare); 
	int num = 19;
	SdllInsert(list, &num);
	
	if (!SdllIsEqual(SdllBegin(list), SdllGetPrev(SdllEnd(list))))
	{
		printf("%s%d: Test Sdll Is-Equal failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sdll Is-Equal done--\n%s", GREEN, RESET);
	
	SdllDestroy(list);
}


void TestFind(void)
{
	sdll_t* list = SdllCreate(&Compare); 
	sdll_iterator_t iter;

	int arr[NUM] = {4,3,2,50,1};
	int num = 50;
	size_t i = 0;
	
	for(i = 0; i < NUM; ++i)
	{
		SdllInsert(list, &arr[i]);
	}
	
	iter = SdllFind(SdllBegin(list), SdllEnd(list), &num, list);
	
	if(50 != *(int*)SdllGetData(iter))
	{
		printf("%s%d: Test Sdll Find failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sdll Find done--\n%s", GREEN, RESET);
	SdllDestroy(list);
}


void TestMerge(void)
{
	sdll_t* list1 = SdllCreate(&Compare); 
	sdll_t* list2 = SdllCreate(&Compare); 
	sdll_iterator_t iter;
	int arr1[6] = {1,2,3,6,7,9};
	int arr2[4] = {4,5,8,10};
	size_t i = 0;
	
	for(i = 0; i < 6; ++i)
	{
		SdllInsert(list1, &arr1[i]);
	}
	
	for(i = 0; i < 4; ++i)
	{
		SdllInsert(list2, &arr2[i]);
	}
	SdllMerge(list1, list2);
	
	iter = SdllBegin(list1);
	
	for (i = 0; i < NUM; ++i)
	{
		if((int)(i+1) != *(int*)SdllGetData(iter))
		{
			printf("%s%d: Test Sdll Merge failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = SdllGetNext(iter);
	}
	printf("%s --Test Sdll Merge done--\n%s", GREEN, RESET);
	
	SdllDestroy(list1);
	SdllDestroy(list2);
}



int Compare(void* arg1, void* arg2)static int Is_MatchIf(void* astatic int Is_MatchIf(void* arg1, void* arg2)
{
	(void)(arg2);	
	
	return ((*(int*)arg1) % 3 == 0);

}rg1, void* arg2)
{
	(void)(arg2);	
	
	return ((*(int*)arg1) % 3 == 0);

}
{
	return (*(int*)arg1) - (*(int*)arg2);
}

static int Is_MatchIf(void* arg1, void* arg2)
{
	(void)(arg2);	
	
	return ((*(int*)arg1) % 3 == 0);

}

static int IncByOne(void* x, void* args)
{
	++(*(int*)x);
	args = (void*)args;
	
	return SUCCESS;
}

