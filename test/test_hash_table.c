#include <stdio.h>
#include <stddef.h>		
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "hash_table.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define STYLE_BOLD "\x1b[1m"
#define COLOR_MAGENTA "\x1b[35m"
#define RESET_ALL "\x1b[0m"
#define SUCCESS (0)
#define FAIL (1)
#define NUM (100)
#define SIZE (10)
#define FALSE (0)
#define TRUE (1)


size_t HashFuncInt(void* key);
int IsSameKeyInt(void* entry, void* key);
int MultByTen(void* x, void* args);
int IsSameKeyStr(void* entry, void* key);
size_t HashFuncStr(void* key);

void TestHashCreateAndDestroy(void);
void TestHashInsert(void);
void TestHashRemove(void);
void TestHashFind(void);
void TestHashForEach(void);
void TestLoadDict(void);



static int num_of_failurs = 0;


int main ()
{
	
	/* TestHashCreateAndDestroy();
	TestHashInsert();
	TestHashRemove();
	TestHashFind();
 	TestHashForEach(); */
	TestLoadDict();


	if (!num_of_failurs)
	{
		printf(COLOR_MAGENTA STYLE_BOLD "----All tests passed successfully----\n" RESET_ALL);
	}

	return 0;
}

void TestHashCreateAndDestroy(void)
{
	hash_table_t* table = HashCreate(NUM, HashFuncInt, IsSameKeyInt);
    if (table == NULL)
	{
		printf(COLOR_RED"%d: Test Hash-Create failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	HashDestroy(table);
	
    printf(COLOR_GREEN "--Test Hash Create done--\n" RESET_ALL);
	printf(COLOR_GREEN "--Test Hash Destroy done--\n" RESET_ALL);
}

void TestHashInsert(void)
{
	hash_table_t* table = HashCreate(NUM, HashFuncInt, IsSameKeyInt);
	size_t i = 0;
	int arr[NUM_OF_DICT] = {0,1,2,3,4,5,6,7,8,9};

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		if (FAIL == HashInsert(table, arr+i, arr+i))
		{
			printf(COLOR_RED"%d: Test Hash-Insert failed \n"RESET_ALL, __LINE__);
			++num_of_failurs; 	
		}
	}
	if (TRUE == HashIsEmpty(table))
	{
		printf(COLOR_RED"%d: Test Hash-Insert failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}
	if (NUM_OF_DICT != HashCount(table))
	{
		printf(COLOR_RED"%d: Test Hash-Insert failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}


	HashDestroy(table);
	
	printf(COLOR_GREEN "--Test Hash Insert done--\n" RESET_ALL);
}

void TestHashRemove(void)
{
	hash_table_t* table = HashCreate(NUM, HashFuncInt, IsSameKeyInt);
	size_t i = 0;
	int arr[NUM_OF_DICT] = {0,1,2,3,4,5,6,7,8,9};

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		HashInsert(table, arr+i, arr+i);
	}

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		HashRemove(table, arr+i);
		if (NUM_OF_DICT-i-1 != HashCount(table))
		{
			printf(COLOR_RED"%d: Test Hash-Remove failed \n"RESET_ALL, __LINE__);
			++num_of_failurs; 	
		}
	}

	if (FALSE == HashIsEmpty(table))
	{
		printf(COLOR_RED"%d: Test Hash-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	if (0 != HashCount(table))
	{
		printf(COLOR_RED"%d: Test Hash-Remove failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	HashDestroy(table);

	printf(COLOR_GREEN "--Test Hash Remove done--\n" RESET_ALL);
	printf(COLOR_GREEN "--Test Hash Count done--\n" RESET_ALL);
	printf(COLOR_GREEN "--Test Hash Is-Empty done--\n" RESET_ALL);
}

void TestHashFind(void)
{
	hash_table_t* table = HashCreate(NUM, HashFuncInt, IsSameKeyInt);
	size_t i = 0;
	int arr[NUM_OF_DICT] = {0,1,2,3,4,5,6,7,8,9};
	int num = 10;

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		HashInsert(table, arr+i, arr+i);
	}

	if (NULL != HashFind(table, &num))
	{
		printf(COLOR_RED"%d: Test Hash-Find failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	if (5 == *(int*)HashFind(table, arr+5))
	{
		printf(COLOR_RED"%d: Test Hash-Find failed \n"RESET_ALL, __LINE__);
		++num_of_failurs; 	
	}

	HashDestroy(table);
	printf(COLOR_GREEN "--Test Hash Find done--\n" RESET_ALL);
}

void TestHashForEach(void)
{
	hash_table_t* table = HashCreate(NUM, HashFuncInt, IsSameKeyInt);
	size_t i = 0;
	int arr[NUM_OF_DICT] = {0,1,2,3,4,5,6,7,8,9};
	int key[NUM_OF_DICT] = {0,1,2,3,4,5,6,7,8,9};

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		HashInsert(table, arr+i, key+1);
	}

	HashForEach(table, MultByTen, NULL);

	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		if ((int)i*10 == *(int*)HashFind(table, arr+i))
		{
			printf(COLOR_RED"%d: Test Hash-For-Each failed \n"RESET_ALL, __LINE__);
			++num_of_failurs; 	
		}
	}
	
	HashDestroy(table);
	printf(COLOR_GREEN "--Test Hash-For-Each done--\n" RESET_ALL);	
}

void TestLoadDict(void)
{
	size_t i = 0;
	hash_table_t* table = HashCreate(NUM/2, HashFuncStr, IsSameKeyStr);
	char** str = NULL;
	size_t num_of_words = 104334;
	char temp[NUM_OF_DICT*NUM_OF_DICT] = {0};
	void* res = NULL;
	FILE* dict = fopen("/usr/share/dict/words", "r");
	if (NULL == dict)
	{
		printf(COLOR_RED"%d: Test Load-Dict failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
		return;
	}

	str = malloc(num_of_words*sizeof(char*));
	if (NULL == str)
	{
		printf(COLOR_RED"%d: Test Load-alloc failed \n"RESET_ALL, __LINE__);
		++num_of_failurs;
		return;
	}

	for (i = 0; i < num_of_words; ++i)
	{
		fgets(temp, NUM_OF_DICT*NUM_OF_DICT, dict);
		str[i] = (char*)malloc(sizeof(char)*strlen(temp) + 1);
		if (NULL == str[i])
		{
			printf(COLOR_RED"%d: Test Load-Dict- copy word failed \n"RESET_ALL, __LINE__);
			++num_of_failurs;
			return;
		}

		strcpy(str[i], temp);

		if (FAIL == HashInsert(table, str[i], str[i]))
		{
			printf(COLOR_RED"%d: Test Load-Dict-(insert to table) failed \n"RESET_ALL, __LINE__);
			++num_of_failurs;
			return;
		}
	}

	printf("Enter a word to check for spelling\n");
	fgets(temp, NUM_OF_DICT*NUM_OF_DICT, stdin);
	res = HashFind(table, temp);
	if (NULL == res)
	{
		printf(COLOR_RED"Word is not spell \n"RESET_ALL);
	}
	else 
	{
		printf(COLOR_GREEN"Word is spell \n"RESET_ALL);
	}	
	
	for ( i = 0; i < num_of_words; ++i)
	{
		free(str[i]);
	}
	free(str);
	fclose(dict);
	HashDestroy(table);
}

size_t HashFuncInt(void* key)
{
	return *(int*)key % NUM;
}

size_t HashFuncStr(void* key)
{
	char c = *(char*)key;
	size_t letter = (size_t)c % 26;

	return letter;
}

int IsSameKeyInt(void* entry, void* key)
{
	return *(int*)((entry_t*)entry)->key == *(int*)key;
}

int IsSameKeyStr(void* entry, void* key)
{
	char* str1 = (char*)key;
	char* str2 = (char*)((entry_t*)entry)->key;

	return strcmp(str1, str2) == 0;
}

int MultByTen(void* entry, void* args)
{
	*(int*)((entry_t*)entry)->value = *(int*)((entry_t*)entry)->value * 10; 
	args = (void*)args;
	
	return SUCCESS;
}
