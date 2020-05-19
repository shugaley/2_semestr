cmake_minimum_required(VERSION 3.15)
project(hash_table)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set_source_files_properties(printf.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")

SET(GCC_COVERAGE_COMPILE_FLAGS "-O3")
SET(GCC_COVERAGE_LINK_FLAGS    "-no-pie")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(CMAKE_CXX_STANDARD 20)

add_executable(hash_table hash-table_main.cpp hash-table_header.h search.asm
        hash-table.cpp new_list_header.h new_list.cpp reader.cpp hash_funcs.cpp
         timer.h for_opt.cpp)
ADD_COMPILE_OPTIONS(-fsanitize=address)