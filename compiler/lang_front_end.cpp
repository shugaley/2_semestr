#include "lang_header.h"

#define $ fprintf(stderr, "%s\n", tkn->word);

tree_elem* Create_TreeLang(tree* tree_lang, FILE* lang_inp, FILE* tree_lang_output)
{
    assert(tree_lang );
    assert(lang_inp);
    assert(tree_lang_output);

    token* token_lang = Create_TokenLang(lang_inp);

    assert(token_lang);

    tree_lang->head = GetG(token_lang);

    free(token_lang);

    assert(tree_lang);
    assert(lang_inp);

    Simplify_Tree(tree_lang->head);

    Print_Tree(tree_lang->head, tree_lang_output);

    assert(tree_lang);
    assert(lang_inp);
    assert(tree_lang_output);

    return tree_lang->head;
}


const token* tkn = {};


#define CHECK_SEMI(tkn) \
{ \
     if(!is_punc_semi(tkn->word) && !is_punc_prace1((tkn - 1)->word)) \
     { \
        fprintf(stderr, "ERROR!!! There isn't ў\n"); \
        Print_Error(*tkn); \
     } \
     else \
        if(is_punc_semi(tkn->word)) \
            tkn++; \
}


#define CHECK_PRACE3(tkn) \
{ \
    if(!is_punc_prace3(tkn->word)) \
    { \
        fprintf(stderr, "ERROR!!! There isn't ЎЎЎ\n"); \
        Print_Error(*tkn); \
    } \
    tkn++; \
}


#define SKIP_INT(tkn) \
{ \
    while(is_func_sys_int(tkn->word)) \
    { \
        tkn += 2; \
        CHECK_SEMI(tkn); \
    } \
}


tree_elem* GetG(const token* token_lang)
{
    assert(token_lang);

    tkn = token_lang;

    if(!is_func_sys_main(tkn->word) && !is_func_sys_int(tkn->word))
    {
        fprintf(stderr, "ERROR!!! There isn't бацька or пасеяць\n");
        Print_Error(*tkn);
    }

    tree_elem* head = (tree_elem*)calloc(1, sizeof(tree_elem));
    head->data = *Create_TreeDataPuncSemiGl();

    tree_elem* pos = head;

    SKIP_INT(tkn);

    while(is_op_ass((tkn + 1)->word))
    {
        pos->left = GetA();

        tree_data data_semi = *Create_TreeDataPuncSemiGl();
        pos = Add_TreeElemLang(data_semi, 'R', pos);

        CHECK_SEMI(tkn);
    };

    if(!is_func_sys_main(tkn->word))
    {
        fprintf(stderr, "ERROR!!! There isn't бацька\n");
        Print_Error(*tkn);
    }

    tree_data data_func_main = *Create_TreeDataFuncMain();
    tree_elem* func_main = Add_TreeElemLang(data_func_main, 'L', pos);

    tkn += 2;

    Fill_Func(func_main);

    while(tkn->mode == MODE_TOKEN_ID)
    {
        tree_data data_semi = *Create_TreeDataPuncSemiGl();
        pos = Add_TreeElemLang(data_semi, 'R', pos);

        tree_data data_func_own = *Create_TreeDataFuncOwnDef();
        tree_elem* func_own = Add_TreeElemLang(data_func_own, 'L', pos);

        tkn += 2;

        Fill_Func(func_own);
    };

    if(tkn->mode != MODE_TOKEN_END)
    {
        fprintf(stderr, "ERROR!!! There isn't бацька\n");
        Print_Error(*tkn);
    }

    return head;
}



tree_elem* GetL()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));

    while(!is_func_sys_ret(tkn->word) && !is_punc_prace1((tkn - 1)->word))
    {
        SKIP_INT(tkn);

        tree_elem* pos1 = pos;

        pos = GetS();

        if(!pos1->left)
            continue;

        pos->parent = pos1;
        pos1->right = pos;
    }

    if(!is_func_sys_ret(tkn->word) && !is_punc_prace1((tkn - 1)->word))
    {
        fprintf(stderr, "ERROR!!! There isn't пажаць or Ў\n");
        Print_Error(*tkn);
    }

    if(is_func_sys_ret(tkn->word))
    {
        tree_elem* pos_ret = GetRet();

        if(pos->left)
        {
            pos_ret->parent = pos;
            pos->right = pos_ret;
        }
        else
            pos = pos_ret;
    }

    while(pos->parent)
        pos = pos->parent;

    if(!pos->left)
    {
        fprintf(stderr, "ERROR!!! Empty Func\n");
        Print_Error(*tkn);
    }

    return pos;
}


