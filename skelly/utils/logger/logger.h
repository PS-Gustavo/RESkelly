#pragma once

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(pop)

#include <defs.h>

namespace skelly {

    class SKELLY_API Logger {
        public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& getSkellyLogger() { return s_SkellyLogger; }
            inline static std::shared_ptr<spdlog::logger>& getBodyLogger() { return s_BodyLogger; }

        private:
            static std::shared_ptr<spdlog::logger> s_SkellyLogger;
            static std::shared_ptr<spdlog::logger> s_BodyLogger;
    };

}

#define SKELLY_LOG_FATAL(...) ::skelly::Logger::getSkellyLogger()->critical(__VA_ARGS__)
#define SKELLY_LOG_TRACE(...) ::skelly::Logger::getSkellyLogger()->trace(__VA_ARGS__)
#define SKELLY_LOG_ERROR(...) ::skelly::Logger::getSkellyLogger()->error(__VA_ARGS__)
#define SKELLY_LOG_WARN(...)  ::skelly::Logger::getSkellyLogger()->warn(__VA_ARGS__)
#define SKELLY_LOG_INFO(...)  ::skelly::Logger::getSkellyLogger()->info(__VA_ARGS__)

#define BODY_LOG_FATAL(...)   ::skelly::Logger::getBodyLogger()->critical(__VA_ARGS__)
#define BODY_LOG_TRACE(...)   ::skelly::Logger::getBodyLogger()->trace(__VA_ARGS__)
#define BODY_LOG_ERROR(...)   ::skelly::Logger::getBodyLogger()->error(__VA_ARGS__)
#define BODY_LOG_WARN(...)    ::skelly::Logger::getBodyLogger()->warn(__VA_ARGS__)
#define BODY_LOG_INFO(...)    ::skelly::Logger::getBodyLogger()->info(__VA_ARGS__)
