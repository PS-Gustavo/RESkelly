#pragma once

//#include <skelly.h>
#include <render.h>

#ifndef PCH_ENABLED
    #include <layer.h>
#endif

namespace skelly {

    class SKELLY_API ImguiLayer : public Layer {
        public:
            ImguiLayer();
            ~ImguiLayer();

            void onAttach();
            void onDetach();
            void onUpdate();
            void onEvent(Event& event);

        private:
            float _m_time = 0.0f;
    };

}