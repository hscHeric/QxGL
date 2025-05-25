#include "renderer.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace qxgl::renderer {
  void useCamera( const Camera &camera ) {
    glMatrixMode( GL_PROJECTION );
    glLoadMatrixf( glm::value_ptr( camera.getProjectionMatrix() ) );

    glMatrixMode( GL_MODELVIEW );
    glLoadMatrixf( glm::value_ptr( camera.getViewMatrix() ) );
  }

  void beginFrame() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );
    glLoadIdentity();
  }

  void endFrame() {
    glFlush();  // chamar glfwSwapBuffers(janela) fora daqui
  }

  void drawAxis( float length ) {
    glBegin( GL_LINES );

    // Eixo X - Vermelho
    glColor3f( 1.0F, 0.0F, 0.0F );
    glVertex3f( 0.0F, 0.0F, 0.0F );
    glVertex3f( length, 0.0F, 0.0F );

    // Eixo Y - Verde
    glColor3f( 0.0F, 1.0F, 0.0F );
    glVertex3f( 0.0F, 0.0F, 0.0F );
    glVertex3f( 0.0F, length, 0.0F );

    // Eixo Z - Azul
    glColor3f( 0.0F, 0.0F, 1.0F );
    glVertex3f( 0.0F, 0.0F, 0.0F );
    glVertex3f( 0.0F, 0.0F, length );

    glEnd();
  }

  void drawGrid( int size, float step ) {
    glColor3f( 0.7F, 0.7F, 0.7F );
    glBegin( GL_LINES );

    for ( int i = -size; i <= size; ++i ) {
      // Linhas paralelas ao eixo Z
      glVertex3f( step * i, 0.0F, -size * step );
      glVertex3f( i * step, 0.0F, size * step );

      // Linhas paralelas ao eixo X
      glVertex3f( -size * step, 0.0F, i * step );
      glVertex3f( size * step, 0.0F, i * step );
    }

    glEnd();
  }

  void drawLine( const Vector3 &from, const Vector3 &to, const glm::vec3 &color ) {
    glColor3f( color.r, color.g, color.b );
    glBegin( GL_LINES );
    glVertex3fv( glm::value_ptr( from.glm() ) );
    glVertex3fv( glm::value_ptr( to.glm() ) );
    glEnd();
  }

  void drawCube( float size ) {
    float s = size / 2.0F;

    glColor3f( 1.0F, 1.0F, 0.0F );
    glBegin( GL_QUADS );

    // Frente
    glVertex3f( -s, -s, s );
    glVertex3f( s, -s, s );
    glVertex3f( s, s, s );
    glVertex3f( -s, s, s );

    // Trás
    glVertex3f( -s, -s, -s );
    glVertex3f( -s, s, -s );
    glVertex3f( s, s, -s );
    glVertex3f( s, -s, -s );

    // Esquerda
    glVertex3f( -s, -s, -s );
    glVertex3f( -s, -s, s );
    glVertex3f( -s, s, s );
    glVertex3f( -s, s, -s );

    // Direita
    glVertex3f( s, -s, -s );
    glVertex3f( s, s, -s );
    glVertex3f( s, s, s );
    glVertex3f( s, -s, s );

    // Topo
    glVertex3f( -s, s, -s );
    glVertex3f( -s, s, s );
    glVertex3f( s, s, s );
    glVertex3f( s, s, -s );

    // Fundo
    glVertex3f( -s, -s, -s );
    glVertex3f( s, -s, -s );
    glVertex3f( s, -s, s );
    glVertex3f( -s, -s, s );

    glEnd();
  }
}  // namespace qxgl::renderer
