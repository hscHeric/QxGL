#include "camera.hpp"

Camera::Camera() : estilo( 0 ) {
  e = qxgl::Vetor3D();
  c = qxgl::Vetor3D();
  u = qxgl::Vetor3D();

  e.x = 0;
  e.y = 1;
  e.z = 10;

  c.x = 0;
  c.y = 1;

  u.x = 0;
  u.y = 1;
  u.z = 0;
}

Camera::Camera( qxgl::Vetor3D e, qxgl::Vetor3D c, qxgl::Vetor3D u ) : estilo( 0 ) {
  this->e = qxgl::Vetor3D();
  this->c = qxgl::Vetor3D();
  this->u = qxgl::Vetor3D();

  this->e.x = e.x;
  this->e.y = e.y;
  this->e.z = e.z;

  this->c.x = c.x;
  this->c.y = c.y;
  this->c.z = c.z;

  this->u.x = u.x;
  this->u.y = u.y;
  this->u.z = u.z;
}

Camera::Camera( GLfloat ex,
                GLfloat ey,
                GLfloat ez,
                GLfloat cx,
                GLfloat cy,
                GLfloat cz,
                GLfloat ux,
                GLfloat uy,
                GLfloat uz )
  : estilo( 0 ) {
  e = qxgl::Vetor3D();
  c = qxgl::Vetor3D();
  u = qxgl::Vetor3D();

  e.x = ex;
  e.y = ey;
  e.z = ez;

  c.x = cx;
  c.y = cy;
  c.z = cz;

  u.x = ux;
  u.y = uy;
  u.z = uz;
}

void Camera::adaptavetorcdisttojogo() {
  c = e + ( c - e ).get_unit();
}

void Camera::adaptavetorcjogotodist( GLfloat r ) {
  c = e + ( c - e ).get_unit() * r;
}
