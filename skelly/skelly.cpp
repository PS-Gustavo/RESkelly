#include <skelly.h>

namespace skelly {

    Skelly::Skelly() {
        init();
    }

    Skelly::~Skelly() {}

    void Skelly::init() {
        createWindow();
        pushOverlay(new skelly::ImguiLayer());
    }
}