
#include "hash-table_header.h"

extern const size_t SIZE_OF_TABLE;
const char NAME_OF_HFUNC[] = "FirstL";

bool hash_table_Construct(new_list* table)
{
    assert(table);

    for(size_t i_list = 0; i_list < SIZE_OF_TABLE; i_list++)
    {
        nListCreate(&table[i_list]);
        //assert_nlist((&table[i_list]));
    }

    //hash_table_dump(table);

    assert(table);

    return true;
}


bool hash_table_Count(new_list* table, struct LINE* lines_text, size_t nlines)
{
    assert(table);

    //Timer timer;

    for(size_t i_line = 0; i_line < nlines / 300; i_line++)  //nlines
    {
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        /*char* word = (char*)calloc(lines_text[i_line].length, sizeof(word[0]));
        size_t i_sym = 0;
        while(i_sym < (lines_text[i_line].length - 1))
        {
            int n = 0;
            sscanf(lines_text[i_line].ptrline + i_sym, "%s %n", word, &n);
            i_sym += n;
            if(isalpha(*word))
                add_word_nlist(table, word);
        }*/
        add_word_nlist(table, lines_text[i_line].ptrline);

       /* int i_list = (Hash_Func1(lines_text[i_line].ptrline) % SIZE_OF_TABLE);
        //fprintf(stderr, "%p\n", table[i_list].elem);

        if(_nListSearch(&table[i_list], lines_text[i_line].ptrline) == 0)
        //if(nListPosSearch(&table[i_list], lines_text[i_line].ptrline) == 0)
        {
            //fprintf(stderr, "%p\n", table[i_list].elem);
            nListInsertBack(&table[i_list], lines_text[i_line].ptrline);
        }*/
    }
    return true;
}


bool add_word_nlist(new_list* table, char* word)
{
    assert(table);
    assert(word);

    int i_list = (Hash_Func1(word) % SIZE_OF_TABLE);

    if(_nListSearch(&table[i_list], word) == 0)
    //if(nListPosSearch(&table[i_list], word) == 0)
        nListInsertBack(&table[i_list], word);


    //nListDump(&table[i_list]);

    assert(table);
    assert(word);

    return true;
}


bool Write_table(FILE* ptr_output, new_list* table)
{
    assert(ptr_output);
    assert(table);

    //fprintf(ptr_output, "------------------%s--------------\n", NAME_OF_HFUNC);

   /* for(size_t i_list = 0; i_list < SIZE_OF_TABLE; i_list++)
    {
        fprintf(ptr_output, "%lu, "  , i_list);
    }*/

    fprintf(ptr_output, "\n");

    for(size_t i_list = 0; i_list < SIZE_OF_TABLE; i_list++)
    {
        fprintf(ptr_output, "%lu, ", table[i_list].size);
    }

    fprintf(ptr_output, "\n");

    return true;
}


bool hash_table_dump(new_list* table)
{
    FILE* err = stderr;

    if(!table)
        fprintf(err, "EROOOOOR!!!");
    else
        fprintf(err, "table [%p]\n", table);

    fprintf(err, "SIZE_OF_TABLE: %lu\n\n", SIZE_OF_TABLE);
    for(size_t i_list = 0; i_list < SIZE_OF_TABLE; i_list++)
    {
        fprintf(err, "--------------list[%lu]--------------\n", i_list);
        nListDump(&table[i_list]);
        fprintf(err, "......................................\n\n");
    }

    return true;
}
