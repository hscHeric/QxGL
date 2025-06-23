#include "draw.hpp"

#include <memory>

namespace qxgl::Drawing {

  void
    draw_box( GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax ) {
    glBegin( GL_QUADS );
    glNormal3f( 0.F, 0.F, -1.F );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( xmin, ymin, zmin );
    glTexCoord2f( 1.0F, 0.0F );
    glVertex3f( xmin, ymax, zmin );
    glTexCoord2f( 1.0F, 1.0F );
    glVertex3f( xmax, ymax, zmin );
    glTexCoord2f( 0.0F, 1.0F );
    glVertex3f( xmax, ymin, zmin );
    glEnd();

    glBegin( GL_QUADS );
    glNormal3f( 1.F, 0.F, 0.F );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( xmax, ymin, zmin );
    glTexCoord2f( 1.0F, 0.0F );
    glVertex3f( xmax, ymax, zmin );
    glTexCoord2f( 1.0F, 1.0F );
    glVertex3f( xmax, ymax, zmax );
    glTexCoord2f( 0.0F, 1.0F );
    glVertex3f( xmax, ymin, zmax );
    glEnd();

    glBegin( GL_QUADS );
    glNormal3f( 0.F, 0.F, 1.F );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( xmax, ymin, zmax );
    glTexCoord2f( 1.0F, 0.0F );
    glVertex3f( xmax, ymax, zmax );
    glTexCoord2f( 1.0F, 1.0F );
    glVertex3f( xmin, ymax, zmax );
    glTexCoord2f( 0.0F, 1.0F );
    glVertex3f( xmin, ymin, zmax );
    glEnd();

    glBegin( GL_QUADS );
    glNormal3f( -1.F, 0.F, 0.F );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( xmin, ymin, zmax );
    glTexCoord2f( 1.0F, 0.0F );
    glVertex3f( xmin, ymax, zmax );
    glTexCoord2f( 1.0F, 1.0F );
    glVertex3f( xmin, ymax, zmin );
    glTexCoord2f( 0.0F, 1.0F );
    glVertex3f( xmin, ymin, zmin );
    glEnd();

    glBegin( GL_QUADS );
    glNormal3f( 0.F, 1.F, 0.F );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( xmin, ymax, zmin );
    glTexCoord2f( 1.0F, 0.0F );
    glVertex3f( xmin, ymax, zmax );
    glTexCoord2f( 1.0F, 1.0F );
    glVertex3f( xmax, ymax, zmax );
    glTexCoord2f( 0.0F, 1.0F );
    glVertex3f( xmax, ymax, zmin );
    glEnd();

    glBegin( GL_QUADS );
    glNormal3f( 0.F, -1.F, 0.F );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( xmax, ymin, zmin );
    glTexCoord2f( 1.0F, 0.0F );
    glVertex3f( xmax, ymin, zmax );
    glTexCoord2f( 1.0F, 1.0F );
    glVertex3f( xmin, ymin, zmax );
    glTexCoord2f( 0.0F, 1.0F );
    glVertex3f( xmin, ymin, zmin );
    glEnd();
  }

  void draw_wire_box(
    GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax ) {
    glBegin( GL_LINES );
    glVertex3f( xmin, ymin, zmin );
    glVertex3f( xmax, ymin, zmin );
    glVertex3f( xmax, ymin, zmin );
    glVertex3f( xmax, ymax, zmin );
    glVertex3f( xmax, ymax, zmin );
    glVertex3f( xmin, ymax, zmin );
    glVertex3f( xmin, ymax, zmin );
    glVertex3f( xmin, ymin, zmin );
    glVertex3f( xmin, ymin, zmax );
    glVertex3f( xmax, ymin, zmax );
    glVertex3f( xmax, ymin, zmax );
    glVertex3f( xmax, ymax, zmax );
    glVertex3f( xmax, ymax, zmax );
    glVertex3f( xmin, ymax, zmax );
    glVertex3f( xmin, ymax, zmax );
    glVertex3f( xmin, ymin, zmax );
    glVertex3f( xmin, ymin, zmin );
    glVertex3f( xmin, ymin, zmax );
    glVertex3f( xmax, ymin, zmin );
    glVertex3f( xmax, ymin, zmax );
    glVertex3f( xmax, ymax, zmin );
    glVertex3f( xmax, ymax, zmax );
    glVertex3f( xmin, ymax, zmin );
    glVertex3f( xmin, ymax, zmax );
    glEnd();
  }

