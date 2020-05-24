#include "lang_back_end.h"

/*Buffer_t Buffer;

auto Funcs = (Func_t*)calloc(MAX_AMOUNT_FUNCS, sizeof(Func_t));

size_t   I_Func = SIZE_LIBRARY + 1;
Var_t* Var_Func = nullptr;  //var in current func*/

BackEnd_t backEnd( (Buffer_t()) );

#define BUFFER   backEnd.buffer_
#define FUNCS    backEnd.func_
#define I_FUNC   backEnd.iFunc_
#define VAR_FUNC backEnd.varFunc_


void Do_BackEnd(tree* tree_lang, FILE* elf)
{
    assert(tree_lang);
    assert(elf);

    PrintTree_BinInBuf(tree_lang->head);

    VAR_FUNC = nullptr;
    Print_NOP(3);
    PrintLibF_BinInBuf();
    PrintMark_BinInBuf();
    PrintOptm_BinInBuf();

    size_t size_code = BUFFER.GetSize();

    Print_Header(elf, size_code);

    fwrite(BUFFER.GetBuffer(), sizeof(char), size_code, elf);
}


//MAIN PRINT FUNCTIONS----------------------------------------------------------------------------------------------

#define L pos->left                       // for main print functions
#define R pos->right                      //

#define i_calls FUNCS[i_func_pos].i_call  // for main print func and functions

