#ifndef LANGUAGE_LANG_HEADER_H
#define LANGUAGE_LANG_HEADER_H

#include "tree_header.h"
//#include "DSL.h"

#define tree_library

#ifndef tree_library
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <sys/stat.h>
#include <cmath>
#include <cstdarg>
#endif


const char LANG_INPUT[]       = "/home/shugaley/proga/projects/2_sem/asm/compiler/input/lang_input_square";
const char DOT[]              = "/home/shugaley/proga/projects/2_sem/asm/compiler/dot_out.dot";
const char ASM_OUTPUT[]       = "/home/shugaley/proga/projects/2_sem/asm/compiler/asm_output";
const char TREE_LANG_OUTPUT[] = "/home/shugaley/proga/projects/2_sem/asm/compiler/tree_output";
const char TREE_LANG_INPUT[]  = "/home/shugaley/proga/projects/2_sem/asm/compiler/tree_input";
const char LANG_OUTPUT[]      = "/home/shugaley/proga/projects/2_sem/asm/compiler/lang_output";

enum MODE
{
    MODE_EMPTY        = 0 ,
    MODE_NUM          = 1 ,
    MODE_OP           = 2 ,
    MODE_VAR          = 4 ,
    MODE_FUNC_MATH    = 11,
    MODE_FUNC_OWN     = 12,
    MODE_FUNC_OWN_DEF = 121,
    MODE_FUNC_MAIN    = 14,
    MODE_FUNC_SYS     = 150,
    MODE_FUNC_SYS_IN  = 151,
    MODE_FUNC_SYS_OUT = 152,
    MODE_FUNC_SYS_IF  = 161,
    MODE_FUNC_SYS_IFE = 162,
    MODE_FUNC_SYS_WH  = 18,
    MODE_FUNC_SYS_RET = 19,
    MODE_FUNC_SYS_INT = 20,
    MODE_OP_COND      = 21,
    MODE_OP_ASS       = 22,
    MODE_OP_MATH      = 25,
    MODE_OP_OP_PAR    = 31,
    MODE_OP_OP_COMMA  = 32,
    MODE_PUNC_SEMI_GL = 41,
    MODE_PUNC_SEMI    = 42,
    MODE_PUNC_PRACE1  = 43,
    MODE_PUNC_PRACE2  = 44,
    MODE_PUNC_PRACE3  = 45,
};

enum OP_MATH
{
    OP_MATH_ADD = 1,
    OP_MATH_SUB = 2,
    OP_MATH_MUL = 3,
    OP_MATH_DIV = 4,
};

enum OP_COND
{
    OP_COND_JA  = 1,
    OP_COND_JB  = 2,
    OP_COND_JAE = 3,
    OP_COND_JBE = 4,
    OP_COND_JE  = 5,
};



//Tokenization-------------------------------------------------------------------------------------------

enum MODE_TOKEN
{
    MODE_TOKEN_END  = 0,
    MODE_TOKEN_NUM  = 1,
    MODE_TOKEN_OP   = 2,
    MODE_TOKEN_PUNC = 3,
    MODE_TOKEN_ID   = 4,
};

struct token
{
    int mode        = POISON ;
    int number      = 666 ;
    char* word      = nullptr;
    size_t num_line = POISON ;
    size_t pos_line = POISON ;
};

token* Create_TokenLang    (FILE* lang_inp);
int WhichToken             (struct line buffer_line, size_t* i_sym, char** word, int* number);
token* Create_TokenEnd     (                         size_t nlines                         );
char* Create_Word          (       line buffer_line, size_t* i_sym                         );
inline size_t Count_MaxSize(       line* buffer,     size_t nlines                         );
inline size_t Skip_Space   (       char* buffer,     size_t i_sym                          );
inline bool isop           (char sym);
void Dump_TokenLang        (token* token_lang);
void Dumpi_TokenLang       (token token_lang);

//Rec-----------------------------------------------------------------------------------------------------
//Front_End-----------------------------------------------------------------------------------------------

tree_elem* Create_TreeLang(tree* tree_lang, FILE* lang_inp, FILE* tree_lang_output);

//G::= {Opss ў A ў}* бацька( {E,}* )       ЎЎЎ L ЎЎЎ
//                   {Id   ( {E,}* )       ЎЎЎ L ЎЎЎ}* \0
tree_elem* GetG(const token* token_lang);

//L::= {S}*   Ret | ЎЎ
tree_elem* GetL();

//Ret::= пажаць E ў
tree_elem* GetRet();

//S::= Ops | A | Ret  ў
tree_elem* GetS();

//Ops::= If | W | Opss
tree_elem* GetOps();

//Opss::= ураджай | угнаенне (E)       ????({E,}+)
tree_elem* GetOpss();


//If::= калі  (C)  {S}* | {S}* Ret ў    Ў
//      інакш      {S}* | {S}* Ret ў    Ў |
//      калі  (C)  {S}* | {S}* Ret ў    Ў
tree_elem* GetIf();

//W::= пакуль(C)   {S}* | {S}* Ret ў    Ў
tree_elem* GetW();

//C::= E [як | больш чым | меньш чым] E
tree_elem* GetC();

//A::= Id гэта E
tree_elem* GetA();

//E::= T{[разам з | без]T}*
tree_elem* GetE();


//--
//T::= P{[прапалоць | скасіць]}*
tree_elem* GetT();


//Pow::= P{[^]}*
//tree_elem* GetPow();


//P::= (E) | M | N | Id
tree_elem* GetP();

//M::= ||| (E)
tree_elem* GetM();

