# Skelly libraries

## pch
if (PCH_ENABLED)
    message(STATUS "Compiling using pre-compiled header support")    
    add_library(pch_shared STATIC ${PCH_FILE})
    target_include_directories(pch_shared PUBLIC
        ${SKELLY_PATH}/
        ${VENDOR_PATH}/spdlog/include/
    )
    set_property(
        TARGET pch_shared
        PROPERTY POSITION_INDEPENDENT_CODE ON
    )
    target_precompile_headers(pch_shared PUBLIC ${SKELLY_PATH}/pch.h)
    
    add_library(pch_static STATIC ${PCH_FILE})
    target_include_directories(pch_static PUBLIC
        ${SKELLY_PATH}/
        ${VENDOR_PATH}/spdlog/include/
    )
    target_precompile_headers(pch_static PUBLIC ${SKELLY_PATH}/pch.h)
endif()
## pch

## logger
add_library(skelly_logger STATIC
    ${SKELLY_PATH}/utils/logger/logger.cpp
)
target_include_directories(skelly_logger PUBLIC
    ${SKELLY_PATH}/utils/logger/
)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_logger REUSE_FROM pch_shared)
endif()
set_property(
    TARGET skelly_logger
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
## logger

## window
add_library(skelly_window STATIC
    ${SKELLY_PATH}/utils/window/window.cpp
)
target_include_directories(skelly_window PUBLIC
    ${SKELLY_PATH}/utils/window/
    ${SKELLY_PATH}/utils/eventHandler/
)
target_link_libraries(skelly_window PUBLIC skelly_logger glfw)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_window REUSE_FROM pch_shared)
endif()
set_property(
    TARGET skelly_window
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
## window

##spdlog
##spdlog

##glfw
##glfw

## skelly_dyn
add_library(skelly_dyn SHARED 
    ${SKELLY_PATH}/skelly.cpp
)
target_include_directories(skelly_dyn PUBLIC
    ${SKELLY_PATH}/
)
target_link_libraries(skelly_dyn PUBLIC skelly_window)
set_property(
    TARGET skelly_dyn
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_dyn REUSE_FROM pch_shared)
endif()
## skelly_dyn