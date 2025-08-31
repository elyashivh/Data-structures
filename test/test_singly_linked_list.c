#include <stdio.h>
#include <assert.h>
#include "singly_linked_list.h"



#include <stdio.h>		/*printf*/
#include <stddef.h>		/*size_t*/


#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


void TestSll(void);
static int IncByOne(void* x, void* args);
static int is_match(void* x1,void* x2);
void TestAppend(void);

static int num_of_failurs = 0;

int main ()
{
	TestSll();	
	TestAppend();
	
	
	printf("%d Tests failed\n", num_of_failurs);
	
	return 0;
}



void TestSll(void)
{
	int num = 0;
	int num1 = 20;
	int num2 = 20;
	int num3 = 30;
	int num4 = 40;
	int num5 = 1;

	list_t* list = SllCreate(); 
	iterator_t iter1 = NULL;
	
	/*Test Sll create*/
	if (NULL == list)
	{
		printf("%s%d: Test Sll-Create failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	printf("%s --Test Sll create done--\n%s", GREEN, RESET);
	
	
	/*Test Sll insert & Is-Empty*/
	if (1 != SllIsEmpty(list))
	{
		printf("%s%d: Test Sll is-empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	if (0 != SllSize(list))
	{
		printf("%s%d: Test Sll Sll-Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	
	iter1 = SllBegin(list);
	iter1 = SllInsert(list, iter1, &num);
	iter1 = SllInsert(list, iter1, &num1);
	iter1 = SllInsert(list, iter1, &num2);
	iter1 = SllInsert(list, iter1, &num3);
	iter1 = SllInsert(list, iter1, &num4);
	
	if (0 != SllIsEmpty(list))
	{
		printf("%s%d: Test Sll is-empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	
	printf("%s --Test Sll insert done--\n%s", GREEN, RESET);
	printf("%s --Test Sll Is-Empty done--\n%s", GREEN, RESET);
	
	
	/*Test Sll Size*/
	if (5 != SllSize(list))
	{
		printf("%s%d: Test Sll Sll-Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sll Size done--\n%s", GREEN, RESET);
	
	
	/*Test Sll Get-Data & Sll-Begin*/
	iter1 = SllGetNext(SllGetNext(iter1));
	
	if (20 != *(int*)SllGetData(iter1))
	{
		printf("%s%d: Test Sll Get-data failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	if (40 != *(int*)SllGetData(SllBegin(list)))
	{
		printf("%s%d: Test Sll Get-data failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sll Get-Data done--\n%s", GREEN, RESET);
	printf("%s --Test Sll-Begin done--\n%s", GREEN, RESET);


	/*Test Sll Remove*/
	iter1 = SllRemove(iter1);
	iter1 = SllRemove(SllBegin(list));
	if (3 != SllSize(list))
	{
		printf("%s%d: Test Sll Size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sll Remove done--\n%s", GREEN, RESET);
	
	
	/*Test Sll For-Each*/
	SllForEach(SllBegin(list),SllEnd(list),&IncByOne, list);
	if (31 != *(int*)SllGetData(SllBegin(list)))
	{
		printf("%s%d: Test Sll-For-Each failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sll-For-Each  done--\n%s", GREEN, RESET);
	
	
	/*Test Sll Find*/
	if (num5 != *(int*)SllGetData(SllFind(SllBegin(list), SllEnd(list), &num5, is_match)))
	{
		printf("%s%d: Test Sll-Find failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Sll-Find done--\n%s", GREEN, RESET);
	
	/*Test Sll Destroy*/
	SllDestroy(list);
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


void TestAppend(void)
{
	
	list_t* list1 = SllCreate();
	list_t* list2 = SllCreate();
	int num1 = 0;
	int num2 = 1;
	int num3 = 2;
	int num4 = 3;
	int num5 = 10;
	int num6 = 20;
	int num7 = 30;
	int num8 = 40;
	
	iterator_t iter1;
	iterator_t iter2;
	
	iter1 = SllBegin(list1);
	iter1 = SllInsert(list1, iter1, &num5);
	iter2 = SllInsert(list1, iter1, &num6);
	iter2 = SllInsert(list1, iter1, &num7);
	iter2 = SllInsert(list1, iter1, &num8);
	
	iter2 = SllBegin(list2);
	iter2 = SllInsert(list2, iter2, &num1);
	iter2 = SllInsert(list2, iter2, &num2);
	iter2 = SllInsert(list2, iter2, &num3);
	iter2 = SllInsert(list2, iter2, &num4);
	
	SllAppend(list1, list2);

	iter1 = SllBegin(list1);
	while(iter1 != SllEnd(list1))
	{
		printf("%d-->", *(int*)SllGetData(iter1));
		iter1 = SllGetNext(iter1);
	}
	printf("\n");
	SllDestroy(list1);
	SllDestroy(list2);
}

