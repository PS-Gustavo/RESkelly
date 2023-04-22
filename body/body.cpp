#include <body.h>

namespace body {

    class BodyLayer : public skelly::Layer {
        public:
            BodyLayer() : Layer("Example") {}

            void onUpdate() override {
                //BODY_LOG_INFO("Example Layer: Update");
            }

            void onEvent(skelly::Event& event) override {
                BODY_LOG_TRACE("{0}", event);
            }

    };

    class Body : public skelly::Application {
        public:
            Body() {
                createWindow();
                pushLayer(new BodyLayer());
                pushOverlay(new skelly::ImguiLayer());
            }

            ~Body() {}
    };
}

int main() {
    try {           
        body::Body App;
        App.run();
    }
    catch(const std::exception& e) {
        std::clog << e.what() << '\n';
        return -1;
    }
        
    return 0;
}