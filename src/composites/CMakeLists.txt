cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(composites LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(COMPOSITES_SOURCES tagged_union.cpp tagged_union.h)

add_library(${PROJECT_NAME} ${COMPOSITES_SOURCES})