void PrintTree_BinInBuf(tree_elem* pos)
{
    if(!pos) return;

    size_t i_func_pos = 0;
    size_t i_var      = 0;

    switch(pos->data.mode)
    {
        case MODE_FUNC_MAIN:

            BUFFER.PrintHexCommand(fninit, fninit_size);    // BEFORE MAIN
            Add_Func(pos);
            i_func_pos = Get_IndexThisFunc(pos);
            PrintTree_CallFunc(i_func_pos, pos);

            PrintTree_Exit();

            i_func_pos = Get_IndexThisFunc(pos);             // START OF MAIN
            VAR_FUNC = Add_FuncVar(pos, i_func_pos);
            PrintTree_DefFunc(i_func_pos);

            PrintTree_BinInBuf(R);
            return;

        case MODE_FUNC_OWN:
            i_func_pos = Get_IndexThisFunc(pos);            // search func; if not found - add
            PrintTree_CallFunc(i_func_pos, pos);
            BUFFER.PrintHexCommand(push_rax, push_rax_size);

            return;

        case MODE_FUNC_OWN_DEF:
            i_func_pos = Get_IndexThisFunc(pos);
            VAR_FUNC = Add_FuncVar(pos, i_func_pos);
            PrintTree_DefFunc(i_func_pos);

            PrintTree_BinInBuf(R);
            return;

        case MODE_FUNC_SYS_IN:
            if(!is_exist_LibFunc(NUM_LIB_SCANF))
                Add_LibFunc(NUM_LIB_SCANF);

            PrintTree_CallFunc(NUM_LIB_SCANF, pos);

            PrintTree_Ass(L->data.word);                             // from rax to var

            return;

        case MODE_FUNC_SYS_IF:
        {
            PrintTree_BinInBuf(L);                                   // write condition
            BUFFER.IncSize(SIZE_ADDRESS);                            // skip 4 bytes for jump
            size_t if_offset = BUFFER.GetSize();                     // save first jump pos

            PrintTree_BinInBuf(R->left);                             // if
            BUFFER.PrintHexCommand(jmp_long, jmp_long_size);
            BUFFER.IncSize(SIZE_ADDRESS);                             // skip 4 bytes for jump
            size_t else_offset = BUFFER.GetSize();                    // save second jump pos

            BUFFER.PrintHexNumberi(BUFFER.GetSize() - if_offset, if_offset - SIZE_ADDRESS);      // fill first jump

            PrintTree_BinInBuf(R->right);                                                        // else

            BUFFER.PrintHexNumberi(BUFFER.GetSize() - else_offset, else_offset - SIZE_ADDRESS);  // fill scnd jump

            return;
        }

        case MODE_FUNC_SYS_WH:
        {
            size_t wh_offset = BUFFER.GetSize();

            PrintTree_BinInBuf(L);
            BUFFER.IncSize(SIZE_ADDRESS);          // skip 4 bytes for jump
            size_t whe_offset = BUFFER.GetSize();  // save jump pos (if not while)

            PrintTree_BinInBuf(R);

            BUFFER.PrintHexCommand(jmp_long, jmp_long_size);
            BUFFER.PrintHexNumber(wh_offset - BUFFER.GetSize() + SIZE_ADDRESS);                 // fill jump while

            BUFFER.PrintHexNumberi(BUFFER.GetSize() - whe_offset, whe_offset - SIZE_ADDRESS);   // fill jump whe
        }

        case MODE_OP_ASS:
            PrintTree_BinInBuf(R);

            BUFFER.PrintHexCommand(pop_rax, pop_rax_size); //rvalue from stack in rax
            PrintTree_Ass(L->data.word);                   //from rax to var

            return;
    }

    PrintTree_BinInBuf(L);
    PrintTree_BinInBuf(R);

    switch(pos->data.mode)
    {
        case MODE_OP_MATH:


            switch(*(pos->data.word))
            {
                case '+':   BUFFER.PrintHexCommand(pop_rbx, pop_rbx_size);
                            BUFFER.PrintHexCommand(pop_rax, pop_rax_size);
                            BUFFER.PrintHexCommand(add_rax_rbx, add_rax_rbx_size);
                            BUFFER.PrintHexCommand(push_rax, push_rax_size);
                            return;

                case '-':   BUFFER.PrintHexCommand(pop_rbx, pop_rbx_size);
                            BUFFER.PrintHexCommand(pop_rax, pop_rax_size);
                            BUFFER.PrintHexCommand(sub_rax_rbx, sub_rax_rbx_size);
                            BUFFER.PrintHexCommand(push_rax, push_rax_size);
                            return;
            }

            BUFFER.PrintHexCommand    (fild_lrspl, fild_lrspl_size);
            BUFFER.PrintHexSmallNumber(SIZE_VAR);

            switch(*(pos->data.word))
            {
                case '*':   BUFFER.PrintHexCommand    (fimul_lrspl, fimul_lrspl_size);
                            BUFFER.PrintHexCommand    (push_small, push_small_size);
                            BUFFER.PrintHexSmallNumber(ACCURACY);
                            BUFFER.PrintHexCommand    (fidiv_lrspl, fidiv_lrspl_size);
                            break;

                case '/':   BUFFER.PrintHexCommand    (fidiv_lrspl, fidiv_lrspl_size);
                            BUFFER.PrintHexCommand    (push_small, push_small_size);
                            BUFFER.PrintHexSmallNumber(ACCURACY);
                            BUFFER.PrintHexCommand    (fimul_lrspl, fimul_lrspl_size);
                            break;

                default: fprintf(stderr, "Error back_end OP_MATH\n");
                            abort();
            }

            BUFFER.PrintHexCommand(fist_lrspl, fist_lrspl_size);

            BUFFER.PrintHexCommand    (movsx_rax_lrspl, movsx_rax_lrspl_size);
            BUFFER.PrintHexCommand    (add_rsp, add_rsp_size);
            BUFFER.PrintHexSmallNumber(3 * SIZE_VAR);
            BUFFER.PrintHexCommand    (push_rax, push_rax_size);
            break;

        case MODE_VAR:
            BUFFER.PrintHexCommand(mov_rax_lrbpl, mov_rax_lrbpl_size);    //mov rax, var
            i_var = Search_Var(pos->data.word);
            BUFFER.PrintHexSmallNumber(0 - VAR_FUNC[i_var].var_offset);

            BUFFER.PrintHexCommand(push_rax, push_rax_size);
            break;

        case MODE_NUM:
        {
            size_t number = ACCURACY * pos->data.number;
            if(is_SmallNumber(number))
            {
                BUFFER.PrintHexCommand(push_small, push_small_size);
                BUFFER.PrintHexSmallNumber(number);
            }
            else
            {
                BUFFER.PrintHexCommand(push, push_size);
                BUFFER.PrintHexNumber(number);
            }
            break;
        }

        case MODE_FUNC_SYS_OUT:
            if(!is_exist_LibFunc(NUM_LIB_PRINTF))
                Add_LibFunc(NUM_LIB_PRINTF);

            BUFFER.PrintHexCommand(pop_rax, pop_rax_size);
            PrintTree_CallFunc(NUM_LIB_PRINTF, pos);

            break;

        case MODE_FUNC_MATH:
            if(!is_exist_LibFunc(NUM_LIB_SQRT))
                Add_LibFunc(NUM_LIB_SQRT);

            BUFFER.PrintHexCommand(pop_rax, pop_rax_size);
            PrintTree_CallFunc(NUM_LIB_SQRT, pos);

            BUFFER.PrintHexCommand(push_rax, push_rax_size);
            break;

        case MODE_FUNC_SYS_RET:
            PrintTree_Ret();
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
            BUFFER.PrintHexCommand(pop_rbx, pop_rbx_size);
            BUFFER.PrintHexCommand(pop_rax, pop_rax_size);
            BUFFER.PrintHexCommand(cmp_rax_rbx, cmp_rax_rbx_size);

            switch(Which_ModeOpCond(pos->data.word))
            {
                case OP_COND_JA :   BUFFER.PrintHexCommand(jle_long, jle_long_size);
                                    break;

                case OP_COND_JB :   BUFFER.PrintHexCommand(jge_long, jge_long_size);
                                    break;

                case OP_COND_JAE:   BUFFER.PrintHexCommand(jl_long, jl_long_size);
                                    break;

                case OP_COND_JBE:   BUFFER.PrintHexCommand(jg_long, jg_long_size);
                                    break;

                case OP_COND_JE :   BUFFER.PrintHexCommand(jne_long, jne_long_size);
                                    break;

                default: fprintf(stderr, "Error front_end OP_COND\n");
                            abort();
            }
            break;
    }

}


