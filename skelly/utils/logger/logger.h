#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <defs.h>

namespace skelly {

    class SKELLY_API logger {
        public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& getSkellyLogger() { return s_SkellyLogger; }
            inline static std::shared_ptr<spdlog::logger>& getBodyLogger() { return s_BodyLogger; }

        private:
            static std::shared_ptr<spdlog::logger> s_SkellyLogger;
            static std::shared_ptr<spdlog::logger> s_BodyLogger;
    };

}

#define SKELLY_LOG_FATAL(...) ::skelly::logger::getSkellyLogger()->fatal(__VA_ARGS__)
#define SKELLY_LOG_TRACE(...) ::skelly::logger::getSkellyLogger()->trace(__VA_ARGS__)
#define SKELLY_LOG_ERROR(...) ::skelly::logger::getSkellyLogger()->error(__VA_ARGS__)
#define SKELLY_LOG_WARN(...)  ::skelly::logger::getSkellyLogger()->warn(__VA_ARGS__)
#define SKELLY_LOG_INFO(...)  ::skelly::logger::getSkellyLogger()->info(__VA_ARGS__)

#define BODY_LOG_FATAL(...)   ::skelly::logger::getBodyLogger()->fatal(__VA_ARGS__)
#define BODY_LOG_TRACE(...)   ::skelly::logger::getBodyLogger()->trace(__VA_ARGS__)
#define BODY_LOG_ERROR(...)   ::skelly::logger::getBodyLogger()->error(__VA_ARGS__)
#define BODY_LOG_WARN(...)    ::skelly::logger::getBodyLogger()->warn(__VA_ARGS__)
#define BODY_LOG_INFO(...)    ::skelly::logger::getBodyLogger()->info(__VA_ARGS__)
