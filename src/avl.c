/*
Author:     Elyashiv Horden  
Date:		14-1-2024	    
CR: 	    Yehonatan Ailon
*/
#include <stdlib.h>     /*malloc & free*/
#include <stddef.h>     /*size_t*/
#include <assert.h>     /*assert*/

#include "avl.h"

#define SUCCESS (0)
#define FAILED (1)
#define TRUE (1)
#define FALSE (0)
#define DATA(node) (node->data)
#define LEFT_CHILD(node) (node->left)
#define RIGHT_CHILD(node) (node->right)
#define HEIGHT(node) (node->height)
#define KEY(node) (node->key)
#define COMPERATOR(tree) (tree->comparator)
#define ROOT(tree) (tree->root)
#define MAX(a,b) (((a) > (b)) ? (a) : (b))


typedef struct node_avl
{
    struct node_avl* left;
    struct node_avl* right;
    void* data;
    void* key;
    int height;
} node_avl_t;

struct avl
{
    node_avl_t* root;
    avl_comp_t comparator;
};


/*                       FORWARD DECLARATION                          */
/******************************************************************** */
static node_avl_t* AVLInsertRecursive(node_avl_t* node, void* data, void* key, avl_comp_t comperator);
static void AVLDestroyRecursive(node_avl_t* node);
static node_avl_t* AVLRemoveRecursive(node_avl_t* node, avl_comp_t comp, void* key);
static void* AVLFindRecursive(node_avl_t* node, void* key, avl_comp_t comp);
static int AVLForeachPre(node_avl_t* node, avl_operation_t operation, void* args);
static int AVLForeachPost(node_avl_t* node, avl_operation_t operation, void* args);
static int AVLForeachIn(node_avl_t* node, avl_operation_t operation, void* args);
static int IncByOne(void* data, void* args);
static node_avl_t* AVLCreateNode(void* data, void* key, node_avl_t* left_child, node_avl_t* right_child, int height);
static int AVLHaveRightChild(node_avl_t* node);
static int AVLHaveLeftChild(node_avl_t* node);
static node_avl_t* AVLGetNextRecusive(node_avl_t* node);
static node_avl_t* AVLBalanceSubTree(node_avl_t* node);
static node_avl_t* AVLRotateLeft(node_avl_t* node);
static node_avl_t* AVLRotateRight(node_avl_t* node);
static int AVLGetMaxHeight(node_avl_t* left_child, node_avl_t* right_child);
static int BalanceFactor(node_avl_t* node);
static int GetHeight(node_avl_t* node);
/********************************************************************* */



/*                           API FUNCTION                               */
/********************************************************************** */

avl_t* AVLCreate(avl_comp_t comparator)
{
    avl_t* tree = NULL;
    assert(comparator);

    tree = (avl_t*)malloc(sizeof(avl_t));
    if(NULL == tree)
    {
        return NULL;
    }

    /*replace to macro*/
    tree->root = NULL;
    tree->comparator = comparator;
    /* tree->height = 0; */

    return tree;
}

void AVLDestroy(avl_t* tree)
{
    assert(tree);

    if (NULL != ROOT(tree))
    {
        AVLDestroyRecursive(ROOT(tree));
    }

    free(tree);
}

int AVLInsert(avl_t* tree, void* data, void* key)
{
    assert(tree);
    
    if (NULL == ROOT(tree))
    {
        ROOT(tree) = AVLCreateNode(data, key, NULL, NULL, 0);
        if (NULL == ROOT(tree))
        {
            return FAILED;
        }
    }
    ROOT(tree) = AVLInsertRecursive(ROOT(tree), data, key, COMPERATOR(tree));
    if (NULL == ROOT(tree))
    {
        return FAILED;
    }

    return SUCCESS;
} 

/* balance func */
void AVLRemove(avl_t* tree, void* key)
{
    assert(tree);
    assert(key);

    ROOT(tree) = AVLRemoveRecursive(ROOT(tree), COMPERATOR(tree), key);
}

void* AVLFind(avl_t* tree, void* key)
{
    assert(tree);
    assert(key);

    return AVLFindRecursive(ROOT(tree), key, COMPERATOR(tree));
}

int AVLForeach(avl_t* tree, avl_operation_t operation, void* args, traversal_type_t traversal_type)
{
    assert(tree);
    assert(operation);

    if (traversal_type == IN_ORDER)
    {
        return AVLForeachIn(ROOT(tree), operation, args);
    }
    else if (traversal_type == PRE_ORDER)
    {
        return AVLForeachPre(ROOT(tree), operation, args);
    }
    else 
    {
        return AVLForeachPost(ROOT(tree), operation, args);
    }
}

int AVLIsEmpty(const avl_t* tree)
{
    assert(tree);

    return (ROOT(tree) == NULL);
}

