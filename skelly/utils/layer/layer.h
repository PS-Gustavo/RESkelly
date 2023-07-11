#pragma once

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <event.h>
#endif

namespace skelly {

    class SKELLY_API Layer {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer();

            virtual void onAttach() {}
            virtual void onDetach() {}
            virtual void onUpdate() {}
            virtual void onImguiRender() {}
            virtual void onEvent(Event& event) {}

            inline const std::string& getName() const { return m_debugName; }
        
        protected:
            std::string m_debugName;
    };
}