#include <logger.h>

namespace skelly {

    std::shared_ptr<spdlog::logger> Logger::_m_skellyLogger;
    std::shared_ptr<spdlog::logger> Logger::_m_bodyLogger;
    

    void Logger::init() {
    
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
        _m_skellyLogger = spdlog::stdout_color_mt("Skelly_Logger");
        _m_skellyLogger->set_level(spdlog::level::trace); 
        
        _m_bodyLogger = spdlog::stdout_color_mt("Body_Logger");
        _m_bodyLogger->set_level(spdlog::level::trace); 
        
    }

}