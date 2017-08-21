cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(data-structures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

# Add data structure subdirectories

add_subdirectory(abstracts)
add_subdirectory(composites)
add_subdirectory(graphs)
add_subdirectory(linear)
add_subdirectory(primitives)
add_subdirectory(trees)

# Done adding data structure subdirectories

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE
                                    abstracts
	                                  composites
	                                  graphs
	                                  linear
	                                  primitives
	                                  trees)
