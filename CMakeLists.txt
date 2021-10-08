cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

option(BUILD_TEST "Build the unit tests" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

project(ruGroupAnalyser)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
include_directories(src)
include_directories(lib/arg-parser/include)
add_subdirectory(src)

if(BUILD_TEST)
    add_subdirectory(tst)
    add_subdirectory(lib/googletest)
    include_directories(lib/googletest/googletest/include)
endif()

set(CMAKE_EXE_LINKER_FLAGS " -static")


if(NOT CMAKE_WIN32_COMPILATION AND NOT CMAKE_WIN64_COMPILATION)
    if(CMAKE_BUILD_TYPE STREQUAL Debug AND BUILD_TEST)
        set(
            MEMCHECK_SCRIPTS
            runWithMemcheck.sh
        )

        file(
            MAKE_DIRECTORY
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/tmp"
        )

        foreach( file_i ${MEMCHECK_SCRIPTS})
            configure_file(
                "${CMAKE_SOURCE_DIR}/scripts/${file_i}"
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/tmp/${file_i}"
                COPYONLY
            )

            file(
                COPY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/tmp/${file_i}"
                DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}"
                FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
            )
        endforeach()

        file(
            REMOVE_RECURSE
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/tmp"
        )

    elseif(CMAKE_BUILD_TYPE STREQUAL Release AND BUILD_TEST)
        set(
            CALLGRIND_SCRIPTS
            parseCallgrind.sh
            runWithCallgrind.sh
        )

        file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/tmp")

        foreach( file_i ${CALLGRIND_SCRIPTS})
            configure_file(
                "${CMAKE_SOURCE_DIR}/scripts/${file_i}"
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/tmp/${file_i}"
                COPYONLY
            )

            file(
                COPY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/tmp/${file_i}"
                DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}"
                FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
            )
        endforeach()

        file(
            REMOVE_RECURSE
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/tmp"
        )

    endif()
endif()
