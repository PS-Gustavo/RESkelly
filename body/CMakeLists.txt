set(ENV{PROJECT_NAME} body)
set(PROJECT_PATH $ENV{ROOT_PATH}/$ENV{PROJECT_NAME})

message("Reading $ENV{PROJECT_NAME} Project libraries.")

project($ENV{PROJECT_NAME}
            VERSION 0.1
            DESCRIPTION "Template Body Application using RES - Rendering Engine Skelly."
            LANGUAGES CXX
)

add_library(
    _$ENV{PROJECT_NAME}_dlapi STATIC
        ${PROJECT_PATH}/utils/dlapi/dlapi.cpp
        ${PROJECT_PATH}/utils/dlapi/dlapi.h
)
target_include_directories(
    _$ENV{PROJECT_NAME}_dlapi PUBLIC
        ${PROJECT_PATH}/utils/dlapi/
)
target_compile_options(_$ENV{PROJECT_NAME}_dlapi PRIVATE "-include" "${pch_file}")

add_library(
    _$ENV{PROJECT_NAME}_skellyloader STATIC
        ${PROJECT_PATH}/utils/skellyloader/skellyloader.cpp
        ${PROJECT_PATH}/utils/skellyloader/skellyloader.h
)
target_include_directories(
    _$ENV{PROJECT_NAME}_skellyloader PUBLIC
        ${SKELLY_PATH}/
        ${SKELLY_PATH}/utils/logger/
        ${SKELLY_PATH}/utils/eventHandler/
        ${VENDOR_PATH}/spdlog/include/
        ${PROJECT_PATH}/utils/dlapi/
        ${PROJECT_PATH}/utils/skellyloader/
)
target_compile_options(_$ENV{PROJECT_NAME}_skellyloader PRIVATE "-include" "${pch_file}")

add_library($ENV{PROJECT_NAME}_skelly_dyn SHARED IMPORTED)
set_target_properties(
    $ENV{PROJECT_NAME}_skelly_dyn PROPERTIES
        IMPORTED_LOCATION $ENV{OUTPUT_PATH}/libskelly_dyn.so
)

add_library($ENV{PROJECT_NAME}_s_logger STATIC IMPORTED)
set_target_properties(
    $ENV{PROJECT_NAME}_s_logger PROPERTIES
        IMPORTED_LOCATION $ENV{OUTPUT_PATH}/lib_s_logger.a
)

add_executable($ENV{PROJECT_NAME}_exec ${PROJECT_PATH}/body.cpp ${PROJECT_PATH}/body.h)
target_include_directories(
    $ENV{PROJECT_NAME}_exec PUBLIC
        ${PROJECT_PATH}/
)
target_compile_options($ENV{PROJECT_NAME}_exec PRIVATE "-include" "${pch_file}")

target_link_libraries(
    $ENV{PROJECT_NAME}_exec PUBLIC 
        $ENV{PROJECT_NAME}_skelly_dyn 
        $ENV{PROJECT_NAME}_s_logger 
        _$ENV{PROJECT_NAME}_dlapi 
        _$ENV{PROJECT_NAME}_skellyloader
)