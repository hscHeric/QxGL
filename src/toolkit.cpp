#include "toolkit.hpp"

#include "draw.hpp"
#include "state.hpp"
#include "vector_3d.hpp"

#include <GL/gl.h>
#include <GL/glut.h>
#include <array>
#include <cmath>

namespace qxgl {
  void ToolKit::display_init() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    const float AR = State::height > 0
                     ? static_cast<float>( State::width ) / static_cast<float>( State::height )
                     : 1.0F;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    if ( State::is_perspective ) {
      float fov = State::use_vanishing_points ? 150.0F : 30.0F;
      gluPerspective( fov, AR, 0.1, 1000.0 );
    } else {
      if ( State::is_ortho ) {
        float w = State::width;
        float h = State::height;
        float f = State::ortho_factor;
        glOrtho( -f * w, f * w, -f * h, f * h, 0.1, 1000.0 );
      } else {  // Projeção Oblíqua
        float s          = 5.0F;
        float near_plane = 0.1F;
        float far_plane  = 100.0F;
        glOrtho( -s, s, -s * AR, s * AR, near_plane, far_plane );

        float alpha = deg_to_rad( 75.0F );
        float phi   = deg_to_rad( -75.0F );

        // CORREÇÃO: A matriz é definida em row-major e usamos a função de transposição.
        GLdouble shear_matrix[16] = { 1.0,
                                      0.0,
                                      1.0 / std::tan( alpha ),
                                      0.0,
                                      0.0,
                                      1.0,
                                      1.0 / std::tan( phi ),
                                      0.0,
                                      0.0,
                                      0.0,
                                      1.0,
                                      0.0,
                                      0.0,
                                      0.0,
                                      0.0,
                                      1.0 };
        mult_transpose_matrix_d( shear_matrix );  // Usando a função correta
      }
    }

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glViewport( 0, 0, State::width, State::height );