void PrintMark_BinInBuf()
{
    assert(BUFFER.GetBuffer());

    for(size_t ii_func = 0; ii_func < I_FUNC; ii_func++)
    {
        for(size_t ii_call = 0; ii_call < FUNCS[ii_func].i_call; ii_call++)
        {
            size_t tmp = FUNCS[ii_func].func_offset - FUNCS[ii_func].call_offset[ii_call] - SIZE_ADDRESS;
            FUNCS[ii_func].call_offset[ii_call] = tmp;
        }
    }

    fprintf(stderr, "%zu", FUNCS[I_FUNC - 1].call_offset[0]);

    for(size_t ii_mark = 0; ii_mark < BUFFER.GetIMark(); ii_mark++)
    {
        BUFFER.PrintHexMark(ii_mark);
    }
}


void  PrintLibF_BinInBuf()
{
    for(size_t i_libfunc = 1; i_libfunc <= SIZE_LIBRARY; i_libfunc++)
    {
        if(!is_exist_LibFunc(i_libfunc))
            continue;
        PrintTree_DefFunc(i_libfunc);
        PrintTree_LibFunc(i_libfunc);
        PrintTree_Ret    (         );
    }
}


void  PrintOptm_BinInBuf()
{
    size_t size_code = BUFFER.GetSize();
    for(size_t i_byte = 0; i_byte < size_code; i_byte++)
    {
        char* now_byte = BUFFER.GetBuffer() + i_byte;

        if(is_ThisCommand(now_byte, call, call_size))
            Optimize_Call(now_byte);

        if(is_ThisCommand(now_byte,  pop_rax, pop_rax_size))
        {
            char* prev1_byte    = now_byte - pop_rax_size;

            Optimize_PushPop(now_byte, prev1_byte);

            char* mb_push_small = prev1_byte - push_small_size - SIZE_SMALL_NUMBER;
            char* mb_push       = prev1_byte - push_size       - SIZE_NUMBER;

            if(is_ThisCommand(prev1_byte,    pop_rbx,    pop_rbp_size))
            {
                if (is_ThisCommand(mb_push_small, push_small, push_small_size))
                    Optimize_PushPop(now_byte, mb_push_small - push_rax_size);

                if(is_ThisCommand(mb_push,         push,      push_size      ))
                    Optimize_PushPop(now_byte, mb_push       - push_rax_size);
            }
        }

        if(is_ThisCommand(now_byte, ret, ret_size))
            Optimize_Ret(now_byte);

        if(is_ThisCommand(now_byte, mov_rax_lrbpl_size, mov_rax_lrbpl_size))
            Optimize_FrameOut(now_byte,
                              now_byte - SIZE_SMALL_NUMBER - mov_lrbpl_rax_size);


    }
}


