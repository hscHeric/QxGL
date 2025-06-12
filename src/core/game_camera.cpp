#include "game_camera.hpp"

namespace qxgl {

  GameCamera::GameCamera() {
    center.z = eye.z - 1.0F;
    style    = CameraStyle::GameCamera;
  }

  GameCamera::GameCamera( const Vector3 &eye, const Vector3 &center, const Vector3 &up )
    : Camera( eye, center, up ) {
    style = CameraStyle::GameCamera;
  }

  GameCamera::GameCamera( GLfloat ex,
                          GLfloat ey,
                          GLfloat ez,
                          GLfloat cx,
                          GLfloat cy,
                          GLfloat cz,
                          GLfloat ux,
                          GLfloat uy,
                          GLfloat uz )
    : Camera( ex, ey, ez, cx, cy, cz, ux, uy, uz ) {
    style = CameraStyle::GameCamera;
  }

  void GameCamera::zoom( GLfloat delta, GLfloat scale ) {
    Vector3 viewDir = center.subtract( eye );
    Vector3 move    = viewDir.multiply( delta / scale );
    eye             = eye.subtract( move );
    center          = center.subtract( move );
  }

  void GameCamera::translateX( GLfloat delta, GLfloat scale ) {
    Vector3 viewDir = center.subtract( eye );
    Vector3 right   = viewDir.cross( up );
    Vector3 move    = right.multiply( delta / scale );
    eye             = eye.subtract( move );
    center          = center.subtract( move );
  }

  void GameCamera::translateY( GLfloat delta, GLfloat scale ) {
    Vector3 move = up.multiply( delta / scale );
    eye          = eye.add( move );
    center       = center.add( move );
  }

  void GameCamera::rotateX( GLfloat angle, GLfloat scale ) {
    Vector3 move = up.multiply( angle / scale );
    center       = center.add( move );

    Vector3 viewDir = center.subtract( eye );
    viewDir.normalize();
    center = eye.add( viewDir );

    Vector3 right = viewDir.cross( up );
    up            = right.cross( viewDir );
    up.normalize();
  }

  void GameCamera::rotateY( GLfloat angle, GLfloat scale ) {
    Vector3 viewDir = center.subtract( eye );
    Vector3 right   = viewDir.cross( up );
    Vector3 move    = right.multiply( angle / scale );
    center          = center.subtract( move );

    Vector3 viewDirNew = center.subtract( eye );
    viewDirNew.normalize();
    center = eye.add( viewDirNew );

    Vector3 upRef = up.y >= 0.0F ? Vector3( 0.0F, 1.0F, 0.0F ) : Vector3( 0.0F, -1.0F, 0.0F );
    Vector3 zAxis = eye - center;
    Vector3 xAxis = upRef ^ zAxis;
    up            = zAxis ^ xAxis;
    up            = !up;
  }

  void GameCamera::rotateZ( GLfloat angle, GLfloat scale ) {
    Vector3 viewDir = center.subtract( eye );
    Vector3 right   = viewDir.cross( up );
    right.normalize();

    Vector3 move = right.multiply( angle / scale );
    up           = up.subtract( move );
    up.normalize();
  }

  Vector3 GameCamera::getPickedPoint( GLfloat screenX, GLfloat screenY ) {
    Vector3 viewDir = eye.subtract( center );
    viewDir.normalize();
    Vector3 right = up.cross( viewDir );
    right.normalize();

    float dx = ( right.x * screenX ) + ( up.x * screenY ) + ( viewDir.x * -1.0F );
    float dy = ( right.y * screenX ) + ( up.y * screenY ) + ( viewDir.y * -1.0F );
    float dz = ( right.z * screenX ) + ( up.z * screenY ) + ( viewDir.z * -1.0F );

    return { eye.x + dx, eye.y + dy, eye.z + dz };
  }

}  // namespace qxgl
