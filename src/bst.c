/*
Author:     Elyashiv Horden  
Date:		5-1-2025	    
CR: 	    Or Elyahu 	
*/
#include <assert.h>     /*assert*/
#include <stdlib.h>     /*malloc & free*/
#include "bst.h"

#define IS_EQUAL (0)
#define GET_ROOT(tree) (tree->root)
#define GET_LEFT(iter) (iter->left)
#define GET_RIGHT(iter) (iter->right)
#define GET_PARENT(iter) (iter->parent)
#define SET_DATA(iter) (iter->data)
#define GET_COMPRATOR(tree) (tree->comparator)

static iterator_t CreateNode(void* data);
static int IsLeftChild(iterator_t iter);
static int IsRightChild(iterator_t iter);
static int HaveLeftChild(iterator_t iter);
static int HaveRightChild(iterator_t iter);
static iterator_t FindSmallest(iterator_t iter);
static iterator_t FindLargest(iterator_t iter);
static status_t Counter(void* data, void* args);



struct node
{
    void* data;
    struct node* left;
    struct node* right;
    struct node* parent;
};

struct bst
{
    struct node root;
    bst_comp_t comparator;
};

bst_t* BSTCreate(bst_comp_t comparator)
{
    bst_t* tree = NULL;
    assert(comparator);

    tree = (bst_t*)malloc(sizeof(bst_t));
    if(!tree)
    {
        return NULL;
    }
    
    ROOT(tree).data = NULL;
    ROOT(tree).left = NULL;
    ROOT(tree).right = NULL;
    ROOT(tree).parent = NULL;
    GET_COMPRATOR(tree) = comparator;

    return tree;
}

void BSTDestroy(bst_t* tree)
{
    assert (tree);

    while (!BSTIsEmpty(tree))
    {
        BSTRemove(BSTBegin(tree));
    }

   free(tree);
}
 
iterator_t BSTInsert(bst_t* tree, void* data)
{
    iterator_t new_node = NULL;
    iterator_t parent = NULL;
    iterator_t runner = NULL;
    iterator_t* edge = NULL;
    bst_comp_t comp = NULL;
    int comp_res = 0;
    assert(tree);

    parent = BSTEnd(tree);
    runner = GET_LEFT(parent);
    edge = &GET_LEFT(parent);
    comp = GET_COMPRATOR(tree);

    while (runner)
    {
        comp_res = comp(BSTGetData(runner), data);
        assert(IS_EQUAL != comp_res);
        parent = runner;

        if (comp_res > IS_EQUAL)
        {
            runner = GET_LEFT(runner);
            edge = &GET_LEFT(parent);
        }
        else
        {
            runner = GET_RIGHT(runner);
            edge = &GET_RIGHT(parent);
        }
    }

    new_node = CreateNode(data);
    if (!new_node)
    {
        return BSTEnd(tree);
    }
    GET_PARENT(new_node) = parent;
    *edge = new_node;
    return new_node;
}

void BSTRemove(iterator_t iter)
{
    iterator_t parent = NULL;
    iterator_t left_child = NULL;
    iterator_t right_child = NULL;
    iterator_t* parent_edge = NULL;
    assert(iter);

    parent = GET_PARENT(iter);
    assert(parent);
    parent_edge = (BSTIsEqual(GET_LEFT(parent), iter)) ? &(GET_LEFT(parent)) : &(GET_RIGHT(parent));
    left_child = GET_LEFT(iter);
    right_child = GET_RIGHT(iter);

    if (HaveRightChild(iter))
    {
        *parent_edge = right_child;
        GET_PARENT(right_child) = parent;

        right_child = FindSmallest(right_child);

        GET_LEFT(right_child) = left_child;

        if (left_child)
        {
            GET_PARENT(left_child) = right_child;
        }
    }

    else
    {
        *parent_edge = left_child;

        if (left_child)
        {
            GET_PARENT(left_child) = parent;
        }
    }

    GET_LEFT(iter) = NULL;
    GET_RIGHT(iter) = NULL;
    GET_PARENT(iter) = NULL;
    free(iter);
}