#undef L
#undef R


//Print++---------------------------------------------------------------------------------------------

void PrintTree_CallFunc(size_t i_func_pos, tree_elem* pos_func)
{
    assert(BUFFER.GetBuffer());

    if(!is_LibFunc(i_func_pos))
        PrintTree_FrameOut(i_func_pos, pos_func);

    PrintTree_CallOut(i_func_pos);

    assert(BUFFER.GetBuffer());
}


void PrintTree_FrameOut(size_t i_func_pos, tree_elem* pos_func)
{
    assert(BUFFER.GetBuffer());

    tree_elem* tmp = pos_func->left;
    for(size_t i_param = 0; i_param < FUNCS[i_func_pos].n_param && tmp; i_param++)
    {
        BUFFER.PrintHexCommand(mov_rax_lrbpl, mov_rax_lrbpl_size);
        size_t i_var = Search_Var(tmp->right->data.word);
        BUFFER.PrintHexSmallNumber(0 - VAR_FUNC[i_var].var_offset);
        BUFFER.PrintHexCommand(push_rax, push_rax_size);
        tmp = tmp->left;
    }

    assert(BUFFER.GetBuffer());
}



void PrintTree_CallOut(size_t i_func_pos)
{
    assert(BUFFER.GetBuffer());

    BUFFER.PrintHexCommand(call, call_size);
    Add_CallOffset(&FUNCS[i_func_pos]);
    BUFFER.SaveHexMark(&FUNCS[i_func_pos].call_offset[i_calls++]);

    assert(BUFFER.GetBuffer());
}



inline void PrintTree_DefFunc (size_t i_func_pos)
{
    assert(BUFFER.GetBuffer());

    Print_NOP(1);
    PrintTree_CallIn(i_func_pos);

    if(!is_LibFunc(i_func_pos))
        PrintTree_FrameIn(i_func_pos);

    assert(BUFFER.GetBuffer());
}


inline void PrintTree_FrameIn(size_t i_func_pos)
{
    assert(BUFFER.GetBuffer());

    size_t n_var = Count_FuncVar(i_func_pos);

    BUFFER.PrintHexCommand(pop_r14, pop_r14_size);
    BUFFER.PrintHexCommand(sub_rsp, sub_rsp_size);
    BUFFER.PrintHexSmallNumber(SIZE_VAR * (n_var - FUNCS[i_func_pos].n_param));
    BUFFER.PrintHexCommand(push_r14, push_r14_size);
    BUFFER.PrintHexCommand(push_rbp, push_rbp_size);
    BUFFER.PrintHexCommand(mov_rbp_rsp, mov_rbp_rsp_size);
    BUFFER.PrintHexCommand(add_rbp, add_rbp_size);
    BUFFER.PrintHexSmallNumber(8 + 8 + SIZE_VAR * n_var);

    assert(BUFFER.GetBuffer());
}


inline void PrintTree_CallIn(size_t i_func_pos)
{
    assert(BUFFER.GetBuffer());

    Add_FuncOffset(&FUNCS[i_func_pos]);                                                 //add addr
    //buffer.PrintHexCommand(pop_r14, pop_r14_size);  // Part of frame
    if(!is_LibFunc(i_func_pos))
        VAR_FUNC = FUNCS[i_func_pos].var;

    assert(BUFFER.GetBuffer());
}




