#include "lang_header.h"

#define L pos->left
#define R pos->right

int deep = 0;

void Print_Lang(tree_elem* pos, FILE* lang_output)
{
    if(!pos) return;

    switch(pos->data.mode)
    {
        case MODE_FUNC_MAIN:

            fprintf(lang_output, "\n\nбацька (");
            Print_Lang(L, lang_output);
            fprintf(lang_output, ")\n");

            fprintf(lang_output, "ЎЎЎ\n");
            deep += 1;
            Print_Lang(R, lang_output);
            fprintf(lang_output, "ЎЎЎ\n\n\n");

            deep -= 1;

            return;

        case MODE_FUNC_OWN:

            fprintf(lang_output, "%s (", pos->data.word);
            Print_Lang(L, lang_output);
            fprintf(lang_output, ")");

            return;

        case MODE_FUNC_OWN_DEF:

            fprintf(lang_output, "%s (", pos->data.word);
            Print_Lang(L, lang_output);
            fprintf(lang_output, ")");

            fprintf(lang_output, "ЎЎЎ\n");
            deep += 1;
            Print_Lang(R, lang_output);
            fprintf(lang_output, "ЎЎЎ\n\n\n");

            deep -= 1;

            return;

        case MODE_FUNC_SYS_IF:

            Print_Indent(lang_output);
            fprintf(lang_output, "калі (");
            Print_Lang(L, lang_output);
            fprintf(lang_output, ")\n");

            Print_Lang(R, lang_output);

            return;

        case MODE_FUNC_SYS_IFE:

            deep += 1;

            Print_Lang(L, lang_output);

            Print_Indent(lang_output);
            fprintf(lang_output, "Ў\n");
            deep -= 1;

            Print_Indent(lang_output);
            fprintf(lang_output, "інакш\n");
            deep += 1;

            Print_Lang(R, lang_output);

            Print_Indent(lang_output);
            fprintf(lang_output, "Ў\n");
            deep -= 1;

            return;

        case MODE_OP_ASS:

            Print_Indent(lang_output);

            Print_Lang(L, lang_output);

            fprintf(lang_output, " гэта ");

            Print_Lang(R, lang_output);

            fprintf(lang_output, " ў\n");

            return;

        case MODE_FUNC_SYS_IN:

            Print_Indent(lang_output);

            fprintf(lang_output, "угнаенне (%s) ў\n", L->data.word);

            return;

        case MODE_FUNC_SYS_OUT:

            Print_Indent(lang_output);

            fprintf(lang_output, "ураджай (");
            Print_Lang(L, lang_output);
            fprintf(lang_output, ") ў\n");

            return;

        case MODE_FUNC_SYS_RET:

            Print_Indent(lang_output);

            fprintf(lang_output, "пажаць ");
            Print_Lang(L, lang_output);
            fprintf(lang_output, " ў\n");

            return;

        case MODE_OP_COND:

            Print_Lang(L, lang_output);

            if(strncmp(pos->data.word, "==", 2) == 0)
                fprintf(lang_output, " як ");

            if(strncmp(pos->data.word, ">", 1) == 0)
                fprintf(lang_output, " больш чым ");

            if(strncmp(pos->data.word, "<", 1) == 0)
                fprintf(lang_output, " меньш чым ");

            if(strncmp(pos->data.word, ">=", 2) == 0)
                fprintf(lang_output, " больш-равно чым ");

            if(strncmp(pos->data.word, "<=", 2) == 0)
                fprintf(lang_output, " меньш-равно чым ");

            Print_Lang(R, lang_output);

            return;

        case MODE_OP_MATH:
            Print_Lang(L, lang_output);

            switch(*pos->data.word)
            {
                case '+':
                    fprintf(lang_output, " разам з ");
                    break;

                case '-':
                    fprintf(lang_output, " без ");
                    break;

                case '*':
                    fprintf(lang_output, " прапалоць ");
                    break;

                case '/':
                    fprintf(lang_output, " скасіць ");
                    break;
            }

            Print_Lang(R, lang_output);

            return;

        case MODE_FUNC_MATH:
            fprintf(lang_output, " корань (");

            Print_Lang(R, lang_output);

            fprintf(lang_output, ")");

            return;

        case MODE_EMPTY:

            return;
    }

    Print_Lang(L, lang_output);
    Print_Lang(R, lang_output);

    switch(pos->data.mode)
    {
        case MODE_VAR:
            fprintf(lang_output, "%s", pos->data.word);
            break;

        case MODE_OP_OP_COMMA:
            fprintf(lang_output, ", ");
            break;

        case MODE_NUM:
            fprintf(lang_output, "%d", pos->data.number);
            break;

        case MODE_OP:
            break;

        case MODE_PUNC_SEMI_GL:
            break;
    }
}


