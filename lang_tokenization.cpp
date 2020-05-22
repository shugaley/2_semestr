#include <cwchar>
#include "lang_header.h"

token* Create_TokenLang(FILE* lang_inp)
{
    assert(lang_inp);

    size_t nlines = 0;
    line* buffer = create_all(lang_inp, &nlines);

    size_t max_size = Count_MaxSize(buffer, nlines);
    token* token_lang = (token*)calloc(max_size, sizeof(token_lang[0]));
    size_t i_token = 0;

    for(size_t i_line = 0; i_line < nlines; i_line++)
    {
        if(buffer[i_line].length == 0)
            continue;

        size_t i_sym = 0;
        while (i_sym < buffer[i_line].length - 1)
        {
            token_lang[i_token].num_line = i_line;
            token_lang[i_token].pos_line = i_sym;

            char* word  = nullptr;
            int number = 0;

            switch (WhichToken(buffer[i_line], &i_sym, &word, &number))
            {
                case MODE_TOKEN_NUM:
                    token_lang[i_token].mode   = MODE_TOKEN_NUM;
                    token_lang[i_token].number = number;
                    break;

                case MODE_TOKEN_OP:
                    token_lang[i_token].mode = MODE_TOKEN_OP;
                    token_lang[i_token].word = word;
                    break;

                case MODE_TOKEN_ID:
                    token_lang[i_token].mode = MODE_TOKEN_ID;
                    token_lang[i_token].word = word;
                    break;

                case MODE_TOKEN_PUNC:
                    token_lang[i_token].mode = MODE_TOKEN_PUNC;
                    token_lang[i_token].word = word;
                    break;

                default:
                    fprintf(stderr, "ERROR TOKENIZATION \nline :  %lu \npos : %lu", i_line, i_sym);
            }
            //Dumpi_TokenLang(token_lang[i_token]);

            i_token++;

            token_lang[i_token] = *Create_TokenEnd(nlines);

            Dump_TokenLang(token_lang);
        }
    }
    return token_lang;
}



#define pos (buffer_line.ptrline + *i_sym)

int WhichToken(line buffer_line, size_t* i_sym, char** word, int* number)
{
    assert(number);

    //printf("\nDEBUG111 - %s\n", (buffer_line.ptrline + *i_sym));

    (*i_sym) = Skip_Space(buffer_line.ptrline, *i_sym);

    if(isdigit(*pos))
    {
        while(isdigit(*pos))
        {
            *number = *number * 10 + (*pos - '0');
            (*i_sym)++;
        }
        return MODE_TOKEN_NUM;
    }

    if(isop(*pos))
    {
        *word = (char*)calloc(1, sizeof(word[0]));
        **word = *pos;
        (*i_sym)++;
        return MODE_TOKEN_OP;
    }

    if(strncmp(pos, "Ў", 2) == 0 || strncmp(pos, "ў", 2) == 0)
    {
        *word = strdup(Create_Word(buffer_line, i_sym));
        return MODE_TOKEN_PUNC;
    }
    else
    {
        *word = strdup(Create_Word(buffer_line, i_sym));
        return MODE_TOKEN_ID;
    }
}


token* Create_TokenEnd(size_t nlines)
{
    token* token_end = (token*)calloc(1, sizeof(token_end[0]));

    token_end->num_line = nlines;
    token_end->pos_line = 0;
    token_end->mode     = MODE_TOKEN_END;
    token_end->word     = (char*)calloc(1, sizeof(token_end->word[0]));

    return token_end;
}


char* Create_Word(line buffer_line, size_t* i_sym)
{
    assert(i_sym);

    char* word = (char*)calloc(buffer_line.length, sizeof(word[0]));
    int n_sym = 0;
    int i_sym_word = 0;

    sscanf(pos, "%s%n", word, &n_sym);
    (*i_sym) += n_sym;
    i_sym_word += n_sym;

    /*fprintf(stderr, "%s", word);
    fprintf(stderr, "!%c!", word[i_sym_word]);*/

    if(isop(word[i_sym_word - 1]))
    {
        word[i_sym_word - 1] = ' ';
        (*i_sym) -= 1;
        return word;
    }

    word[i_sym_word++] = ' ';

    (*i_sym) = Skip_Space(buffer_line.ptrline, *i_sym);

    if(!strncmp(word, "больш", 10) || !strncmp(word, "разам", 10) || !strncmp(word, "меньш", 10) ||
       !strncmp(word, "больш-равно", 21) || !strncmp(word, "меньш-равно", 21) )
    {
        (*i_sym) = Skip_Space(buffer_line.ptrline, *i_sym);
        sscanf(pos, "%s%n", (word + i_sym_word), &n_sym);
        (*i_sym) += n_sym;

        if(isop(word[i_sym_word - 1]))
        {
            word[i_sym_word - 1] = ' ';
            (*i_sym) -= 1;
            return word;
        }
    }

    (*i_sym) = Skip_Space(buffer_line.ptrline, *i_sym);

    return word;
}

#undef pos


inline size_t Count_MaxSize(line* buffer, size_t nlines)
{
    assert(buffer);

    size_t max_size = 0;

    for(size_t i_line = 0; i_line < nlines; i_line++)
        max_size += buffer[i_line].length;

    assert(buffer);

    return max_size;
}



inline size_t Skip_Space(char* buffer, size_t i_sym)
{
    assert(buffer);

    while(*(buffer + i_sym) == ' '  ||
          *(buffer + i_sym) == '\t' ||
          *(buffer + i_sym) == '\n' )
    {
        (i_sym)++;
    }

    assert(buffer);

    return i_sym;
}


inline bool isop(char sym)
{
    if(sym  == ')' || sym  == '(' || sym  == ',')
        return true;
    else
        return false;
}


void Dump_TokenLang(token* token_lang)
{
    assert(token_lang);

    fprintf(stderr, "MODE     NUMBER      NUM_LINE       POS_LINE      WORD\n");

    for(size_t i_token = 0; token_lang[i_token].mode != MODE_TOKEN_END; i_token++)
        fprintf(stderr, "%2d%12d%12lu%12lu          %s\n", token_lang[i_token].mode,
                                          token_lang[i_token].number, token_lang[i_token].num_line,
                                          token_lang[i_token].pos_line, token_lang[i_token].word);

    fprintf(stderr, "\n\n\n\n\n\n");
}


void Dumpi_TokenLang(token token_lang)
{
    fprintf(stderr, "MODE     WORD      NUMBER      NUM_LINE       POS_LINE\n");

    fprintf(stderr, "%d    %5s%8d%8lu%8lu\n", token_lang.mode, token_lang.word,
                                          token_lang.number, token_lang.num_line,
                                          token_lang.pos_line);
}