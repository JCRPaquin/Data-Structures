cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(graphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(GRAPHS_SOURCES directed_graph.cpp directed_graph.h adj_list_graph.cpp adj_list_graph.h adj_matrix_graph.cpp adj_matrix_graph.h incidence_graph.cpp incidence_graph.h)

add_library(${PROJECT_NAME} ${GRAPHS_SOURCES})

