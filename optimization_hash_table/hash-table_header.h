#ifndef HASH_TABLE_HASH_TABLE_HEADER_H
#define HASH_TABLE_HASH_TABLE_HEADER_H

#include "new_list_header.h"
#include "timer.h"

const size_t SIZE_OF_TABLE = 1001;

struct LINE
{
    int length = 0;
    char* ptrline = nullptr;
};



bool hash_table_Construct(new_list* table);

bool hash_table_Count(new_list* table, struct LINE* lines_text, size_t nlines);
bool add_word_nlist(new_list* table, char* word);

bool hash_table_dump(new_list* table);

bool Write_table(FILE* ptr_output, new_list* table);

//FOR OPT--------------

new_list** TestCreate_Tables(struct LINE* lines_text, size_t nlines);
void TestFind_WordTables(new_list** tables, char* word);

//Reader---------------

LINE* create_all(FILE* ptr_input, size_t* nlines);

char* create_ar_text(FILE* pnt_input, size_t* size);
LINE* create_struct_lines(char* text, size_t* nlines, size_t size);

size_t count_size();
size_t count_symbol(const char* text, size_t size, char symbol);

//FUNC--------------------------

int Hash_Func1               (const char* word);
int Hash_Func_First_Letter   (const char* word);
int Hash_Func_Len            (const char* word);
int Hash_Func_Sum_Let        (const char* word);
int Hash_Func_Rol            (const char* word);
int Hash_Func_GNU            (const char* word);
unsigned int Hash_FuncMURMUR (const char* word);


#endif //HASH_TABLE_HASH_TABLE_HEADER_H
