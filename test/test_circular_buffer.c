#include <stdio.h>		/*printf*/
#include <stddef.h>		/*size_t*/

#include "circular_buffer.h"


#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

/*#define NUM_OF_TESTS (1)*/
#define CAPACITY (1000)


void TestCB(void);


static int num_of_failurs = 0;

int main ()
{
	TestCB();
	
	printf("%d Tests failed\n", num_of_failurs);
	
	return 0;
}


void TestCB(void)
{
	char str1[] = "abc";
	char str2[] = "123";
	char str3[] = "efg";
	char str4[] = "blblaa";
	char str5[] = "bl";
	char str6[] = "bla";
	
	size_t counter = 0;
	
	/*Test Create circular_buffer*/
	c_buffer_t* cb = CBCreate(1000);
	
	if (NULL == cb)
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	
	printf("%s --Test Circular Buffer Create done--\n%s", GREEN, RESET);
	
	
	/*Test is-empty*/
	if (1 != CBIsEmpty(cb))
	{
		printf("%s%d: Test CB is-empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Circular Buffer is-empty done--\n%s", GREEN, RESET);
	
/*	printf("free %ld\n", CBGetFreeSpace(cb));*/
/*	printf("size %ld\n", CBGetSize(cb));*/
/*	printf("couter %ld\n", counter);*/
	
	/*Test write data*/
	counter = CBWrite(cb, str1, 4);
/*	printf("free %ld\n", CBGetFreeSpace(cb));*/
/*	printf("size %ld\n", CBGetSize(cb));*/
/*	printf("couter %ld\n", counter);*/
	
	counter += 	CBWrite(cb, str2, 4);
/*	printf("free %ld\n", CBGetFreeSpace(cb));*/
/*	printf("size %ld\n", CBGetSize(cb));*/
/*	printf("couter %ld\n", counter);*/
	
	counter += 	CBWrite(cb, str3, 4);
/*	printf("free %ld\n", CBGetFreeSpace(cb));*/
/*	printf("size %ld\n", CBGetSize(cb));*/
/*	printf("couter %ld\n", counter);*/
	
	if (0 == counter)
	{
		printf("%s%d: Test CB Write failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Circular Buffer write done--\n%s", GREEN, RESET);
	
	
	/*Test get size*/
	if (CBGetSize(cb) != 12)
	{
		printf("%s%d: Test CB get-size failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Circular Buffer get-size done--\n%s", GREEN, RESET);
	
	/*Test free-space */
	if (CBGetFreeSpace(cb) != CAPACITY - counter)
	{
		printf("%s%d: Test CB free-space failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Circular Buffer free-space done--\n%s", GREEN, RESET);
	
	/*Test is-empty*/
	if (0 != CBIsEmpty(cb))
	{
		printf("%s%d: Test CB is-empty failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	
	printf("%s --Test Circular Buffer is-empty done--\n%s", GREEN, RESET);
	
	/*Test read data*/
	counter -= CBRead(str4, cb, 6);
	counter -= CBRead(str5, cb, 2);
	counter -= CBRead(str6, cb, 4);
	
	if (counter != CBGetSize(cb))
	{
		printf("%s%d: Test CB Test CB Read  failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 
	}
	printf("%s --Test Circular Buffer Read data done--\n%s", GREEN, RESET);
	
	CBDestroy(cb);
	
	printf("%s --Test Circular Buffer Destroy done--\n%s", GREEN, RESET);
}

