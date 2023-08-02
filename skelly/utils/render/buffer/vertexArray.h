#pragma once

#include <buffer.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <logger.h>
#endif

namespace skelly {

    class VertexArray {
        public:
            virtual ~VertexArray() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
            virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

            virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
            virtual const std::vector<std::shared_ptr<IndexBuffer>>& getIndexBuffers() const = 0;

            static VertexArray* create();
    };

}