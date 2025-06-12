#include "orbit_camera.hpp"

#include "camera.hpp"

#include <GL/gl.h>

namespace qxgl {

  OrbitCamera::OrbitCamera()
    : Camera(
        Vector3( 0.0F, 1.0F, 10.0F ), Vector3( 0.0F, 1.0F, 0.0F ), Vector3( 0.0F, 1.0F, 0.0F ) ) {
    style = Orbit;
  }

  OrbitCamera::OrbitCamera( const Vector3 &eye, const Vector3 &center, const Vector3 &up )
    : Camera( eye, center, up ) {
    style = Orbit;
  }

  OrbitCamera::OrbitCamera( GLfloat ex,
                            GLfloat ey,
                            GLfloat ez,
                            GLfloat cx,
                            GLfloat cy,
                            GLfloat cz,
                            GLfloat ux,
                            GLfloat uy,
                            GLfloat uz )
    : Camera( ex, ey, ez, cx, cy, cz, ux, uy, uz ) {}

  void OrbitCamera::zoom( GLfloat delta, GLfloat scale ) {
    auto  dir         = eye.subtract( center ).unit();
    float move_amount = delta * scale * 0.1F;

    float current_distance = eye.distanceTo( center );
    if ( current_distance - move_amount < 0.1f && move_amount > 0 ) {
      eye = center.add( dir.multiply( 0.1f ) );
      return;
    }

    eye = eye.subtract( dir.multiply( move_amount ) );
  }

  void OrbitCamera::translateX( GLfloat delta, GLfloat scale ) {
    auto  vec             = center.subtract( eye );
    auto  x_axis          = vec.cross( up ).unit();
    float pan_sensitivity = eye.distanceTo( center ) * 0.005f;
    float factor          = delta * scale * pan_sensitivity;

    eye    = eye + x_axis.multiply( factor );
    center = center + x_axis.multiply( factor );
  }

  void OrbitCamera::translateY( GLfloat delta, GLfloat scale ) {
    float pan_sensitivity = eye.distanceTo( center ) * 0.005f;
    float factor          = delta * scale * pan_sensitivity;

    eye    = eye + up.multiply( factor );
    center = center + up.multiply( factor );
  }

  void OrbitCamera::rotateX( GLfloat angle, GLfloat scale ) {
    auto center_to_eye    = eye.subtract( center );
    auto ceter_to_eye_len = center_to_eye.length();

    GLfloat rotation_magnitude = angle * scale * 0.01F;

    eye = eye + ( up * ( ( ( 1.0 / 30.0 ) * ceter_to_eye_len ) * rotation_magnitude ) );

    center_to_eye = eye.subtract( center );
    center_to_eye.normalize();
    center_to_eye = center_to_eye * ceter_to_eye_len;
    eye           = center + center_to_eye;

    auto x_axis = up.cross( center_to_eye );
    up          = center_to_eye.cross( x_axis );
    up.normalize();
  }

  void OrbitCamera::rotateY( GLfloat angle, GLfloat scale ) {
    auto center_to_eye    = eye.subtract( center );
    auto ceter_to_eye_len = center_to_eye.length();
    auto x_axis           = up.cross( center_to_eye ).unit();

    GLfloat rotation_magnitude = angle * scale * 0.01F;

    eye = eye + ( x_axis * ( ( ( 1.0 / 30.0 ) * ceter_to_eye_len ) * rotation_magnitude ) );

    center_to_eye = eye.subtract( center );
    center_to_eye.normalize();
    center_to_eye = center_to_eye * ceter_to_eye_len;
    eye           = center + center_to_eye;

    Vector3 up_axis = ( up.y >= 0.0F ) ? Vector3( 0.0F, 1.0F, 0.0F ) : Vector3( 0.0F, -1.0F, 0.0F );

    x_axis = up_axis.cross( center_to_eye );
    up     = center_to_eye.cross( x_axis );
    up.normalize();
  }

  void OrbitCamera::rotateZ( GLfloat angle, GLfloat scale ) {
    auto vec    = center.subtract( eye );
    auto x_axis = vec.cross( up ).unit();

    GLfloat rotation_magnitude = angle * scale * 0.01F;

    up = up + ( x_axis * rotation_magnitude );
    up.normalize();
  }

  Vector3 OrbitCamera::getPickedPoint( GLfloat screenX, GLfloat screenY ) {
    auto center_to_eye = eye.subtract( center );
    center_to_eye.normalize();
    auto x_axis = up.cross( center_to_eye ).unit();

    float dx = ( x_axis.x * screenX ) + ( up.x * screenY ) + ( center_to_eye.x * -1 );
    float dy = ( x_axis.y * screenX ) + ( up.y * screenY ) + ( center_to_eye.y * -1 );
    float dz = ( x_axis.z * screenX ) + ( up.z * screenY ) + ( center_to_eye.z * -1 );

    dx += eye.x;
    dy += eye.y;
    dz += eye.z;

    return { dx, dy, dz };
  }
}  // namespace qxgl
