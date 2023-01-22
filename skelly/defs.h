#pragma once

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