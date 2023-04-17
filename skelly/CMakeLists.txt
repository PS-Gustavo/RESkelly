# Skelly libraries

## pch
if (PCH_ENABLED)
    message(STATUS "Compiling using pre-compiled header support")    
    add_library(pch_shared STATIC ${PCH_FILE})
    set(pch_libs 
        ${SKELLY_PATH}/
        ${SKELLY_PATH}/utils/eventHandler/
        ${SKELLY_PATH}/utils/layer/
        ${VENDOR_PATH}/spdlog/include/
    )
    target_include_directories(pch_shared PUBLIC ${pch_libs})
    set_property(
        TARGET pch_shared
        PROPERTY POSITION_INDEPENDENT_CODE ON
    )
    target_precompile_headers(pch_shared PUBLIC ${SKELLY_PATH}/pch.h)
    
    add_library(pch_static STATIC ${PCH_FILE})
    target_include_directories(pch_static PUBLIC ${pch_libs})
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
set_property(
    TARGET skelly_logger
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_logger REUSE_FROM pch_shared)
else()
    target_include_directories(skelly_logger PUBLIC
        ${SKELLY_PATH}/
        ${VENDOR_PATH}/spdlog/include/
    )
endif()
## logger

## window
add_library(skelly_window STATIC
    ${SKELLY_PATH}/utils/window/window.cpp
)
target_include_directories(skelly_window PUBLIC
    ${SKELLY_PATH}/utils/window/
    ${SKELLY_PATH}/utils/eventHandler/
)
target_link_libraries(skelly_window PUBLIC skelly_logger glfw glad)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_window REUSE_FROM pch_shared)
endif()
set_property(
    TARGET skelly_window
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
## window

##layers
add_library(skelly_layer STATIC
    ${SKELLY_PATH}/utils/layer/layer.cpp
    ${SKELLY_PATH}/utils/layer/layerStack.cpp
)
set(skelly_layer_libs ${SKELLY_PATH}/utils/layer/)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_layer REUSE_FROM pch_shared)
else()
    set(skelly_layer_libs ${skelly_layer_libs} ${SKELLY_PATH}/ ${SKELLY_PATH}/utils/eventHandler/)
endif()
target_include_directories(skelly_layer PUBLIC ${skelly_layer_libs})
set_property(
    TARGET skelly_layer
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
##layers

##render
add_library(skelly_render STATIC
    ${SKELLY_PATH}/utils/render/render.cpp
)
set(skelly_render_libs 
    ${SKELLY_PATH}/utils/render/
    ${VENDOR_PATH}/imguiCM/imgui/
    )
if(${PCH_ENABLED})
    target_precompile_headers(skelly_render REUSE_FROM pch_shared)
else()
    set(skelly_render_libs ${skelly_layer_libs} ${SKELLY_PATH}/)
endif()
target_include_directories(skelly_render PUBLIC ${skelly_render_libs})
target_link_libraries(skelly_render PUBLIC glfw glad)
set_property(
    TARGET skelly_render
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
##render

##glfw
##glfw

## skelly_dyn
add_library(skelly_dyn SHARED 
    ${SKELLY_PATH}/skelly.cpp
)
target_include_directories(skelly_dyn PUBLIC
    ${SKELLY_PATH}/
)
target_link_libraries(skelly_dyn PUBLIC skelly_window skelly_layer)
set_property(
    TARGET skelly_dyn
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_dyn REUSE_FROM pch_shared)
endif()
## skelly_dyn