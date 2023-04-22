# Skelly libraries

## pch
if (PCH_ENABLED)
    message(STATUS "Compiling using pre-compiled header support")    
    set(pch_libs 
        ${SKELLY_PATH}/
        ${SKELLY_PATH}/utils/eventHandler/
        ${SKELLY_PATH}/utils/layer/
        ${VENDOR_PATH}/spdlog/include/
    )
    add_library(pch_static STATIC ${PCH_FILE})
    add_library(pch_shared STATIC ${PCH_FILE})
    target_link_libraries(pch_static PUBLIC glfw glad)
    target_link_libraries(pch_shared PUBLIC glfw glad)
    target_include_directories(pch_static PUBLIC ${pch_libs})
    target_include_directories(pch_shared PUBLIC ${pch_libs})
    set_property(
        TARGET pch_shared
        PROPERTY POSITION_INDEPENDENT_CODE ON
    )
    target_precompile_headers(pch_static PUBLIC ${SKELLY_PATH}/pch.h)
    target_precompile_headers(pch_shared PUBLIC ${SKELLY_PATH}/pch.h)
endif()
## pch

## creating libraries
foreach(lib IN LISTS skelly_libs)
    add_library(${lib} STATIC ${${lib}_path})
endforeach()

if(${PCH_ENABLED})
    foreach(lib IN LISTS skelly_libs)
        target_precompile_headers(${lib} REUSE_FROM pch_shared)
    endforeach()
else()
    target_link_libraries(pch_shared PUBLIC spdlog)
endif()
target_link_libraries(skelly_window PUBLIC skelly_logger glfw glad)
target_link_libraries(skelly_render PUBLIC glfw glad imgui)
target_compile_definitions(skelly_render PRIVATE IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

foreach(lib IN LISTS skelly_libs)
    target_include_directories(${lib} PUBLIC ${${lib}_includes})
    set_property(
        TARGET ${lib}
        PROPERTY POSITION_INDEPENDENT_CODE ON
    )
endforeach()

## skelly_dyn
add_library(skelly_dyn SHARED
    ${SKELLY_PATH}/skelly.cpp
    ${SKELLY_PATH}/utils/layer/imgui/imguiLayer.cpp
)
target_include_directories(skelly_dyn PUBLIC
    ${SKELLY_PATH}/
    ${SKELLY_PATH}/utils/layer/imgui/
)
target_link_libraries(skelly_dyn PUBLIC skelly_window skelly_layer skelly_render)
set_property(
    TARGET skelly_dyn
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_dyn REUSE_FROM pch_shared)
endif()
## skelly_dyn