
#include "lang_back_end.h"

#define AssertBuffer() AssertBuffer()

//MAIN------------------------------------------------------------------------------------------------

Buffer_t::Buffer_t() :
    maxsize_(BEGIN_MAXSIZE),
    buffer_ ( (char*)calloc(maxsize_, sizeof(buffer_[0])) ),
    pc_     (buffer_),
    mark_   ( (Mark_t*)calloc(MAX_AMOUNT_CALL * MAX_AMOUNT_FUNCS, sizeof(Mark_t)) ),
    i_mark_ (0),
    library_( (Library_t*)calloc(SIZE_LIBRARY, sizeof(Library_t)) )
{
    AssertBuffer();
}

Buffer_t::~Buffer_t()
{
    free(library_);
    i_mark_ = 0;
    pc_ = nullptr;
    free(buffer_);
    maxsize_ = 0;
}


bool Buffer_t::AssertBuffer()
{
    assert(maxsize_);
    assert(buffer_);
    assert(pc_);
    assert(mark_);
    assert(library_);

    return true;
}


//INC----------------------------------------------------------------------------------------------------

bool Buffer_t::CheckMaxsize()
{
    AssertBuffer();

    if(pc_ - buffer_ >= maxsize_ - 10)
    {
        IncreaseMaxsize();
        return true;
    }
    else
        return false;
}


void Buffer_t::IncreaseMaxsize()
{
    AssertBuffer();

    auto  tmp_mark_  = (size_t*)calloc(i_mark_, sizeof(size_t));
    for(size_t ii_mark = 0; ii_mark < i_mark_; ii_mark++)
    {
        tmp_mark_[ii_mark] = mark_[ii_mark].mark - buffer_;
    }

    size_t size = pc_ - buffer_;
    auto tmp_buffer = (char*)calloc(size, sizeof(char));
    CopyBuffer(tmp_buffer, buffer_, size);

    buffer_ = (char*)realloc(buffer_, 2 * maxsize_);
    maxsize_ *= 2;

    CopyBuffer(buffer_, tmp_buffer, size);
    pc_ = buffer_ + size;

    for(size_t ii_mark = 0; ii_mark < i_mark_; ii_mark++)
    {
        mark_[ii_mark].mark = buffer_ + tmp_mark_[ii_mark];
    }

    free(tmp_buffer);
    free(tmp_mark_);

    AssertBuffer();
    return;
}


void Buffer_t::IncSize(size_t size)
{
    AssertBuffer();
    pc_ += size;
}

//PRINT-----------------------------------------------------------------------------------------------


void Buffer_t::PrintHexCommand(size_t command, size_t size_command)
{
    AssertBuffer();
    CheckMaxsize();

    for(size_t i_pos = 0; i_pos < size_command; i_pos++)
    {
        size_t copy_command = command;
        copy_command = copy_command >> 8 * i_pos;;
        pc_[i_pos] = copy_command;
    }

    pc_ += size_command;

    CheckMaxsize();
    AssertBuffer();
}


void Buffer_t::PrintHexNumber(size_t number)
{
    AssertBuffer();
    CheckMaxsize();

    PrintHexCommand(number, SIZE_NUMBER);

    CheckMaxsize();
    AssertBuffer();
}

void Buffer_t::PrintHexNumberi(size_t number, size_t i_byte)
{
    AssertBuffer();
    CheckMaxsize();

    size_t tmp_size = GetSize();
    pc_ = GetBuffer() + i_byte;

    PrintHexNumber(number);

    pc_ = GetBuffer() + tmp_size;

    CheckMaxsize();
    AssertBuffer();
}


void Buffer_t::PrintHexSmallNumber(size_t number)
{
    AssertBuffer();
    CheckMaxsize();

    PrintHexCommand(number, SIZE_SMALL_NUMBER);

    CheckMaxsize();
    AssertBuffer();
}

//MARK------------------------------------------------------------------------------------------------------

