cmake_minimum_required(VERSION 3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.16)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RESkelly
            VERSION 0.1
            DESCRIPTION "Rendering Engine Skelly - Modular and barebones solution for modern visual applications."
            LANGUAGES CXX
)

## Pathing variables
# global folders
set(ROOT_PATH $ENV{PWD})
set(CONFIG_PATH ${ROOT_PATH}/config)
set(VENDOR_PATH ${ROOT_PATH}/vendors)
set(SKELLY_PATH ${ROOT_PATH}/skelly)
set(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
# pch pathing file
set(PCH_FILE ${SKELLY_PATH}/pch.cpp)

## include project options
message(STATUS "Importing project configurations")
include(${ROOT_PATH}/config/project.config)

## vendor project options
# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${VENDOR_PATH}/glfw/)
# glad
add_subdirectory(${VENDOR_PATH}/glad/)


## global properties
# Platform configurations
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "${CMAKE_SYSTEM_NAME} system detected, applying platform specific configs.")
    add_compile_definitions(PLATFORM_LINUX)
endif()
# Project run mode configurations
if (${DEBUG_ENABLED})
    message(STATUS "CONFIG: Debug mode enabled.")
    add_compile_definitions(ENABLE_ASSERTS)
endif()
# Compile options
if (${BENCHMARK_ENABLED})
    message(STATUS "CONFIG: Compiler benchmark mode active.")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
endif()
if (${PCH_ENABLED})
    message(STATUS "CONFIG: PCH enabled.")
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