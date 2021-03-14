cmake_minimum_required(VERSION 2.8.8)
project(ptrtrack)

set(LLVM_DIR "/home/yph/Programming/llvm-project/build-debug/lib/cmake/llvm")
find_package(LLVM)


if( NOT LLVM_FOUND )
  message(FATAL_ERROR "LLVM package can't be found")
else()
  message(STATUS ${LLVM_DIR})
  message(STATUS ${LLVM_INCLUDE_DIRS})
endif()
# include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti")

add_subdirectory(ptrtrack)