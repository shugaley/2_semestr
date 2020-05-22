cmake_minimum_required(VERSION 3.15)
project(language)

set(CMAKE_CXX_STANDARD 20)

add_executable(compiler
        lang_header.h lang_commands.h lang_main.cpp lang.cpp
        tree_header.h tree.cpp tree_dot.cpp
        lang_reader.cpp lang_tokenization.cpp
        lang_front_end.cpp lang_middle_end.cpp lang_back_end0.cpp lang_front_end_back.cpp
        lang_which_is.cpp
        lang_back_end.h lang_back_end.cpp lang_back_end_buffer.cpp
        )