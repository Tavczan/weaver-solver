cmake_minimum_required(VERSION 3.18.0)

project(weaver-solver C)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(main main.c ${SRC_FILES})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-Wall)