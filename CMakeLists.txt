cmake_minimum_required(VERSION 3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.16)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RESkelly
            VERSION 0.1
            DESCRIPTION "Rendering Engine Skelly - Modular and barebones solution for modern visual applications."
            LANGUAGES CXX
)

## project options
# verbose
set(CMAKE_VERBOSE_MAKEFILE OFF)
# compile benchmarks
set(BENCHMARK_ENABLED OFF)
# pch
set(PCH_ENABLED OFF)

## global properties
if (${BENCHMARK_ENABLED})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
endif()
if (${PCH_ENABLED})
    add_compile_definitions(PCH_ENABLED)
endif()

## global pathing variables
set(ENV{ROOT_PATH} $ENV{PWD})
set(ENV{OUTPUT_PATH} ${CMAKE_CURRENT_BINARY_DIR})
set(VENDOR_PATH $ENV{PWD}/vendors)
set(SKELLY_PATH $ENV{ROOT_PATH}/skelly)
set(PCH_FILE "${OUTPUT_PATH}/pch.h.ghc")
set(pch_file "${SKELLY_PATH}/pch.h")

message(STATUS "Importing Skelly libraries")
include($ENV{ROOT_PATH}/skelly/CMakeLists.txt OPTIONAL RESULT_VARIABLE SKELLY_INCLUDED)

# Reads available projects
file(STRINGS project.list PROJECT_LIST)

# For each project, create structures using the project-specific CMakeLists file
while(PROJECT_LIST)
    list(POP_FRONT PROJECT_LIST PROJECT)
    add_subdirectory(${PROJECT})
endwhile()