void Print_Indent(FILE* lang_output)
{
    assert(lang_output);

    for(int i_deep = 0; i_deep < deep; i_deep++)
        fprintf(lang_output, "\t");
}


#undef R
#undef L


//Read-------------------------------------------------------------------------------------------------------

tree* Read_TreeLang(tree* tree_lang, FILE* tree_lang_input)
{
    assert(tree_lang);
    assert(tree_lang_input);

    char* buffer = create_only_ar_text(tree_lang_input);

    size_t i_sym = 0;
    tree_elem* pos = nullptr;
    Create_TreeLangElem(tree_lang, buffer, &i_sym, pos);

    free(buffer);

    assert(tree_lang);
    assert(tree_lang_input);

    return tree_lang;
}




tree_elem* Create_TreeLangElem(tree* tree_lang, char* buffer, size_t* i_sym, tree_elem* pos)
{
    assert(buffer);
    assert(i_sym);

    if(*i_sym == 0)
        pos =  Create_TreeLangHead(tree_lang, buffer, i_sym);

    *i_sym = Skip_SpaceB(buffer, *i_sym);

    if(buffer[*i_sym] == '@')
    {
        (*i_sym)++;
        *i_sym = Skip_SpaceB(buffer, *i_sym);

        if     (!pos->left)
        {
            pos->left = Create_TreeLangNil();
            pos->left->parent = pos;
        }

        else if(!pos->right)
        {
            pos->right = Create_TreeLangNil();
            pos->right->parent = pos;
        }
    }


    if(buffer[*i_sym] == '{')
    {
        (*i_sym)++;
         *i_sym = Skip_SpaceB(buffer, *i_sym);
        char* string = Create_String(buffer, i_sym);

        if      (!pos->left )
            pos = Add_TreeBranch(pos, 'L');

        else if (!pos->right)
            pos = Add_TreeBranch(pos, 'R');

        Create_TreeData(pos, string);
        Create_TreeLangElem(tree_lang, buffer, i_sym, pos);
    }

    if(buffer[*i_sym] == '}')
    {
        (*i_sym)++;
         *i_sym = Skip_SpaceB(buffer, *i_sym);
        pos = pos->parent;
        Create_TreeLangElem(tree_lang, buffer, i_sym, pos);
    }

    return pos;
}


tree_elem* Create_TreeLangHead(tree* tree_lang, char* buffer, size_t* i_sym)
{
    assert     (tree_lang);
    assert     (buffer );
    assert     (i_sym  );

    Create_Tree(tree_lang);

    while(buffer[*i_sym] != '{')
        (*i_sym)++;

    (*i_sym)++;

    char* string = Create_String(buffer, i_sym);
    tree_data new_data = *Create_TreeDataPuncSemiGl();

    tree_lang->head = (tree_elem*)calloc(1, sizeof(tree_elem));
    tree_lang->head->data = new_data;

    assert     (tree_lang);
    assert     (buffer );
    assert     (i_sym  );
    assert     (string );

    return tree_lang->head;
}