inline void PrintTree_Ret()
{
    assert(BUFFER.GetBuffer());

    BUFFER.PrintHexCommand(pop_rax, pop_rax_size);

    size_t n_var = Count_FuncVarTab();
    if(n_var != -1)
    {
        BUFFER.PrintHexCommand(pop_rbp, pop_rbp_size);
        BUFFER.PrintHexCommand(pop_r14, pop_r14_size);
        BUFFER.PrintHexCommand(add_rsp, add_rsp_size);
        BUFFER.PrintHexSmallNumber(SIZE_VAR * n_var);
        BUFFER.PrintHexCommand(push_r14, push_r14_size);
    }

    BUFFER.PrintHexCommand(ret, ret_size);
    Print_NOP(1);

    assert(BUFFER.GetBuffer());
}


inline void PrintTree_Exit()
{
    assert(BUFFER.GetBuffer());

    BUFFER.PrintHexCommand(mov_rax, mov_rax_size);                          //EXIT
    BUFFER.PrintHexNumber(60);
    BUFFER.PrintHexCommand(xor_rdi_rdi, xor_rdi_rdi_size);
    BUFFER.PrintHexCommand(syscall, syscall_size);
    Print_NOP(1);

    assert(BUFFER.GetBuffer());
}


inline void PrintTree_LibFunc (size_t num_func)
{
    assert(BUFFER.GetBuffer());

    for(size_t i_byte = 0; i_byte < BUFFER.GetLibSize(num_func); i_byte++)
    {
        BUFFER.PrintHexCommand(BUFFER.GetLibCodei(num_func, i_byte), 1);
    }

    assert(BUFFER.GetBuffer());
}


inline void PrintTree_Ass(char* var_name)
{
    assert(var_name);
    assert(BUFFER.GetBuffer());

    BUFFER.PrintHexCommand(mov_lrbpl_rax, mov_lrbpl_rax_size);  //push in rax from var in L
    size_t i_var = Search_Var(var_name);
    BUFFER.PrintHexSmallNumber(0 - VAR_FUNC[i_var].var_offset);

    assert(BUFFER.GetBuffer());
}


#undef i_calls


//FUNC------------------------------------------------------------------------------------------------

size_t Add_Func(tree_elem* pos_func)
{
    assert(pos_func);

    FUNCS[I_FUNC].func_name   = strdup(pos_func->data.word);
    FUNCS[I_FUNC].n_param     = Count_FuncParam(pos_func);
    FUNCS[I_FUNC].var         = (Var_t*) calloc(MAX_AMOUNT_VARS, sizeof(var_table));
    FUNCS[I_FUNC].call_offset = (size_t*)calloc(MAX_AMOUNT_CALL, sizeof(size_t)   );
    FUNCS[I_FUNC].i_call      = 0;
    //funcs[i_func].number    = Add_FuncNumber(&funcs[i_func]);
    I_FUNC++;

    assert(pos_func);

    return I_FUNC - 1;
}


size_t Search_Func(tree_elem* pos_func)
{
    assert(pos_func);

    char* func_name = pos_func->data.word;

    size_t i_func_pos = SIZE_LIBRARY + 1;
    while(i_func_pos < MAX_AMOUNT_FUNCS && FUNCS[i_func_pos].func_name)
    {
        if(strncmp(func_name, FUNCS[i_func_pos].func_name, strlen_utf8(func_name + 1) + 1) == 0)
            return i_func_pos;
        i_func_pos++;
    }

    i_func_pos = MAX_AMOUNT_FUNCS;

    assert(pos_func);

    return i_func_pos;
}


size_t Search_Var(char* name_var)
{
    assert(name_var);

    for(size_t i_var = 0; VAR_FUNC[i_var].var_name; i_var++)
    {
        char* var_name = VAR_FUNC[i_var].var_name;
        if(strncmp(var_name, name_var, strlen_utf8(var_name + 1) + 1) == 0)
            return i_var;
    }
}


