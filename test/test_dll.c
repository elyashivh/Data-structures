#include <stdio.h>		/*printf*/
#include <stddef.h>		/*size_t*/
#include <assert.h>
#include "dll.h"


#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define NUM (10)

static int Is_MatchForMultiy(void* arg1, void* arg2);
static int IncByOne(void* x, void* args);
static int is_match(void* x1,void* x2);
void TestDll1(void);
void TestDll2(void);
void TestDllMultiFind(void);
void TestDllForEach(void);
void TeatDllSplice(void);

static int num_of_failurs = 0;

int main ()
{
	TestDll1();	
	TestDll2();
	TestDllMultiFind();
	TestDllForEach();
	TeatDllSplice();
	
	printf("%d Tests failed\n", num_of_failurs);
	
	return 0;
}


void TestDll1(void)
{
	int num = 0;
	int num1 = 20;
	int num2 = 20;
	int num3 = 30;
	int num4 = 40;
	int num5 = 1;

	dll_t* list = DllCreate(); 
	dll_iterator_t iter1 = NULL;
	
	/*Test Dll create*/
	if (NULL == list)
	{
		printf("%s%d: Test Dll-Create failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	printf("%s --Test Dll create done--\n%s", GREEN, RESET);
	
	
	/*Test Dll insert & Is-Empty*/
	if (1 != DllIsEmpty(list))
	{
		printf("%s%d: Test Dll is-empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	if (0 != DllSize(list))
	{
		printf("%s%d: Test Dll Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	
	iter1 = DllBegin(list);
	iter1 = DllInsert(list, iter1, &num);
	iter1 = DllInsert(list, iter1, &num1);
	iter1 = DllInsert(list, iter1, &num2);
	iter1 = DllInsert(list, iter1, &num3);
	iter1 = DllInsert(list, iter1, &num4);
	
	if (0 != DllIsEmpty(list))
	{
		printf("%s%d: Test Dll is-empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	
	printf("%s --Test Dll insert done--\n%s", GREEN, RESET);
	printf("%s --Test Dll Is-Empty done--\n%s", GREEN, RESET);
	
	
	/*Test Dll Size*/
	if (5 != DllSize(list))
	{
		printf("%s%d: Test Dll Dll-Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll Size done--\n%s", GREEN, RESET);
	
	
	/*Test Dll Get-Data & Dll-Begin*/
	iter1 = DllGetNext(DllGetNext(iter1));
	
	if (20 != *(int*)DllGetData(iter1))
	{
		printf("%s%d: Test Dll Get-data failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	if (40 != *(int*)DllGetData(DllBegin(list)))
	{
		printf("%s%d: Test Dll Get-data failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll Get-Data done--\n%s", GREEN, RESET);
	printf("%s --Test Dll-Begin done--\n%s", GREEN, RESET);


	/*Test Dll Remove*/
	iter1 = DllRemove(iter1);
	iter1 = DllRemove(DllBegin(list));
	if (3 != DllSize(list))
	{
		printf("%s%d: Test Dll Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll Remove done--\n%s", GREEN, RESET);
	
	
	/*Test Dll For-Each*/
	DllForEach(DllBegin(list),DllEnd(list),&IncByOne, list);
	if (31 != *(int*)DllGetData(DllBegin(list)))
	{
		printf("%s%d: Test Dll-For-Each failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll-For-Each  done--\n%s", GREEN, RESET);
	
	
	/*Test Dll Find*/
	if (num5 != *(int*)DllGetData(DllFind(DllBegin(list), DllEnd(list), &num5, is_match)))
	{
		printf("%s%d: Test Dll-Find failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll-Find done--\n%s", GREEN, RESET);
	
	/*Test Dll Destroy*/
	DllDestroy(list);
}


void TestDll2(void)
{
	int num = 0;
	int num1 = 20;
	int num2 = 20;
	int num3 = 30;
	int num4 = 40;
	int num5 = 1;

	dll_t* list = DllCreate(); 
	dll_iterator_t iter1 = NULL;
	
	iter1 = DllBegin(list);
	iter1 = DllInsert(list, iter1, &num1);
	iter1 = DllInsert(list, iter1, &num2);
	iter1 = DllInsert(list, iter1, &num3);
	
	
	/*Test Dll Push Front & back*/
	DllPushFront(list, &num);
	DllPushBack(list, &num5);

	if (num != *(int*)DllGetData(DllBegin(list)))
	{
		printf("%s%d: Test Dll Push Front failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	iter1 = DllGetNext(iter1);
	if (num5 != *(int*)DllGetData(DllGetPrev(DllEnd(list))))
	{
		printf("%s%d: Test Dll Push back failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll Push Front & back done--\n%s", GREEN, RESET);

	
	/*Test Dll Pop Front & back*/
	if (num != *(int*)DllPopFront(list))
	{
		printf("%s%d: Test Dll pop Front failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	iter1 = DllGetNext(iter1);
	if (num5 != *(int*)DllPopBack(list))
	{
		printf("%s%d: Test Dll pop back failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll Pop Front & back done--\n%s", GREEN, RESET);
	printf("%s --Test Dll Begin & End done--\n%s", GREEN, RESET);
	
	
	/*Test Dll Set-Data*/
	DllSetData(DllBegin(list), &num4);
	if (num4 != *(int*)DllGetData(DllBegin(list)))
	{
		printf("%s%d: Test Dll Set-Data failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Dll Set-Data done--\n%s", GREEN, RESET);
	
	
	DllDestroy(list);
}
	

void TestDllMultiFind(void)
{
	dll_t* dll1 = DllCreate();
	dll_t* dll2 = DllCreate();
	int arr[NUM] = {0};
	int ans[] = {0,2,4,6,8};
	size_t i = 0;
	dll_iterator_t iter = NULL;

	for (i = 0; i < NUM; ++i)
	{
		arr[i] = i;
		DllPushBack(dll1, &arr[i]);
	}
	
	DllMultiFind(dll2, DllBegin(dll1), DllEnd(dll1), NULL, Is_MatchForMultiy);
	
	iter = DllBegin(dll2);
	
	for(i = 0; i < NUM/2; ++i)
	{
		if(ans[i] != *(int*)DllGetData(iter))
		{
			printf("%s%d: Test Dll Multi-Find failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = DllGetNext(iter);
	}

	printf("%s --Test Dll Multi-Find done--\n%s", GREEN, RESET);
	
	DllDestroy(dll1);
	DllDestroy(dll2);
}


void TestDllForEach(void)
{
	dll_t* list = DllCreate();
	int arr[NUM] = {0};
	size_t i = 0;
	dll_iterator_t iter = NULL;

	for (i = 0; i < NUM; ++i)
	{
		arr[i] = i;
		DllPushBack(list, &arr[i]);
	}
	iter = DllBegin(list);
	
	DllForEach(DllBegin(list),DllEnd(list), &IncByOne, list);
	
	iter = DllBegin(list);
	for (i = 0; i < NUM; ++i)
	{
		if((arr[i]) != *(int*)DllGetData(iter))
		{
			printf("%s%d: Test Dll For-Each failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = DllGetNext(iter);
	}
	printf("%s --Test Dll For-Each done--\n%s", GREEN, RESET);
	
	DllDestroy(list);
}


void TeatDllSplice(void)
{
	dll_t* src = DllCreate();
	dll_t* dst = DllCreate();
	int list1[] = {1,2,3,4,5,6,7};
	int list2[] = {1,2,3,8,9,10,4,5,6};
	int i = 0;
	dll_iterator_t from = NULL;
	dll_iterator_t to = NULL;
	dll_iterator_t iter = NULL;
	
	for(i = 0; i < 7; ++i)
	{
		DllPushBack(src,&list1[i]);
	}
	for(i = 0; i < 9; ++i)
	{
		DllPushBack(dst, &list2[i]);
	}
	
	iter = DllEnd(src);
	from = DllGetNext(DllGetNext(DllGetNext(DllBegin(dst))));
	to = DllGetNext(DllGetNext(DllGetNext(from)));
	
	DllSplice(iter,from,to);
	
	iter = DllBegin(src);
	for (i = 0; i < NUM; ++i)
	{
		if(i+1 != *(int*)DllGetData(iter))
		{
			printf("%s%d: Test Dll Multi-Find failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 
		}
		iter = DllGetNext(iter);
	}

	printf("%s --Test Dll Splice done--\n%s", GREEN, RESET);
	DllDestroy(src);
	DllDestroy(dst);
}

static int IncByOne(void* x, void* args)
{
	++(*(int*)x);
	args = (void*)args;
	
	return SUCCESS;
}


static int is_match(void* x1,void* x2)
{
	return *(int*)x1 == *(int*)x2;
}


static int Is_MatchForMultiy(void* arg1, void* arg2)
{
	(void)(arg2);	
	
	return ((*(int*)arg1) % 2 == 0);

}


