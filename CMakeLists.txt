cmake_minimum_required(VERSION 3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.16)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RESkelly
            VERSION 0.1
            DESCRIPTION "Rendering Engine Skelly - Modular and barebones solution for modern visual applications."
            LANGUAGES CXX
)

## global pathing variables
set(ROOT_PATH $ENV{PWD})
set(CONFIG_PATH ${ROOT_PATH}/config)
set(VENDOR_PATH ${ROOT_PATH}/vendors)
set(SKELLY_PATH ${ROOT_PATH}/skelly)
set(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(PCH_FILE ${SKELLY_PATH}/pch.h)

## include project options
message(STATUS "Importing project configurations")
include(${ROOT_PATH}/config/project.config)

## global properties
if (${BENCHMARK_ENABLED})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
endif()
if (${PCH_ENABLED})
    add_compile_definitions(PCH_ENABLED)
endif()

message(STATUS "Importing Skelly libraries")
include(${ROOT_PATH}/skelly/CMakeLists.txt)

# Reads available projects
file(STRINGS config/project.list PROJECT_LIST)

# For each project, create structures using the project-specific CMakeLists file
while(PROJECT_LIST)
    list(POP_FRONT PROJECT_LIST PROJECT)
    add_subdirectory(${PROJECT})
endwhile()