inline size_t Add_CallOffset(Func_t* func)
{
    assert(func);

    func->call_offset[func->i_call] = BUFFER.GetSize();

    assert(func);

    return func->call_offset[func->i_call];
}



inline size_t Add_FuncOffset(Func_t* func)
{
    assert(func);

    func->func_offset = BUFFER.GetSize();

    assert(func);

    return func->func_offset;
}


inline size_t Get_IndexThisFunc(tree_elem* pos_func)
{
    assert(pos_func);

    size_t i_func_pos = Search_Func(pos_func);                                  //search func
    if(i_func_pos == MAX_AMOUNT_FUNCS)                              //if not found - add
        i_func_pos = Add_Func(pos_func);

    Check_NParam(pos_func, i_func_pos);

    return  i_func_pos;
}



void Add_LibFunc(size_t num_func)
{
    FILE* elf_lib = nullptr;
    switch(num_func)
    {
        case NUM_LIB_SCANF:
            BUFFER.SetLibName(NUM_LIB_SCANF, "scanf");
            elf_lib = fopen(ELF_SCANF, "r");
            break;

        case NUM_LIB_PRINTF:
            BUFFER.SetLibName(NUM_LIB_PRINTF, "printf");
            elf_lib = fopen(ELF_PRINTF, "r");
            break;

        case NUM_LIB_SQRT:
            BUFFER.SetLibName(NUM_LIB_SQRT, "sqrt");
            elf_lib = fopen(ELF_SQRT, "r");
            break;

        default:
            fprintf(stderr, "LIB_NOT_FOUND");
    }

    Add_LibSize(num_func, elf_lib);

    fseek(elf_lib, OFFSET_CODE - OFFSET_HEADER, SEEK_SET);
    BUFFER.SetLibByteCode(num_func, elf_lib);

    fclose(elf_lib);

    FUNCS[num_func].func_name   = strdup(BUFFER.GetLibName(num_func));
    FUNCS[num_func].n_param     = 1;
    FUNCS[num_func].var         = nullptr;
    FUNCS[num_func].call_offset = (size_t*)calloc(MAX_AMOUNT_CALL, sizeof(size_t));
    FUNCS[num_func].i_call      = 0;

    return;
}


void Add_LibSize(size_t num_func, FILE* elf_lib)
{
    assert(elf_lib);

    fseek(elf_lib, OFFSET_SIZE_CODE - OFFSET_HEADER, SEEK_SET);
    size_t size = ReadType_HexCode(elf_lib, sizeof(size_t)) - 0x80;
    BUFFER.SetLibSize(num_func, size);

    assert(elf_lib);
}


Var_t* Add_FuncVar(tree_elem* pos_func, size_t i_func_pos)
{
    assert(pos_func);

    size_t n_param = FUNCS[i_func_pos].n_param;

    tree_elem* tmp = pos_func->left;
    for(size_t i_param = 0; i_param < n_param; i_param++)
    {
        FUNCS[i_func_pos].var[i_param].var_name   = strdup(tmp->right->data.word);
        FUNCS[i_func_pos].var[i_param].var_offset = SIZE_VAR * (i_param + 1);             //НО ОН ОТРИЦАТЕЛЬНЫЙ от rbp !!!
        tmp = tmp->left;
    }

    size_t offset_now = n_param * SIZE_VAR;
    Add_FuncVarLoc(pos_func->right, i_func_pos, &offset_now);

    Func_Dump(i_func_pos);

    return FUNCS[i_func_pos].var;
}



void Add_FuncVarLoc (tree_elem* pos_func, size_t i_func_pos, size_t* offset_now)
{
    if (!pos_func) return;

    Add_FuncVarLoc(pos_func->left, i_func_pos, offset_now);

    if(pos_func->data.mode == MODE_VAR)
    {
        if(!is_exist_Var(pos_func->data.word, i_func_pos))
        {
            *offset_now += SIZE_VAR;
            size_t i_var = *offset_now / SIZE_VAR - 1;
            FUNCS[i_func_pos].var[i_var].var_name   = strdup(pos_func->data.word);
            FUNCS[i_func_pos].var[i_var].var_offset = *offset_now;
        }
    }

    Add_FuncVarLoc(pos_func->right, i_func_pos, offset_now);

    return;
}