size_t AVLSize(const avl_t* tree)
{
    size_t counter = 0;
    assert(tree);
    if (NULL == ROOT(tree))
    {
        return 0;
    }

    AVLForeach((avl_t*)tree, &IncByOne, &counter, IN_ORDER);
    return counter;
}

size_t AVLHeight(const avl_t* tree)
{
    assert(tree);

    return ROOT(tree) == NULL ? -1 : HEIGHT(ROOT(tree));
}


/*                          STATIC FUNCTION                             */
/********************************************************************** */
static node_avl_t* AVLInsertRecursive(node_avl_t* node, void* data, void* key, avl_comp_t comperator)
{
    if (NULL == node)
    {
        return AVLCreateNode(data, key, NULL, NULL, 0);
    }
    /*assert(comperator(DATA(node), key) != 0) to unsupport double keys*/
    if (comperator(DATA(node), key) > 0)
    {
        LEFT_CHILD(node) = AVLInsertRecursive(LEFT_CHILD(node), data, key, comperator);
    }
    else if (comperator(DATA(node), key) < 0)
    {
        RIGHT_CHILD(node) = AVLInsertRecursive(RIGHT_CHILD(node), data, key, comperator);
    }

    HEIGHT(node) = 1 + AVLGetMaxHeight(LEFT_CHILD(node), RIGHT_CHILD(node));

    return AVLBalanceSubTree(node);
}

static void AVLDestroyRecursive(node_avl_t* node)
{
    if (AVLHaveLeftChild(node))
    {
        AVLDestroyRecursive(LEFT_CHILD(node));
    }
    if (AVLHaveRightChild(node))
    {
        AVLDestroyRecursive(RIGHT_CHILD(node));
    }
    free(node);
}

static node_avl_t* AVLRemoveRecursive(node_avl_t* node, avl_comp_t comp, void* key)
{
    node_avl_t* temp = NULL;

    if (NULL == node)
    {
        return NULL;
    }

    if (comp(DATA(node), key) > 0)
    {
        LEFT_CHILD(node) = AVLRemoveRecursive(LEFT_CHILD(node), comp, key);
    }
    else if (comp(DATA(node), key) < 0)
    {
        RIGHT_CHILD(node) = AVLRemoveRecursive(RIGHT_CHILD(node), comp, key);
    }

    /*find the node to remove*/
    else 
    {
        /*have no children*/
        if (FALSE == AVLHaveLeftChild(node) && FALSE == AVLHaveRightChild(node))
        {
            free (node);
            return NULL;
        }
        /*have left child*/
        else if (FALSE == AVLHaveLeftChild(node))
        {
            temp = RIGHT_CHILD(node);
            free(node);
            return temp;
        }
        /*have right child*/
        else if (FALSE == AVLHaveRightChild(node))
        {
            temp = LEFT_CHILD(node);
            free(node);
            return temp;
        }
        /*have 2 children*/
        else
        {
            temp = AVLGetNextRecusive(RIGHT_CHILD(node));
            DATA(node) = DATA(temp);
            KEY(node) = KEY(temp);
            RIGHT_CHILD(node) = AVLRemoveRecursive(RIGHT_CHILD(node), comp, KEY(node));
        }
    }

    HEIGHT(node) = 1 + AVLGetMaxHeight(LEFT_CHILD(node), RIGHT_CHILD(node));
    return AVLBalanceSubTree(node);
}

static void* AVLFindRecursive(node_avl_t* node, void* key, avl_comp_t comp)
{
    if(node == NULL)
    {
        return NULL;
    }
    if (comp(DATA(node), key) == 0)
    {
        return DATA(node);
    }
    else if (comp(DATA(node), key) > 0)
    {
        return AVLFindRecursive(LEFT_CHILD(node), key,comp);
    }
    else 
    {
        return AVLFindRecursive(RIGHT_CHILD(node), key, comp);
    }
}

static int AVLForeachPre(node_avl_t* node, avl_operation_t operation, void* args)
{
    /*use LUT*/
    if (NULL == node)
    {
        return SUCCESS;
    }
    if (FAILED == operation(node->data, args))
    {
        return FAILED;
    }
    else if (FAILED == AVLForeachPre(LEFT_CHILD(node), operation, args))
    {
        return FAILED;
    }
    else if (FAILED == AVLForeachPre(RIGHT_CHILD(node), operation, args))
    {
        return FAILED;
    }

    return SUCCESS;
}