  void draw_selected_box(
    GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax ) {
    const float DX = ( xmax - xmin ) / 8.0F;
    const float DY = ( ymax - ymin ) / 8.0F;
    const float DZ = ( zmax - zmin ) / 8.0F;

    glBegin( GL_LINES );
    glVertex3f( xmin, ymin, zmin );
    glVertex3f( xmin + DX, ymin, zmin );
    glVertex3f( xmax - DX, ymin, zmin );
    glVertex3f( xmax, ymin, zmin );
    glVertex3f( xmax, ymin, zmin );
    glVertex3f( xmax, ymin + DY, zmin );
    glVertex3f( xmax, ymax - DY, zmin );
    glVertex3f( xmax, ymax, zmin );
    glVertex3f( xmax, ymax, zmin );
    glVertex3f( xmax - DX, ymax, zmin );
    glVertex3f( xmin + DX, ymax, zmin );
    glVertex3f( xmin, ymax, zmin );
    glVertex3f( xmin, ymax, zmin );
    glVertex3f( xmin, ymax - DY, zmin );
    glVertex3f( xmin, ymin + DY, zmin );
    glVertex3f( xmin, ymin, zmin );
    glVertex3f( xmin, ymin, zmax );
    glVertex3f( xmin + DX, ymin, zmax );
    glVertex3f( xmax - DX, ymin, zmax );
    glVertex3f( xmax, ymin, zmax );
    glVertex3f( xmax, ymin, zmax );
    glVertex3f( xmax, ymin + DY, zmax );
    glVertex3f( xmax, ymax - DY, zmax );
    glVertex3f( xmax, ymax, zmax );
    glVertex3f( xmax, ymax, zmax );
    glVertex3f( xmax - DX, ymax, zmax );
    glVertex3f( xmin + DX, ymax, zmax );
    glVertex3f( xmin, ymax, zmax );
    glVertex3f( xmin, ymax, zmax );
    glVertex3f( xmin, ymax - DY, zmax );
    glVertex3f( xmin, ymin + DY, zmax );
    glVertex3f( xmin, ymin, zmax );
    glVertex3f( xmin, ymin, zmin );
    glVertex3f( xmin, ymin, zmin + DZ );
    glVertex3f( xmin, ymin, zmax - DZ );
    glVertex3f( xmin, ymin, zmax );
    glVertex3f( xmax, ymin, zmin );
    glVertex3f( xmax, ymin, zmin + DZ );
    glVertex3f( xmax, ymin, zmax - DZ );
    glVertex3f( xmax, ymin, zmax );
    glVertex3f( xmax, ymax, zmin );
    glVertex3f( xmax, ymax, zmin + DZ );
    glVertex3f( xmax, ymax, zmax - DZ );
    glVertex3f( xmax, ymax, zmax );
    glVertex3f( xmin, ymax, zmin );
    glVertex3f( xmin, ymax, zmin + DZ );
    glVertex3f( xmin, ymax, zmax - DZ );
    glVertex3f( xmin, ymax, zmax );
    glEnd();
  }

  void draw_quad( GLfloat xmin, GLfloat y, GLfloat zmin, GLfloat side_length ) {
    glBegin( GL_LINES );
    glVertex3f( xmin, y, zmin );
    glVertex3f( xmin, y, zmin + side_length );
    glVertex3f( xmin, y, zmin + side_length );
    glVertex3f( xmin + side_length, y, zmin + side_length );
    glVertex3f( xmin + side_length, y, zmin + side_length );
    glVertex3f( xmin + side_length, y, zmin );
    glVertex3f( xmin + side_length, y, zmin );
    glVertex3f( xmin, y, zmin );
    glEnd();
  }

