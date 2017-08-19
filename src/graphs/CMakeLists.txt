cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(graphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(GRAPHS_SOURCES)

add_library(${PROJECT_NAME} ${GRAPHS_SOURCES})

