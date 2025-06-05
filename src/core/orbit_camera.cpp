#include "orbit_camera.hpp"

#include "camera.hpp"

#include <GL/gl.h>

namespace qxgl {

  OrbitCamera::OrbitCamera()
    : Camera(
        Vector3( 0.0F, 1.0F, 10.0F ), Vector3( 0.0F, 1.0F, 0.0F ), Vector3( 0.0F, 1.0F, 0.0F ) ) {}

  OrbitCamera::OrbitCamera( const Vector3 &eye, const Vector3 &center, const Vector3 &up )
    : Camera( eye, center, up ) {}

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
    auto dir     = eye.subtract( center ).unit();
    auto new_eye = eye.add( dir.multiply( ( delta * scale ) / 20.0F ) );
    if ( ( ( center - new_eye ) * dir ) >= 0.0001F ) {
      eye = new_eye;
    }
  }

  void OrbitCamera::translateX( GLfloat delta, GLfloat scale ) {
    auto  vec    = center.subtract( eye );  // vetor olho ao centro
    auto  x_     = vec.cross( up ).unit();  // eixo X local (right)
    float factor = vec.length() * ( scale - delta ) / 300.0F;

    eye    = eye + x_.multiply( factor );
    center = center + x_.multiply( factor );
  }

  void OrbitCamera::translateY( GLfloat delta, GLfloat scale ) {
    auto  vec    = center.subtract( eye );  // vetor olho ao centro
    float factor = vec.length() * ( scale - delta ) / 300.0F;

    eye    = eye - up.multiply( factor );
    center = center - up.multiply( factor );
  }

  void OrbitCamera::rotateX( GLfloat angle, GLfloat scale ) {
    auto center_to_eye    = eye.subtract( center );
    auto ceter_to_eye_len = center_to_eye.length();

    eye = eye + ( up * ( ( ( 1.0 / 30.0 ) * ceter_to_eye_len ) * ( angle * scale ) / 5.0 ) );

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

    eye = eye + ( x_axis * ( ( ( 1.0 / 30.0 ) * ceter_to_eye_len ) * ( angle * scale ) / 5.0 ) );

    center_to_eye = eye.subtract( center );
    center_to_eye.normalize();
    center_to_eye = center_to_eye * ceter_to_eye_len;
    eye           = center + center_to_eye;

    // Atualização de "up" para não rotacionar em torno de Z
    Vector3 up_axis = ( up.y >= 0.0F ) ? Vector3( 0.0F, 1.0F, 0.0F ) : Vector3( 0.0F, -1.0F, 0.0F );

    x_axis = up_axis.cross( center_to_eye );
    up     = center_to_eye.cross( x_axis );
    up.normalize();
  }

  void OrbitCamera::rotateZ( GLfloat angle, GLfloat scale ) {
    auto vec    = center.subtract( eye );  // vetor do olho ao centro
    auto x_axis = vec.cross( up ).unit();  // eixo X local

    up = up + ( x_axis * ( ( angle * scale ) / 300.0F ) );
    up.normalize();
  }

  Vector3 OrbitCamera::getPickedPoint( GLfloat screenX, GLfloat screenY ) {
    // Calculando a base da câmera
    auto center_to_eye = eye.subtract( center );
    center_to_eye.normalize();
    auto x_axis = up.cross( center_to_eye ).unit();

    // Mudança da base da câmera para a base do mundo (canônica)
    float dx = ( x_axis.x * screenX ) + ( up.x * screenY ) + ( center_to_eye.x * -1 );
    float dy = ( x_axis.y * screenX ) + ( up.y * screenY ) + ( center_to_eye.y * -1 );
    float dz = ( x_axis.z * screenX ) + ( up.z * screenY ) + ( center_to_eye.z * -1 );

    // Translação em relação à posição da câmera
    dx += eye.x;
    dy += eye.y;
    dz += eye.z;

    return { dx, dy, dz };
  }
}  // namespace qxgl
