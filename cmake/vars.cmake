message(STATUS "Importing project variables")

## Compile configs
if (MSVC)
    set(compiler_options /W4)
else()
    set(compiler_options -Wall -Wextra -Wpedantic -Werror)
endif()

## Global paths
# folders
set(CONFIG_PATH ${ROOT_PATH}/config)
set(VENDOR_PATH ${ROOT_PATH}/vendors)
set(SKELLY_PATH ${ROOT_PATH}/skelly)
set(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
# pch pathing file
set(PCH_FILE ${SKELLY_PATH}/pch.cpp)

## Skelly libs
set(skelly_libs 
    imgui
    skelly_logger
    skelly_contexts
    skelly_shader
    skelly_window
    skelly_layer
    skelly_render
    skelly_core
)

## Skelly libs source paths
set(imgui_path
    ${VENDOR_PATH}/imgui/imgui.cpp
    ${VENDOR_PATH}/imgui/imgui_demo.cpp
    ${VENDOR_PATH}/imgui/imgui_draw.cpp
    ${VENDOR_PATH}/imgui/imgui_tables.cpp
    ${VENDOR_PATH}/imgui/imgui_widgets.cpp
    ${VENDOR_PATH}/imgui/backends/imgui_impl_opengl3.cpp
    ${VENDOR_PATH}/imgui/backends/imgui_impl_glfw.cpp
)
set(skelly_logger_path ${SKELLY_PATH}/utils/logger/logger.cpp)
set(skelly_contexts_path ${SKELLY_PATH}/utils/render/context/renderContext.cpp)
set(skelly_shader_path ${SKELLY_PATH}/utils/render/shader/shader.cpp)
set(skelly_window_path ${SKELLY_PATH}/utils/window/window.cpp)
set(skelly_layer_path ${SKELLY_PATH}/utils/layer/layer.cpp ${SKELLY_PATH}/utils/layer/layerStack.cpp)
set(skelly_render_path ${SKELLY_PATH}/utils/render/render.cpp)
set(skelly_core_path
    ${SKELLY_PATH}/utils/application/application.cpp
    ${SKELLY_PATH}/utils/layer/imgui/imguiLayer.cpp
    ${SKELLY_PATH}/utils/inputPoll/input.cpp
)

## Skelly lib include paths
set(imgui_includes
    ${VENDOR_PATH}/imgui/
    ${VENDOR_PATH}/imgui/backends/
)
set(skelly_logger_includes ${SKELLY_PATH}/utils/logger/)
set(skelly_contexts_includes ${SKELLY_PATH}/utils/render/context/)
set(skelly_shader_includes ${SKELLY_PATH}/utils/render/shader/)
set(skelly_window_includes 
    ${SKELLY_PATH}/utils/window/
    ${SKELLY_PATH}/utils/eventHandler/
)
set(skelly_layer_includes  ${SKELLY_PATH}/utils/layer/)
set(skelly_render_includes
    ${SKELLY_PATH}/utils/render/
)
set(skelly_core_includes
    ${SKELLY_PATH}/utils/application/
    ${SKELLY_PATH}/utils/layer/imgui/
    ${SKELLY_PATH}/utils/inputPoll/
    ${SKELLY_PATH}/utils/inputBindings/
)
if(NOT ${PCH_ENABLED})
    set(skelly_logger_includes ${skelly_logger_includes} ${SKELLY_PATH}/ ${VENDOR_PATH}/spdlog/include/)
    set(skelly_contexts_includes ${skelly_contexts_includes} ${SKELLY_PATH}/)
    set(skelly_shader_includes ${skelly_shader_includes} ${SKELLY_PATH}/)
    set(skelly_layer_includes ${skelly_layer_includes} ${SKELLY_PATH}/ ${SKELLY_PATH}/utils/eventHandler/)
    set(skelly_render_includes ${skelly_render_includes} ${SKELLY_PATH}/ ${VENDOR_PATH}/imgui/)
endif()