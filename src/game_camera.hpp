#ifndef CAMERAJOGO_H
#define CAMERAJOGO_H

#include "camera.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

class CameraJogo : public Camera {
public:
  CameraJogo();
  CameraJogo( qxgl::Vetor3D e, qxgl::Vetor3D c, qxgl::Vetor3D u );
  CameraJogo( GLfloat ex,
              GLfloat ey,
              GLfloat ez,
              GLfloat cx,
              GLfloat cy,
              GLfloat cz,
              GLfloat ux,
              GLfloat uy,
              GLfloat uz );
  ~CameraJogo() {};

  // vetor Vec e u sempre unitarios e perpendiculares
  virtual void          zoom( GLfloat, GLfloat );
  virtual void          translatex( GLfloat, GLfloat );
  virtual void          translatey( GLfloat, GLfloat );
  virtual void          rotatex( GLfloat, GLfloat );
  virtual void          rotatey( GLfloat, GLfloat );
  virtual void          rotatez( GLfloat, GLfloat );
  virtual qxgl::Vetor3D getPickedPoint( GLfloat, GLfloat );
};

#endif
