# Compiler

This project is continuation of the project of my language from 1st semestr. I recommended to read about [my language](https://github.com/shugaley/1_semestr/tree/master/language "My own belarussian program language") before reading about the compiler of this language.

### Description

First of all I made simple elf file. There are headers struct of it:

```cpp
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
};
```

* [Back_End](https://github.com/shugaley/2_semestr/blob/master/compiler/lang_back_end.cpp) - translates language tree to real elf file ([example](https://github.com/shugaley/2_semestr/blob/master/compiler/elf.out)).

* [Class Buffer](https://github.com/shugaley/2_semestr/blob/master/compiler/lang_back_end_buffer.cpp) - my main tool for making back end.

### Standart Library

I made the analog of standard library for my language. There are a few elf files. They was compiled by nasm from my .s programs.

* [Printf](https://github.com/shugaley/2_semestr/blob/master/compiler/library/printf.out) - prints numbers with fixed precision (default is two decimal places). 

* [Printf_int](https://github.com/shugaley/2_semestr/blob/master/compiler/library/printf_int.out) - printf int numbers.

* [Scanf](https://github.com/shugaley/2_semestr/blob/master/compiler/library/scanf.out) - scanes numbers with fixed precision (default is two decimal places). 

* [Scanf_int](https://github.com/shugaley/2_semestr/blob/master/compiler/library/scanf_int.out) - scanes int numbers.

* [Square](https://github.com/shugaley/2_semestr/blob/master/compiler/library/sqrt.out) - count square root of numbers with fixed precision (default is two decimal places).  

## A Few Words About Compiler Optimization 

Ok. I did it. Compiler has been finished. This year of endless proga has been finished. 

I measured the average acceleration. lang_input_test.txt was used for this (there are calculations of 8! N-times).
There are results:

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/General1.png)

Not bad (acceleration is about 900).
But it became obvious that this can be done even faster after analyzing the resulting code in edb.

### Optimization

I made some optimizations. There are comparisons of first version and optimized version:

1)

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/1.png)
![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/1_opt.png)


2)

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/2.png)
![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/2_opt.png)

3)

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/3.png)
![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/3_opt.png)

### Final Results

I could speed up my code by about 10%. Not bad for a few hours of work.

There are final results:

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/General_final_final.png)
