cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.1)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RESkelly
            VERSION 0.1
            DESCRIPTION "Rendering Engine Skelly - Modular and barebones solution for modern visual applications."
            LANGUAGES CXX
)

# Skelly libraries
add_library(
    skelly_dyn SHARED 
        skelly/skelly.cpp
        skelly/skelly.h
        skelly/utils/logger/logger.cpp
        skelly/utils/logger/logger.h
)
target_include_directories(
    skelly_dyn PUBLIC
        skelly/
        skelly/utils/logger/
        vendors/spdlog/include/
)
set_property(
    TARGET skelly_dyn 
    PROPERTY POSITION_INDEPENDENT_CODE ON
)

add_library(
    _s_logger STATIC
        skelly/utils/logger/logger.cpp
        skelly/utils/logger/logger.h
)
target_include_directories(
    _s_logger PUBLIC
        skelly/
        skelly/utils/logger/
        vendors/spdlog/include
)

# Reads available projects
file(STRINGS project.list PROJECT_LIST)

# For each project, create structures using the project-specific CMakeLists file
while(PROJECT_LIST)
    list(POP_FRONT PROJECT_LIST PROJECT)
    include(${PROJECT}/CMakeLists.txt)
endwhile()