#ifndef CAMERADISTANTE_H
#define CAMERADISTANTE_H

#include "Camera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class CameraDistante : public Camera {
public:
  CameraDistante();
  CameraDistante( Vetor3D e, Vetor3D c, Vetor3D u );
  CameraDistante( GLfloat ex,
                  GLfloat ey,
                  GLfloat ez,
                  GLfloat cx,
                  GLfloat cy,
                  GLfloat cz,
                  GLfloat ux,
                  GLfloat uy,
                  GLfloat uz );
  ~CameraDistante() = default;

  void    zoom( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
  void    translatex( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
  void    translatey( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
  void    rotatex( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
  void    rotatey( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
  void    rotatez( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
  Vetor3D getPickedPoint( GLfloat /*unused*/, GLfloat /*unused*/ ) override;
};

#endif