tree_elem* Create_TreeLangNil()
{
    tree_elem* new_elem = (tree_elem*)calloc(1, sizeof(tree_elem));

    new_elem->data.mode = MODE_EMPTY;
    new_elem->data.word = "@";

    return new_elem;
}


tree_elem* Add_TreeBranch(tree_elem* pos, char branch)
{
    assert(pos);

    tree_elem* new_pos = (tree_elem*)calloc(1, sizeof(tree_elem));

    new_pos->parent = pos;

    if(branch == 'L')
        pos->left = new_pos;

    if(branch == 'R')
        pos->right = new_pos;

    return new_pos;
}

//BUFFERWORK------------------------------------------------------------------------------------------

char* Create_String(char* buffer, size_t* i_sym)
{
    assert(buffer);
    assert(i_sym );

    char* string = (char*)calloc(MAXSIZE_DATA, sizeof(string[0]));

    size_t n_sym = 0;

    while(buffer[*i_sym] != '{' && buffer[*i_sym] != '}' && buffer[*i_sym] != '@')
        string[n_sym++] = buffer[(*i_sym)++];

    return string;
}


inline size_t Skip_SpaceB(char* buffer, size_t i_sym)
{
    assert(buffer);

    while(buffer[i_sym] && (buffer[i_sym] == ' ' || buffer[i_sym] == '\t'))
        (i_sym)++;

    assert(buffer);

    return i_sym;
}


//DATA---------------------------------------------------------------------------------------------------


tree_data* Create_TreeData(tree_elem* pos, char* string)
{
    assert(pos);
    assert(string);

    pos->data.mode = Which_ModeData(pos, string);
    if(pos->data.mode == MODE_NUM)
        sscanf(string, "%d", &pos->data.number);
    else
        pos->data.word = strdup(string);

    return &pos->data;
}



int Which_ModeData(tree_elem* pos, char* string)
{
    assert(string);

    if(isdigit(*string))
        return MODE_NUM;

    switch(*string)
    {
        case '$':

            if(pos->parent->data.mode == MODE_PUNC_SEMI_GL)
            {
                if(strncmp(string, "$main", 5) == 0)
                    return MODE_FUNC_MAIN;
                else
                    return MODE_FUNC_OWN_DEF;
            }
            else
                return MODE_FUNC_OWN;

        case ';':
            return MODE_PUNC_SEMI_GL;

        case ',':
            return MODE_OP_OP_COMMA;

        case '=':

            if(*(string + 1) == '=' || *(string + 1) == '<' || *(string + 1) == '>')
                return MODE_OP_COND;
            else
                return MODE_OP_ASS;

        default:
            break;
    }


    if(*string == '>' || *string == '<')
        return MODE_OP_COND;

    if(*string == '+' || *string == '-' || *string == '/' || *string == '*')
        return MODE_OP_MATH;

    if(strncmp(string, "ret", 3) == 0)
        return MODE_FUNC_SYS_RET;

    if(strcmp(string, "if-else") == 0)
        return MODE_FUNC_SYS_IFE;

    if(strcmp(string, "if") == 0)
        return MODE_FUNC_SYS_IF;

    if(strncmp(string, "while", 5) == 0)
        return MODE_FUNC_SYS_WH;

    if(strncmp(string, "op", 2) == 0)
        return MODE_OP;

    if(is_func_mathB(string))
        return MODE_FUNC_MATH;

    if(strncmp(string, "get", 3) == 0)
        return MODE_FUNC_SYS_IN;

    if(strncmp(string, "put", 3) == 0)
        return MODE_FUNC_SYS_OUT;

    return MODE_VAR;
}


bool is_func_mathB(char* string)
{
    assert(string);

    #define DEF_FUNC_MATH(word, com_sys, len) \
        if(strcmp(string, #com_sys) == 0)\
            return true;

    #define FUNC_MATH

    #include "lang_commands.h"

    #undef DEF_FUNC_MATH

    return false;
}