//N::= {[0-9]}+
tree_elem* GetN();

//Id::= {[]}+
tree_elem* GetId();



tree_elem* Add_TreeElemLang(data_t value, char branch, tree_elem* pos);
tree_elem* Fill_Func     (tree_elem* func);
tree_elem* Fill_FuncParam(tree_elem* func);
tree_elem* Fill_IfElseWh();
tree_elem* Tie_Elems(tree_elem* pos, tree_elem*  pos_l, tree_elem*  pos_r);
bool Swap_Elem      (                tree_elem** pos1,  tree_elem** pos2);
size_t strlen_utf8(char* str);

tree_data* Create_TreeDataPuncSemiGl();
tree_data* Create_TreeDataOp        ();
tree_data* Create_TreeDataOpOpComma ();
tree_data* Create_TreeDataFuncMain  ();
tree_data* Create_TreeDataFuncOwn   ();
tree_data* Create_TreeDataFuncOwnDef();
tree_data* Create_TreeDataFuncSysRet();
tree_data* Create_TreeDataFuncSys   ();
tree_data* Create_TreeDataFuncSysIf ();
tree_data* Create_TreeDataFuncSysIfe();
tree_data* Create_TreeDataFuncSysWh ();
tree_data* Create_TreeDataOpCond    ();
tree_data* Create_TreeDataOpAss     ();
tree_data* Create_TreeDataOpMath    ();
tree_data* Create_TreeDataVar       ();
tree_data* Create_TreeDataNum       ();
tree_data* Create_TreeDataFuncMath  ();

inline void Print_Error(const token token_err);

void Print_Tree(tree_elem* pos, FILE* tree_lang_output);

//MIDDLE_END---------------------------------------------------------------------------------------------

void Simplify_Tree(tree_elem* pos);


//BACK_END0-------------------------------------------------------------------------------------------------

struct var_table
{
    char* name = nullptr;
    size_t adress = 0;
};

struct func_table
{
    char* name = nullptr;
    int n_param = 0;
    var_table* var = nullptr;
    //int i_var = 0;
};

void PrintAsm_TreeLang(tree_elem* pos, FILE* asm_out);

size_t Push_RamParam  (tree_elem* pos, FILE* asm_out);
char* Cut_Space(char* word);

bool Exist_Var      (char*  var_name);
size_t Find_Var     (char*  var_name);
size_t Find_EmptyVar(              );
size_t Create_Var   (char*  var_name);

size_t Find_Func    (char* func_name);
size_t Create_Func     (tree_elem* pos_func);
size_t Count_FuncNParam(tree_elem* pos_func);


void Print_DumpVar(tree_elem* pos);

//WHICH_IS---------------------------------------------------------------------------------------------------------

bool is_func_sys_int (char* com);
bool is_func_sys_main(char* com);
bool is_op_op_comma  (char* com);
bool is_op_op_par    (char* com);
bool is_op_op_par_l  (char* com);
bool is_punc_semi    (char* com);
bool is_punc_prace3  (char* com);
bool is_punc_prace2  (char* com);
bool is_punc_prace1  (char* com);
bool is_func_sys_ret (char* com);
bool is_func_sys_if  (char* com);
bool is_func_sys_ife (char* com);
bool is_func_sys_wh  (char* com);
bool is_func_sys     (char* com);
bool is_op_ass       (char* com);
bool is_func_math    (char* com);
bool is_func_sys_out (char* com);
bool is_func_sys_in  (char* com);

bool is_func_sys_ret_main(tree_elem* pos);

bool is_end          (tree_elem* pos);
bool is_$            (tree_elem* pos);
bool is_zero         (tree_elem* pos);
bool is_one          (tree_elem* pos);
bool is_high_priority(tree_elem* pos);
bool is_num          (tree_elem* pos);

int Which_ModeOpMath (char* word_com);
int Which_ModeOpCond (char* word_com);

char* Which_OpMath   (char* word_com);
char* Which_FuncSys  (char* word_com);
char* Which_OpCond   (char* word_com);
char* Which_FuncMath (char* word_com);


//FRONT_END_BACK---------------------------------------------------------------------------------------------

void Print_Lang   (tree_elem* pos, FILE* lang_output);
void Print_Indent (                FILE* lang_output);

//Read.............

tree* Read_TreeLang(tree* tree_lang, FILE* tree_lang_input);

tree_elem* Create_TreeLangElem (tree* tree_lang, char* buffer, size_t* i_sym, tree_elem* pos);
tree_elem* Create_TreeLangHead (tree* tree_lang, char* buffer, size_t* i_sym);
tree_elem* Add_TreeBranch      (tree_elem* pos,  char branch);
tree_elem* Create_TreeLangNil();

char* Create_String      (char* buffer, size_t* i_sym);
inline size_t Skip_SpaceB(char* buffer, size_t  i_sym);
size_t count_sizeB();

tree_data* Create_TreeData     (tree_elem* pos, char* string);
int Which_ModeData             (tree_elem* pos, char* string);
bool is_func_mathB             (                char* string);


//Reader-----------------------------------------------------------------------------------------------------

struct line
{
    int length;
    char* ptrline;
};

line* create_all    (FILE* ptr_input, size_t* nlines);
char* create_ar_text(FILE* pnt_input,                 size_t* size);
line* create_struct_lines(char* text, size_t* nlines, size_t  size);
size_t count_size();
size_t count_symbol(const char* text, size_t size, char symbol);

char* create_only_ar_text(FILE* ptr_input);



#endif //LANGUAGE_LANG_HEADER_H
