#ifndef __SDLL__H__
#define __SDLL__H__

#include <stddef.h>
#include "dll.h"

typedef int(*comperator_t)(void*, void*);
typedef struct list sdll_t;


typedef struct sdll_iterator
{
    dll_iterator_t iterator;
    
    #ifndef NDEBUG
        sdll_t* list;
    #endif
} sdll_iterator_t;


sdll_t* SdllCreate(comperator_t comperator);

void SdllDestroy(sdll_t* s_list);

void* SdllPopBack(sdll_t* s_list); 

void* SdllPopFront(sdll_t* s_list);   

sdll_iterator_t SdllInsert(sdll_t* s_list, void* data); /* Inserts before */

sdll_iterator_t SdllRemove(sdll_iterator_t s_iterator);

sdll_iterator_t SdllFind(sdll_iterator_t from, sdll_iterator_t to, void* data, sdll_t* s_list);

sdll_iterator_t SdllFindIf(sdll_iterator_t from, sdll_iterator_t to, void* data, 
                           int (*IsMatch)(void*, void*));
                           
size_t SdllSize(const sdll_t* s_list);

int SdllIsEmpty(const sdll_t* s_list);

void* SdllGetData(const sdll_iterator_t s_iterator);

sdll_iterator_t SdllGetNext(const sdll_iterator_t s_iterator);

sdll_iterator_t SdllGetPrev(const sdll_iterator_t s_iterator);

sdll_iterator_t SdllBegin(const sdll_t* s_list);

sdll_iterator_t SdllEnd(const sdll_t* s_list);

status_t SdllForEach(sdll_iterator_t from, sdll_iterator_t to, int (*OperationFunc)(void*, void*), void* args);

int SdllIsEqual(sdll_iterator_t s_iterator1, sdll_iterator_t s_iterator2);

void SdllMerge(sdll_t* s_list1, sdll_t* s_list2);

#endif /* end of header guard __SDLL__H__ */



