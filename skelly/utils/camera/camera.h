#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/geometric.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "utils/render/shader/shader.h"

#include <functional>
#include <iostream>

namespace skelly {

  class Camera {
    public:
      
      Camera()
        : speed_(2.5f), position_({0.0f, 0.0f, 2.0f}), target_({0.0f, 0.0f, 0.0f}) {
          direction_ = glm::normalize(position_ - target_);
          up_ = {0.0f, 1.0f, 0.0f};
          right_ = glm::normalize(glm::cross(up_, direction_));
        };
      
      Camera(float posx, float posy, float posz)
        : speed_(2.5f), position_({posx, posy, posz}), target_({0.0f, 0.0f, 0.0f}) {
          direction_ = glm::normalize(position_ - target_);
          up_ = {0.0f, 1.0f, 0.0f};
          right_ = glm::normalize(glm::cross(up_, direction_));
        };

      Camera(float posx, float posy, float posz, float tarx, float tary, float tarz)
        : speed_(2.5f), position_({posx, posy, posz}), target_({tarx, tary, tarz}) {
          direction_ = glm::normalize(position_ - target_);
          up_ = {0.0f, 1.0f, 0.0f};
          right_ = glm::normalize(glm::cross(up_, direction_));
        };

      glm::vec3 getPos() {return position_;}
      glm::vec3 getTarget() {return target_;}
      glm::vec3 getDirection() {return direction_;}
      glm::vec3 getUp() {return up_;}
      glm::vec3 getRight() {return right_;}
      glm::mat4 getView() {return view_;}

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

      void setSpeed(float speed) {speed_ = speed;}
      float getSpeed() {return speed_;}

      void moveUp (float speed) {position_ += up_*speed;}
      void moveDown (float speed) {position_ -= up_*speed;}
      void moveForward (float speed) {position_ += direction_*speed;}
      void moveBackward (float speed) {position_ -= direction_*speed;}
      void moveRight (float speed) {position_ += glm::normalize(glm::cross(direction_, up_))*speed;}
      void moveLeft (float speed) {position_ -= glm::normalize(glm::cross(direction_, up_))*speed;}

      void run() {render_routine_();}

    private:
      float speed_;
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
