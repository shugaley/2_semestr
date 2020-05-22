#include "lang_header.h"

bool is_func_sys_int(char* com)
{
    assert(com);

    if(!strncmp(com, "пасеяць", 14))
        return true;
    else
        return false;
}



bool is_func_sys_main(char* com)
{
    assert(com);

    if(!strncmp(com, "бацька", 12))
        return true;
    else
        return false;
}


bool is_op_op_comma(char* com)
{
    assert(com);

    if(!strncmp(com, ",", 1))
        return true;
    else
        return false;
}


bool is_op_op_par(char* com)
{
    assert(com);

    if(!strncmp(com, ")", 1) || !strncmp(com, "(", 1))
        return true;
    else
        return false;
}

bool is_op_op_par_l(char* com)
{
    assert(com);

    if(!strncmp(com, "(", 1))
        return true;
    else
        return false;
}


bool is_punc_semi(char* com)
{
    assert(com);

    if(!strncmp(com, "ў", 2))
        return true;
    else
        return false;
}


bool is_punc_prace3(char* com)
{
    assert(com);

    if(!strncmp(com, "ЎЎЎ", 6))
        return true;
    else
        return false;
}

bool is_punc_prace2(char* com)
{
    assert(com);

    if(!strncmp(com, "ЎЎ", 4) && !is_punc_prace3(com))
        return true;
    else
        return false;
}


bool is_punc_prace1(char* com)
{
    assert(com);

    if(!strncmp(com, "Ў", 2) && !is_punc_prace2(com) && !is_punc_prace3(com))
        return true;
    else
        return false;
}


bool is_func_sys_ret(char* com)
{
    assert(com);

    if(!strncmp(com, "пажаць", 12))
        return true;
    else
        return false;
}


bool is_func_sys_if(char* com)
{
    assert(com);

    if(!strncmp(com, "калі", 8))
        return true;
    else
        return false;
}

bool is_func_sys_ife(char* com)
{
    assert(com);

    if(!strncmp(com, "інакш", 10))
        return true;
    else
        return false;
}


bool is_func_sys_wh(char* com)
{
    assert(com);

    if(!strncmp(com, "пакуль", 12))
        return true;
    else
        return false;
}


bool is_func_sys(char* com)
{
    assert(com);

    #define DEF_FUNC_SYS(word, com_sys, len) \
        if(strncmp(com, #word, len) == 0)\
            return true;

    #define FUNC_SYS

    #include "lang_commands.h"

    #undef DEF_FUNC_SYS

    return false;
}


bool is_op_ass(char* com)
{
    assert(com);

    if(!strncmp(com, "гэта", 8))
        return true;
    else
        return false;
}


bool is_func_math(char* com)
{
    assert(com);

    #define DEF_FUNC_MATH(word, com_sys, len) \
        if(strncmp(com, #word, len) == 0)\
            return true;

    #define FUNC_MATH

    #include "lang_commands.h"

    #undef DEF_FUNC_MATH

    return false;
}


bool is_func_sys_out(char* com)
{
    assert(com);

    if(!strncmp(com, "ураджай", 14))
        return true;
    else
        return false;
}


bool is_func_sys_in(char* com)
{
     assert(com);

    if(!strncmp(com, "угнаенне", 16))
        return true;
    else
        return false;
}

//BACK_END------------------------------------------------------------------------------------------------------


bool is_func_sys_ret_main(tree_elem* pos)
{
    assert(pos);

    bool flag_true = false;

    while(pos)
    {
        if(pos->data.mode == MODE_FUNC_MAIN)
            flag_true = true;
        pos = pos->parent;
    }

    return flag_true;
}


//SIMPLIFY---------------------------------------------------------------------------------------------------------------


bool is_zero(tree_elem* pos)
{
    assert(pos);

    if(pos->data.mode == MODE_NUM && pos->data.number == 0)
        return true;
    else
        return false;
}


bool is_one(tree_elem* pos)
{
    assert(pos);

    if(pos->data.mode == MODE_NUM && pos->data.number == 1)
        return true;
    else
        return false;
}


bool is_num(tree_elem* pos)
{
    assert(pos);

    if(pos->data.mode == MODE_NUM)
        return true;
    else
        return false;
}


bool is_end(tree_elem* pos)
{
    assert(pos);

    if(is_$(pos) || (!pos->left && !pos->right))
        return true;
    else
        return false;
}



bool is_$(tree_elem* pos)
{
    assert(pos);

    if(*pos->data.word == '$')
        return true;
    else
        return false;
}



bool is_high_priority(tree_elem* pos)
{
    assert(pos);

    if((pos->data.mode == MODE_OP_MATH && (*pos->data.word == '*' ||
                                           *pos->data.word == '/'  ||
                                           *pos->data.word == '^'    )) ||
        pos->data.mode == MODE_FUNC_MATH)
        return true;
    else
        return false;
}


//WHICH--------------------------------------------------------------------------------------------------------


int Which_ModeOpMath(char* word_com)
{
    assert(word_com);

    #define DEF_OP_MATH(word, op, len, num) \
        if(strncmp(word_com, #word, len) == 0)\
            return num;

    #define OP_MATH

    #include "lang_commands.h"

    #undef DEF_OP_MATH

    return 0;
}


int Which_ModeOpCond(char* word_com)
{
    assert(word_com);

    #define DEF_OP_COND(word, op, len, num) \
        if(strncmp(word_com, #op, strlen(#op)) == 0)\
            return num;

    #define OP_COND

    #include "lang_commands.h"

    #undef DEF_OP_COND

    return 0;
}

char* Which_OpMath(char* word_com)
{
    assert(word_com);

    #define DEF_OP_MATH(word, op, len, num) \
        if(strncmp(word_com, #word, len) == 0)\
        { \
            char* temp_word = strdup(#op); \
            return temp_word; \
        }

    #define OP_MATH

    #include "lang_commands.h"

    #undef DEF_OP_MATH

    return nullptr;
}


char* Which_FuncMath(char* word_com)
{
    assert(word_com);

    #define DEF_FUNC_MATH(word, op, len) \
        if(strncmp(word_com, #word, len) == 0)\
        { \
            char* temp_word = strdup(#op); \
            return temp_word; \
        }

    #define FUNC_MATH

    #include "lang_commands.h"

    #undef DEF_FUNC_MATH

    return nullptr;
}


char* Which_FuncSys(char* word_com)
{
    assert(word_com);

    #define DEF_FUNC_SYS(word, com_sys, len) \
        if(strncmp(word_com, #word, len) == 0)\
        { \
            char* temp_word = strdup(#com_sys); \
            return temp_word; \
        }

    #define FUNC_SYS

    #include "lang_commands.h"

    #undef DEF_OP_MATH
}


char* Which_OpCond(char* word_com)
{
    assert(word_com);

    #define DEF_OP_COND(word, com_sys, len, num) \
        if(strncmp(word_com, #word, len) == 0)\
        { \
            char* temp_word = strdup(#com_sys); \
            return temp_word; \
        }

    #define OP_COND

    #include "lang_commands.h"

    #undef DEF_OP_COND
}