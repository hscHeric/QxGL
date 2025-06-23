#include "camera.hpp"

namespace qxgl {

  Camera::Camera()
    : eye_{ 0.0f, 1.0f, 10.0f }
    , center_{ 0.0f, 1.0f, 0.0f }
    , up_{ 0.0f, 1.0f, 0.0f }
    , style_{ CameraStyle::GAME } {}

  Camera::Camera( const Vetor3D &eye, const Vetor3D &center, const Vetor3D &up )
    : eye_{ eye }, center_{ center }, up_{ up }, style_{ CameraStyle::GAME } {}

  Camera::Camera( GLfloat ex,
                  GLfloat ey,
                  GLfloat ez,
                  GLfloat cx,
                  GLfloat cy,
                  GLfloat cz,
                  GLfloat ux,
                  GLfloat uy,
                  GLfloat uz )
    : eye_{ ex, ey, ez }, center_{ cx, cy, cz }, up_{ ux, uy, uz }, style_{ CameraStyle::GAME } {}

  void Camera::normalize_distance() {
    center_ = eye_ + ( center_ - eye_ ).get_unit();
  }

  void Camera::set_distance( GLfloat r ) {
    center_ = eye_ + ( center_ - eye_ ).get_unit() * r;
  }

}  // namespace qxgl
