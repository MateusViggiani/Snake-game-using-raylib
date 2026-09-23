cmake_minimum_required(VERSION 3.20)

if(NOT CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER clang++)
endif()

project(Jogo LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include(FetchContent)

find_package(raylib QUIET)
if(NOT raylib_FOUND)
  message(STATUS "raylib nao encontrada no sistema, baixando...")
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(raylib)
else()
  message(STATUS "usando raylib do sistema")
endif()

find_package(GTest QUIET)
if(NOT GTest_FOUND)
  message(STATUS "GoogleTest nao encontrado no sistema, baixando...")
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(googletest)
else()
  message(STATUS "usando GoogleTest do sistema")
endif()

add_executable(jogo main.cpp)
target_link_libraries(jogo PRIVATE raylib)

enable_testing()
add_executable(testes teste.cpp)
target_link_libraries(testes PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(testes)

option(ENABLE_SANITIZERS "AddressSanitizer + UBSan" OFF)
if(ENABLE_SANITIZERS)
  foreach(alvo jogo testes)
    target_compile_options(${alvo} PRIVATE -fsanitize=address,undefined -g)
    target_link_options(${alvo} PRIVATE -fsanitize=address,undefined)
  endforeach()
endif()
