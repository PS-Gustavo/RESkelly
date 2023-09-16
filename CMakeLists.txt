cmake_minimum_required(VERSION 3.25.2)

if(${CMAKE_VERSION} VERSION_LESS 3.25.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RESkelly
            VERSION 0.1
            DESCRIPTION "Rendering Engine Skelly - Modular and barebones solution for modern visual applications."
            LANGUAGES CXX
)
set(ROOT_PATH $ENV{PWD})

## include project options
include(${ROOT_PATH}/cmake/config.cmake)

## include variables
include($ENV{PWD}/cmake/vars.cmake)

## vendor project options
# OpenGL suite
if (${TARGET_OPENGL})
    message(STATUS "Using OpenGL as rendering API.")    
    # glfw
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    add_subdirectory(${VENDOR_PATH}/glfw/)
    # glm
    add_subdirectory(${VENDOR_PATH}/glm/)
    # glad
    add_subdirectory(${VENDOR_PATH}/glad/)
    # OpenGL
    find_package(OpenGL REQUIRED)
    add_compile_definitions(TARGET_OPENGL)
endif()

## set global compiler options
add_compile_options(${compiler_options})

## global properties
# Platform configurations
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "${CMAKE_SYSTEM_NAME} system detected, applying platform specific configs.")
    add_compile_definitions(PLATFORM_LINUX)
endif()
# Project run mode configurations
if (${DEBUG_ENABLED})
    message(STATUS "CONFIG: Debug mode enabled.")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_definitions(ENABLE_ASSERTS)
    add_compile_definitions(DEBUG_ENABLED)
endif()
# Compile options
if (${BENCHMARK_ENABLED})
    message(STATUS "CONFIG: Compiler benchmark mode active.")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
endif()
if (${TEST_ENABLED})
    message(STATUS "CONFIG: Functional tests enabled.")
    add_compile_definitions(TEST_ENABLED)
endif()
if (${PCH_ENABLED})
    message(STATUS "CONFIG: PCH enabled.")
    add_compile_definitions(PCH_ENABLED)
endif()

message(STATUS "Importing Skelly libraries")
include(${ROOT_PATH}/skelly/CMakeLists.txt)

# Read available projects
file(STRINGS config/project.list PROJECT_LIST)

# For each project, create structures using the project-specific CMakeLists file
while(PROJECT_LIST)
    list(POP_FRONT PROJECT_LIST PROJECT)
    add_subdirectory(${PROJECT})
endwhile()