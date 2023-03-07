message("Reading Body Project libraries.")

add_library(
    _b_dlapi STATIC
        body/utils/dlapi/dlapi.cpp
        body/utils/dlapi/dlapi.h
)
target_include_directories(
    _b_dlapi PUBLIC
        body/utils/dlapi/
)

add_library(
    _b_skellyloader STATIC
        body/utils/skellyloader/skellyloader.cpp
        body/utils/skellyloader/skellyloader.h
)
target_include_directories(
    _b_skellyloader PUBLIC
        skelly/
        skelly/utils/logger/
        vendors/spdlog/include/
        body/utils/dlapi/
        body/utils/skellyloader/
)

add_executable(initial body/body.cpp body/body.h)
target_include_directories(
    initial PUBLIC
        body/
)

target_link_libraries(
    initial PUBLIC skelly_dyn _s_logger _b_dlapi _b_skellyloader
)