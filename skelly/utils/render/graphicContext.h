#pragma once

namespace skelly {

    class GraphicContext {
        public:
            virtual void init() = 0;
            virtual void swapBuffers() = 0;
    };

}