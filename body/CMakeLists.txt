set(ENV{PROJECT_NAME} body)
set(PROJECT_PATH ${ROOT_PATH}/$ENV{PROJECT_NAME})

message(STATUS "Reading $ENV{PROJECT_NAME} Project libraries.")

project($ENV{PROJECT_NAME}
            VERSION 0.1
            DESCRIPTION "Template Body Application using RES - Rendering Engine Skelly."
            LANGUAGES CXX
)

## dlapi
add_library(_$ENV{PROJECT_NAME}_dlapi STATIC
    ${PROJECT_PATH}/utils/dlapi/dlapi.cpp)
set(DLAPI_LIBS ${PROJECT_PATH}/utils/dlapi/)
if (${PCH_ENABLED})
    target_precompile_headers(_$ENV{PROJECT_NAME}_dlapi REUSE_FROM pch_target)
endif()
target_include_directories(_$ENV{PROJECT_NAME}_dlapi PUBLIC
    ${DLAPI_LIBS}
)
## dlapi

## skellyloader
add_library(_$ENV{PROJECT_NAME}_skellyloader STATIC
    ${PROJECT_PATH}/utils/skellyloader/skellyloader.cpp)
set(SKELLYLOADER_LIBS ${SKELLY_PATH}/ 
    ${SKELLY_PATH}/utils/logger/
    ${SKELLY_PATH}/utils/eventHandler/
    ${PROJECT_PATH}/utils/dlapi/
    ${PROJECT_PATH}/utils/skellyloader/
)
if (${PCH_ENABLED})
    target_precompile_headers(_$ENV{PROJECT_NAME}_skellyloader REUSE_FROM pch_target)
else()
    set(SKELLYLOADER_LIBS ${SKELLYLOADER_LIBS} ${VENDOR_PATH}/spdlog/include/)
endif()
target_include_directories(_$ENV{PROJECT_NAME}_skellyloader PUBLIC
    ${SKELLYLOADER_LIBS}
)
## skellyloader

## skelly imports
add_library($ENV{PROJECT_NAME}_skelly_dyn SHARED IMPORTED)
set_target_properties($ENV{PROJECT_NAME}_skelly_dyn PROPERTIES
    IMPORTED_LOCATION ${OUTPUT_PATH}/libskelly_dyn.so
)
## skelly imports

## body_exec
add_executable($ENV{PROJECT_NAME}_exec ${PROJECT_PATH}/body.cpp ${PROJECT_PATH}/body.h)
target_include_directories($ENV{PROJECT_NAME}_exec PRIVATE
    ${PROJECT_PATH}/
)
if (${PCH_ENABLED})
    target_precompile_headers($ENV{PROJECT_NAME}_exec REUSE_FROM pch_target)
endif()
target_link_libraries($ENV{PROJECT_NAME}_exec PRIVATE 
    $ENV{PROJECT_NAME}_skelly_dyn 
    _$ENV{PROJECT_NAME}_dlapi
    _$ENV{PROJECT_NAME}_skellyloader
)
## body_exec