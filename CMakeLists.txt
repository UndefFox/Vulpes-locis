cmake_minimum_required(VERSION 3.24.1)

project(vulpeslocis)

set(CMKAE_CXX_STANDART 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BUILD_PARALLEL_LEVEL 6)

set(PROJECT_NAME vulpeslocis)
set(SHADERS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/shaders)

include_directories(./include)

add_subdirectory(src)
add_subdirectory(shaders)

add_custom_target(Documentation ALL
    doxygen Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