tree_elem* GetRet()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataOp();

    tree_data data_func_sys_ret = *Create_TreeDataFuncSysRet();
    tree_elem* ret = Add_TreeElemLang(data_func_sys_ret, 'L', pos);
    tkn++;

    ret->left = GetE();

    CHECK_SEMI(tkn);

    return pos;
}


tree_elem* GetS()
{
    tree_elem* pos = nullptr;

    if(is_op_ass((tkn + 1)->word))
        pos = GetA();
    else
        pos = GetOps();

    CHECK_SEMI(tkn);

    return pos;
}


tree_elem* GetOps()
{
    tree_elem* pos = nullptr;

    SKIP_INT(tkn);

    if(is_func_sys_if(tkn->word))
    {
        pos = GetIf();
        return pos;
    }

    if(is_func_sys_wh(tkn->word))
    {
        pos = GetW();
        return pos;
    }

    if(is_func_sys(tkn->word))
    {
        pos = GetOpss();
        return pos;
    }

    return pos;
}


tree_elem* GetOpss()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataOp();

    tree_data pos1_data = *Create_TreeDataFuncSys();
    tree_elem* pos1 = Add_TreeElemLang(pos1_data, 'L', pos);

    tkn++;

    tree_elem* pos2 = GetE();

    pos2->parent = pos1;
    pos1->left = pos2;

    return pos;
}


tree_elem* GetIf()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataOp();

    tree_data data_func_sys_if = *Create_TreeDataFuncSysIf();
    tree_elem* pos1 = Add_TreeElemLang(data_func_sys_if, 'L', pos);

    tkn += 2;

    pos1->left  = GetC();

    tkn++;

    tree_data data_func_sys_ife = *Create_TreeDataFuncSysIfe();
    tree_elem* pos2 = Add_TreeElemLang(data_func_sys_ife, 'R', pos1);

    tree_elem* pos3 = Fill_IfElseWh();            //pos3___left-if-else

    pos3->parent = pos2;
    pos2->left = pos3;

    tkn++;

    if(is_func_sys_ife(tkn->word))
    {
        tkn++;

        tree_elem* pos4 = Fill_IfElseWh();

        pos4->parent = pos2;
        pos2->right = pos4;

        tkn++;
    }

    return pos;
}


tree_elem* GetW()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataOp();

    tree_data data_func_sys_wh = *Create_TreeDataFuncSysWh();
    tree_elem* pos1 = Add_TreeElemLang(data_func_sys_wh, 'L', pos);

    tkn += 2;

    pos1->left = GetC();

    tkn++;

    tree_elem* pos2 = Fill_IfElseWh();

    pos2->parent = pos1;
    pos1->right = pos2;

    tkn++;

    return pos;
}



tree_elem* GetC()
{
    tree_elem* pos1 = GetE();

    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataOpCond();
    tkn++;

    tree_elem* pos2 = GetE();

    pos = Tie_Elems(pos, pos1, pos2);

    return pos;
}


tree_elem* GetA()
{
    tree_elem* pos1 = GetId();

    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataOp();

    tree_elem* posa = (tree_elem*)calloc(1, sizeof(tree_elem));
    posa->data = *Create_TreeDataOpAss();
    tkn++;

    pos->left = posa;
    posa->parent = pos;

    tree_elem* pos2 = GetE();

    posa = Tie_Elems(posa, pos1, pos2);

    return pos;
}


