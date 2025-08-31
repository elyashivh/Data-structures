#include <stdio.h>
#include <stdlib.h>		/*malloc & free*/

#include "stack.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define SIZE (10)

void TestStackCreateAndDestroy(void);
void TestStackPushAndPopAndPeek(void);
void TestStackIsEmptyAndSize(void);
void TestStackCapacity(void);

int main ()
{
	TestStackCreateAndDestroy();
	TestStackPushAndPopAndPeek();
	TestStackIsEmptyAndSize();
	TestStackCapacity();
	
	return 0;
}


void TestStackCreateAndDestroy(void)
{
	stack_t* stack = StackCreate(NUM_OF_DICT, sizeof(int));
	if (NULL != stack)
	{
		printf("%sCreated stack done\n%s", GREEN, RESET);
	}
	else
	{
		printf("%s%d:Created stack failed\n%s", RED, __LINE__, RESET); 	
	}
	
	StackDestroy(stack);
	printf("%sDestroy stack done\n%s", GREEN, RESET);
}


/*void StackPop(stack_t* stack)*/
/*{*/
/*	*/
/*}*/


void TestStackPushAndPopAndPeek(void)
{
	int num1 = 10;
	int num2 = 20;
	int ans1 = 0;
	int ans2 = 20;
	
	stack_t* stack = StackCreate(NUM_OF_DICT, sizeof(int));
	
	StackPush(stack, &num1);
	StackPush(stack, &num2);
	
	ans2 = *(int*)StackPeek(stack);
	if (num2 != ans2)
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	StackPop(stack);
	ans1 = *(int*)StackPop(stack);
	if (num1 != ans1)
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	StackDestroy(stack);
	printf("%sTestStackPushAndPopAndPeek done\n%s", GREEN, RESET);
}


void TestStackIsEmptyAndSize(void)
{
	int num1 = 10;
	int num2 = 20;
	int num3 = 30;
	stack_t* stack = StackCreate(NUM_OF_DICT, sizeof(int));
	
	if (0 != StackSize(stack))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	StackPush(stack, &num1);
	StackPush(stack, &num2);
	StackPush(stack, &num3);
	if (3 != StackSize(stack))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}	
	StackDestroy(stack);
	
	printf("%sTestStackIsEmptyAndSize done\n%s", GREEN, RESET);
}


void TestStackCapacity(void)
{
	stack_t* stack = StackCreate(NUM_OF_DICT, sizeof(int));
	if (NUM_OF_DICT != StackCapacity(stack))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	StackDestroy(stack);
	printf("%sTestStackCapacity done\n%s", GREEN, RESET);
}






