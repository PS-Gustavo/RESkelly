# Skelly libraries
add_library(
    skelly_dyn SHARED 
        ${SKELLY_PATH}/skelly.cpp
        ${SKELLY_PATH}/skelly.h
        ${SKELLY_PATH}/utils/logger/logger.cpp
        ${SKELLY_PATH}/utils/logger/logger.h
)
target_include_directories(
    skelly_dyn PUBLIC
        ${SKELLY_PATH}/
        ${SKELLY_PATH}/utils/logger/
        ${VENDOR_PATH}/spdlog/include/
)
set_property(
    TARGET skelly_dyn 
    PROPERTY POSITION_INDEPENDENT_CODE ON
)

add_library(
    _s_logger STATIC
        ${SKELLY_PATH}/utils/logger/logger.cpp
        ${SKELLY_PATH}/utils/logger/logger.h
)
target_include_directories(
    _s_logger PUBLIC
        ${SKELLY_PATH}/
        ${SKELLY_PATH}/utils/logger/
        ${VENDOR_PATH}/spdlog/include
)