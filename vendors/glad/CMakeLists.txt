
cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)

project(glad VERSION 3.4.0 LANGUAGES C)

add_library(glad STATIC
    ${VENDOR_PATH}/glad/src/gl.c
)
target_include_directories(glad PUBLIC
    ${VENDOR_PATH}/glad/include/
)
set_property(
    TARGET glad
    PROPERTY POSITION_INDEPENDENT_CODE ON
)