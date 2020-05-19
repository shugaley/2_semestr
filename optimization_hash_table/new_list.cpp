
#include "new_list_header.h"

const size_t BEGIN_MAXSIZE = 1;
const data_t PPOISON = nullptr;
const int POISON = -666;
const size_t MAXSIZE_WORD = 50;

bool nListCreate(new_list* list_name)
{
    assert(list_name);

    list_name->elem    = nullptr;
    list_name->head    = 0;
    list_name->tail    = 0;
    list_name->size    = 0;
    list_name->maxsize = 0;
    list_name->free    = 0;
    list_name->err = NO_ERR;

    nListMaxsizeCreate(list_name);

    assert(list_name);
    assert_nlist(list_name);

    return true;
}


bool nListMaxsizeCreate(new_list* list_name)
{
    assert(list_name);

    if(list_name->maxsize == 0)
        list_name->maxsize = BEGIN_MAXSIZE;

    list_name->elem = (new_list_elem*)calloc(list_name->maxsize + 1, sizeof(list_name->elem[0]));

    list_name->head    = 0;
    list_name->tail    = 0;
    list_name->free    = 1;

    list_name->elem[0].data = PPOISON;
    list_name->elem[0].next = 0;
    list_name->elem[0].prev = 0;

    nListFreeCreate(list_name);

    assert(list_name);
    assert_nlist(list_name);

    return true;
}


bool nListFreeCreate(new_list* list_name)
{
    assert(list_name);

    for(size_t i_free = list_name->free; i_free < list_name->maxsize; i_free++)
    {
        list_name->elem[i_free].next = i_free + 1;
        list_name->elem[i_free].prev = -POISON;
    }

    list_name->elem[list_name->maxsize].next = -POISON;
    list_name->elem[list_name->maxsize].prev = -POISON;

    assert(list_name);

    return true;
}


bool nListMaxsizeInc(new_list* list_name)
{
    assert(list_name);
    assert_nlist(list_name);

    list_name->maxsize *= 2;

    list_name->elem = (new_list_elem*)realloc(list_name->elem, (list_name->maxsize + 1) * sizeof(new_list_elem));

    nListFreeCreate(list_name);

    assert(list_name);
    assert_nlist(list_name);

    return true;
}


size_t nListFirstElemCreate(new_list* list_name, data_t value)
{
    assert(list_name);
    assert_nlist(list_name);

    size_t i_new = list_name->free;

    list_name->elem[i_new].data = value;

    list_name->head             = i_new;
    list_name->tail             = i_new;
    list_name->free             = list_name->elem[list_name->free].next;
    //strcpy(list_name->elem[i_new].data, value);
    list_name->elem[i_new].next = 0;
    list_name->elem[i_new].prev = 0;
    list_name->size++;

    assert(list_name);
    assert_nlist(list_name);

    return i_new;
}


#define CHECK_POS(pos) \
{\
    if(pos > list_name->maxsize || pos < 0)\
    {\
        printf("Elem not found. Please check number of position");\
        return false;\
    }\
    if(list_name->elem[pos].prev == -POISON)\
    {\
        printf("Elem is free. Please check number of position");\
        return false;\
    }\
}

#define PREPARE(list_name)\
{\
    if(list_name->size >= list_name->maxsize - 1)\
        nListMaxsizeInc(list_name);\
    if(!list_name->size)\
        return nListFirstElemCreate(list_name, value);\
}

#define NEXT_FREE(list_name) list_name->free = list_name->elem[list_name->free].next;


size_t nListInsertAfter(new_list* list_name, data_t value, size_t pos_before)
{
    assert(list_name);
    assert_nlist(list_name);

    PREPARE(list_name);

    CHECK_POS(pos_before);

    if(pos_before == list_name->tail)
        nListInsertBack(list_name, value);

    if(!pos_before)
        nListInsertFront(list_name, value);

    size_t i_new = list_name->free;
    NEXT_FREE(list_name);

    size_t pos_after = list_name->elem[pos_before].next;

    list_name->elem[i_new].data = value;
    list_name->elem[i_new].next = pos_after;
    list_name->elem[i_new].prev = pos_before;

    list_name->elem[pos_after ].prev = i_new;
    list_name->elem[pos_before].next = i_new;

    list_name->size++;

    assert(list_name);
    assert_nlist(list_name);

    return i_new;
}


size_t nListInsertBefore(new_list* list_name, data_t value, size_t pos_after)
{
    assert(list_name);
    assert_nlist(list_name);

    PREPARE(list_name);

    CHECK_POS(pos_after);

    if(pos_after == list_name->head)
        nListInsertFront(list_name, value);

    if(!pos_after)
        nListInsertBack(list_name, value);

    size_t i_new = list_name->free;
    NEXT_FREE(list_name);

    size_t pos_before = list_name->elem[pos_after].prev;

    list_name->elem[i_new].data = value;
    list_name->elem[i_new].next = pos_after;
    list_name->elem[i_new].prev = pos_before;

    list_name->elem[pos_after ].prev = i_new;
    list_name->elem[pos_before].next = i_new;

    list_name->size++;

    assert(list_name);
    assert_nlist(list_name);

    return i_new;
}

size_t nListInsertFront(new_list* list_name, data_t value)
{
    assert(list_name);
    assert_nlist(list_name);

    PREPARE(list_name);

    size_t i_new = list_name->free;
    NEXT_FREE(list_name);

    list_name->elem[i_new].data           = value;
    list_name->elem[i_new].next           = list_name->head;
    list_name->elem[i_new].prev           = 0;
    list_name->elem[list_name->head].prev = i_new;
    list_name->head = i_new;

    list_name->size++;

    assert(list_name);
    assert_nlist(list_name);

    return i_new;
}


