

#include <stdlib.h>		/*malloc & free*/
#include <assert.h>		/*assert*/

#include "sdll.h"


typedef enum 
{
	FALSE,
	TRUE
} bool_t;


struct list
{
    dll_t* list;
    comperator_t comperator;
};

static comperator_t Comparator_g;

static sdll_iterator_t DllToSdll(sdll_iterator_t sdll_iterator, dll_iterator_t dll_iterator);
static dll_iterator_t SdllToDll(sdll_iterator_t sdll_iterator);
static sdll_iterator_t SdllSetlist(sdll_iterator_t s_iter, const sdll_t* slist);
int NotComper(void* arg1, void* arg2);


sdll_t* SdllCreate(comperator_t comperator)
{
	sdll_t* slist = (sdll_t*)malloc(sizeof(sdll_t));
	if(NULL	== slist)
	{
		return NULL;
	}
	slist->list = DllCreate();
	if (NULL == slist->list)
	{
		free(slist);
		return NULL;
	}
	slist->comperator = comperator;
	
	return slist;
}

void SdllDestroy(sdll_t* s_list)
{
	assert(NULL != s_list);
	
	DllDestroy(s_list->list);
	free(s_list);
}

void* SdllPopBack(sdll_t* s_list)
{
	assert(NULL != s_list);
	
	return DllPopBack(s_list->list);
}

void* SdllPopFront(sdll_t* s_list)
{
	assert(NULL != s_list);

	return DllPopFront(s_list->list);
}  


sdll_iterator_t SdllInsert(sdll_t* s_list, void* data)
{
	sdll_iterator_t temp = {0};

	assert(s_list);
	assert(s_list->list);
	
	temp = SdllBegin(s_list);
	while (FALSE == DllIsEqual(SdllToDll(temp), DllEnd(s_list->list)))
	{
		if (s_list->comperator(DllGetData(SdllToDll(temp)), data) >= 0)
		{
			break;
		}
		else
		{
			temp.iterator = DllGetNext(SdllToDll(temp));
		}
	}
	temp.iterator = DllInsert(s_list->list, temp.iterator, data);
	return temp;
}

sdll_iterator_t SdllRemove(sdll_iterator_t s_iterator)
{
	dll_iterator_t temp = NULL;
	sdll_iterator_t ans = {0};
	
	assert(s_iterator.list);
	
	temp = SdllToDll(s_iterator);
	temp = DllRemove(temp);
	ans = DllToSdll(ans, temp);
	return SdllSetlist(ans, s_iterator.list);
}


sdll_iterator_t SdllFind(sdll_iterator_t from, sdll_iterator_t to, void* data, sdll_t* s_list)
{
	dll_iterator_t dll_ans = {0};
	dll_iterator_t dll_from = {0};
	dll_iterator_t dll_to = {0};
	
	assert(from.list);
	assert(to.list);
	assert(s_list);
	assert(from.list == to.list);
	
	Comparator_g = s_list->comperator;
	dll_from = SdllToDll(from);
	dll_to = SdllToDll(to);
	dll_ans = DllFind(dll_from, dll_to, data, NotComper);
	from = DllToSdll(from, dll_ans);

	return 	SdllSetlist(from, from.list);
}


sdll_iterator_t SdllFindIf(sdll_iterator_t from, sdll_iterator_t to, void* data, int (*IsMatch)(void*, void*))
{
	dll_iterator_t dll_to = {0};
	dll_iterator_t dll_from = {0};
	dll_iterator_t dll_ans = {0};
	sdll_iterator_t ans = {0};
	
	assert(from.list);
	assert(to.list);
	assert(from.list == to.list);
	
	dll_to = SdllToDll(to);
	dll_from = SdllToDll(from);
	dll_ans = DllFind(dll_from, dll_to, data, IsMatch);
	ans = DllToSdll(from, dll_ans);
	return ans;
}

                           
size_t SdllSize(const sdll_t* s_list)
{
	assert(NULL != s_list);	
	
	return (DllSize(s_list->list));
}

int SdllIsEmpty(const sdll_t* s_list)
{
	assert(NULL != s_list);
	
	return (DllIsEmpty(s_list->list));
}

void* SdllGetData(const sdll_iterator_t s_iterator)
{
	dll_iterator_t temp = NULL;
	
	temp = SdllToDll(s_iterator);
	
	return DllGetData(temp);
}

