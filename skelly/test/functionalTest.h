#include <helloTriangle/helloTriangle.h>
#include <testCamera/testCamera.h>
#include <skelly.h>

namespace test {

    class TestLayer : public skelly::Layer {
        public:
            TestLayer() : Layer("Test") {}

            void onUpdate() override {}
            void onEvent([[maybe_unused]] skelly::Event& event) override {
                BODY_LOG_TRACE("{0}", event);
            }
            void onAttach() override {}
            void onDetach() override {}
    };

    class Test : public skelly::Skelly {
        public:
            Test(std::string appName) : Skelly(appName) {
                pushLayer(new TestLayer());
            }
            ~Test() {}
    };

    std::pair<bool, std::string> functionalRegression();

}