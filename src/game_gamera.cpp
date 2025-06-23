#include "game_camera.hpp"

CameraJogo::CameraJogo() : Camera() {
  c.z    = e.z - 1.0F;
  estilo = CAMJOGO;
}

CameraJogo::CameraJogo( qxgl::Vetor3D e, qxgl::Vetor3D c, qxgl::Vetor3D u ) : Camera( e, c, u ) {
  estilo = CAMJOGO;
}

CameraJogo::CameraJogo( GLfloat ex,
                        GLfloat ey,
                        GLfloat ez,
                        GLfloat cx,
                        GLfloat cy,
                        GLfloat cz,
                        GLfloat ux,
                        GLfloat uy,
                        GLfloat uz )
  : Camera( ex, ey, ez, cx, cy, cz, ux, uy, uz ) {
  estilo = CAMJOGO;
}

void CameraJogo::zoom( GLfloat win_y, GLfloat last_y ) {
  const float DELTA        = ( win_y - last_y ) / 20.0F;
  const auto  DIRECTION    = c - e;
  const auto  DISPLACEMENT = DIRECTION * DELTA;

  e -= DISPLACEMENT;
  c -= DISPLACEMENT;
}

void CameraJogo::translatex( GLfloat win_x, GLfloat last_x ) {
  const float DELTA           = ( last_x - win_x ) / 30.0F;
  const auto  VIEW_DIRECTION  = c - e;
  const auto  RIGHT_DIRECTION = VIEW_DIRECTION ^ u;  // Produto vetorial
  const auto  DISPLACEMENT    = RIGHT_DIRECTION * DELTA;

  e -= DISPLACEMENT;
  c -= DISPLACEMENT;
}

void CameraJogo::translatey( GLfloat win_y, GLfloat last_y ) {
  const float DELTA        = ( last_y - win_y ) / 30.0F;
  const auto  DISPLACEMENT = u * DELTA;

  e += DISPLACEMENT;
  c += DISPLACEMENT;
}

void CameraJogo::rotatex( GLfloat win_y, GLfloat last_y ) {
  const float DELTA = ( last_y - win_y ) / 500.0F;
  c += u * DELTA;

  const auto FORWARD_VEC = ( c - e ).get_unit();
  c                      = e + FORWARD_VEC;

  const auto RIGHT_VEC = FORWARD_VEC ^ u;
  u                    = ( RIGHT_VEC ^ FORWARD_VEC ).get_unit();
}

void CameraJogo::rotatey( GLfloat win_x, GLfloat last_x ) {
  const float DELTA           = ( last_x - win_x ) / 500.0F;
  const auto  VIEW_DIRECTION  = c - e;
  const auto  RIGHT_DIRECTION = VIEW_DIRECTION ^ u;
  c -= RIGHT_DIRECTION * DELTA;

  const auto FORWARD_VEC   = ( c - e ).get_unit();
  c                        = e + FORWARD_VEC;
  const auto WORLD_UP      = qxgl::Vetor3D( 0.0F, 1.0F, 0.0F );
  const auto NEW_RIGHT_VEC = ( WORLD_UP ^ FORWARD_VEC ).get_unit();
  u                        = ( FORWARD_VEC ^ NEW_RIGHT_VEC ).get_unit();
}

void CameraJogo::rotatez( GLfloat win_x, GLfloat last_x ) {
  const float DELTA = ( last_x - win_x ) / 300.0F;

  const auto RIGHT_VEC = ( ( c - e ) ^ u ).get_unit();

  u -= RIGHT_VEC * DELTA;
  u.normalize();
}

qxgl::Vetor3D CameraJogo::getPickedPoint( GLfloat x, GLfloat y ) {
  const auto Z_AXIS = ( e - c ).get_unit();       // Vetor "para frente" da câmera
  const auto X_AXIS = ( u ^ Z_AXIS ).get_unit();  // Vetor "para a direita" da câmera
  const auto Y_AXIS = u;                          // O vetor 'up' da câmera já é o eixo Y local

  const auto WORLD_OFFSET = ( X_AXIS * x ) + ( Y_AXIS * y ) - ( Z_AXIS * 1.0F );

  return e + WORLD_OFFSET;
}
