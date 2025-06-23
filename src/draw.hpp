#ifndef DESENHA_H
#define DESENHA_H

#include "vector_3d.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

class Desenha {
public:
  Desenha()  = default;
  ~Desenha() = default;
  static void drawBox( GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
  static void drawWireBox( GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
  static void drawSelectedBox( GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
  static void drawQuad( GLfloat, GLfloat, GLfloat, GLfloat );
  static void drawGrid( int, GLfloat, int, int );
  static void gluClosedCylinder( GLUquadric *, GLdouble, GLdouble, GLdouble, GLint, GLint );
  static void gluCapsule( GLUquadric *, GLdouble, GLdouble, GLdouble, GLint, GLint );
  static void drawArrow( qxgl::Vetor3D from, qxgl::Vetor3D to, GLfloat larg = 0.0 );
  static void drawDoubleArrow( qxgl::Vetor3D from, qxgl::Vetor3D to, GLfloat larg = 0.0 );
  static void drawEixos( GLfloat );

  static void setTransformODE( const float *pos, const float *R );
};

#endif
