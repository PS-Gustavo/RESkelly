message(STATUS "Importing project variables")

## Global paths
# folders
set(CONFIG_PATH ${ROOT_PATH}/config)
set(VENDOR_PATH ${ROOT_PATH}/vendors)
set(SKELLY_PATH ${ROOT_PATH}/skelly)
set(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
# pch pathing file
set(PCH_FILE ${SKELLY_PATH}/pch.cpp)

## Skelly libs
set(skelly_libs skelly_logger skelly_window skelly_layer skelly_render)

## Skelly libs source paths
set(skelly_logger_path ${SKELLY_PATH}/utils/logger/logger.cpp)
set(skelly_window_path ${SKELLY_PATH}/utils/window/window.cpp)
set(skelly_layer_path ${SKELLY_PATH}/utils/layer/layer.cpp ${SKELLY_PATH}/utils/layer/layerStack.cpp)
set(skelly_render_path ${SKELLY_PATH}/utils/render/render.cpp)
set(skelly_l_imgui_path ${SKELLY_PATH}/utils/layer/imgui/imguiLayer.cpp)

## Skelly lib include paths
set(skelly_logger_includes ${SKELLY_PATH}/utils/logger/)
set(skelly_window_includes 
    ${SKELLY_PATH}/utils/window/
    ${SKELLY_PATH}/utils/eventHandler/
)
set(skelly_layer_includes  ${SKELLY_PATH}/utils/layer/)
set(skelly_render_includes
    ${SKELLY_PATH}/utils/render/
    ${VENDOR_PATH}/imguiCM/imgui/
)
set(skelly_l_imgui_includes ${SKELLY_PATH}/utils/layer/imgui/)
if(NOT ${PCH_ENABLED})
    set(skelly_logger_includes ${skelly_logger_includes} ${SKELLY_PATH}/)
    set(skelly_layer_includes ${skelly_layer_includes} ${SKELLY_PATH}/ ${SKELLY_PATH}/utils/eventHandler/)
    set(skelly_render_includes ${skelly_render_includes} ${SKELLY_PATH}/ {VENDOR_PATH}/imguiCM/imgui/)
    set(skelly_l_imgui_includes ${skelly_l_imgui_includes} ${SKELLY_PATH}/ ${SKELLY_PATH}/utils/render/)
endif()