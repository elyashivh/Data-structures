#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "avl.h"

#define SUCCESS (0)
#define FAIL (1)
#define TRUE (1)
#define FALSE (0)


/*Macro definitions*/
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

/*Global vars*/
static int num_of_fails;


static const char *red = "\033[31m";
static const char *green = "\033[32m";
static const char *yellow = "\033[33m";
static const char *reset = "\033[0m";

typedef struct
{
    int arr[10];
    int j;
}for_tests_t;

static int Comparator(const void* data, const void* key)
{
    return *(int*)data - *(int*)key;
}

static int StringComparator(const void* data, const void* key)
{
    return strcmp((const char*)data, (const char*)key);
}
static int CheckTree(void* data, void* args)
{
    for_tests_t* temp = (for_tests_t*)args; 

    if( temp->arr[temp->j] != *(int*)data)
    {
        return FAIL;
    }
    temp->j += 1;
    return SUCCESS;
}

static int TestInsert();
static int TestInsertMore();
static int TestRemove();
static int TestFind();
static int TestForEach();
static int TestIsEmpty();
static int TestSize();
static int TestHeight();
static void TestInsertWithHeight();

int main()
{
    int num_fails = 0;

    num_fails += TestCreateAndDestroy();
    num_fails += TestInsert();
    num_fails +=TestInsertMore();
    num_fails += TestRemove();
    num_fails += TestFind();
    num_fails += TestForEach();
    num_fails += TestIsEmpty();
    num_fails += TestSize();
    num_fails += TestHeight();

    TestInsertWithHeight();
    if(num_fails == 0)
    {
        printf("%sAll Tests has passed!%s\n",green, reset);
    }
    else
    {
        printf("%sSome Tests has failed!%s\n", red, reset);
    }
    return 0;
}


static void TestInsertWithHeight()
{
    avl_t *avl = AVLCreate(Comparator);
    int arr[] = {20, 10, 30, 40};
    int right_right_rotate = 50;
    int arr2[] = {5, 15, 3};
    int left_left_rotate = 0;
    int arr3[] = {35, 25, 45, 55, 60};
    int right_left_rotation = 57;
    size_t i = 0;

    assert(NULL != avl);

    printf("%sTesting InsertWithHeight...%s\n", YELLOW, RESET);
    for (i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        if (0 != AVLInsert(avl, &arr[i], &arr[i]))
        {
            printf("%sInsertWithHeight test failed on inserting%s\n", RED, RESET);
            ++num_of_fails;
            return;
        }
    }

    if (3 != AVLHeight(avl) + 1)
    {
        printf("%sInsertWithHeight test failed%s\n", RED, RESET);
        ++num_of_fails;
        return;
    }

    AVLInsert(avl, &right_right_rotate, &right_right_rotate);
    if (3 != AVLHeight(avl) + 1)
    {
        printf("%sInsertWithHeight test failed on right-right rotation.%s\n", RED, RESET);
        ++num_of_fails;
        return;
    }


    for (i = 0; i < sizeof(arr2) / sizeof(int); i++)
    {
        if (0 != AVLInsert(avl, &arr2[i], &arr2[i]) )
        {
            printf("%sInsertWithHeight test failed on inserting%s\n", RED, RESET);
            ++num_of_fails;
            return;
        }
    }


    if (4 != AVLHeight(avl) + 1)
    {
        printf("%sInsertWithHeight test failed%s\n", RED, RESET);
        ++num_of_fails;
        return;
    }

    AVLInsert(avl, &left_left_rotate, &left_left_rotate);
    if (4 != AVLHeight(avl) + 1)
    {
        printf("%sInsertWithHeight test failed on left-left rotation.%s\n", RED, RESET);
        ++num_of_fails;
        return;
    }

    for (i = 0; i < sizeof(arr3) / sizeof(int); i++)
    {
        if (0 != AVLInsert(avl, &arr3[i], &arr3[i]) )
        {
            printf("%sInsertWithHeight test failed on inserting%s\n", RED, RESET);
            ++num_of_fails;
            return;
        }
    }

    if (5 != AVLHeight(avl) + 1)
    {
        printf("%sInsertWithHeight test failed%s\n", RED, RESET);
        ++num_of_fails;
        return;
    }


    AVLInsert(avl, &right_left_rotation, &right_left_rotation);

    if (5 != AVLHeight(avl) + 1)
    {
        printf("%sInsertWithHeight test failed on right-left rotation.%s\n", RED, RESET);
        ++num_of_fails;
        return;
    }

    AVLDestroy(avl);
    printf("%sInsertWithHeight test passed.%s\n", GREEN, RESET);
}



