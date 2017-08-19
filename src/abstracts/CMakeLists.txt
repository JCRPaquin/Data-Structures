cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(abstracts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(ABSTRACTS_SOURCES)

add_library(${PROJECT_NAME} ${ABSTRACTS_SOURCES})

