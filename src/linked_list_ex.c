#include <assert.h>		/*assert*/
#include <stddef.h>		/*NULL*/

#include "linked_list_ex.h"

/* 
* Author: Elyashiv Horden 
* Date: 3.12.2024
* Reviewer: Or Elyahu
*/

#define TRUE (1)
#define FALSE (0)

static size_t CountNodes(node_t* head);

/*Reverse the order of a given slist*/
node_t* Flip(node_t* head)
{
	node_t* curr = NULL;
	node_t* prev = NULL;
	node_t* next = NULL;
	assert(NULL != head);
	
	curr = head;
	next = head->next;
	head->next = NULL;

	while (NULL != next)
	{
		prev = curr;
		curr = next;
		next = next->next;
		curr->next = prev;
	}
	
	return curr;
}

/*Tells whether a given slist has loop*/
int HasLoop(const node_t* head)
{
	const node_t* runner = NULL;
	const node_t* stepper = NULL;
	assert(NULL != head);
	
	runner = head->next;
	stepper = head;
	while (NULL != runner->next)
	{
		if (stepper == runner)
		{
			return TRUE;
		}
		stepper = stepper->next;
		runner = runner->next;
		if (NULL != runner)
		{
			runner = runner->next;	
		}
		
	}
	return FALSE;
}

/*Returns a pointer to a first node mutual to both slist*/
node_t* FindIntersection(node_t* head_1, node_t* head_2)
{
	node_t* runner1 = head_1;
	node_t* runner2 = head_2;
	size_t len1 = 0;
	size_t len2 = 0;
	size_t i = 0;
	assert(NULL != head_1);
	assert(NULL != head_2);
	
	len1 = CountNodes(head_1);
	len2 = CountNodes(head_2);
	
	if (len1 > len2)
	{
		for (i = 0; i < len1 - len2; ++i)
		{
			runner1 = runner1->next;
		}
	}
	if (len1 < len2)
	{
		for (i = 0; i < len2 - len1; ++i)
		{
			runner2 = runner2->next;
		}
	}
	while (runner2 != runner1)
	{
		runner1 = runner1->next;
		runner2 = runner2->next;
	}
	
	return runner1;
}

static size_t CountNodes(node_t* head)
{
	size_t counter = 0;
	assert(NULL != head);

	while (NULL != head)
	{
		++counter;
		head = head->next;
	}
	return counter;
}









