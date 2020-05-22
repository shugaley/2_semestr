cmake_minimum_required(VERSION 3.9)

project(TEST)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set_source_files_properties(printf.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")

SET(GCC_COVERAGE_LINK_FLAGS    "-no-pie")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(CMAKE_CXX_STANDARD 20)

add_executable(printf
        printf.asm
        test.cpp)

