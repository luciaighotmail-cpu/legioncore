cmake_minimum_required(VERSION 3.20)
project(legioncore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fail closed: treat warnings as errors in CI
option(LEGIONCORE_WERROR "Treat warnings as errors" ON)
if(LEGIONCORE_WERROR)
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_library(legioncore
  src/command.cpp
  src/authority.cpp
  src/state_machine.cpp
  src/interlock.cpp
  src/nonce.cpp
  src/digest.cpp
)

target_include_directories(legioncore
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

enable_testing()
add_subdirectory(tests)
