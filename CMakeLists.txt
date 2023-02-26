cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.1)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Skelly 
            VERSION 0.1
            DESCRIPTION "Rendering Engine Skelly - Modular and barebones solution for modern visual applications."
            LANGUAGES CXX
)

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
        skelly/vendors/spdlog/include/
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
        skelly/vendors/spdlog/include
)

add_library(
    _b_dlapi STATIC
        body/utils/dlapi/dlapi.cpp
        body/utils/dlapi/dlapi.h
)
target_include_directories(
    _b_dlapi PUBLIC
        body/utils/dlapi/
)

add_library(
    _b_skellyloader STATIC
        body/utils/skellyloader/skellyloader.cpp
        body/utils/skellyloader/skellyloader.h
)
target_include_directories(
    _b_skellyloader PUBLIC
        skelly/
        skelly/utils/logger/
        skelly/vendors/spdlog/include/
        body/utils/dlapi/
        body/utils/skellyloader/
)

add_executable(initial body/body.cpp body/body.h)
target_include_directories(
    initial PUBLIC
        body/
)

target_link_libraries(
    initial PUBLIC skelly_dyn _s_logger _b_dlapi _b_skellyloader
)