cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(primitives LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(PRIMITIVES_SOURCES str_rope.cpp str_rope.h str_trie.cpp str_trie.h bigint.cpp bigint.h)

add_library(${PROJECT_NAME} ${PRIMITIVES_SOURCES})

