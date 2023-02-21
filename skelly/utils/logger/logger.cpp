#include <logger.h>

namespace skelly {

    std::shared_ptr<spdlog::logger> logger::s_SkellyLogger;
    std::shared_ptr<spdlog::logger> logger::s_BodyLogger;
    

    void logger::init() {
    
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
        s_SkellyLogger = spdlog::stdout_color_mt("Skelly_logger");
        s_SkellyLogger->set_level(spdlog::level::trace); 
        
        s_BodyLogger = spdlog::stdout_color_mt("Body_logger");
        s_BodyLogger->set_level(spdlog::level::trace); 
        
    }

}