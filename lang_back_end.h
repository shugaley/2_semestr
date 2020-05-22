#ifndef LANGUAGE_LANG_BACK_END_H
#define LANGUAGE_LANG_BACK_END_H

#include "lang_header.h"

const size_t SIZE_ADDRESS      = 4;
const size_t SIZE_NUMBER       = 4;
const size_t SIZE_VAR          = 8;
const size_t SIZE_SMALL_NUMBER = 1;

const size_t OFFSET_CODE      = 0x0000000000400080;
const size_t OFFSET_HEADER    = 0x0000000000400000;
const size_t OFFSET_SIZE_CODE = 0x0000000000400060;

const size_t MAX_AMOUNT_FUNCS = 20;
const size_t MAX_AMOUNT_VARS  = 12;
const size_t MAX_AMOUNT_CALL  = 100;

const size_t ACCURACY         = 100;

const char      ELF[] = "/home/shugaley/proga/projects/2_sem/asm/compiler/elf.out";
const char TEST_ELF[] = "/home/shugaley/proga/projects/2_sem/asm/compiler/test_lib.out";

//HEADER-----------------------------------------------------------------------------------------------------------


struct ELF_header
{
    const int    EI_MAG      = 0x464C457F;          //ELF
    const char   I_CLASS     = 0x02;                //64 BIT
    const char   EI_DATA     = 0x01;                //DATA2LSB (Little-Endian)
    const char   EI_VERSION  = 0x01;                //EV_CURRENT
    const char   EI_OSABI    = 0x00;                //UNIX System V ABI
    const size_t EI_OSABIVER = 0x0000000000000000;
    const short  E_TYPE      = 0x0002;              //ET_EXEC (Executable file)
    const short  E_MACHINE   = 0x003E;              //EM_X86_64 (AMD x86- 64 architecture)
    const int    E_VERSION   = 0x00000001;          //EV_CURRENT
    const size_t E_ENTRY     = OFFSET_CODE;
    const size_t E_PHOFF     = 0x0000000000000040;
    const size_t E_SHOFF     = 0x0000000000000000;  //7002
    const int    E_FLAGS     = 0x00000000;
    const short  E_EHSIZE    = 0x0040;
    const short  E_PHENTSIZE = 0x0038;
    const short  E_PHNUM     = 0x0001;
    const short  E_SHENTSIZE = 0x0040;
    const short  E_SHNUM     = 0x0005;
    const short  E_SHSTRNDX  = 0x0004;

    //const size_t SIZE_ELF_HEADER = 96;  //0x60
};

struct Program_header
{
    const int    P_TYPE      = 0x00000001;          //PT_LOAD (Loadable segment)
    const int    P_FLAGS     = 0x00000005;          //Execute|Read
    const size_t P_OFFSET    = 0x0000000000000000;
    const size_t P_VADDR     = OFFSET_HEADER;
    const size_t P_PADDR     = OFFSET_HEADER;
          size_t P_FILES     = 000000000000000000;
          size_t P_MEMSZ     = 000000000000000000;
    const size_t P_ALIGN     = 0x0000000000200000;
    const size_t P_SPAC      = 0x0000000000000000;

    //const size_t SIZE_PROGRAM_HEADER = 32;  //0x80 - 0x60
};

//OTHER STRUCTS-----------------------------------------------------------------------------------------

struct Var_t
{
    char*  var_name = nullptr;
    size_t var_offset = 0;
};

struct Func_t
{
    char*   func_name = nullptr;
    size_t  n_param = 0;
    Var_t*  var = nullptr;

    size_t* call_offset = nullptr;
    size_t  i_call = 0;
    size_t  func_offset = 0;
};

//FUNCTIONS---------------------------------------------------------------------------------------------

void Do_BackEnd(tree* tree_lang, FILE* elf);

/*char* Create_ElfHeader(size_t P_FILESZ, size_t P_MEMSZ = 0);
char* Print_FieldHeader(char* pos, size_t field, int size_field);*/
void Print_Header(FILE* elf, size_t size_code);

void  PrintTree_BinInBuf(tree_elem* pos);
void  PrintLibF_BinInBuf();
void  PrintMark_BinInBuf();
void  PrintOptm_BinInBuf();

inline void PrintTree_CallFunc   (size_t i_func_pos, tree_elem* pos_func);
inline void PrintTree_FrameOut   (size_t i_func_pos, tree_elem* pos_func);
inline void PrintTree_CallOut    (size_t i_func_pos);
inline void PrintTree_DefFunc    (size_t i_func_pos);
inline void PrintTree_FrameIn    (size_t i_func_poc);
inline void PrintTree_CallIn     (size_t i_func_poc);
inline void PrintTree_Ret        (                 );
inline void PrintTree_Exit       (                 );
inline void PrintTree_LibFunc    (size_t num_func  );
inline void PrintTree_Ass        (char* var_name   );

       size_t Add_Func         (tree_elem* pos_func);
       size_t Search_Func      (tree_elem* pos_func);
       size_t Search_Var       (char* name_var);