//SERVICE-----------------------------------------------------------------------------------------------


size_t ReadType_HexCode(FILE* file_hex, size_t size_type)
{
    assert(file_hex);

    char* buf_hex = Read_HexCode(file_hex, size_type);

    size_t hex = 0;
    for(size_t i_byte = 0; i_byte < size_type; i_byte++)
    {
        size_t tmp_byte = buf_hex[i_byte];
        if(tmp_byte > 0xFF)
        {
            tmp_byte = 0 - tmp_byte;
            tmp_byte = 0xFF - tmp_byte;
            tmp_byte++;
        }
        tmp_byte = tmp_byte << 8 * i_byte;
        hex += tmp_byte;
    }

    return hex;
}

char* Read_HexCode(FILE* file_hex, size_t amount)
{
    assert(file_hex);

    auto buf_hex = (char*)calloc(amount, sizeof(char));
    for(size_t i_byte = 0; i_byte < amount; i_byte++)
    {
        char tmp = 0;
        fscanf(file_hex, "%c", &tmp);
        buf_hex[i_byte] = tmp;
    }

    return buf_hex;
}


inline bool is_exist_LibFunc(size_t num_func)
{
    return BUFFER.GetLibrary(num_func) != nullptr;
}

inline bool  is_LibFunc(size_t num_func)
{
    return num_func <= SIZE_LIBRARY;
}


inline bool is_exist_Var(char* name_var, size_t i_func_pos)
{
    for(size_t i_var = 0; FUNCS[i_func_pos].var[i_var].var_name; i_var++)
    {
        char* var_name = FUNCS[i_func_pos].var[i_var].var_name;
        if(strncmp(var_name, name_var, strlen_utf8(var_name + 1) + 1) == 0)
            return true;
    }

    return false;
}


inline bool  is_SmallNumber  (int num)
{
    return num <= 127 && num >= -128;

}

inline bool Check_NParam(tree_elem* pos_func, size_t i_func_pos)
{
    assert(pos_func);

    if(Count_FuncParam(pos_func) != FUNCS[i_func_pos].n_param)
        fprintf(stderr, "Error nparam %s", Cut_Space(FUNCS[i_func_pos].func_name));

    return true;
}


size_t Count_FuncParam(tree_elem* pos_func)
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


size_t Count_FuncVar(size_t i_func_pos)
{
    size_t n_var = 0;
    while(FUNCS[i_func_pos].var[n_var].var_name)
        n_var++;

    return n_var;
}


size_t Count_FuncVarTab()
{
    if(VAR_FUNC)
    {
        size_t n_var = 0;
        while(VAR_FUNC[n_var].var_name)
            n_var++;

        return n_var;
    }

    return -1;
}


//OPTIMIZATION-------------------------------------------------------------------------------------------

void Optimize_Call(char* now_byte)
{
    char* prev1_byte = now_byte - pop_rax_size;
    char* prev2_byte = now_byte - pop_rax_size - push_rax_size;

    Optimize_PushPop (prev1_byte, prev2_byte);

    Optimize_FrameOut(prev1_byte - SIZE_SMALL_NUMBER - mov_rax_lrbpl_size,      // lib_func
                      prev1_byte - SIZE_SMALL_NUMBER - mov_rax_lrbpl_size
                                 - SIZE_SMALL_NUMBER - mov_lrbpl_rax_size);

    Optimize_FrameOut(prev2_byte - SIZE_SMALL_NUMBER - mov_rax_lrbpl_size,      // own_func
                      prev2_byte - SIZE_SMALL_NUMBER - mov_rax_lrbpl_size
                                 - SIZE_SMALL_NUMBER - mov_lrbpl_rax_size);
}



void Optimize_Ret(char* now_byte)
{
    char* prev1_byte = now_byte - pop_rax_size;
    char* prev2_byte = now_byte - pop_rax_size - push_rax_size;

    Optimize_PushPop (prev1_byte, prev2_byte);
}



