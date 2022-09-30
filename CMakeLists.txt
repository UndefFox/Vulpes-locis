cmake_minimum_required(VERSION 3.24.1)

project(vulpeslocis)

set(CMKAE_CXX_STANDART 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(./src)

add_subdirectory(src)

add_custom_target(documentation ALL doxygen Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
