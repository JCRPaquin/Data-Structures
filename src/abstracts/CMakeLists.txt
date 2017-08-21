cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(abstracts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(ABSTRACTS_SOURCES
        map/abstract_map.cpp map/abstract_map.h map/associative_map.cpp map/associative_map.h map/tree_map.cpp
        map/tree_map.h map/hash_map.cpp map/hash_map.h set/abstract_set.cpp set/abstract_set.h set/hash_set.cpp
        set/hash_set.h set/tree_set.cpp set/tree_set.h set/multi_set.cpp set/multi_set.h map/multi_map.cpp
        map/multi_map.h stack.cpp stack.h queue/abstract_queue.cpp queue/abstract_queue.h queue/double_queue.cpp
        queue/double_queue.h queue/priority_queue.cpp queue/priority_queue.h queue/queue.cpp queue/queue.h
        set/disjoint_set.cpp set/disjoint_set.h)

add_library(${PROJECT_NAME} ${ABSTRACTS_SOURCES})

