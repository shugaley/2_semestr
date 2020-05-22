#include "lang_header.h"

const size_t MAXSIZE_VAR_TABLE = 10;
//var_table* var = (var_table*)calloc(MAXSIZE_VAR_TABLE, sizeof(var[0]));

const size_t MAXSIZE_FUNC_TABLE = 10;
func_table* func = (func_table*)calloc(MAXSIZE_FUNC_TABLE, sizeof(func[0]));

var_table* varfunc = nullptr;

//size_t i_var  = 0;
size_t i_ram      = 0;
size_t i_ram_temp = 0;

size_t jmp_if = 0;

size_t i_func0 = 0;

#define L pos->left
#define R pos->right

void PrintAsm_TreeLang(tree_elem* pos, FILE* asm_out)
{
    if(!pos) return;

    Print_DumpVar(pos);

    size_t jmp_temp = 0;
    size_t i_pos_func = 0;

    switch(pos->data.mode)
    {
        case MODE_FUNC_MAIN:
            fprintf(asm_out, "push %lu\n", i_ram);
            fprintf(asm_out, "push ex\n");

            i_pos_func = Create_Func(pos);

            varfunc = func[i_pos_func].var;

            PrintAsm_TreeLang(L, asm_out);
            PrintAsm_TreeLang(R, asm_out);

            fprintf(asm_out, "end\n");

            return;

        case MODE_FUNC_OWN:
            if(Find_Func(pos->data.word) == -1)
                Create_Func(pos);

            if(Count_FuncNParam(pos) != func[Find_Func(pos->data.word)].n_param)
            {
                fprintf(stderr, "Error nparam out %s", Cut_Space(pos->data.word));
                abort();
            }

            fprintf(asm_out, "push %lu\n", i_ram_temp);

            PrintAsm_TreeLang(L, asm_out);

            fprintf(asm_out, "push %lu\n", i_ram);
            fprintf(asm_out, "push ex\n");

            fprintf(asm_out, "call f%lu\n", Find_Func(pos->data.word));

            fprintf(asm_out, "push dx\n");
            fprintf(asm_out, "push %lu\n", i_ram);
            fprintf(asm_out, "pop dx\n");
            fprintf(asm_out, "sub\n");
            fprintf(asm_out, "push ex\n");

            fprintf(asm_out, "pop ax\n");

            return;

        case MODE_FUNC_OWN_DEF:
            i_ram_temp = 0;

            i_pos_func = Find_Func(pos->data.word);
            varfunc = func[i_pos_func].var;

            fprintf(asm_out, "f%lu:\n", Find_Func(pos->data.word));

            Push_RamParam(pos, asm_out);

            i_ram_temp = func[i_pos_func].n_param;
            i_ram += i_ram_temp;

            PrintAsm_TreeLang(R, asm_out);

            i_ram -= i_ram_temp;

            return;

        case MODE_FUNC_SYS_IN:
            fprintf(asm_out, "in\n");

            fprintf(asm_out, "push [ex + %lu]\n", varfunc[Find_Var(L->data.word)].adress);

            return;

        case MODE_FUNC_SYS_IF:
            jmp_temp = jmp_if++;

            PrintAsm_TreeLang(L, asm_out);
            fprintf(asm_out, "else_if_%lu\n",    jmp_temp);

            PrintAsm_TreeLang(R->left, asm_out);
            fprintf(asm_out, "jmp end_if_%lu\n", jmp_temp);
            fprintf(asm_out, "else_if_%lu:\n",    jmp_temp);

            PrintAsm_TreeLang(R->right, asm_out);
            fprintf(asm_out, "end_if_%lu:\n",     jmp_temp);

            return;

        case MODE_OP_ASS:
            PrintAsm_TreeLang(R, asm_out);

            size_t pos_var = 0;
            char* var_name = L->data.word;

            if(!Exist_Var(var_name))
                pos_var = Create_Var(var_name);
            else
                pos_var = Find_Var(var_name);

            fprintf(asm_out, "push [ex + %lu]\n", varfunc[pos_var].adress);

            return;
    }


    PrintAsm_TreeLang(L, asm_out);
    PrintAsm_TreeLang(R, asm_out);


    switch(pos->data.mode)
    {
        case MODE_OP_MATH:

            switch(*pos->data.word)
            {
                case '+': fprintf(asm_out, "add\n");
                            break;

                case '-': fprintf(asm_out, "sub\n");
                            break;

                case '*': fprintf(asm_out, "mul\n");
                            break;

                case '/': fprintf(asm_out, "div\n");
                            break;

                default: fprintf(stderr, "Error front_end OP_MATH\n");
                            abort();
            }
            break;

        case MODE_FUNC_MATH:
            fprintf(asm_out, "%s\n", pos->data.word);
            break;

        case MODE_VAR:
            fprintf(asm_out, "pop [ex + %lu]\n", varfunc[Find_Var(pos->data.word)].adress);
            break;

        case MODE_NUM:
            fprintf(asm_out, "push %d\n", pos->data.number);
            break;

        case MODE_FUNC_SYS_OUT:
            fprintf(asm_out, "out\n");
            break;

        case MODE_FUNC_SYS_RET:
            fprintf(asm_out, "push ax\n");

            if(!is_func_sys_ret_main(pos))
                fprintf(asm_out, "ret\n");

            i_ram -= i_ram_temp;

            break;

        case MODE_OP:
            break;

        case MODE_PUNC_SEMI_GL:
            break;

        case MODE_FUNC_SYS_IFE:
            break;

        case MODE_OP_OP_COMMA:
            break;

        case MODE_OP_COND:

            switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JA : fprintf(asm_out, "jae ");
                                    break;

                case OP_COND_JB : fprintf(asm_out, "jbe ");
                                    break;

                case OP_COND_JAE: fprintf(asm_out, "ja " );
                                    break;

                case OP_COND_JBE: fprintf(asm_out, "jb " );
                                    break;

                case OP_COND_JE : fprintf(asm_out, "jne ");
                                    break;

                default: fprintf(stderr, "Error front_end OP_COND\n");
                            abort();
            }
            break;
    }

    return;
}


