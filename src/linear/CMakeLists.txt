cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(linear LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(LINEAR_SOURCES arrays/circular_buffer.cpp arrays/circular_buffer.h arrays/gap_buffer.cpp arrays/gap_buffer.h lists/linked_list.cpp lists/linked_list.h lists/abstract_list.cpp lists/abstract_list.h lists/doubly_linked_list.cpp lists/doubly_linked_list.h lists/xor_linked_list.cpp lists/xor_linked_list.h lists/self_organizing_list.cpp lists/self_organizing_list.h lists/skip_list.cpp lists/skip_list.h lists/unrolled_list.cpp lists/unrolled_list.h)

add_library(${PROJECT_NAME} ${LINEAR_SOURCES})
