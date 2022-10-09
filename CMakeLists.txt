cmake_minimum_required(VERSION 3.16)
project(crimson)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

list(APPEND CRIMSON_CORE lexer.cc compiler.cc)

option(BUILD_TEST "build test modules" ON)

find_package(LLVM REQUIRED)

if (BUILD_TEST)
  find_package(GTest REQUIRED)
  find_package(Threads REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
endif()

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(crimson main.cc ${CRIMSON_CORE})
llvm_map_components_to_libnames(llvm_libs core orcjit native)
target_link_libraries(crimson ${LLVM_LIBS})

if (BUILD_TEST)
  add_executable(diff_test tests/diff_test.cc ${CRIMSON_CORE})
  target_link_libraries(diff_test ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(diff_test ${CMAKE_THREAD_LIBS_INIT})
endif()
