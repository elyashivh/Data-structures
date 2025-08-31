#include <stdio.h>

#include "vector.h"


#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define NUM_OF_TESTS (5)


void TestVectorCreateAndDestroy(void);
void TestVectorPushPopGetInt(void);
void TestVectorReserveAndShrink(void);

static int num_of_failurs = 0;
int main ()
{
	TestVectorCreateAndDestroy();
	TestVectorPushPopGetInt();
	TestVectorReserveAndShrink();
	
	printf("%d Tests failed\n", num_of_failurs);
	
	return 0;
}


void TestVectorCreateAndDestroy(void)
{
	vector_t* vector = VectorCreate(sizeof(int));
	
	if (NULL == vector)
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}

	VectorDestroy(vector);
	
	printf("%s --Test Vector Create And Destroy done--\n%s", GREEN, RESET);
}


void TestVectorPushPopGetInt(void)
{
	int i = 0;
	vector_t* vector = VectorCreate(sizeof(int));
	int tests[NUM_OF_TESTS] = {0, -100, 100, -1, 99};
	
	/* ---Test for Push function---*/
	for (i = 0; i < NUM_OF_TESTS; ++i)
	{
		if (SUCCESS != VectorPushBack(vector, (tests+i)))
		{
			printf("%s%d: Test Vector Push Int failed at %d iteration\n%s", RED, __LINE__, i, RESET);
			++num_of_failurs; 	
		}
	}
	
	/* ---Test for get size function---*/
	if (NUM_OF_TESTS != VectorGetSize(vector))
		{
			printf("%s%d: Test Vector Get Size failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 	
		}
		
	/* ---Test for get capacity function---*/
	if (8 != VectorGetCapacity(vector))
		{
			printf("%s%d: Test Vector Get Capacity failed\n%s", RED, __LINE__, RESET);
			++num_of_failurs; 	
		}
	
	/* ---Test for getAccess function---*/
	for (i = 0; i < NUM_OF_TESTS; ++i)
	{
		if (tests[i] != *(int*)VectorGetAccess(vector, i))
		{
			printf("%s%d: Test Vector Get Int failed at %d iteration\n%s", RED, __LINE__, i, RESET);
			++num_of_failurs; 	
		}
	}
	
	for (i = NUM_OF_TESTS-1; i >= 0; --i)
	{
		VectorPopBack(vector);
		
		if (tests[i] != *(int*)VectorGetAccess(vector, i))
		{
			printf("%s%d: Test Vector Get Int failed at %d iteration\n%s", RED, __LINE__, i, RESET);
			++num_of_failurs; 	
		}
	}
	
	printf("%s --Test Vector Push & Pop & Get Int done--\n%s", GREEN, RESET);
	VectorDestroy(vector);
}


void TestVectorReserveAndShrink(void)
{
	vector_t* vector = VectorCreate(sizeof(int));
	size_t i = 0;	
	size_t tests[NUM_OF_TESTS] = {2, 3, 33, 64, 100};
	
	for (i = 0; i < NUM_OF_TESTS; ++i)
	{
		VectorReserve(vector, tests[i]);
		if (tests[i] != VectorGetCapacity(vector))
		{
			printf("%s%d: Test Vector Reserve failed at %ld iteration\n%s", RED, __LINE__, i, RESET);
			printf("%ld\n", VectorGetCapacity(vector));
			printf("%ld\n", tests[i]);
			++num_of_failurs; 	
		}
	}
	VectorDestroy(vector);
	
	printf("%s --Test Vector Reserve And Shrink done--\n%s", GREEN, RESET);
}