void Optimize_PushPop(char* com_1, char* com_2)                         // in asm:   com2
{                                                                       //           com1
    if(is_ThisCommand(com_1,  pop_rax,  pop_rax_size) &&
       is_ThisCommand(com_2, push_rax, push_rax_size))
    {
        *com_1 = nop;
        *com_2 = nop;
    }
}


void Optimize_FrameOut(char* com_1, char* com_2)                         // in asm:   com2
{                                                                        //           com1
    if(is_ThisCommand(com_1, mov_rax_lrbpl, mov_rax_lrbpl_size) &&
       is_ThisCommand(com_2, mov_lrbpl_rax, mov_lrbpl_rax_size)    )
    {
        if(is_EqualNumberRbp(com_1, com_2))

            for(size_t i_byte = 0; i_byte < mov_rax_lrbpl_size + SIZE_SMALL_NUMBER; i_byte++)
            {
                com_1[i_byte] = nop;
                com_2[i_byte] = nop;
            }
    }
}


bool is_ThisCommand(const char* now_byte, size_t command, size_t size_command)
{
    for(size_t i_byte = 0; i_byte < size_command; i_byte++)
    {
        size_t copy_command = command;
        copy_command = copy_command >> 8 * i_byte;

        /*if(now_byte[0] == 0x48 && now_byte[1] == 0xFFFFFF8B && now_byte[2] == 0x45)
            fprintf(stderr, "\n%x---%x\n", now_byte[i_byte], static_cast<char>(copy_command));
*/
        if(now_byte[i_byte] != static_cast<char>(copy_command))
            return false;
    }

    return true;
}


bool is_EqualNumberRbp(const char* com_1, const char* com_2)                // [rbp + number]
{                                                                           // chech num1 == num2
    return *(com_1 + mov_rax_lrbpl_size) == *(com_2 + mov_lrbpl_rax_size);
}


//CREATING HEADER----------------------------------------------------------------------------------------

void Print_Header(FILE* elf, size_t size_code)
{
    ELF_header         elf_header = {};
    Program_header program_header = {};

    program_header.P_FILES = size_code;
    program_header.P_MEMSZ = size_code;

    fwrite(&elf_header,        sizeof(ELF_header),     1, elf);
    fwrite(&program_header,    sizeof(Program_header), 1, elf);
}


//SYS----------------------------------------------------------------------------------------------

void Print_NOP(size_t n)
{
    for(int i = 0; i < n; i++)
    {
        BUFFER.PrintHexCommand(nop, nop_size);
    }
}


void Func_Dump(size_t i_func_pos)
{
    fprintf(stderr, "\n\n\n ---HELLO DOLBOED ITS YOU FUCKING FUNC---\n");
    fprintf(stderr, "[%p]\n", FUNCS);
    fprintf(stderr, "name func - %s\n", FUNCS[i_func_pos].func_name);
    fprintf(stderr, "number func - %zu\n", i_func_pos);
    fprintf(stderr, "nparam - %zu\n", FUNCS[i_func_pos].n_param);

    if(!is_LibFunc(i_func_pos))
    {
        fprintf(stderr, "\n name_var\t\t\t offset_var\n");
        for(size_t i_var = 0; FUNCS[i_func_pos].var[i_var].var_name; i_var++)
        {
            fprintf(stderr, "%s\t\t\t\t", FUNCS[i_func_pos].var[i_var].var_name);
            fprintf(stderr, "%zu\n", FUNCS[i_func_pos].var[i_var].var_offset);
        }
        fprintf(stderr, "\n mark vrode poka work tak chto goodbye dolboeb ebany\n--------------------------------\n");
    }
}

void FuncAll_Dump()
{
    fprintf(stderr, "\n\n=======================================================================\n\n");

    for(size_t i = 1; FUNCS[i].func_name; i++)
        Func_Dump(i);

    fprintf(stderr, "\n\n=======================================================================\n\n");
    return;
}


#undef buffer
#undef Funcs
#undef i_Func
#undef var_Func
