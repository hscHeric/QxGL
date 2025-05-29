#include "camera.hpp"

namespace qxgl {
  Camera::Camera()
    : eye( 0.0F, 1.0F, 10.0F ), center( 0.0F, 1.0F, 0.0F ), up( 0.0F, 1.0F, 0.0F ), style( 0 ) {}

  Camera::Camera( const Vector3 &eye, const Vector3 &center, const Vector3 &up )
    : eye( eye ), center( center ), up( up ), style( 0 ) {}

  Camera::Camera( GLfloat ex,
                  GLfloat ey,
                  GLfloat ez,
                  GLfloat cx,
                  GLfloat cy,
                  GLfloat cz,
                  GLfloat ux,
                  GLfloat uy,
                  GLfloat uz )
    : eye( ex, ey, ez ), center( cx, cy, cz ), up( ux, uy, uz ), style( 0 ) {}

}  // namespace qxgl
