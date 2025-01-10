#pragma once

#include <render.h>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

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
            
      // auxiliary functions
      virtual void setBool(const std::string &name, bool value) const = 0;         
      virtual void setInt(const std::string &name, int value) const = 0;
      virtual void setFloat(const std::string &name, float value) const = 0;
      virtual void setVec2(const std::string &name, const glm::vec2 &value) const = 0;
      virtual void setVec2(const std::string &name, float x, float y) const = 0;
      virtual void setVec3(const std::string &name, const glm::vec3 &value) const = 0;
      virtual void setVec3(const std::string &name, float x, float y, float z) const = 0;
      virtual void setVec4(const std::string &name, const glm::vec4 &value) const = 0;
      virtual void setVec4(const std::string &name, float x, float y, float z, float w) const = 0;
      virtual void setMat2(const std::string &name, const glm::mat2 &mat) const = 0;
      virtual void setMat3(const std::string &name, const glm::mat3 &mat) const = 0;
      virtual void setMat4(const std::string &name, const glm::mat4 &mat) const = 0;

      // virtual void load(std::string& vertexSrc, std::string& fragmentSrc) const = 0;
      virtual int getMaxVertexAttributes() const = 0;
            
      static Shader* create(std::string& vertexSrc, std::string& fragmentSrc);
  };

}
