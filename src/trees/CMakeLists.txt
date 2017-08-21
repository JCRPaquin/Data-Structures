cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(trees LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(TREES_SOURCES abstract_tree.cpp abstract_tree.h aa_tree.cpp aa_tree.h avl_tree.cpp avl_tree.h red_black_tree.cpp red_black_tree.h splay_tree.cpp splay_tree.h binary_search_tree.cpp binary_search_tree.h treap.cpp treap.h randomized_binary_search_tree.cpp randomized_binary_search_tree.h quad_tree.cpp quad_tree.h range_tree.cpp range_tree.h)

add_library(${PROJECT_NAME} ${TREES_SOURCES})

