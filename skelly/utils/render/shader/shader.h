#pragma once

#include <render.h>

#ifndef PCH_ENABLED
    #include <string>
    #include <vector>
    #include <logger.h>
#endif

namespace skelly {

    class Shader {
        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            // virtual void load(std::string& vertexSrc, std::string& fragmentSrc) const = 0;
            virtual int getMaxVertexAttributes() const = 0;
            
            static Shader* create(std::string& vertexSrc, std::string& fragmentSrc);
    };

}