size_t Push_RamParam(tree_elem* pos, FILE* asm_out)
{
    assert(pos);

    size_t i_pos_func = Find_Func(pos->data.word);

    size_t i_param = 0;
    tree_elem* pos_temp = pos;
    while(i_param < func[i_pos_func].n_param)
    {
        fprintf(asm_out, "push [ex + %lu]\n", i_param);
        pos_temp = pos_temp->left;
        func[i_pos_func].var[i_param].name   = strdup(pos_temp->right->data.word);
        func[i_pos_func].var[i_param].adress = i_param;
        i_param++;
    }

    return func[i_pos_func].n_param;
}





bool Exist_Var(char* var_name)
{
    assert(var_name);

    if(Find_Var(var_name) != -1)
        return true;
    else
        return false;
}


size_t Find_Var(char* var_name)
{
    assert(var_name);

    size_t i_pos_var = 0;
    while(i_pos_var < MAXSIZE_VAR_TABLE && i_pos_var != Find_EmptyVar())
    {
        if(strncmp(var_name, varfunc[i_pos_var].name, strlen_utf8(var_name)) == 0)
            return i_pos_var;
        i_pos_var++;
    }

    return -1;
}


char* Cut_Space(char* word)
{
    assert(word);

    char* temp = strdup(word);

    size_t i = 0;
    while(temp[i] != ' ')
        i++;

    temp[i] = '\0';

    return temp;
}



size_t Find_EmptyVar()
{
    assert(varfunc);

    size_t i_var = 0;
    while(varfunc[i_var].name)
        i_var++;

    return i_var;
}



size_t Create_Var(char* var_name)
{
    assert(var_name);

    size_t i_var = Find_EmptyVar();

    varfunc[i_var].name = strdup(var_name);
    varfunc[i_var].adress = i_ram_temp;
    i_ram++;
    i_ram_temp++;

    return i_var;
}



size_t Find_Func(char* func_name)
{
    assert(func_name);

    size_t i_pos_func = 0;
    while(i_pos_func < MAXSIZE_VAR_TABLE && func[i_pos_func].name)
    {
        fprintf(stderr, "!!!!!!%s     %s\n", func[i_pos_func].name, func_name);
        if(strncmp(func_name, func[i_pos_func].name, strlen_utf8(func_name + 1) + 1) == 0)
            return i_pos_func;
        i_pos_func++;
    }

    return -1;
}


size_t Create_Func(tree_elem* pos_func)
{
    assert(pos_func);

    func[i_func0].name = strdup(pos_func->data.word);
    func[i_func0].n_param = Count_FuncNParam(pos_func);
    func[i_func0].var = (var_table*)calloc(MAXSIZE_VAR_TABLE, sizeof(var_table));

    i_func0++;

    return i_func0 - 1;
}


size_t Count_FuncNParam(tree_elem* pos_func)
{
    assert(pos_func);

    tree_elem* pos = pos_func;
    size_t i_param = 0;
    while(pos->left)
    {
        i_param++;
        pos = pos->left;
    }

    return i_param;
}




void Print_DumpVar(tree_elem* pos)
{
    if(!varfunc)
        return ;

    fprintf(stderr, "\n\n\n\n==============================================================\n");
    fprintf(stderr, "==============================================================\n");

    fprintf(stderr, "%s\n", pos->data.word);

    fprintf(stderr, "iii \t n_param \t\t\t\t var \t\t\t\t\t name\n");
    for(size_t i = 0; i < MAXSIZE_FUNC_TABLE; i++)
        fprintf(stderr, "%lu %8d \t\t\t [%p] \t\t\t %s\n", i, func[i].n_param, func[i].var, func[i].name);

    fprintf(stderr, "\n-------------------------\n");

    fprintf(stderr, "varfunc [%p]\n", varfunc);

    //fprintf(stderr, "i_var: %lu\n", i_var);
    fprintf(stderr, "i_ram: %lu\n", i_ram);
    fprintf(stderr, "i_ram_temp: %lu\n", i_ram);

    fprintf(stderr, "iii \t address \t name\n");
    for(size_t i = 0; i < MAXSIZE_VAR_TABLE; i++)
        fprintf(stderr, "%lu %8lu\t\t%s\n", i, varfunc[i].adress, varfunc[i].name);
}