    if ( State::cam ) {
      gluLookAt( State::cam->get_eye().x,
                 State::cam->get_eye().y,
                 State::cam->get_eye().z,
                 State::cam->get_center().x,
                 State::cam->get_center().y,
                 State::cam->get_center().z,
                 State::cam->get_up().x,
                 State::cam->get_up().y,
                 State::cam->get_up().z );
    }
  }

  void ToolKit::display_end() {
    glutSwapBuffers();
  }

  void ToolKit::set_light( int   id,
                           float posx,
                           float posy,
                           float posz,
                           bool  on_off_key_default,
                           bool  attenuated,
                           bool  low,
                           bool  hidden,
                           bool  pontual,
                           bool  spot,
                           bool  on_off_user_control ) {
    if ( id < 0 || id > 7 )
      return;

    if ( !on_off_key_default ) {
      State::is_light_enabled[id] = on_off_user_control;
    }
    State::is_light_hidden[id] = hidden;
    State::is_light_point[id]  = pontual;
    State::is_light_spot[id]   = spot;

    GLenum light_id = GL_LIGHT0 + id;
    if ( State::is_lighting_enabled && State::is_light_enabled[id] ) {
      glEnable( light_id );
    } else {
      glDisable( light_id );
    }

    GLfloat ambient[]  = { 0.2F, 0.2F, 0.2F, 1.0F };
    GLfloat diffuse[]  = { 0.7F, 0.7F, 0.7F, 1.0F };
    GLfloat specular[] = { 0.7F, 0.7F, 0.7F, 1.0F };
    if ( low ) {
      ambient[0] = ambient[1] = ambient[2] = 0.02F;
      diffuse[0] = diffuse[1] = diffuse[2] = 0.4F;
      specular[0] = specular[1] = specular[2] = 0.5F;
    }
    glLightfv( light_id, GL_AMBIENT, ambient );
    glLightfv( light_id, GL_DIFFUSE, diffuse );
    glLightfv( light_id, GL_SPECULAR, specular );

    GLfloat pos[] = { posx + State::light_position_offset.x,
                      posy + State::light_position_offset.y,
                      posz + State::light_position_offset.z,
                      State::is_light_point[id] ? 1.0F : 0.0F };
    glLightfv( light_id, GL_POSITION, pos );

    if ( State::is_lighting_enabled && State::is_light_enabled[id] &&
         !State::is_light_hidden[id] ) {
      glPushAttrib( GL_LIGHTING_BIT );
      glDisable( GL_LIGHTING );
      glColor3f( 1.0F, 1.0F, 1.0F );
      glPushMatrix();
      glTranslatef( pos[0], pos[1], pos[2] );
      glutSolidSphere( 0.05, State::slices, State::stacks );
      glPopMatrix();
      glPopAttrib();
    }

    if ( spot ) {
      const GLfloat LIGHT_DIRECTION[] = { 0.0F, 0.0F, -1.0F, 1.0F };
      glLightfv( light_id, GL_SPOT_DIRECTION, LIGHT_DIRECTION );
      glLightf( light_id, GL_SPOT_CUTOFF, State::spot_angle );
    } else {
      glLightf( light_id, GL_SPOT_CUTOFF, 180.0F );
    }

    glLightf( light_id, GL_CONSTANT_ATTENUATION, attenuated ? 2.0F : 1.0F );
    glLightf( light_id, GL_LINEAR_ATTENUATION, attenuated ? 1.0F : 0.0F );
    glLightf( light_id, GL_QUADRATIC_ATTENUATION, attenuated ? 0.5F : 0.0F );
  }

  void ToolKit::set_color( float r, float g, float b, float a, bool specular ) {
    GLfloat mat_ambient[]      = { 0.6F * r, 0.6F * g, 0.6F * b, a };
    GLfloat mat_diffuse[]      = { r, g, b, a };
    GLfloat mat_specular_val[] = { 0.0F, 0.0F, 0.0F, a };
    if ( specular ) {
      mat_specular_val[0] = mat_specular_val[1] = mat_specular_val[2] = 1.0F;
    }
    GLfloat high_shininess[] = { 100.0F };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular_val );
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
  }

  void ToolKit::mult_transpose_matrix_f( GLfloat *m ) {
    GLfloat m_transposed[16];
    for ( int i = 0; i < 4; ++i ) {
      for ( int j = 0; j < 4; ++j ) {
        m_transposed[( i * 4 ) + j] = m[( j * 4 ) + i];
      }
    }
    glMultMatrixf( m_transposed );
  }

  void ToolKit::mult_transpose_matrix_d( GLdouble *m ) {
    GLdouble m_transposed[16];
    for ( int i = 0; i < 4; ++i ) {
      for ( int j = 0; j < 4; ++j ) {
        m_transposed[( i * 4 ) + j] = m[( j * 4 ) + i];
      }
    }
    glMultMatrixd( m_transposed );
  }

  void ToolKit::draw_sphere( float x, float y, float z, float radius ) {
    GLUquadric *quad = gluNewQuadric();
    gluQuadricDrawStyle( quad, GLU_FILL );
    gluQuadricNormals( quad, GLU_SMOOTH );
    gluQuadricTexture( quad, GL_TRUE );

    glPushMatrix();
    glTranslatef( x, y, z );
    gluSphere( quad, radius, State::slices, State::stacks );
    glPopMatrix();

    gluDeleteQuadric( quad );
  }

  void ToolKit::draw_box(
    float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool inverted ) {
    if ( inverted ) {
      glPushAttrib( GL_POLYGON_BIT );
      glCullFace( GL_FRONT );
      Drawing::draw_box( xmin, ymin, zmin, xmax, ymax, zmax );
      glPopAttrib();
    } else {
      Drawing::draw_box( xmin, ymin, zmin, xmax, ymax, zmax );
    }
  }

  void ToolKit::draw_floor( float width, float height ) {
    glPushMatrix();
    glTranslated( 0.0, -0.001, 0.0 );
    glBegin( GL_QUADS );
    glNormal3f( 0.0F, 1.0F, 0.0F );
    glTexCoord2f( 0.0F, height );
    glVertex3f( -width / 2, 0.0F, height / 2 );
    glTexCoord2f( width, height );
    glVertex3f( width / 2, 0.0F, height / 2 );
    glTexCoord2f( width, 0.0F );
    glVertex3f( width / 2, 0.0F, -height / 2 );
    glTexCoord2f( 0.0F, 0.0F );
    glVertex3f( -width / 2, 0.0F, -height / 2 );
    glEnd();
    glPopMatrix();
  }

  void ToolKit::draw_origin( float size ) {
    if ( State::show_global_axes ) {
      Drawing::draw_axes( size );
    }
  }

  void ToolKit::enable_texture( bool render_texture, bool texture_automatic, TextureGenMode mode ) {
    if ( !render_texture )
      return;

    glEnable( GL_TEXTURE_2D );
    if ( texture_automatic ) {
      glEnable( GL_TEXTURE_GEN_S );
      glEnable( GL_TEXTURE_GEN_T );

      GLenum gl_mode = GL_EYE_LINEAR;
      switch ( mode ) {
        case TextureGenMode::OBJECT   : gl_mode = GL_OBJECT_LINEAR; break;
        case TextureGenMode::SphereMap: gl_mode = GL_SPHERE_MAP; break;
        case TextureGenMode::EYE      :
        default                       : gl_mode = GL_EYE_LINEAR; break;
      }
      glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, gl_mode );
      glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, gl_mode );
    }
  }

  void ToolKit::disable_texture( bool render_texture, bool texture_automatic ) {
    if ( !render_texture ) {
      return;
    }

    glDisable( GL_TEXTURE_2D );
    if ( texture_automatic ) {
      glDisable( GL_TEXTURE_GEN_S );
      glDisable( GL_TEXTURE_GEN_T );
    }
  }

}  // namespace qxgl