size_t nListInsertBack(new_list* list_name, data_t value)
{
    assert(list_name);
    assert_nlist(list_name);

    //nListDump(list_name);

    PREPARE(list_name);

    size_t i_new = list_name->free;
    NEXT_FREE(list_name);

    //nListDump(list_name);

    /*list_name->elem[i_new].data = (char*)calloc(MAXSIZE_WORD, sizeof(char));

    strcpy(list_name->elem[i_new].data, value);*/

    list_name->elem[i_new].data = value;
    list_name->elem[i_new].next           = 0;
    list_name->elem[i_new].prev           = list_name->tail;
    list_name->elem[list_name->tail].next = i_new;
    list_name->tail = i_new;

    list_name->size++;

    /*fprintf(stderr, "%p\n", list_name);
    fprintf(stderr, "%p\n", &list_name->elem);*/

    assert(list_name);
    assert_nlist(list_name);

    return i_new;
}

#undef NEXT_FREE
#undef PREPARE


bool nListDelete(new_list* list_name, size_t pos)
{
    assert(list_name);
    assert_nlist(list_name);

    CHECK_POS(pos);

   size_t pos_after = list_name->elem[pos].next;
   size_t pos_before = list_name->elem[pos].prev;


    if(pos != list_name->head && pos != list_name->tail)
    {
        list_name->elem[pos_after ].prev = pos_before;
        list_name->elem[pos_before].next = pos_after;
    }

    if(pos == list_name->head)
    {
        list_name->elem[pos_after ].prev = pos_before;
        list_name->head = pos_after;
    }

    if(pos == list_name->tail)
    {
        list_name->elem[pos_before].next = pos_after;
        list_name->tail = pos_before;
    }

    list_name->size--;

    list_name->elem[pos].data = 0;
    list_name->elem[pos].next = list_name->free;
    list_name->elem[pos].prev = -POISON;

    list_name->free = pos;

    assert(list_name);
    assert_nlist(list_name);

    return true;
}

#undef CHECK_POS


size_t nListPosSearch(new_list* list_name, data_t value)
{
    assert(list_name);

    for(size_t i_pos = list_name->head; i_pos != list_name->free && i_pos != 0; i_pos = list_name->elem[i_pos].next)
    {
        //fprintf(stderr, "%s and %s\n", list_name->elem[i_pos].data, value);
        if(strcmp(list_name->elem[i_pos].data, value) == 0)
            return i_pos;
    }

    return 0;
}



bool nListClear(new_list* list_name)
{
   assert(list_name);
   assert_nlist(list_name);

   for(size_t i_elem = 0; i_elem < list_name->maxsize; i_elem++)
       free(list_name->elem[i_elem].data);

   return true;
}


bool nListDestroy(new_list* list_name)
{
    assert(list_name);
    assert_nlist(list_name);

    nListClear(list_name);

    free(list_name->elem);

    list_name->elem    = nullptr;
    list_name->head    = 0;
    list_name->tail    = 0;
    list_name->size    = 0;
    list_name->maxsize = 0;
    list_name->free    = 0;
    list_name->err = NO_ERR;

    return true;
}

//--------------------------------------------------

#define OK(what, code) \
    if(what) \
    { list_name->err = code; return false;}

bool nListOK(new_list* list_name)
{
    assert(list_name);

    OK (list_name->err != NO_ERR,                   ERR_ERR);
    OK (list_name->elem == nullptr,                 ERR_ELEM_NULLPTR);
    OK (list_name->elem[0].data != PPOISON,         ERR_ZERO_DATA);
    OK (list_name->elem[0].next != 0,               ERR_ZERO_NEXT);
    OK (list_name->elem[0].prev != 0,               ERR_ZERO_PREV);
    OK (list_name->elem[list_name->head].prev != 0, ERR_HEAD);
    OK (list_name->elem[list_name->tail].next != 0, ERR_TAIL);

    assert(list_name);

    return true;
}

#undef OK


bool nListDump(new_list* list_name)
{
    FILE* err = stderr;

    fprintf(err, "It's dump fucking idiot! You did something wrong again\n");

    if(!list_name)
        fprintf(err, "EROOOOOR!!!");
    else
        fprintf(err, "list_name [%p]\n\n", list_name);

    fprintf(err, "----------------------\n");

    fprintf(err, "HEAD: %lu   TAIL: %lu \n", list_name->head, list_name->tail);
    fprintf(err, "SIZE: %lu   MAXSIZE: %lu \n", list_name->size, list_name->maxsize);
    fprintf(err, "FREE: %lu \n\n", list_name->free);



   fprintf(err, "i        data         next      prev\n");
   for(size_t i_size = 0; i_size < list_name->free; i_size++)
   {
       fprintf(err, "%lu", i_size);
       fprintf(err, "%10s[%lu]\n", list_name->elem[i_size].data, i_size);
       /*for(int i = 0; list_name->elem[i_size].data && list_name->elem[i_size].data[i] != '\0'; i++)
           fprintf(err, "%x ", list_name->elem[i_size].data[i]);*/
       fprintf(err, "%10lu", list_name->elem[i_size].next);
       fprintf(err, "%10lu\n", list_name->elem[i_size].prev);
   }
   fprintf(err, "\n\n\n");

   return true;
}