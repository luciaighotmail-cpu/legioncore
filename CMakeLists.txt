cmake_minimum_required(VERSION 3.20)
project(legioncore VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Fail closed: treat warnings as errors for our C++ code
option(LEGIONCORE_WERROR "Treat warnings as errors" ON)

# Official BLAKE3 1.8.7 portable + dispatch
set(BLAKE3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/blake3)
add_library(blake3_c STATIC
  ${BLAKE3_DIR}/blake3.c
  ${BLAKE3_DIR}/blake3_dispatch.c
  ${BLAKE3_DIR}/blake3_portable.c
)
target_include_directories(blake3_c PUBLIC ${BLAKE3_DIR})
target_compile_definitions(blake3_c PRIVATE
  BLAKE3_USE_NEON=0
  BLAKE3_NO_SSE2=1
  BLAKE3_NO_SSE41=1
  BLAKE3_NO_AVX2=1
  BLAKE3_NO_AVX512=1
)
# Third-party: do not treat its warnings as errors
target_compile_options(blake3_c PRIVATE -Wall -Wextra)

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
  PRIVATE
    ${BLAKE3_DIR}
)

if(LEGIONCORE_WERROR)
  target_compile_options(legioncore PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(legioncore PRIVATE blake3_c)

enable_testing()
add_subdirectory(tests)
