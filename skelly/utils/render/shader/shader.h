#pragma once

#include <glad/gl.h>

#ifndef PCH_ENABLED
    #include <string>
    #include <vector>
    #include <logger.h>
#endif

namespace skelly {

    class Shader {
        public:
            Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
            ~Shader();

            void bind() const;
            void unbind() const;

        private:
            uint32_t _m_rendererId;
    };

}