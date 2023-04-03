# Skelly libraries

## pch_target
set(PCH_FILE ${SKELLY_PATH}/pch.cpp)

if (PCH_ENABLED)
    message(STATUS "Compiling using pre-compiled header support")
    add_library(pch_target OBJECT ${SKELLY_PATH}/pch.cpp)
    target_include_directories(pch_target PUBLIC
        ${SKELLY_PATH}/
        ${VENDOR_PATH}/spdlog/include/
    )
    target_precompile_headers(pch_target PUBLIC ${SKELLY_PATH}/pch.h)
endif()


## pch_target

## skelly_dyn
add_library(skelly_dyn SHARED 
    ${SKELLY_PATH}/skelly.cpp
    ${SKELLY_PATH}/utils/logger/logger.cpp
)
target_include_directories(skelly_dyn PUBLIC
    ${SKELLY_PATH}/
    ${SKELLY_PATH}/utils/logger/
    ${SKELLY_PATH}/utils/eventHandler/
    ${VENDOR_PATH}/spdlog/include/
)
set_property(
    TARGET skelly_dyn
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
if(${PCH_ENABLED})
    target_compile_options(skelly_dyn PRIVATE "-include" "${PCH_FILE}")
endif()
## skelly_dyn