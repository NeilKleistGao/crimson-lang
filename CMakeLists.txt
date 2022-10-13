cmake_minimum_required(VERSION 3.16)
project(crimson)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

list(APPEND CRIMSON_CORE lexer.cc compiler.cc)

option(BUILD_TEST "build test modules" ON)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

if (BUILD_TEST)
  find_package(GTest REQUIRED)
  find_package(Threads REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
endif()

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(LLVM_LIBS core support)

SET(CLANG_LIBRARIES
        clang
        clangFrontend
        clangDriver
        clangSerialization
        clangParse
        clangSema
        clangAnalysis
        clangEdit
        clangAST
        clangLex
        clangBasic)

set(LLVM_ENABLE_RTTI OFF)
set(LLVM_ENABLE_EH OFF)

add_executable(crimson main.cc ${CRIMSON_CORE})
target_link_libraries(crimson ${LLVM_LIBS} ${CLANG_LIBRARIES})

if (BUILD_TEST)
  add_executable(diff_test tests/diff_test.cc ${CRIMSON_CORE})
  target_link_libraries(diff_test ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(diff_test ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(diff_test ${LLVM_LIBS} ${CLANG_LIBRARIES})
endif()
