#pragma once

#include <string>
#include <functional>
#include <sstream>

#define SKELLY_API

#ifdef RES_PLATFORM_WINDOWS
    #ifdef RES_BUILD_DLL
        #define SKELLY_API __declspec(dllexport)
    #else
        #define SKELLY_API __declspec(dllimport)
    #endif
#endif

#ifdef RES_PLATFORM_LINUX
    #define SKELLY_API
#endif

/**
 * Event Handler definitions
*/

#define BIT(x) (1 << x)

#define EVENT_CLASS_TYPE(type) \
    static EventType getStaticType() { return EventType::##type; }\
    virtual EventType getEventType() const override { return getStaticType(); }\
    virtual const char* getName() const override { return  #type; }

#define EVENT_CLASS_CATEGORY(category)\
    virtual int getCategoryFlags() const override { return category; }
