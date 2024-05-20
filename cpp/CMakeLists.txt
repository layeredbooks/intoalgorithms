cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(k)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-I/opt/homebrew/opt/llvm/include)
add_compile_options(-Wall -Wextra -Wshadow)

add_link_options(-L/opt/homebrew/opt/llvm/lib)
add_link_options(-L/opt/homebrew/opt/llvm/lib/c++ -Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message("Debug mode")
    add_compile_options(-g -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    message("Release mode")
    add_compile_options(-g -O2)
endif()

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_subdirectory(graph)