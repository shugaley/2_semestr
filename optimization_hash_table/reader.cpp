#include "hash-table_header.h"

extern const char* FILE_INPUT;

struct LINE* create_all(FILE* ptr_input, size_t* nlines)
{
    assert(ptr_input);

    size_t size = count_size();

    char* text = create_ar_text(ptr_input, &size);

    *nlines = count_symbol(text, size, '\n');

    LINE* lines = create_struct_lines(text, nlines, size);

    return lines;
}


char* create_ar_text(FILE* ptr_input, size_t* size)
{

    assert(ptr_input);

    char* text = (char*)calloc(*size + 1, sizeof(text[0]));
    *size = fread(text, sizeof(text[0]), *size, ptr_input) + 1;
    text = (char*)realloc(text, *size + 1);

    return text;
}



LINE* create_struct_lines(char* text, size_t* nlines, size_t size)
{

    assert(text);

    if (*nlines == 0)
        *nlines = count_symbol(text, size, '\n');


    LINE* lines = (struct LINE*)calloc(*nlines + 1, sizeof(lines[0]));

    size_t line = 0, i = 0;

    lines[line].ptrline = &text[i];
    for (line = 1; line < *nlines; line++)								   //line - Г±Г·ГҐГІГ·ГЁГЄ Г±ГІГ°Г®ГЄ
    {

        while (text[i] && text[i] != '\n')
            i++;

        text[i] = '\0';
        i++;

        lines[line].ptrline = &text[i];
        lines[line - 1].length = (int) (lines[line].ptrline - lines[line - 1].ptrline);
    }

    text[i] = '\0';

    return lines;
}



size_t count_size()
{
    struct stat struct_text = {};
    if (stat(FILE_INPUT, &struct_text))
    {
        perror("Failure structure of file creation");
        abort();
    }

    size_t size = struct_text.st_size;

    return size;
}



size_t count_symbol(const char* text, size_t size, char symbol)
{

    assert(text);

    int nlines = 0;

    size_t i_sym = 0;
    for (; i_sym < size; i_sym++)									//i - СЃС‡РµС‚С‡РёРє СЃРёРјРІРѕР»РѕРІ
        if (!text[i_sym] || text[i_sym] == symbol)
            nlines++;

    return (text[i_sym - 1] != symbol) ? nlines : ++nlines;
}