void* BSTGetData(const iterator_t iter)
{
    assert(iter);

    return iter->data;
}

iterator_t BSTFind(const bst_t* tree, void* data)
{
    iterator_t iter = NULL;
    int comp_res = 0;
    assert(tree);

    iter = GET_LEFT(BSTEnd(tree));
    while (iter)
    {
        comp_res = GET_COMPRATOR(tree)(BSTGetData(iter), data);
        if (IS_EQUAL == comp_res)
        {
            return iter;
        }
        iter = (comp_res > IS_EQUAL) ? (GET_LEFT(iter)) : (GET_RIGHT(iter));
    }

    return BSTEnd(tree);
}

status_t BSTForEach(iterator_t from, iterator_t to, bst_operation_t operation, void* args)
{
    status_t status = OPERATION_FAILED;
    assert(from);
    assert(to);
    assert(operation);

    while(!BSTIsEqual(from, to))
    {
        status = operation(BSTGetData(from), args);
        if (SUCCESS != status)
        {
            return status;
        }
        from = BSTNext(from);
    }
    return status;
}

size_t BSTSize(const bst_t* tree)
{
    size_t counter = 0;
    assert(tree);

    BSTForEach(BSTBegin(tree), BSTEnd(tree), Counter, &counter);

    return counter;
}

int BSTIsEmpty(const bst_t* tree)
{
    assert(tree);

    return (ROOT(tree).left == NULL);
}

int BSTIsEqual(const iterator_t iter1, const iterator_t iter2)
{
    return iter1 == iter2;
}

iterator_t BSTPrev(const iterator_t iter)
{
    iterator_t runner = NULL;
    assert(iter);

    runner = GET_LEFT(iter);
    if (runner)
    {
        return FindLargest(runner);
    }
    runner = iter;

    while(IsLeftChild(runner))
    {
        runner = GET_PARENT(runner);
    }

    return GET_PARENT(runner);
}

iterator_t BSTNext(const iterator_t iter)
{
    iterator_t runner = NULL;
    assert(iter);
    
    runner = GET_RIGHT(iter);
    if (runner)
    {
        return FindSmallest(runner);
    }

    runner = iter;
    while (IsRightChild(runner))
    {
        runner = GET_PARENT(runner);
    }
    
    return GET_PARENT(runner);
}

iterator_t BSTBegin(const bst_t* tree)
{
    assert(tree);
    
    return FindSmallest(BSTEnd(tree));
}

iterator_t BSTEnd(const bst_t* tree)
{
    assert(tree);
    return &(((bst_t*)tree)->root);
}

static iterator_t CreateNode(void* data)
{
    iterator_t new_node = NULL;

    new_node = (iterator_t)malloc(sizeof(struct node));
    if(!new_node)
    {
        return NULL;
    }

    SET_DATA(new_node) = data;
    GET_LEFT(new_node) = NULL;
    GET_RIGHT(new_node) = NULL;
    GET_PARENT(new_node) = NULL;
 
    return new_node;
}

static int IsRightChild(iterator_t iter)
{
    return(BSTIsEqual(GET_RIGHT(GET_PARENT(iter)), iter));
}

static int IsLeftChild(iterator_t iter)
{
    return(BSTIsEqual(GET_LEFT(GET_PARENT(iter)), iter));
}

static int HaveLeftChild(iterator_t iter)
{
    return (NULL != GET_LEFT(iter)); 
}

static int HaveRightChild(iterator_t iter)
{
    return (NULL != GET_RIGHT(iter));
}

static iterator_t FindSmallest(iterator_t iter)
{
    while (HaveLeftChild(iter))
    {
        iter = GET_LEFT(iter);
    }
    
    return iter;
}

static iterator_t FindLargest(iterator_t iter)
{
    while(HaveRightChild(iter))
    {
        iter = GET_RIGHT(iter);
    }

    return iter;
}

static status_t Counter(void* data, void* args)
{
	(void) data;
	*(size_t*) args += 1;
	return SUCCESS;
}
