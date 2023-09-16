set(ENV{PROJECT_NAME} body)
set(PROJECT_PATH ${ROOT_PATH}/$ENV{PROJECT_NAME})

message(STATUS "Reading $ENV{PROJECT_NAME} Project libraries.")

project($ENV{PROJECT_NAME}
            VERSION 0.1
            DESCRIPTION "Template Body Application using RES - Rendering Engine Skelly."
            LANGUAGES CXX
)

## body_exec
add_executable($ENV{PROJECT_NAME}_exec ${PROJECT_PATH}/body.cpp)
set (body_exec_libs ${PROJECT_PATH}/)
if (${PCH_ENABLED})
    target_precompile_headers($ENV{PROJECT_NAME}_exec REUSE_FROM pch_static)
endif()
target_include_directories($ENV{PROJECT_NAME}_exec PRIVATE ${body_exec_libs})
target_link_libraries($ENV{PROJECT_NAME}_exec PRIVATE skelly_dyn OpenGL::GL)
## body_exec