cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(linear LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(LINEAR_SOURCES)

add_library(${PROJECT_NAME} ${LINEAR_SOURCES})
