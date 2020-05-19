
#include "hash-table_header.h"

const size_t COUNT_OF_TABLES = 7;

new_list** TestCreate_Tables(struct LINE* lines_text, size_t nlines)
{
    auto tables = (new_list**)calloc(SIZE_OF_TABLE, sizeof(new_list*));
    for(size_t i_table = 0; i_table < COUNT_OF_TABLES; i_table++)
    {
        tables[i_table] = (new_list*)calloc(SIZE_OF_TABLE, sizeof(new_list));
        hash_table_Construct(tables[i_table]);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_Func1(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[0][i_list], word);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_Func_First_Letter(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[1][i_list], word);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_Func_Len(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[2][i_list], word);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_Func_Sum_Let(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[3][i_list], word);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_Func_Rol(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[4][i_list], word);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_Func_GNU(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[5][i_list], word);
    }

    for(size_t i_line = 0; i_line < nlines; i_line++)  //nlines
    {
        char* word = lines_text[i_line].ptrline;
        if(lines_text[i_line].length == 0 || lines_text[i_line].length == 1)
            continue;
        int i_list = (Hash_FuncMURMUR(word) % SIZE_OF_TABLE);

        nListInsertBack(&tables[6][i_list], word);
    }
    return tables;
}

const size_t NUM = 20000000;

void TestFind_WordTables(new_list** tables, char* word)
{
    int i_list = 0;

    Timer timer;

    i_list = (Hash_Func1(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM / 1000; i++)
    {
        //nListDump(&tables[0][i_list]);
        //if(nListPosSearch(&tables[0][i_list], word) == 0)
        if(_nListSearch(&tables[0][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_Func1    = %.3f\n", timer.elapsed());
    timer.reset();

    i_list = (Hash_Func_First_Letter(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM / 10; i++)
    {
        //if(nListPosSearch(&tables[1][i_list], word) == 0)
        if(_nListSearch(&tables[1][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_Func_First_Letter    = %.3f\n", timer.elapsed());
    timer.reset();

    i_list = (Hash_Func_Len(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM / 100; i++)
    {
        //if(nListPosSearch(&tables[2][i_list], word) == 0)
        if(_nListSearch(&tables[2][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_Func_Len    = %.3f\n", timer.elapsed());
    timer.reset();

    i_list = (Hash_Func_Sum_Let(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM; i++)
    {
        //if(nListPosSearch(&tables[3][i_list], word) == 0)
        if(_nListSearch(&tables[3][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_Func_Sum_Let    = %.3f\n", timer.elapsed());
    timer.reset();

    i_list = (Hash_Func_Rol(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM; i++)
    {
        //if(nListPosSearch(&tables[4][i_list], word) == 0)
        if(_nListSearch(&tables[4][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_Func_Rol    = %.3f\n", timer.elapsed());
    timer.reset();

    i_list = (Hash_Func_GNU(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM; i++)
    {
        //if(nListPosSearch(&tables[5][i_list], word) == 0)
        if(_nListSearch(&tables[5][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_Func_GNU    = %.3f\n", timer.elapsed());
    timer.reset();

    i_list = (Hash_FuncMURMUR(word) % SIZE_OF_TABLE);
    for(size_t i = 0; i < NUM; i++)
    {
        //if(nListPosSearch(&tables[6][i_list], word) == 0)
        if(_nListSearch(&tables[6][i_list], word) == 0)
            fprintf(stderr, "fuck\n");
    }

    fprintf(stderr, "Hash_FuncMURMUR    = %.3f\n", timer.elapsed());
    timer.reset();
}