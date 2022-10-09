cmake_minimum_required(VERSION 3.15)
project(crimson)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(crimson main.cc)
llvm_map_components_to_libnames(llvm_libs core orcjit native)
target_link_libraries(crimson ${LLVM_LIBS})
