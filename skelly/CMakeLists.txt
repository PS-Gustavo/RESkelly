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
    target_link_libraries(pch_static PUBLIC glfw glad glm)
    target_link_libraries(pch_shared PUBLIC glfw glad glm)
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
endif()

## WIP: conditionals should go here
target_link_libraries(skelly_api PUBLIC 
    skelly_logger
    imgui glm glad glfw
)
##
target_link_libraries(skelly_render PUBLIC
    skelly_logger skelly_api
    imgui
)
target_link_libraries(skelly_input PUBLIC skelly_api)
target_link_libraries(skelly_window PUBLIC skelly_api)
target_link_libraries(skelly_layer PUBLIC skelly_window skelly_api)
target_link_libraries(skelly_core PUBLIC
    skelly_window skelly_render skelly_layer
    imgui
)
if(${TEST_ENABLED}) 
    target_link_libraries(skelly_test PUBLIC skelly_core)
endif()

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
)
target_include_directories(skelly_dyn PUBLIC
    ${SKELLY_PATH}/utils/application/
)
target_link_libraries(skelly_dyn PUBLIC skelly_core)
if(${TEST_ENABLED})
    target_link_libraries(skelly_dyn PUBLIC skelly_test)
endif()
set_property(
    TARGET skelly_dyn
    PROPERTY POSITION_INDEPENDENT_CODE ON
)
if(${PCH_ENABLED})
    target_precompile_headers(skelly_dyn REUSE_FROM pch_shared)
endif()
## skelly_dyn