void Buffer_t::SaveHexMark(size_t* offset)
{
    AssertBuffer();
    CheckMaxsize();

    mark_[i_mark_].offset = offset;
    mark_[i_mark_].mark   = pc_;
    pc_ += SIZE_ADDRESS;
    i_mark_++;

    CheckMaxsize();
    AssertBuffer();
}

void Buffer_t::PrintHexMark(size_t ii_mark)
{
    AssertBuffer();
    //fprintf(stderr, "%d", *mark_[ii_mark].offset);

    for(size_t i_pos = 0; i_pos < SIZE_ADDRESS; i_pos++)
    {
        size_t copy_mark = *mark_[ii_mark].offset;
        copy_mark = copy_mark >> 8 * i_pos;
        mark_[ii_mark].mark[i_pos] = copy_mark;
    }
    AssertBuffer();
}

//Library-------------------------------------------------------------------------------------------------------


void Buffer_t::SetLibName(size_t num_func, char* name)
{
    AssertBuffer();

    library_[num_func].name = strdup(name);

    AssertBuffer();
}


void Buffer_t::SetLibSize(size_t num_func, size_t size)
{
    AssertBuffer();

    library_[num_func].size_code = size;

    AssertBuffer();
}


void Buffer_t::SetLibByteCode(size_t num_func, FILE* elf_func)
{
    AssertBuffer();
    assert(elf_func);

    size_t size = library_[num_func].size_code;
    library_[num_func].byte_code = (char*)calloc(size, sizeof(char));

    for(size_t i_byte = 0; i_byte < size; i_byte++)
    {
        fscanf(elf_func, "%c", &library_[num_func].byte_code[i_byte]);
    }

    for(size_t i_byte = 0; i_byte < size; i_byte++)
    {
        fprintf(stderr, "%c", library_[num_func].byte_code[i_byte]);
    }

    assert(elf_func);
    AssertBuffer();

    return;
}


//Getters--------------------------------------------------------------------------------------------------------

char* Buffer_t::GetBuffer()
{
    AssertBuffer();
    return buffer_;
}


char Buffer_t::GetBufferi(size_t i)
{
    AssertBuffer();
    return buffer_[i];
}

char* Buffer_t::GetLibName (size_t num_func)
{
    AssertBuffer();
    return library_[num_func].name;
}


size_t Buffer_t::GetSize()
{
    AssertBuffer();
    return (pc_ - buffer_);
}


size_t Buffer_t::GetIMark()
{
    AssertBuffer();
    return i_mark_;
}

char*  Buffer_t::GetLibrary(size_t i)
{
    AssertBuffer();
    return library_[i].byte_code;
}


char Buffer_t::GetLibCodei(size_t num_func, size_t i)
{
    AssertBuffer();
    return library_[num_func].byte_code[i];
}

size_t Buffer_t::GetLibSize(size_t num_func)
{
    AssertBuffer();
    return library_[num_func].size_code;
}

#undef AssertBuffer();

//SERVICE------------------------------------------------------------------------------------------------------

inline char* CopyBuffer(char* buf_to, char* buf_from, size_t size)
{
    assert(buf_to);
    assert(buf_from);

    for(size_t i_char = 0; i_char < size; i_char++)
        buf_to[i_char] = buf_from[i_char];

    return buf_to;

}


//MAIN CLASS---------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

BackEnd_t::BackEnd_t(const Buffer_t& buffer) :
    buffer_(buffer),
    func_   ( (Func_t*)calloc(MAX_AMOUNT_FUNCS, sizeof(Func_t)) ),
    iFunc_  (SIZE_LIBRARY + 1),
    varFunc_(nullptr)
{
    return;
}

BackEnd_t::~BackEnd_t()
{
    varFunc_ = nullptr;
    iFunc_   = 0;
    //free(func_);
}


/*Buffer_t BackEnd_t::GetBuffer ()
{
    return buffer_;
}


Func_t* BackEnd_t::GetFunc ()
{
    return func_;
}


size_t BackEnd_t::GetIFunc()
{
    return iFunc_;
}

Var_t* BackEnd_t::GetVarFunc()
{
    return varFunc_;
}*/




