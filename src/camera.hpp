#ifndef CAMERA_H
#define CAMERA_H

#define CAMDIST 1
#define CAMJOGO 2

#include "vector_3d.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class Camera {
public:
  qxgl::Vetor3D e;
  qxgl::Vetor3D c;
  qxgl::Vetor3D u;

  int estilo;

  Camera();
  Camera( qxgl::Vetor3D e, qxgl::Vetor3D c, qxgl::Vetor3D u );
  Camera( GLfloat ex,
          GLfloat ey,
          GLfloat ez,
          GLfloat cx,
          GLfloat cy,
          GLfloat cz,
          GLfloat ux,
          GLfloat uy,
          GLfloat uz );
  ~Camera() {};

  virtual void          zoom( GLfloat, GLfloat )           = 0;
  virtual void          translatex( GLfloat, GLfloat )     = 0;
  virtual void          translatey( GLfloat, GLfloat )     = 0;
  virtual void          rotatex( GLfloat, GLfloat )        = 0;
  virtual void          rotatey( GLfloat, GLfloat )        = 0;
  virtual void          rotatez( GLfloat, GLfloat )        = 0;
  virtual qxgl::Vetor3D getPickedPoint( GLfloat, GLfloat ) = 0;
  void                  adaptavetorcdisttojogo();
  void                  adaptavetorcjogotodist( GLfloat r );
};

#endif
