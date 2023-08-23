#include <body.h>

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

            virtual void onImguiRender() override {
            // Custom Imgui features    
            }

    };

    class Body : public skelly::Skelly {
        public:
            Body() {
                pushLayer(new BodyLayer());
            }

            ~Body() {}
    };
}

int main() {
    try {           
        body::Body App;
        App.mockTriangle();       
        App.run();
    }
    catch(const std::exception& e) {
        std::clog << e.what() << '\n';
        return -1;
    }
        
    return 0;
}