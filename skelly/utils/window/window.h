#pragma once

#include <windowEvent.h>
#include <mouseEvent.h>
#include <keyEvent.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <logger.h>
    #include <string>
    #include <functional>
#endif

// Platform agnostic section
namespace skelly {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "RESkelly",
            unsigned int width = 1280,
            unsigned int height = 720
        ) : title(title), width(width), height(height) {}
    };

    class SKELLY_API Window {
        public:
            using EventCallbackFn = std::function<void(Event&)>;

            virtual ~Window() {}

            virtual void onUpdate() = 0;

            virtual unsigned int getWidth() const = 0;
            virtual unsigned int getHeight() const = 0;

            virtual void setEventCallback(const EventCallbackFn& callback) = 0;
            virtual void setVSync(bool enabled) = 0;
            virtual bool isVSync() const = 0;

            virtual void* getNativeWindow() const = 0;

            static Window* create(const WindowProps& props = WindowProps());
    };
}