tree_elem* GetE()
{
    tree_elem* pos = GetT();

    while(Which_ModeOpMath(tkn->word) == OP_MATH_ADD || Which_ModeOpMath(tkn->word) == OP_MATH_SUB)
    {
        tree_elem* pos1 = (tree_elem*)calloc(1, sizeof(tree_elem));
        pos1->data = *Create_TreeDataOpMath();

        tkn++;

        Swap_Elem(&pos, &pos1);

        tree_elem* pos2 = GetT();

        pos = Tie_Elems(pos, pos1, pos2);
    }

    return pos;
}


tree_elem* GetT()
{
    tree_elem* pos = GetP();

    while(Which_ModeOpMath(tkn->word) == OP_MATH_MUL || Which_ModeOpMath(tkn->word) == OP_MATH_DIV)
    {
        tree_elem* pos1 = (tree_elem*)calloc(1, sizeof(tree_elem));
        pos1->data = *Create_TreeDataOpMath();

        tkn++;

        Swap_Elem(&pos, &pos1);

        tree_elem* pos2 = GetP();

        pos = Tie_Elems(pos, pos1, pos2);
    }

    return pos;
}


tree_elem* GetP()
{
    tree_elem* pos = nullptr;

    if(is_op_op_par(tkn->word))
    {
        tkn++;

        pos = GetE();

        tkn++;

        return pos;
    }

    if(tkn->mode == MODE_TOKEN_NUM)
    {
        pos = GetN();

        return pos;
    }

    if(tkn->mode == MODE_TOKEN_ID)
    {
        if(is_func_math(tkn->word))
            pos = GetM();
        else
            pos = GetId();

        return pos;
    }

    return pos;
}


tree_elem* GetM()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataFuncMath();

    tkn += 2;

    pos->right = GetE();

    tkn++;

    return pos;
}


tree_elem* GetN()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));
    pos->data = *Create_TreeDataNum();

    tkn++;

    return pos;
}


tree_elem* GetId()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));

    if(!is_op_op_par_l((tkn + 1)->word))
    {
        pos->data = *Create_TreeDataVar();
        tkn++;
    }

    else
    {
        pos->data = *Create_TreeDataFuncOwn();

        tkn += 2;

        pos = Fill_FuncParam(pos);
    }

    return pos;
}


//---------------------------------------------------------------------------------------------------------------------


tree_elem* Add_TreeElemLang(data_t value, char branch, tree_elem* pos)
{
    assert(pos);

    tree_elem* new_elem = (tree_elem*)calloc(1, sizeof(new_elem[0]));

    Create_New_TreeElem(new_elem);

    new_elem->data = value;
    new_elem->parent = pos;

    if (branch == 'L')
        pos->left = new_elem;

    if (branch == 'R')
        pos->right = new_elem;

    return new_elem;
}


tree_elem* Fill_Func(tree_elem* func)
{
    assert(func);

    tree_elem* pos = func;

    if(is_op_op_par(tkn->word))
        tkn++;

    pos = Fill_FuncParam(pos);

    CHECK_PRACE3(tkn);

    tree_elem* posL = GetL();
    func->right = posL;
    posL->parent = func;

    CHECK_PRACE3(tkn);

    return func;
}


tree_elem* Fill_FuncParam(tree_elem* func)
{
    assert(func);

    tree_elem* pos = func;

    while(is_op_op_comma((tkn + 1)->word) || is_op_op_par((tkn + 1)->word) || Which_OpMath((tkn + 1)->word))
    {
        tree_elem* pos1 = pos;

        tree_data data_temp = *Create_TreeDataOpOpComma();
        pos = Add_TreeElemLang(data_temp, 'L', pos);

        pos1->left = pos;
        pos->parent = pos1;

        tree_elem* elem_E = GetE();
        elem_E->parent = pos;
        pos->right = elem_E;

        tkn++;
    }

    return func;
}


tree_elem* Fill_IfElseWh()
{
    tree_elem* pos = (tree_elem*)calloc(1, sizeof(tree_elem));             //pos___if-else
    while(!is_func_sys_ret(tkn->word) && !is_punc_prace1(tkn->word))
    {
        tree_elem* pos1 = pos;

        pos = GetS();

        if(!pos1->left)
            continue;

        pos->parent = pos1;
        pos1->right = pos;
    }

    if(is_func_sys_ret(tkn->word))
    {
        tree_elem* pos_ret = GetRet();

        if(pos->data.mode != MODE_EMPTY)
        {
            pos_ret->parent = pos;
            pos->right = pos_ret;
        }
        else
            pos = pos_ret;
    }

    while(pos->parent)
        pos = pos->parent;

    return pos;
}


