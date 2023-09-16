
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

#include <logger.h>

namespace skelly {

    // Two pointers are initialized to separate logger messages between what is intrinsic to
    // the engine and what is developed by the end user in a body project. skellyLogger should
    // not be used in the body project.
    std::shared_ptr<spdlog::logger> Logger::_m_skellyLogger;
    std::shared_ptr<spdlog::logger> Logger::_m_bodyLogger;
    
    void Logger::init(std::string appName) {
    
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
        std::string skellyLoggerName = appName+"_Skelly_Logger";
        std::string bodyLoggerName = appName+"_Logger";

        _m_skellyLogger = spdlog::stdout_color_mt(skellyLoggerName);
        _m_skellyLogger->set_level(spdlog::level::trace); 
        
        _m_bodyLogger = spdlog::stdout_color_mt(bodyLoggerName);
        _m_bodyLogger->set_level(spdlog::level::trace); 
        
    }

}