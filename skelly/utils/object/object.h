
#include "glm/vec3.hpp"
#include "glm/ext.hpp"

#include <string>

namespace skelly {

  class Object {
    public:

      Object(std::string label) : label_(label) {}
      Object(glm::vec3 position, float angle) : position_(position), angle_(angle) {}
      Object(glm::vec3 position, float angle, std::string label) : position_(position), angle_(angle), label_(label) {}

      glm::vec3 getPosition() {return position_;}
      bool setPosition(glm::vec3 position) {
          position_ = position;
          return true;
      }
      float getAngle() {return angle_;}
      bool setAngle(float angle) {
          angle_ = angle;
          return true;
      }
      std::string getLabel() {return label_;}
      bool setLabel(std::string label) {
        label_ = label;
        return true;
      }
      bool hasLabel() {
        return label_ != "";
      }

      void populateModelMatrix(glm::vec3 rotation_axis) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position_);
        model = glm::rotate(model, glm::radians(angle_), rotation_axis);
        model_ = model;
      }
      glm::mat4 getModel() {
        return model_;
      }

    private:
      glm::vec3 position_ = glm::vec3();
      float angle_ = 0.0f;
      glm::mat4 model_;
      std::string label_;
      bool is_modified = false;

  };
}