#pragma once

#include <skelly.h>

// use if running any example
#include <helloTriangle.h>

#ifndef PCH_ENABLED
    #include <iostream>
#endif

namespace body {

    class BodyLayer : public skelly::Layer {
        public:
            BodyLayer() : Layer("Example") {}

            void onUpdate() override {}

            void onEvent(skelly::Event& event) override {
                BODY_LOG_TRACE("{0}", event);
            }

            void onAttach() override {}
            void onDetach() override {}
    };

    class Body : public skelly::Skelly {
        public:
            Body() {
                pushLayer(new BodyLayer());
            }
            ~Body() {}
    };
}