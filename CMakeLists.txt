cmake_minimum_required(VERSION 3.0)

project(
  traitor
  DESCRIPTION
    "experiments with c++ template metaprogramming"
  LANGUAGES
    C
    CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build")

if (CMAKE_BUILD_TYPE STREQUAL "")
  message(STATUS "No build type was specified using -DCMAKE_BUILD_TYPE=[DEBUG|RELEASE]. Defaulting to Release build")
  set(CMAKE_BUILD_TYPE "DEBUG")
endif()

# Debug build compile flags
#   - remove "-fsanitize=address,undefined" if you do not have [ASan](https://github.com/google/sanitizers/wiki/AddressSanitizer) installed
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -DDEBUG_MODE -D_GLIBCXX_DEBUG -fsanitize=address,undefined -ftemplate-depth=100000000  -fconstexpr-depth=100000000 -fconstexpr-ops-limit=100000000")

# Release build compile flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -ftemplate-depth=100000000 -fconstexpr-depth=100000000 -fconstexpr-ops-limit=100000000")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CXX Flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

add_subdirectory(./bubble-sort)
add_subdirectory(./factorial)
add_subdirectory(./fibonacci)
add_subdirectory(./for)
add_subdirectory(./gcd)
add_subdirectory(./insertion-sort)
add_subdirectory(./odd-template-params)
add_subdirectory(./selection-sort)