inline size_t Add_CallOffset   (Func_t* func);
inline size_t Add_FuncOffset   (Func_t* func);
inline size_t Get_IndexThisFunc(tree_elem* pos_func);
       void   Add_LibFunc      (size_t num_func);
       void   Add_LibSize      (size_t num_func, FILE* elf_lib);
       Var_t* Add_FuncVar      (tree_elem* pos_func, size_t i_func_pos);
       void   Add_FuncVarLoc   (tree_elem* pos_func, size_t i_func_pos, size_t* offset_now);

inline bool  is_exist_LibFunc(size_t num_func);
inline bool  is_LibFunc      (size_t num_func);
inline bool  is_exist_Var    (char* name_var,      size_t i_func_pos);
inline bool  is_SmallNumber  (int num);
inline bool  Check_NParam    (tree_elem* pos_func, size_t i_func_pos);

size_t   ReadType_HexCode(FILE* file_hex, size_t size_type);
char*        Read_HexCode(FILE* file_hex, size_t amount);

size_t Count_FuncParam (tree_elem* pos_func);
size_t Count_FuncVar   (size_t i_func_pos);
size_t Count_FuncVarTab();

void Optimize_Call    (char* now_byte          );
void Optimize_Ret     (char* now_byte          );
void Optimize_PushPop (char* com_1, char* com_2);
void Optimize_FrameOut(char* com_1, char* com_2);

bool is_ThisCommand   (const char* now_byte, size_t command, size_t size_command);
bool is_EqualNumberRbp(const char* com_1, const char* com_2);


void Print_NOP(size_t n);
void Func_Dump(size_t i_func_pos);
void FuncAll_Dump();

//CLASS BUFFER--------------------------------------------------------------------------------------------

const size_t BEGIN_MAXSIZE = 20;
const size_t SIZE_LIBRARY  = 3;

enum Num_Library_Func
{
    NUM_LIB_SCANF  = 1,
    NUM_LIB_PRINTF = 2,
    NUM_LIB_SQRT   = 3,
};

const char ELF_SCANF[]   = "/home/shugaley/proga/projects/2_sem/asm/compiler/library/scanf.out";
const char ELF_PRINTF[]  = "/home/shugaley/proga/projects/2_sem/asm/compiler/library/printf.out";
const char ELF_SQRT[]    = "/home/shugaley/proga/projects/2_sem/asm/compiler/library/sqrt.out";

struct Library_t
{
    char*  name      = nullptr;
    char*  byte_code = nullptr;
    size_t size_code = 0;
};


struct Mark_t
{
    char*   mark   = nullptr;
    size_t* offset = nullptr;
};


class Buffer_t
{
public:
    explicit Buffer_t();
    ~Buffer_t();
    bool AssertBuffer();

    void IncreaseMaxsize();
    bool CheckMaxsize();
    void IncSize(size_t size = 0);

    void PrintHexCommand    (size_t command, size_t size_command);
    void PrintHexNumber     (size_t number);
    void PrintHexSmallNumber(size_t number);
    void PrintHexNumberi    (size_t number, size_t i_byte);

    void SaveHexMark(size_t* offset);
    void PrintHexMark(size_t ii_mark);

    void SetLibName    (size_t num_func, char* name);
    void SetLibSize    (size_t num_func, size_t size);
    void SetLibByteCode(size_t num_func, FILE* elf_func);

    char*  GetBuffer ();
    char   GetBufferi(size_t i = 0);
    size_t GetSize   ();
    size_t GetIMark  ();
    char*  GetLibrary(size_t i = 0);
    char*  GetLibName (size_t num_func);
    size_t GetLibSize (size_t num_func);
    char   GetLibCodei(size_t num_func, size_t i = 0);

private:
    size_t maxsize_;
    char* buffer_;
    char* pc_;
    Mark_t* mark_;
    size_t  i_mark_;
    Library_t* library_;
};

inline char* CopyBuffer(char* buf_to, char* buf_from, size_t size);

//MAIN CLASS--------------------------------------------------------------------------------------------------

class BackEnd_t
{
public:
    explicit BackEnd_t(const Buffer_t& buffer);
    ~BackEnd_t();

    /*Buffer_t GetBuffer ();
    Func_t*  GetFunc   ();
    size_t   GetIFunc  ();
    Var_t*   GetVarFunc();*/

public:
    Buffer_t buffer_;
    Func_t*  func_;
    size_t   iFunc_;        //number of next empty func
    Var_t*   varFunc_;       //var in current func

};


//BYTE_CODE---------------------------------------------------------------------------------------------------

const size_t ja_mask = 0x3100;
const size_t jb_mask = 0x3000;
const size_t je_mask = 0x7000;

enum Code_Basic
{
    call         = 0xE8,    call_size        = 1,
    ret          = 0xC3,    ret_size         = 1,

