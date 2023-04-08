set(ENV{PROJECT_NAME} body)
set(PROJECT_PATH ${ROOT_PATH}/$ENV{PROJECT_NAME})

message(STATUS "Reading $ENV{PROJECT_NAME} Project libraries.")

project($ENV{PROJECT_NAME}
            VERSION 0.1
            DESCRIPTION "Template Body Application using RES - Rendering Engine Skelly."
            LANGUAGES CXX
)

## skelly imports
add_library($ENV{PROJECT_NAME}_skelly_dyn SHARED IMPORTED)
set_target_properties($ENV{PROJECT_NAME}_skelly_dyn PROPERTIES
    IMPORTED_LOCATION ${OUTPUT_PATH}/libskelly_dyn.so
)
## skelly imports

## body_exec
add_executable($ENV{PROJECT_NAME}_exec ${PROJECT_PATH}/body.cpp)
target_include_directories($ENV{PROJECT_NAME}_exec PRIVATE
    ${PROJECT_PATH}/
)
# set_property(
#     TARGET $ENV{PROJECT_NAME}_exec
#     PROPERTY POSITION_INDEPENDENT_CODE ON
# )
if (${PCH_ENABLED})
    target_precompile_headers($ENV{PROJECT_NAME}_exec REUSE_FROM pch_static)
endif()
target_link_libraries($ENV{PROJECT_NAME}_exec PRIVATE skelly_dyn)
target_compile_options($ENV{PROJECT_NAME}_exec PUBLIC "-lGL -lglew")

## body_exec