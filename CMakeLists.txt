# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.7.2)

# 项目信息
project(ALGORITHM_COLLECTION)

# include路径
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/review_algorithms)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

# 生成debug版本
SET(CMAKE_BUILD_TYPE "Debug")
# 生成release版本
# SET(CMAKE_BUILD_TYPE "release")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
endif ()

SET(CMAKE_MAKE_PROGRAMC "/usr/bin/make")
SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")

add_subdirectory(review_algorithms)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE srcs LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(srcfile IN LISTS srcs)
    # Get file name without directory
    get_filename_component(mainname ${srcfile} NAME_WE)
    message("srcfile: ${srcfile}  exename: ${mainname}")
    add_executable(${mainname} ${srcfile})
endforeach()

target_link_libraries(test_sort PUBLIC ReviewAlgs)
target_link_libraries(test_str_search PUBLIC ReviewAlgs)
target_link_libraries(test_segment_tree PUBLIC ReviewAlgs)