tree_elem* Tie_Elems(tree_elem* pos, tree_elem* pos_l, tree_elem* pos_r)
{
    assert(pos);

    pos->left  = pos_l;
    pos->right = pos_r;
    pos_l->parent = pos;
    pos_r->parent = pos;

    assert(pos);

    return pos;
}


bool Swap_Elem(tree_elem** pos1, tree_elem** pos2)
{
    assert(pos1);
    assert(pos2);

    tree_elem* temp = *pos1;
    *pos1 = *pos2;
    *pos2 = temp;

    assert(pos1);
    assert(pos2);

    return true;
}


size_t strlen_utf8(char* str)
{
    assert(str);

    size_t len = 0;
    for(size_t i_sym = 0; i_sym < 1000; i_sym += 2)
    {
        if(isspace(*(str + i_sym)))
            break;

        len += 2;
    }

    return len;
}

#undef CHECK_SEMI
#undef CHECK_PRACE3
#undef SKIP_INT


//---------------------------------------------------------------------------------------------------------------------

tree_data* Create_TreeDataPuncSemiGl()
{
    tree_data* punc_semi_gl = (tree_data*)calloc(1, sizeof(tree_data));

    punc_semi_gl->mode = MODE_PUNC_SEMI_GL;

    char temp_word[] = ";";
    punc_semi_gl->word = strdup(temp_word);

    return punc_semi_gl;
}


tree_data* Create_TreeDataOp()
{
    tree_data* op = (tree_data*)calloc(1, sizeof(tree_data));

    op->mode = MODE_OP;

    char temp_word[] = "op";
    op->word = strdup(temp_word);

    return op;
}


tree_data* Create_TreeDataFuncMain()
{
    tree_data* func_main = (tree_data*)calloc(1, sizeof(tree_data));

    func_main->mode = MODE_FUNC_MAIN;

    char temp_word[] = "$main";
    func_main->word = strdup(temp_word);

    return func_main;
}


tree_data* Create_TreeDataOpOpComma()
{
    tree_data* op_op_comma = (tree_data*)calloc(1, sizeof(tree_data));

    op_op_comma->mode = MODE_OP_OP_COMMA;

    char temp_word[] = ",";
    op_op_comma->word = strdup(temp_word);

    return op_op_comma;
}


tree_data* Create_TreeDataFuncOwn()
{
    tree_data* func_own = (tree_data*)calloc(1, sizeof(tree_data));

    func_own->mode = MODE_FUNC_OWN;

    char* temp_word = (char*)calloc(strlen_utf8(tkn->word) + 3, sizeof(char));
    strcat(temp_word, "$");
    strcat(temp_word, tkn->word);
    func_own->word = strdup(temp_word);

    return func_own;
}


tree_data* Create_TreeDataFuncOwnDef()
{
    tree_data* func_own = (tree_data*)calloc(1, sizeof(tree_data));

    func_own->mode = MODE_FUNC_OWN_DEF;

    char* temp_word = (char*)calloc(strlen_utf8(tkn->word) + 3, sizeof(char));
    strcat(temp_word, "$");
    strcat(temp_word, tkn->word);
    func_own->word = strdup(temp_word);

    return func_own;
}


tree_data* Create_TreeDataFuncSysRet()
{
    tree_data* func_sys_ret = (tree_data*)calloc(1, sizeof(tree_data));

    func_sys_ret->mode = MODE_FUNC_SYS_RET;

    char temp_word[] = "ret";
    func_sys_ret->word = strdup(temp_word);

    return func_sys_ret;
}


tree_data* Create_TreeDataFuncSys()
{
    tree_data* func_sys = (tree_data*)calloc(1, sizeof(tree_data));

    func_sys->mode = MODE_FUNC_SYS;

    if(is_func_sys_in(tkn->word))
        func_sys->mode = MODE_FUNC_SYS_IN;

    if(is_func_sys_out(tkn->word))
        func_sys->mode = MODE_FUNC_SYS_OUT;

    func_sys->word = strdup(Which_FuncSys(tkn->word));

    return func_sys;
}


