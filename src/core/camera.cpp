#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace qxgl {

  Camera::Camera()
    : position( 0.0F, 0.0F, 5.0F ), direction( 0.0F, 0.0F, -1.0F ), up( 0.0F, 1.0F, 0.0F ) {
    updateViewMatrix();
  }

  void Camera::setPosition( const Vector3 &pos ) {
    position = pos;
    updateViewMatrix();
  }

  void Camera::setDirection( const Vector3 &dir ) {
    direction = dir;
    updateViewMatrix();
  }

  void Camera::setUp( const Vector3 &upVec ) {
    up = upVec;
    updateViewMatrix();
  }

  const glm::mat4 &Camera::getViewMatrix() const {
    return viewMatrix;
  }

  const glm::mat4 &Camera::getProjectionMatrix() const {
    return projectionMatrix;
  }

  void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt( position.glm(),                  // posição da câmera
                              ( position + direction ).glm(),  // ponto que está olhando
                              up.glm()                         // vetor para cima
    );
  }

}  // namespace qxgl
