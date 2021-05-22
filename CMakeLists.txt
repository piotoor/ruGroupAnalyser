cmake_minimum_required(VERSION 3.10)
project(ruGroupAnalyser)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

option(GPROF_ENABLED "Enabled gprof profiling" OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

if(GPROF_ENABLED)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
include_directories(src)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)


configure_file(
    "${CMAKE_SOURCE_DIR}/scripts/parseCallgrind.sh"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}"
    COPYONLY
)

configure_file(
    "${CMAKE_SOURCE_DIR}/scripts/runWithCallgrind.sh"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}"
    COPYONLY
)


configure_file(
    "${CMAKE_SOURCE_DIR}/scripts/runWithMemcheck.sh"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}"
    COPYONLY
)
