cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(test-driver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

# Set up Catch
set(CATCH_REPO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Catch)
set(CATCH_HEADER_DIR ${CATCH_REPO_DIR}/single_include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CATCH_REPO_DIR}/contrib)
include(ParseAndAddCatchTests)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_HEADER_DIR})
# Catch setup done


include_directories(../src)

set(TEST_SOURCES
        test.cpp tests/test_catch.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} data-structures Catch)

ParseAndAddCatchTests(${PROJECT_NAME})
