
/****************************************************************************************
 * 
 * Parietal
 * Window Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Basic OpenGL support, basic creation procedures with
 * fixed dimensions;
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the Window creator module. It allows for the creation of a single window
 * instance. Window calls upo GraphicContext, which is an interface to the API specific
 * RenderContext. Platform specific implementation is carried out in Skelly/API/
 * 
 ***************************************************************************************/

#pragma once

// Platform specific implementation requires these libraries
#include <windowEvent.h>
#include <mouseEvent.h>
#include <keyEvent.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <logger.h>
    #include <string>
    #include <functional>
#endif

namespace skelly {

    class Window {
        public:
            virtual ~Window() {}

            // Event handling setup
            using EventCallbackFn = std::function<void(Event&)>;
            virtual void setEventCallback(const EventCallbackFn& callback) = 0;

            // Run loop upater
            virtual void onUpdate() = 0;
            
            // VSync
            virtual void setVSync(bool enabled) = 0;
            virtual bool isVSync() const = 0;

            // API-specific object fetchers
            virtual void* getNativeWindow() const = 0;
            static APITarget getTargetAPI() { return _s_targetAPI; }

            // Window attribute handlers
            virtual unsigned int getWidth() const = 0;
            virtual void setWidth(unsigned int width) = 0;
            
            virtual unsigned int getHeight() const = 0;
            virtual void setHeight(unsigned int height) = 0;

            // agnostic instantiator
            static Window* create(const WindowProps& props = WindowProps());
        private:
            static APITarget _s_targetAPI;
    };
}