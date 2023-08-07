#pragma once

#include <rendererAPI.h>

namespace skelly {

    class Renderer {
        public:
            static void beginScene();
            static void endScene();

            static void submit(std::shared_ptr<VertexArray>& vertexArray);

            inline static APITarget getTargetAPI() { return RendererAPI::getTargetAPI(); }
    };

    class RenderCommands {
        public:

            inline static void setClearColor(const glm::vec4& color)
                { _s_rendererAPI->setClearColor(color); };
                
            inline static void clear() { _s_rendererAPI->clear(); }

            inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) 
                { _s_rendererAPI->drawIndexed(vertexArray); }

        private:
            static RendererAPI* _s_rendererAPI;
    };

}