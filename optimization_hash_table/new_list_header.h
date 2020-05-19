#ifndef HASH_TABLE_NEW_LIST_HEADER_H
#define HASH_TABLE_NEW_LIST_HEADER_H


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <sys/stat.h>
#include <cmath>

//typedef char* data_t;
using data_t = char*;

enum ErrorCode
{
    NO_ERR = 1000000,
    ERR_ERR = 1100000,
    ERR_ELEM_NULLPTR = 1000010,
    ERR_ZERO_DATA = 1000001,
    ERR_ZERO_NEXT = 1000002,
    ERR_ZERO_PREV = 1000003,
    ERR_HEAD = 100100,
    ERR_TAIL = 100110,
};

struct new_list_elem
{
    data_t data = 0;
    size_t prev = 0;
    size_t next = 0;
};

struct new_list
{
    new_list_elem* elem = nullptr;
    size_t head = 0;
    size_t tail = 0;
    size_t size = 0;
    size_t maxsize = 0;
    size_t free = 0;
    int err = 0;
};


bool nListCreate       (new_list* list_name);
bool nListMaxsizeCreate(new_list* list_name);
bool nListFreeCreate   (new_list* list_name);
bool nListMaxsizeInc   (new_list* list_name);
size_t nListFirstElemCreate(new_list* list_name, data_t value);

size_t nListInsertAfter(new_list* list_name, data_t value, size_t pos_before);
size_t nListInsertBefore (new_list* list_name, data_t value, size_t pos_after);

size_t nListInsertFront(new_list* list_name, data_t value);
size_t nListInsertBack(new_list* list_name, data_t value);

bool nListDelete(new_list* list_name, size_t pos);
size_t nListPosSearch(new_list* list_name, data_t value);
extern "C" size_t _nListSearch(new_list* list_name, data_t value);

bool nListDestroy(new_list* list_name);
bool nListClear(new_list* list_name);

bool nListOK(new_list* list_name);
bool nListDump(new_list* list_name);




#define DEDD

//SECURE-----

#define dump(list_name) \
{\
    printf("Error file %s\n",__FILE__); \
    printf("Error function %s\n", __PRETTY_FUNCTION__); \
    printf("Error line %d\n",__LINE__); \
    nListDump(list_name); \
}

#ifdef DED
#define assert_nlist(list_name) \
    if(!nListOK(list_name)) \
        { dump(list_name); printf("Error code %d\n\n\n", list_name->err);  abort(); }
#else
#define assert_nlist ;
#endif

//-----------


#endif //HASH_TABLE_NEW_LIST_HEADER_H
