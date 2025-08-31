#ifndef __LINKED_LIST_EX_H__
#define __LINKED_LIST_EX_H__



typedef struct node
{
	void* data;
	struct node* next;
} node_t;

/*Revese the order of a given slist*/
node_t* Flip(node_t* head);

/*Tells whether a given slist has loop*/
int HasLoop(const node_t* head);

/*Returns a pointer to a first node mutual to both slist*/
node_t* FindIntersection(node_t* head_1, node_t* head_2);




#endif /* end of header guard __LINKED_LIST_EX_H__ */
