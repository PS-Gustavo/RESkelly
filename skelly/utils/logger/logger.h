
/****************************************************************************************
 * 
 * Sphenoid
 * Logger Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Basic logging, setup and Spdlog usage
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the logging solution. It allows the application to send relevant messages to
 * the console, as well as provide the funcionality to create asserts and warnings or error
 * messages during runs. Currently, it uses the SPDLog solution.
 * 
 ***************************************************************************************/

#pragma once

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <memory>
    #include <spdlog/spdlog.h>
    #include <spdlog/fmt/ostr.h>
    #include <spdlog/sinks/stdout_color_sinks.h>
#endif

namespace skelly {

    class SKELLY_API Logger {
        public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& getSkellyLogger() { return _m_skellyLogger; }
            inline static std::shared_ptr<spdlog::logger>& getBodyLogger() { return _m_bodyLogger; }

        private:
            static std::shared_ptr<spdlog::logger> _m_skellyLogger;
            static std::shared_ptr<spdlog::logger> _m_bodyLogger;
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