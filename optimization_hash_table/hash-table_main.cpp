
#include "hash-table_header.h"


const char* FILE_INPUT = "/home/shugaley/proga/projects/2_sem/asm/optim_hash_table/words2.txt";
const char* FILE_OUTPUT = "/home/shugaley/proga/projects/1_sem/hash-table/outt.txt";
extern const size_t SIZE_OF_TABLE;

int main()
{
    //Timer timer;

    FILE* ptr_input = fopen(FILE_INPUT, "r");
    size_t nlines = 0;
    struct LINE* lines_text = create_all(ptr_input, &nlines);
    fclose(ptr_input);

    /*new_list* table = (new_list*)calloc(SIZE_OF_TABLE, sizeof(table[0]));
    hash_table_Construct(table);

    hash_table_Count(table, lines_text, nlines);

    FILE* ptr_output = fopen(FILE_OUTPUT, "w");
    Write_table(ptr_output, table);
    fclose(ptr_output);*/

//FOR OPT---

    new_list** tables = TestCreate_Tables(lines_text, nlines);
    TestFind_WordTables(tables, "world\r");

//---

//    hash_table_dump(table);

    free(lines_text);
    free(tables);

    //fprintf(stderr, "search time = %.3f\n", static_cast<double>(clock() - start_search_time) / CLOCKS_PER_SEC);
    //fprintf(stderr, "all time    = %.3f\n", static_cast<double>(clock())/ CLOCKS_PER_SEC);
    //fprintf(stderr, "all time    = %.3f\n", t.elapsed());
    return 0;
}