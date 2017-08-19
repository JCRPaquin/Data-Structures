cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(trees LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(TREES_SOURCES)

add_library(${PROJECT_NAME} ${TREES_SOURCES})

