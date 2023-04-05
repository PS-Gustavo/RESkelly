#pragma once

#define SKELLY_API

#ifdef PLATFORM_WINDOWS
    #ifdef BUILD_DLL
        #define SKELLY_API __declspec(dllexport)
    #else
        #define SKELLY_API __declspec(dllimport)
    #endif
#endif

#ifdef PLATFORM_LINUX
    #define SKELLY_API
#endif

#ifdef ENABLE_ASSERTS
    #ifdef PLATFORM_WINDOWS
        #define SKELLY_ASSERT(x, ...) { if(!(x)) { SKELLY_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
        #define BODY_ASSERT(x, ...) { if(!(x)) { BODY_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #endif
    #ifdef PLATFORM_LINUX
        #define SKELLY_ASSERT(x, ...) { if(!(x)) { SKELLY_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
        #define BODY_ASSERT(x, ...) { if(!(x)) { BODY_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #endif
#else
    #define SKELLY_ASSERT(x, ...)
    #define BODY_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define EVENT_CLASS_TYPE(type) \
    static EventType getStaticType() { return EventType::type; }\
    virtual EventType getEventType() const override { return getStaticType(); }\
    virtual const char* getName() const override { return  #type; }

#define EVENT_CLASS_CATEGORY(category)\
    virtual int getCategoryFlags() const override { return category; }
