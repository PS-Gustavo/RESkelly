#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/geometric.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "utils/render/shader/shader.h"

#include <functional>
#include <iostream>

namespace skelly {

  class Camera {
    public:
      
      Camera()
        : position_({0.0f, 0.0f, 2.0f}), target_({0.0f, 0.0f, 0.0f}) {
          direction_ = glm::normalize(position_ - target_);
          up_ = {0.0f, 1.0f, 0.0f};
          right_ = glm::normalize(glm::cross(up_, direction_));
        };
      
      Camera(float posx, float posy, float posz)
        : position_({posx, posy, posz}), target_({0.0f, 0.0f, 0.0f}) {
          direction_ = glm::normalize(position_ - target_);
          up_ = {0.0f, 1.0f, 0.0f};
          right_ = glm::normalize(glm::cross(up_, direction_));
        };

      Camera(float posx, float posy, float posz, float tarx, float tary, float tarz)
        : position_({posx, posy, posz}), target_({tarx, tary, tarz}) {
          direction_ = glm::normalize(position_ - target_);
          up_ = {0.0f, 1.0f, 0.0f};
          right_ = glm::normalize(glm::cross(up_, direction_));
        };

      
      void updatePos(glm::vec3 position) {position_ = position; updateDir();};
      void updateTarget(glm::vec3 target) {target_ = target; updateDir();};
      void updateDir() {direction_ = glm::normalize(position_ - target_);};
      glm::mat4 updateView() {
        view_ = glm::lookAt(position_, target_, up_);
        return view_;
      };
      glm::mat4 updateView(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
        updatePos(position);
        updateTarget(target);
        up_ = up;
        return updateView();
      }
      void setRoutine(std::function<void()> routine) {
        render_routine_ = routine;
        has_routine_ = true;
      }
      bool hasRoutine() {return has_routine_;}

      void run() {render_routine_();}

    private:
      glm::vec3 position_;
      glm::vec3 target_;
      glm::vec3 direction_;
      glm::vec3 up_;
      glm::vec3 right_;
      glm::mat4 view_;
      std::function<void()> render_routine_;
      bool has_routine_ = false;
  };
}