sdll_iterator_t SdllGetNext(const sdll_iterator_t s_iterator)
{
	dll_iterator_t temp = NULL;
	sdll_iterator_t ans = {0};
	temp = SdllToDll(s_iterator);
	ans = DllToSdll(ans, DllGetNext(temp));
	
	return SdllSetlist(ans, s_iterator.list);
}

sdll_iterator_t SdllGetPrev(const sdll_iterator_t s_iterator)
{
	dll_iterator_t temp = NULL;
	sdll_iterator_t ans = {0};
	assert(s_iterator.list);
	
	temp = SdllToDll(s_iterator);
	ans = DllToSdll(ans, DllGetPrev(temp));
	
	return SdllSetlist(ans, s_iterator.list);
}

sdll_iterator_t SdllBegin(const sdll_t* s_list)
{
	dll_iterator_t temp = NULL;
	sdll_iterator_t ans = {0};
	assert(NULL != s_list);

	temp = DllBegin(s_list->list);
	ans = DllToSdll(ans, temp);
	ans = SdllSetlist(ans, s_list);

	return ans;
}

sdll_iterator_t SdllEnd(const sdll_t* s_list)
{
	dll_iterator_t temp = NULL;
	sdll_iterator_t ans = {0};
	assert(NULL != s_list);
	
	temp = DllEnd(s_list->list);
	ans = DllToSdll(ans, temp);
	ans = SdllSetlist(ans, s_list);
	return ans;
}


status_t SdllForEach(sdll_iterator_t from, sdll_iterator_t to, int (*OperationFunc)(void*, void*), void* args)
{
	dll_iterator_t dll_from = {0};
	dll_iterator_t dll_to = {0};
	
	assert(from.list);
	assert(to.list);
	assert(from.list == to.list);
	
	dll_from = SdllToDll(from);
	dll_to = SdllToDll(to);
	
	return DllForEach(dll_from, dll_to, OperationFunc, args);
}


int SdllIsEqual(sdll_iterator_t s_iterator1, sdll_iterator_t s_iterator2)
{
	dll_iterator_t dll_iterator1 = {0};
	dll_iterator_t dll_iterator2 = {0};
	
	assert(s_iterator1.list);
	assert(s_iterator2.list);
	assert(s_iterator1.list == s_iterator2.list);

	
	dll_iterator1= SdllToDll(s_iterator1);
	dll_iterator2= SdllToDll(s_iterator2);
	return DllIsEqual(dll_iterator1, dll_iterator2);
}

void SdllMerge(sdll_t* s_list1, sdll_t* s_list2)
{
	sdll_iterator_t iter1 = {0};
	sdll_iterator_t iter2 = {0};
	sdll_iterator_t from = {0};
	sdll_iterator_t to = {0};
	
	assert(NULL != s_list1);
	assert(NULL != s_list2);
	
	iter1 = SdllBegin(s_list1);
	while (FALSE == SdllIsEmpty(s_list2) && FALSE == SdllIsEqual(iter1, SdllEnd(s_list1)))
	{
		iter2 = SdllBegin(s_list2);
		from = iter2;
		to = iter2;
		while (s_list1->comperator(SdllGetData(iter1), SdllGetData(to)) > 0 && FALSE == SdllIsEqual(iter1, SdllEnd(s_list1)))
		{
			to = SdllGetNext(to);
		}
		if(FALSE == SdllIsEqual(from, to))
		{
			DllSplice(SdllToDll(iter1), SdllToDll(from), SdllToDll(to));
		}
		else
		{
			iter2 = SdllGetNext(iter2);
		}
		iter1 = SdllGetNext(iter1);
	}
	DllSplice(SdllToDll(iter1), SdllToDll(SdllBegin(s_list2)), SdllToDll(SdllEnd(s_list2)));
	
}





static sdll_iterator_t DllToSdll(sdll_iterator_t sdll_iterator, dll_iterator_t dll_iterator)
{
	sdll_iterator.iterator = dll_iterator;
	
	return sdll_iterator;
}


static dll_iterator_t SdllToDll(sdll_iterator_t sdll_iterator)
{
	return sdll_iterator.iterator;
}


static sdll_iterator_t SdllSetlist(sdll_iterator_t s_iter, const sdll_t* slist)
{
	assert(NULL != slist);
	
	#ifndef NDEBUG
        s_iter.list = (sdll_t*)slist;
    #endif
    
    return s_iter;
}


int NotComper(void* arg1, void* arg2)
{
	return !(Comparator_g(arg1,arg2));
}