static int AVLForeachPost(node_avl_t* node, avl_operation_t operation, void* args)
{
    if (NULL == node)
    {
        return SUCCESS;
    }
    if (FAILED == AVLForeachPost(LEFT_CHILD(node), operation, args))
    {
        return FAILED;
    }
    else if (FAILED == AVLForeachPost(RIGHT_CHILD(node), operation, args))
    {
        return FAILED;
    }
    else if (FAILED == operation(node->data, args))
    {
        return FAILED;
    }

    return SUCCESS;
}

static int AVLForeachIn(node_avl_t* node, avl_operation_t operation, void* args)
{
   if (NULL == node)
    {
        return SUCCESS;
    }
    if (FAILED == AVLForeachIn(LEFT_CHILD(node), operation, args))
    {
        return FAILED;
    }
    else if (FAILED == operation(node->data, args))
    {
        return FAILED;
    }
    else if (FAILED == AVLForeachIn(RIGHT_CHILD(node), operation, args))
    {
        return FAILED;
    }

    return SUCCESS; 
}

static int IncByOne(void* data, void* args)
{
	(void) data;
	*(size_t*) args += 1;
	return SUCCESS;
}

/*delete left&right child arguments and height*/
static node_avl_t* AVLCreateNode(void* data, void* key, node_avl_t* left_child, node_avl_t* right_child, int height)
{
    node_avl_t* new_node = NULL;

    new_node = (node_avl_t*)malloc(sizeof(node_avl_t));
    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->key = key;
    DATA(new_node) = data;
    LEFT_CHILD(new_node) = left_child;
    RIGHT_CHILD(new_node) = right_child;
    HEIGHT(new_node) = height;

    return new_node;
}

static int AVLHaveRightChild(node_avl_t* node)
{
    return (RIGHT_CHILD(node) != NULL);
}

static int AVLHaveLeftChild(node_avl_t* node)
{
    return (LEFT_CHILD(node) != NULL);
}

static node_avl_t* AVLGetNextRecusive(node_avl_t* node)
{
    return (LEFT_CHILD(node) == NULL ? node: AVLGetNextRecusive(LEFT_CHILD(node)));
}

static node_avl_t* AVLBalanceSubTree(node_avl_t* node)
{
    /*unbalanced in  right sub-tree*/
    if(BalanceFactor(node) > 1)
    {
        /*re use the if's*/
        /*LL rotate*/
        if (BalanceFactor(RIGHT_CHILD(node)) >= 0)
        {
            return AVLRotateLeft(node);
        }
        /*RL rotate*/
        else 
        {
            RIGHT_CHILD(node) = AVLRotateRight(RIGHT_CHILD(node));
            return AVLRotateLeft(node);
        }
    }
    /*unbalanced in  left sub-tree*/
    else if (BalanceFactor(node) < -1)
    {   
        /*RR rotate*/
        if (BalanceFactor(LEFT_CHILD(node)) <= 0)
        {
            return AVLRotateRight(node);
        }
        /*LR rotate*/
        else
        {
            LEFT_CHILD(node) = AVLRotateLeft(LEFT_CHILD(node));
            return AVLRotateRight(node);
        }
    }
    /*sub tree is balanced*/
    else
    {
        return node;
    }
}

static node_avl_t* AVLRotateLeft(node_avl_t* node)
{
    node_avl_t* new_node = RIGHT_CHILD(node);
    node_avl_t* left_sub_tree = LEFT_CHILD(RIGHT_CHILD(node));

    LEFT_CHILD(new_node) = node;
    RIGHT_CHILD(node) = left_sub_tree;

    HEIGHT(node) = 1 + AVLGetMaxHeight(LEFT_CHILD(node), RIGHT_CHILD(node));
    HEIGHT(new_node) = 1 + AVLGetMaxHeight(LEFT_CHILD(new_node), RIGHT_CHILD(new_node));

    return new_node;
}

static node_avl_t* AVLRotateRight(node_avl_t* node)
{
    node_avl_t* new_node = LEFT_CHILD(node);
    node_avl_t* right_sub_tree = RIGHT_CHILD(LEFT_CHILD(node));

    RIGHT_CHILD(new_node) = node;
    LEFT_CHILD(node) = right_sub_tree;

    HEIGHT(node) = 1 + AVLGetMaxHeight(LEFT_CHILD(node), RIGHT_CHILD(node));
    HEIGHT(new_node) = 1 + AVLGetMaxHeight(LEFT_CHILD(new_node), RIGHT_CHILD(new_node));

    return new_node;
}

static int AVLGetMaxHeight(node_avl_t* left_child, node_avl_t* right_child)

{
    return MAX(GetHeight(right_child), GetHeight(left_child));
}

static int BalanceFactor(node_avl_t* node)
{
    return GetHeight(RIGHT_CHILD(node)) - GetHeight(LEFT_CHILD(node));
}

static int GetHeight(node_avl_t* node)
{
    return NULL == node ? (-1) : HEIGHT(node);
}