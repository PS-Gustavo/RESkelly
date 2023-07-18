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

#ifdef PLATFORM_IOS
    #define SKELLY_API
#endif

#ifdef USING_OPENGL
#endif

#ifdef USING_DIRECTX
#endif

#ifdef USING_VULKAN
#endif

#ifdef DEBUG_ENABLED
    #define ENABLE_ASSERTS 1
#endif

#if ENABLE_ASSERTS
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

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)

#define EVENT_CLASS_TYPE(type) \
    static EventType getStaticType() { return EventType::type; }\
    EventType getEventType() const override { return getStaticType(); }\
    const char* getName() const override { return  #type; }

#define EVENT_CLASS_CATEGORY(category)\
    int getCategoryFlags() const override { return category; }

#define DISPATCH_BINDER(type, fn)\
    dispatcher.dispatch<type>(std::bind(&fn, this, std::placeholders::_1))
