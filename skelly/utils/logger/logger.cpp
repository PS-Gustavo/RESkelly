#include <logger.h>

namespace skelly {

    std::shared_ptr<spdlog::logger> Logger::s_SkellyLogger;
    std::shared_ptr<spdlog::logger> Logger::s_BodyLogger;
    

    void Logger::init() {
    
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
        s_SkellyLogger = spdlog::stdout_color_mt("Skelly_Logger");
        s_SkellyLogger->set_level(spdlog::level::trace); 
        
        s_BodyLogger = spdlog::stdout_color_mt("Body_Logger");
        s_BodyLogger->set_level(spdlog::level::trace); 
        
    }

}