  void draw_grid( int half_nx, GLfloat y, int half_nz, int dimension ) {
    glPushMatrix();
    for ( int i = -half_nx * dimension; i <= ( half_nx - 1 ) * dimension; i += dimension ) {
      for ( int k = -half_nz * dimension; k <= ( half_nz - 1 ) * dimension; k += dimension ) {
        draw_quad( static_cast<GLfloat>( i ),
                   y,
                   static_cast<GLfloat>( k ),
                   static_cast<GLfloat>( dimension ) );
      }
    }
    glPopMatrix();
  }

  void draw_closed_cylinder(
    GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks ) {
    gluQuadricNormals( quad, GLU_SMOOTH );
    gluQuadricTexture( quad, GL_TRUE );
    glPushMatrix();
    gluCylinder( quad, base, top, height, slices, stacks );
    glTranslated( 0, 0, height );
    gluDisk( quad, 0, top, slices, stacks );
    glRotated( 180, 0, 1, 0 );
    glTranslated( 0, 0, height );
    gluDisk( quad, 0, base, slices, stacks );
    glPopMatrix();
  }

  void draw_capsule(
    GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks ) {
    gluQuadricNormals( quad, GLU_SMOOTH );
    gluQuadricTexture( quad, GL_TRUE );
    glPushMatrix();
    gluCylinder( quad, base, top, height, slices, stacks );
    gluSphere( quad, base, slices, stacks );
    glTranslated( 0, 0, height );
    gluSphere( quad, top, slices, stacks );
    glPopMatrix();
  }

  void draw_axes( GLfloat size ) {
    const GLfloat RED[]   = { 0.8F, 0.1F, 0.1F, 1.0F };
    const GLfloat GREEN[] = { 0.1F, 0.8F, 0.1F, 1.0F };
    const GLfloat BLUE[]  = { 0.1F, 0.1F, 0.8F, 1.0F };

    // RAII para o objeto GLUquadric. Garante que gluDeleteQuadric é chamado.
    std::unique_ptr<GLUquadric, decltype( &gluDeleteQuadric )> quad( gluNewQuadric(),
                                                                     &gluDeleteQuadric );

    glPushAttrib( GL_LINE_BIT | GL_ENABLE_BIT );
    glLineWidth( 2.0F );
    glDisable( GL_LIGHTING );

    // Eixo X (Vermelho)
    glColor3fv( RED );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( size, 0, 0 );
    glEnd();
    glPushMatrix();
    glTranslatef( size, 0, 0 );
    glRotatef( 90, 0, 1, 0 );
    draw_closed_cylinder( quad.get(), 0.05F * size, 0, 0.15F * size, 10, 10 );
    glPopMatrix();

    // Eixo Y (Verde)
    glColor3fv( GREEN );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, size, 0 );
    glEnd();
    glPushMatrix();
    glTranslatef( 0, size, 0 );
    glRotatef( -90, 1, 0, 0 );
    draw_closed_cylinder( quad.get(), 0.05F * size, 0, 0.15F * size, 10, 10 );
    glPopMatrix();

    // Eixo Z (Azul)
    glColor3fv( BLUE );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, size );
    glEnd();
    glPushMatrix();
    glTranslatef( 0, 0, size );
    draw_closed_cylinder( quad.get(), 0.05F * size, 0, 0.15F * size, 10, 10 );
    glPopMatrix();

    glPopAttrib();
  }

  void apply_ode_transform( const float *pos, const float *R ) {
    GLfloat matrix[16] = { R[0], R[4], R[8],  0.0F, R[1],   R[5],   R[9],   0.0F,
                           R[2], R[6], R[10], 0.0F, pos[0], pos[1], pos[2], 1.0F };
    glMultMatrixf( matrix );
  }

}  // namespace qxgl::Drawing