tree_data* Create_TreeDataFuncSysIf()
{
    tree_data* func_sys_if = (tree_data*)calloc(1, sizeof(tree_data));

    func_sys_if->mode = MODE_FUNC_SYS_IF;

    char temp_word[] = "if";
    func_sys_if->word = strdup(temp_word);

    return func_sys_if;
}


tree_data* Create_TreeDataFuncSysIfe()
{
    tree_data* func_sys_ife = (tree_data*)calloc(1, sizeof(tree_data));

    func_sys_ife->mode = MODE_FUNC_SYS_IFE;

    char temp_word[] = "if-else";
    func_sys_ife->word = strdup(temp_word);

    return func_sys_ife;
}


tree_data* Create_TreeDataFuncSysWh()
{
    tree_data* func_sys_wh = (tree_data*)calloc(1, sizeof(tree_data));

    func_sys_wh->mode = MODE_FUNC_SYS_WH;

    char temp_word[] = "while";
    func_sys_wh->word = strdup(temp_word);

    return func_sys_wh;
}


tree_data* Create_TreeDataOpCond()
{
    tree_data* op_cond = (tree_data*)calloc(1, sizeof(tree_data));

    op_cond->mode = MODE_OP_COND;

    op_cond->word = strdup(Which_OpCond(tkn->word));

    return op_cond;
}


tree_data* Create_TreeDataOpAss()
{
    tree_data* op_ass = (tree_data*)calloc(1, sizeof(tree_data));

    op_ass->mode = MODE_OP_ASS;

    char temp_word[] = "=";
    op_ass->word = strdup(temp_word);

    return op_ass;
}


tree_data* Create_TreeDataOpMath()
{
    tree_data* op_math = (tree_data*)calloc(1, sizeof(tree_data));

    op_math->mode = MODE_OP_MATH;

    op_math->word = strdup(Which_OpMath(tkn->word));

    return op_math;
}


tree_data* Create_TreeDataVar()
{
    tree_data* var = (tree_data*)calloc(1, sizeof(tree_data));

    var->mode = MODE_VAR;

    var->word = strdup(tkn->word);

    return var;
}


tree_data* Create_TreeDataNum()
{
    tree_data* num = (tree_data*)calloc(1, sizeof(tree_data));

    num->mode = MODE_NUM;

    num->number = tkn->number;

    return num;
}

tree_data* Create_TreeDataFuncMath()
{
    tree_data* func_math = (tree_data*)calloc(1, sizeof(tree_data));

    func_math->mode = MODE_FUNC_MATH;

    func_math->word = strdup(Which_FuncMath(tkn->word));

    return func_math;
}


inline void Print_Error(const token token_err)
{
    /*fprintf(stderr, "num_line: %s\t", __PRETTY_FUNCTION__);
    fprintf(stderr, "pos_line: %d\n", __LINE__);*/
    fprintf(stderr, "by_num_line: %lu\t", token_err.num_line);
    fprintf(stderr, "by_pos_line: %lu\n", token_err.pos_line);
    abort();
}


//PRINT-------------------------------------------------------------------------------------------------------

void Print_Tree(tree_elem* pos, FILE* tree_lang_output)
{
    assert(tree_lang_output);
    //assert(pos);


    if(!pos)
    {
        fprintf(tree_lang_output, "@");
        return;
    }

    fprintf(tree_lang_output, "{");

    if(pos->data.mode == MODE_NUM)
        fprintf(tree_lang_output, "%d", pos->data.number);
    else
        fprintf(tree_lang_output, "%s", pos->data.word);
//    if(pos->left) Print_Tree(pos->left, tree_output);

    if(!pos->right && !pos->left)
    {
        fprintf(tree_lang_output, "}");
        return;
    }

    Print_Tree(pos->left, tree_lang_output);

//    if(pos->right) Print_Tree(pos->right, tree_output);

    Print_Tree(pos->right, tree_lang_output);

    fprintf(tree_lang_output, "}");

    assert(tree_lang_output);
}