static int TestFind()
{
    int num_fails = 0;

    avl_t* tree = AVLCreate(StringComparator);
    size_t i = 0;
    char* arr[] = { "abc", "bcd", "aaa","hello"};
    char* string_to_find1 = "aaa";
    char* string_to_find2 = "hello";
    void* return_value_to_check = NULL;

    printf("%sTesting TestFind!\n%s",yellow, reset );

    for( i = 0; i < sizeof(arr)/sizeof(char*) ; ++i)
    {
        AVLInsert(tree,arr[i], arr[i]);
    }
    
    return_value_to_check = AVLFind(tree,string_to_find1);
    if(strcmp(string_to_find1,return_value_to_check) != 0)
    {
        ++num_fails;
        printf("%sTest number #1 failed in TestFind!\n%s",red, reset);
    }
    return_value_to_check = AVLFind(tree,string_to_find2);
    if(strcmp(string_to_find2,return_value_to_check) != 0)
    {
        ++num_fails;
        printf("%sTest number #2 failed in TestFind!\n%s",red, reset);
    }

    AVLDestroy(tree);

    if(num_fails == 0)
    {
        printf("%sTest ended succesfully!\n%s", green, reset);
    }


    return num_fails;
}
static int TestForEach()
{
    int num_fails = 0;
    avl_t* tree = AVLCreate(Comparator);
    size_t i = 0;
    int arr[] = { 1, 2 ,3 ,4 ,5};
    for_tests_t ftt_in_order = { {1,2,3,4,5}, 0};
    for_tests_t ftt_pre_order = { {2,1,4,3,5}, 0};
    for_tests_t ftt_post_order = { {1,3,5,4,2}, 0};

    printf("%sTesting TestForEach!\n%s",yellow, reset );

    for( i = 0; i < sizeof(arr)/sizeof(int); ++i)
    {
        if( AVLInsert(tree,arr+i, arr+i) != SUCCESS)
        {
            printf("%sFailed TestForEach in line: %d%s\n", red, __LINE__, reset);
        }
    }


    if(AVLForeach(tree, CheckTree, &ftt_in_order, IN_ORDER) == FAIL)
    {
        ++num_fails;
        printf("%sFailed TestForEach in order in line: %d%s\n", red, __LINE__, reset);
    }

    if(AVLForeach(tree, CheckTree, &ftt_pre_order, PRE_ORDER) == FAIL)
    {
        ++num_fails;
        printf("%sFailed TestForEach pre order in line: %d%s\n", red, __LINE__, reset);
    } 
    
    if(AVLForeach(tree, CheckTree, &ftt_post_order, POST_ORDER) == FAIL)
    {
        ++num_fails;
        printf("%sFailed TestForEach post order in line: %d%s\n", red, __LINE__, reset);
    }

    AVLDestroy(tree);
    if(num_fails == 0)
    {
        printf("%sTest ended succesfully!\n%s", green, reset);
    }
    return num_fails;
}
static int TestIsEmpty()
{
    int num_fails = 0;

    avl_t* tree = AVLCreate(StringComparator);
    size_t i = 0;
    char* arr[] = { "abc", "bcd", "aaa","hello"};


    printf("%sTesting TestIsEmpty!\n%s",yellow, reset );

    if(AVLIsEmpty(tree) != TRUE)
    {
        ++num_fails;
        printf("%sTest #1 TestIsEmpty has failed in line %d!%s\n",red, __LINE__, reset);
    }

    for( i = 0; i < sizeof(arr)/sizeof(char*) ; ++i)
    {
        AVLInsert(tree,arr[i], arr[i]);
    }
    
    if(AVLIsEmpty(tree) != FALSE)
    {
        ++num_fails;
        printf("%sTest #2 TestIsEmpty has failed in line %d!%s\n",red, __LINE__, reset);
    }
    for( i = 0; i < sizeof(arr)/sizeof(char*) ; ++i)
    {
        AVLRemove(tree, arr[i]);
    }

    if(AVLIsEmpty(tree) != TRUE)
    {
        ++num_fails;
        printf("%sTest #1 TestIsEmpty has failed in line %d!%s\n",red, __LINE__, reset);
    }

    AVLDestroy(tree);

    if(num_fails == 0)
    {
        printf("%sTest ended succesfully!\n%s", green, reset);
    }


    return num_fails;
}
static int TestSize()
{
    int num_fails = 0;

    avl_t* tree = AVLCreate(StringComparator);
    size_t i = 0;
    char* arr[] = { "abc", "bcd", "aaa","hello"};


    printf("%sTesting TestSize!\n%s",yellow, reset );

    for( i = 0; i < sizeof(arr)/sizeof(char*) ; ++i)
    {
        AVLInsert(tree,arr[i], arr[i]);
        if(AVLSize(tree) != i + 1)
        {
            printf("%sTest #1 TestSize has failed in line %d!%s\n",red, __LINE__, reset);
        }
    }
    
    for( i = 0; i < sizeof(arr)/sizeof(char*) ; ++i)
    {
        AVLRemove(tree, arr[i]);
        if(AVLSize(tree) != (sizeof(arr)/sizeof(char*) - i - 1))
        {
            printf("%sTest #2 TestSize has failed in line %d!%s\n",red, __LINE__, reset);
        }
    }

    AVLDestroy(tree);

    if(num_fails == 0)
    {
        printf("%sTest ended succesfully!\n%s", green, reset);
    }


    return num_fails;
}
static int TestHeight()
{
    int num_fails = 0;

    avl_t* tree = AVLCreate(StringComparator);
    size_t i = 0;
    char* arr[] = { "abc", "bcd", "aaa","hello"};
    int res[] = {-1,0,1,1,2};

    printf("%sTesting TestHeight!\n%s",yellow, reset );

    if(AVLHeight(tree) != res[0])
    {
        printf("%sTest #1 TestHeight has failed in line %d!%s\n",red, __LINE__, reset);
    }
    for( i = 0; i < sizeof(arr)/sizeof(char*) ; ++i)
    {
        AVLInsert(tree,arr[i], arr[i]);
        if(AVLHeight(tree) != res[i+1])
        {
            printf("%sTest #2 TestHeight has failed in line %d!%s\n",red, __LINE__, reset);
        }
    }
    
    AVLDestroy(tree);

    if(num_fails == 0)
    {
        printf("%sTest ended succesfully!\n%s", green, reset);
    }


    return num_fails;
}
