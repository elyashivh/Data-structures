#include <stdio.h>		/*printf*/
#include <stdlib.h>		/*malloc & free*/
#include <stddef.h>		/*size_t*/
#include <assert.h>		/*assert*/

#include "linked_list_ex.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define NUM_OF_ELEMENTS (10)

void TestFlip(void);
void TestHasLoop(void);
void TestFindIntersection(void);
static node_t* CreateNode(void* data);
static node_t* CreateList(void);
static node_t* CreateLoopList(void);
static void PrintList(node_t* head);
void DestroyList(node_t* head, int num);

static int num_of_failurs = 0;


int main ()
{

	TestFlip();
	TestHasLoop();
	TestFindIntersection();
	
	printf("%d Tests failed\n", num_of_failurs);
	
	return 0;
}



void TestFlip(void)
{
	node_t* head = CreateList();
	printf("The original list is: \n");
	PrintList(head);
	head = Flip(head);
	printf("After filp list is: \n");
	PrintList(head);
	DestroyList(head, NUM_OF_ELEMENTS);	
	
	printf("%s --Test Flip done--\n%s", GREEN, RESET);
}

void TestHasLoop(void)
{
	node_t* head1 = CreateList();
	node_t* head2 = CreateLoopList();
	
	if (0 != HasLoop(head1))
	{
		printf("%s%d: Test Has-Loop failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	if (1 != HasLoop(head2))
	{
		printf("%s%d: Test Has-Loop failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}
	
	DestroyList(head1, NUM_OF_ELEMENTS);
	DestroyList(head2, NUM_OF_ELEMENTS);		
	printf("%s --Test Has-Loop done--\n%s", GREEN, RESET);
}


void TestFindIntersection(void)
{
	int num1 = 100;
	int num2 = 200;
	node_t* head = CreateList();
	node_t* head_intersection = CreateNode(&num1);
	node_t* node_a = CreateNode(&num2);
	
	head_intersection->next = node_a;
	node_a->next = head;
	
	
	if (10 != *(int*)FindIntersection(head, head_intersection)->data)
	{
		printf("%s%d: Test Test Find-Intersection failed\n%s", RED, __LINE__, RESET);
		++num_of_failurs; 	
	}

	DestroyList(head, NUM_OF_ELEMENTS);
	DestroyList(head_intersection, 2);		
	
	printf("%s --Test Find-Intersection done--\n%s", GREEN, RESET);
}

static node_t* CreateNode(void* data)
{
	node_t* head = malloc (sizeof(node_t));
	if (NULL == head)
	{
		return NULL;
	}

	head->data = data;
	head->next = NULL;
	
	return head;
}


static node_t* CreateList(void)
{
	static int arr[NUM_OF_ELEMENTS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	node_t* head = CreateNode(arr);
	node_t* node_a = CreateNode(arr + 1);
	node_t* node_b = CreateNode(arr + 2);
	node_t* node_c = CreateNode(arr + 3);
	node_t* node_d = CreateNode(arr + 4);
	node_t* node_e = CreateNode(arr + 5);
	node_t* node_f = CreateNode(arr + 6);
	node_t* node_g = CreateNode(arr + 7);
	node_t* node_h = CreateNode(arr + 8);
	node_t* node_i = CreateNode(arr + 9);
	head->next = node_a;
	node_a->next = node_b;
	node_b->next = node_c;
	node_c->next = node_d;
	node_d->next = node_e;
	node_e->next = node_f;
	node_f->next = node_g;
	node_g->next = node_h;
	node_h->next = node_i;
	
	return head;
}

static node_t* CreateLoopList(void)
{
	static int arr[NUM_OF_ELEMENTS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	node_t* head = CreateNode(arr);
	node_t* node_a = CreateNode(arr + 1);
	node_t* node_b = CreateNode(arr + 2);
	node_t* node_c = CreateNode(arr + 3);
	node_t* node_d = CreateNode(arr + 4);
	node_t* node_e = CreateNode(arr + 5);
	node_t* node_f = CreateNode(arr + 6);
	node_t* node_g = CreateNode(arr + 7);
	node_t* node_h = CreateNode(arr + 8);
	node_t* node_i = CreateNode(arr + 9);
	head->next = node_a;
	node_a->next = node_b;
	node_b->next = node_c;
	node_c->next = node_d;
	node_d->next = node_e;
	node_e->next = node_f;
	node_f->next = node_g;
	node_g->next = node_h;
	node_h->next = node_i;
	node_i->next = node_e;
	
	return head;
}

/*static node_t* CreateIntersectionList(node_t* head)*/
/*{*/
/*	static int arr2[3] = {1, 2, 3};*/
/*	size_t i = 0;*/
/*	*/
/*	node_t* head_intersection = CreateNode(arr2);*/
/*	node_t* node_a = CreateNode(arr2 + 1);*/
/*	node_t* node_b = CreateNode(arr2 + 2);*/
/*	node_t* node_c = CreateNode(arr2 + 3);*/
/*	*/
/*	head = head->next->head->next->head->next;*/
/*	*/
/*	node_a->next = node_b;*/
/*	node_b->next = node_c;*/
/*	node_c->next = node_d;*/
/*	*/
/*	return head;*/
/*}*/


static void PrintList(node_t* head)
{
	size_t i = 0;
	for (i = 0; i < NUM_OF_ELEMENTS; ++i)
	{
		printf("%d --> ", *(int*)head->data);
		head = head->next;
	}
	printf("NULL \n");
}

void DestroyList(node_t* head, int num)
{
	int i = 0; 
	node_t* temp;
	assert (NULL != head);

	for (i = 0; i < num; ++i)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}




















