cmake_minimum_required(VERSION 2.6)

project(5lab)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(SOURCE1_EXE src/kmp.cpp)
set(SOURCE2_EXE src/shift.cpp)
set(SOURCE_LIB src/kmp_functions.cpp)

add_library(kmp_func STATIC ${SOURCE_LIB})

add_executable(kmp ${SOURCE1_EXE})
target_link_libraries(kmp kmp_func)
add_executable(shift ${SOURCE2_EXE})
target_link_libraries(shift kmp_func)

add_subdirectory(test)