    syscall      = 0x050F,  syscall_size     = 2,

    nop          = 0x90,    nop_size         = 1,

    push_small   = 0x6A,    push_small_size  = 1,
    push         = 0x68,    push_size        = 1,

    zero         = 0x00,    zero_size        = 1,

    jge_long     = 0x8D0F, jge_long_size    = 2,
    jg_long      = 0x8F0F,  jg_long_size    = 2,
    jl_long      = 0x8C0F,  jl_long_size    = 2,
    jle_long     = 0x8E0F, jle_long_size    = 2,


    ja           = 0x77,    ja_size          = 1,
    ja_long      = 0x870F,  ja_long_size     = 2,
    jae          = 0x73,    jae_size         = 1,
    jae_long     = 0x830F,  jae_long_size    = 2,
    jb           = 0x72,    jb_size          = 1,
    jb_long      = 0x820F,  jb_long_size     = 2,
    jbe          = 0x76,    jbe_size         = 1,
    jbe_long     = 0x860F,  jbe_long_size    = 1,
    je           = 0x74,    je_size          = 1,
    je_long      = 0x840F,  je_long_size     = 2,
    jne          = 0x75,    jne_size         = 1,
    jne_long     = 0x850F,  jne_long_size    = 2,
    jmp          = 0xEB,    jmp_size         = 1, // 0x80 ... 0x79
    jmp_long     = 0xE9,    jmp_long_size    = 1,
};


enum Code_Push_Pop
{
    push_rax     = 0x50,    push_rax_size    = 1,
    push_rbx     = 0x53,    push_rbx_size    = 1,
    push_rdx     = 0x52,    push_rdx_size    = 1,
    push_rbp     = 0x55,    push_rbp_size    = 1,
    push_rsi     = 0x56,    push_rsi_size    = 1,
    push_rdi     = 0x57,    push_rdi_size    = 1,
    push_r9      = 0x5141,  push_r9_size     = 2,
    push_r14     = 0x5641,  push_r14_size    = 2,

    pop_rax      = 0x58,    pop_rax_size     = 1,
    pop_rbx      = 0x5B,    pop_rbx_size     = 1,
    pop_rbp      = 0x5D,    pop_rbp_size     = 1,
    pop_r11      = 0x5B41,  pop_r11_size     = 2,
    pop_r14      = 0x5E41,  pop_r14_size     = 2,
};


enum Code_Reg
{
    mov_rax      = 0xB8,    mov_rax_size     = 1,
    mov_rbx      = 0xBB,    mov_rbx_size     = 1,
    mov_rdx      = 0x08BA,  mov_rdx_size     = 2,
    mov_rdi      = 0xBF,    mov_edi_size     = 1,

    add_rbp      = 0xC58348, add_rbp_size    = 3,

    add_rsp      = 0xC48348, add_rsp_size    = 3,
    sub_rsp      = 0xEC8348, sub_rsp_size    = 3,

    xor_rax_rax = 0xC03148, xor_rax_rax_size = 3,
    xor_rdi_rdi = 0xff3148, xor_rdi_rdi_size = 3,
};

enum Code_Reg_Reg
{
    mov_rax_lrbpl   = 0x458B48,     mov_rax_lrbpl_size = 3,
    movsx_rax_lrspl = 0x24046348, movsx_rax_lrspl_size = 4,
    mov_rbx_lrbpl   = 0x5D8B48,     mov_rbx_lrbpl_size = 3,

    mov_lrbpl_rax = 0x458948, mov_lrbpl_rax_size = 3,

    mov_rbp_rsp   = 0xE58948, mov_rbp_rsp_size   = 3,
    mov_rsi_rsp   = 0xE68948, mov_rsi_rsp_size   = 3,

    add_rax_rbx   = 0xD80148, add_rax_rbx_size   = 3,
    sub_rax_rbx   = 0xD82948, sub_rax_rbx_size   = 3,
    mul_rbx       = 0xE3F748, mul_rbx_size       = 3,
    div_rbx       = 0xF3F748, div_rbx_size       = 3,

    cmp_rax       = 0x8348,       cmp_rax_size   = 2,
    cmp_rax_rbx   = 0xD83948, cmp_rax_rbx_size   = 3,
};

enum Code_Math
{
    fninit       = 0xE3DB,        fninit_size = 2,
    fild_lrspl   = 0x2444DB,  fild_lrspl_size = 3,
    fidiv_lrspl  = 0x2434DA, fidiv_lrspl_size = 3,
    fimul_lrspl  = 0x240CDA, fimul_lrspl_size = 3,
    fist_lrspl   = 0x2414DB,  fist_lrspl_size = 3,

    fcom         = 0xD1D8,          fcom_size = 2,
    fnstsw_ax    = 0xE0DF,      fnstsw_ax_size = 2,
    sahf         = 0x9E,            sahf_size = 1,
};



#endif //LANGUAGE_LANG_BACK_END_H
