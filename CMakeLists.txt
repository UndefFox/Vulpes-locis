cmake_minimum_required(VERSION 3.24.1)

project(vulpeslocis)

# Global variable setup:
set(CMKAE_CXX_STANDART 17)
set(CMAKE_BUILD_PARALLEL_LEVEL 6)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Scripts:
include(cmakescripts/directoryLayoutSetup.txt)
include(cmakescripts/copyResources.txt)

add_subdirectory(src)

add_custom_target(Documentation ALL
    doxygen Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

