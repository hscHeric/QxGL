#include "state.hpp"

#include "camera.hpp"
#include "distant_camera.hpp"
#include "game_camera.hpp"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>

namespace qxgl {

  // --- Inicialização dos Membros Estáticos ---

  // Estado da Janela e Projeção
  int   State::width                = 800;
  int   State::height               = 600;
  bool  State::is_perspective       = true;
  bool  State::use_vanishing_points = false;
  bool  State::is_ortho             = true;
  float State::ortho_factor         = 0.0025F;

  // Estado do Mouse e Interação
  bool                                  State::is_picking               = false;
  bool                                  State::is_left_button_pressed   = false;
  bool                                  State::is_middle_button_pressed = false;
  bool                                  State::is_right_button_pressed  = false;
  bool                                  State::is_mouse_moving          = false;
  std::chrono::steady_clock::time_point State::last_move_time    = std::chrono::steady_clock::now();
  const int                             State::IDLE_THRESHOLD_MS = 100;
  MouseLock                             State::mouse_lock        = MouseLock::NotLocked;
  float                                 State::last_x            = 0.0F;
  float                                 State::last_y            = 0.0F;

  // Câmera
  std::unique_ptr<Camera> State::cam                 = std::make_unique<DistantCamera>();
  std::array<float, 9>    State::saved_camera        = { 5, 5, 20, 0, 0, 0, 0, 1, 0 };
  int                     State::camera_preset_index = 0;

  // Animação Automática da Câmera
  int   State::auto_rotation_counter  = 9999;
  float State::auto_motion_value      = 90.0F;
  Axis  State::auto_motion_axis       = Axis::Y;
  int   State::auto_motion_iterations = 10;

  // Parâmetros de Renderização
  int State::slices = 200;
  int State::stacks = 200;

  // Iluminação
  bool                State::is_lighting_enabled    = true;
  bool                State::is_3d_lighting_enabled = true;  // Equivalente a 'iluminacao3D'
  std::array<bool, 8> State::is_light_enabled = { true, true, true, true, true, true, true, false };
  std::array<bool, 8> State::is_light_hidden  = { false };
  std::array<bool, 8> State::is_light_point   = { true, true, true, true, true, true, true, true };
  std::array<bool, 8> State::is_light_spot    = { false };
  float               State::spot_angle       = 25.0F;
  bool                State::show_light_transform_guides = false;

  // Transparência e Viewports
  bool  State::is_object_transparent  = false;
  float State::object_alpha           = 0.5F;
  bool  State::use_multiple_viewports = false;
  bool  State::show_global_axes       = true;

  // Transformações de Objeto/Cena
  bool    State::is_transforming_object = false;
  Vetor3D State::object_position        = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::object_rotation        = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::object_scale           = { 1.0F, 1.0F, 1.0F };
  Vetor3D State::light_position_offset  = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::d_object_translation   = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::d_object_rotation      = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::d_object_scale         = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::d_camera_rotation      = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::d_camera_pan           = { 0.0F, 0.0F, 0.0F };
  Vetor3D State::d_camera_zoom          = { 0.0F, 0.0F, 0.0F };

  void State::resize( int w, int h ) {
    width  = w;
    height = h;
  }

  void State::default_display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    const float ar = height > 0 ? (float)width / (float)height : 1.0;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 30., ar, 0.1, 1000. );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glViewport( 0, 0, width, height );
    glLoadIdentity();
    gluLookAt( cam->get_eye().x,
               cam->get_eye().y,
               cam->get_eye().z,
               cam->get_center().x,
               cam->get_center().y,
               cam->get_center().z,
               cam->get_up().x,
               cam->get_up().y,
               cam->get_up().z );

    // LIGHT0
    glEnable( GL_LIGHT0 );
    GLfloat light_ambient[]  = { 0.2F, 0.2F, 0.2F, 1.0F };
    GLfloat light_diffuse[]  = { 0.7F, 0.7F, 0.7F, 1.0F };
    GLfloat light_specular[] = { 0.7F, 0.7F, 0.7F, 1.0F };
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    GLfloat light_position[] = { 0.0F, 1.0F, 0.0F, 1.0F };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );

    glDisable( GL_LIGHTING );
    glColor4f( 1.0, 1.0, 1.0, 1.0 );
    glPushMatrix();
    glTranslatef( light_position[0], light_position[1], light_position[2] );
    glutSolidSphere( 0.02, slices, stacks );
    glPopMatrix();
    glEnable( GL_LIGHTING );

    GLfloat mat_ambient[]    = { 0.4F, 0.2F, 0.1F, 1.0F };
    GLfloat mat_diffuse[]    = { 0.8F, 0.4F, 0.1F, 1.0F };
    GLfloat mat_specular[]   = { 1.0F, 1.0F, 1.0F, 1.0F };
    GLfloat high_shininess[] = { 100.0F };
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );

    glDisable( GL_CULL_FACE );
    glPushMatrix();
    glTranslated( 0., -0.0001, 0. );
    float quad_width   = 5.0F;
    float quad_height  = 5.0F;
    float discr_width  = 1.0F;
    float discr_height = 1.0F;
    for ( float i = -0.5F * quad_width; i < 0.5F * quad_width; i += discr_width ) {
      for ( float j = -0.5F * quad_height; j < 0.5F * quad_height; j += discr_height ) {
        glPushMatrix();
        glTranslatef( i, 0.0, j );
        glBegin( GL_QUADS );
        glNormal3f( 0., 1., 0. );
        glVertex3f( 0.0, 0.0, discr_height );
        glVertex3f( discr_width, 0.0, discr_height );
        glVertex3f( discr_width, 0.0, 0.0 );
        glVertex3f( 0.0, 0.0, 0.0 );
        glEnd();
        glPopMatrix();
      }
    }
    glPopMatrix();
    glEnable( GL_CULL_FACE );

    glutSwapBuffers();
  }

  void State::change_camera() {
    camera_preset_index = ( camera_preset_index ) % 16;

    // Usar std::make_unique para criar a nova câmera
    switch ( camera_preset_index ) {
      case 0:
        is_perspective       = true;
        use_vanishing_points = false;
        cam                  = std::make_unique<DistantCamera>();
        break;
      case 1:
        is_perspective = false;
        is_ortho       = true;
        cam            = std::make_unique<DistantCamera>( 0, 1, 5, 0, 1, 0, 0, 1, 0 );
        break;
      // ... outros casos ...
      case 15:
        is_perspective       = true;
        use_vanishing_points = false;
        cam                  = std::make_unique<DistantCamera>( saved_camera[0],
                                               saved_camera[1],
                                               saved_camera[2],
                                               saved_camera[3],
                                               saved_camera[4],
                                               saved_camera[5],
                                               saved_camera[6],
                                               saved_camera[7],
                                               saved_camera[8] );
        break;
      default:  // Adicionado para cobrir todos os casos
        break;
    }
    ortho_factor = 0.00025F * ( cam->get_center() - cam->get_eye() ).magnitude();
  }

  void State::default_key( unsigned char key, int x, int y ) {
    switch ( key ) {
      case 27:
      case 13:
      case 'q': exit( 0 ); break;
      case 'F': glutFullScreen(); break;
      case 'f': glutReshapeWindow( 800, 600 ); break;
      case 'o': is_perspective = !is_perspective; break;
      case 'O':
        is_ortho             = !is_ortho;
        use_vanishing_points = !use_vanishing_points;
        break;
      case '0' ... '7': is_light_enabled[key - '0'] = !is_light_enabled[key - '0']; break;
      case 'c':
        camera_preset_index = ( camera_preset_index - 1 + 16 ) % 16;
        change_camera();
        break;
      case 'C':
        camera_preset_index = ( camera_preset_index + 1 ) % 16;
        change_camera();
        break;
      case 'j':
        camera_preset_index = 1;  // Para consistência
        cam                 = std::make_unique<GameCamera>();
        break;
      case 's':
        saved_camera = { cam->get_eye().x,    cam->get_eye().y,    cam->get_eye().z,
                         cam->get_center().x, cam->get_center().y, cam->get_center().z,
                         cam->get_up().x,     cam->get_up().y,     cam->get_up().z };
        break;
      case 'm': mouse_lock = MouseLock( ( int( mouse_lock ) + 1 ) % 3 ); break;
      case 'i':  // Resetar transformações
        object_position       = { 0.0F, 0.0F, 0.0F };
        object_rotation       = { 0.0F, 0.0F, 0.0F };
        object_scale          = { 1.0F, 1.0F, 1.0F };
        light_position_offset = { 0.0F, 0.0F, 0.0F };
        break;
      case '=':
        slices += 5;
        stacks += 5;
        break;
      case '-':
        slices -= 5;
        stacks -= 5;
        break;
      case 'X': auto_cam_move( -90, Axis::X, auto_motion_iterations ); break;
      case 'x': auto_cam_move( 90, Axis::X, auto_motion_iterations ); break;
      case 'Y': auto_cam_move( 90, Axis::Y, auto_motion_iterations ); break;
      case 'y': auto_cam_move( -90, Axis::Y, auto_motion_iterations ); break;
      case 'Z': auto_cam_move( 2, Axis::Z, auto_motion_iterations ); break;
      case 'z': auto_cam_move( -2, Axis::Z, auto_motion_iterations ); break;
    }
    glutPostRedisplay();
  }

  void State::auto_cam_move( float value, Axis axis, int n_iterations ) {
    if ( axis == Axis::Z && value < 0 &&
         cam->get_eye().get_distance( cam->get_center() ) <= 1.001F ) {
      return;
    }
    if ( axis == Axis::Y && fabs( cam->get_up().y ) <= 0.1F ) {
      return;
    }
    auto_rotation_counter  = 0;
    auto_motion_value      = value;
    auto_motion_axis       = axis;
    auto_motion_iterations = n_iterations;
  }

  void State::auto_cam_motion( float value, Axis axis, int n_iterations ) {
    // O valor 237.58 era o HALF_PI original. A lógica é preservada.
    const float ROTATION_FACTOR = 237.58F / 90.0F;
    switch ( axis ) {
      case Axis::X:
        if ( auto_rotation_counter < n_iterations ) {
          cam->rotate_x( 0, ROTATION_FACTOR * value / n_iterations );
          auto_rotation_counter++;
        }
        break;
      case Axis::Y:
        if ( auto_rotation_counter < n_iterations ) {
          cam->rotate_y( 0, ROTATION_FACTOR * value / n_iterations );
          auto_rotation_counter++;
        }
        break;
      case Axis::Z:
        if ( auto_rotation_counter < n_iterations ) {
          cam->zoom( 0, 20.0f * value / n_iterations );
          auto_rotation_counter++;
        }
        break;
    }
  }

  void State::check_mouse_idle() {
    auto now = std::chrono::steady_clock::now();
    auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>( now - last_move_time ).count();
    if ( duration > IDLE_THRESHOLD_MS && is_mouse_moving ) {
      is_mouse_moving = false;
    }
  }

  void State::idle() {
    check_mouse_idle();
    if ( !is_mouse_moving ) {
      d_object_translation = { 0.0F, 0.0F, 0.0F };
      d_object_rotation    = { 0.0F, 0.0F, 0.0F };
      d_object_scale       = { 0.0F, 0.0F, 0.0F };
      d_camera_rotation    = { 0.0F, 0.0F, 0.0F };
      d_camera_pan         = { 0.0F, 0.0F, 0.0F };
      d_camera_zoom        = { 0.0F, 0.0F, 0.0F };
    }
    glutPostRedisplay();
  }

  void State::timer( int time ) {
    auto_cam_motion( auto_motion_value, auto_motion_axis, auto_motion_iterations );
    glutPostRedisplay();
    glutTimerFunc( 16, State::timer, 0 );
  }

  void State::default_mouse_button( int button, int state, int x, int y ) {
    d_object_translation = d_object_rotation = d_object_scale = { 0, 0, 0 };
    d_camera_rotation = d_camera_pan = d_camera_zoom = { 0, 0, 0 };

    if ( button == GLUT_LEFT_BUTTON ) {
      is_left_button_pressed = ( state == GLUT_DOWN );
    }
    if ( button == GLUT_MIDDLE_BUTTON ) {
      is_middle_button_pressed = ( state == GLUT_DOWN );
    }
    if ( button == GLUT_RIGHT_BUTTON ) {
      is_right_button_pressed = ( state == GLUT_DOWN );
    }

    last_x = x;
    last_y = y;
  }

  void State::mouse_move( int x, int y ) {
    if ( MouseLock::OnlyX == mouse_lock ) {
      last_y = y;
    }
    if ( MouseLock::OnlyY == mouse_lock ) {
      last_x = x;
    }

    last_move_time  = std::chrono::steady_clock::now();
    is_mouse_moving = true;

    // Zerar deltas
    d_object_translation = d_object_rotation = d_object_scale = { 0, 0, 0 };
    d_camera_rotation = d_camera_pan = d_camera_zoom = { 0, 0, 0 };

    const float DELTA_X = x - last_x;
    const float DELTA_Y = y - last_y;

    // Lógica de controle do mouse preservada
    if ( is_left_button_pressed && !is_right_button_pressed && !is_middle_button_pressed ) {
      if ( !is_transforming_object && ( !show_light_transform_guides || !is_object_transparent ) ) {
        cam->rotate_x( y, last_y );
        cam->rotate_y( x, last_x );
      }
      if ( is_transforming_object ) {
        d_camera_pan.y = d_object_rotation.x = DELTA_Y / 10.0F;
        d_camera_pan.x = d_object_rotation.y = DELTA_X / 10.0F;
        object_rotation.x += d_object_rotation.x;
        object_rotation.y += d_object_rotation.y;
      }
      if ( show_light_transform_guides && is_object_transparent ) {
        object_alpha -= DELTA_Y / 100.0F;
        object_alpha = std::max( object_alpha, 0.0F );
        object_alpha = std::min( object_alpha, 1.0F );
      }
    }

    if ( !is_left_button_pressed && is_right_button_pressed && !is_middle_button_pressed ) {
      if ( !is_transforming_object && !show_light_transform_guides ) {
        cam->translate_x( x, last_x );
        cam->translate_y( y, last_y );
      }
      if ( is_transforming_object ) {
        d_camera_rotation.x = d_object_translation.x = DELTA_X / 100.0F;
        d_camera_rotation.y = d_object_translation.y = -DELTA_Y / 100.0F;
        object_position.x += d_object_translation.x;
        object_position.y += d_object_translation.y;
      }
      if ( show_light_transform_guides ) {
        light_position_offset.x += DELTA_X / 100.0F;
        light_position_offset.y += -DELTA_Y / 100.0F;
      }
    }

    if ( is_left_button_pressed && is_right_button_pressed && !is_middle_button_pressed ) {
      if ( !is_transforming_object && !show_light_transform_guides ) {
        cam->zoom( y, last_y );
        ortho_factor = 0.00025F * ( cam->get_center() - cam->get_eye() ).magnitude();
      }
      if ( is_transforming_object ) {
        d_camera_rotation.z = d_object_translation.z = DELTA_Y / 100.0F;
        object_position.z += d_object_translation.z;
        d_camera_pan.z = d_object_rotation.z = -DELTA_X / 10.0F;
        object_rotation.z += d_object_rotation.z;
      }
      if ( show_light_transform_guides ) {
        light_position_offset.z += DELTA_Y / 100.0F;
        spot_angle += -DELTA_X / 10.0F;
      }
    }

    if ( !is_left_button_pressed && !is_right_button_pressed && is_middle_button_pressed ) {
      if ( is_transforming_object ) {
        d_camera_zoom.x = d_object_scale.x = DELTA_X / 100.0F;
        d_camera_zoom.y = d_object_scale.y = -DELTA_Y / 100.0F;
        object_scale.x += d_object_scale.x;
        object_scale.y += d_object_scale.y;
      }
    }

    if ( is_left_button_pressed && !is_right_button_pressed && is_middle_button_pressed ) {
      if ( is_transforming_object ) {
        d_camera_zoom.z = d_object_scale.z = DELTA_Y / 100.0F;
        object_scale.z += d_object_scale.z;
      }
    }

    last_x = x;
    last_y = y;
  }

  // O restante das funções utilitárias
  void State::multiply_matrix_by_vector( float       result[4],
                                         const float matrix[16],
                                         const float vector[4] ) {
    for ( int i = 0; i < 4; ++i ) {
      result[i] = 0.0f;
      for ( int j = 0; j < 4; ++j ) {
        result[i] += matrix[( j * 4 ) + i] * vector[j];  // Column-major
      }
    }
  }

  void State::show_matrix_in_2d( const float matrix[16] ) {
    for ( int i = 0; i < 4; ++i ) {
      for ( int j = 0; j < 4; ++j ) {
        std::cout << std::fixed << std::setprecision( 2 ) << matrix[( j * 4 ) + i] << "  ";
      }
      std::cout << "\n";
    }
  }

  void State::apply_composite_transform() {
    glTranslated( object_position.x, object_position.y, 0.0 );
    glRotated( object_rotation.z, 0, 0, 1 );
    glScaled( object_scale.x, object_scale.y, 1.0 );
  }

  void State::show_local_and_global_coords( float local_point[4] ) {
    std::cout << "Coords locais: " << local_point[0] << ", " << local_point[1] << ", "
              << local_point[2] << "\n";

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();

    apply_composite_transform();

    float composite_matrix[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, composite_matrix );
    show_matrix_in_2d( composite_matrix );

    float global_point[4];
    multiply_matrix_by_vector( global_point, composite_matrix, local_point );
    std::cout << "Coords globais: " << global_point[0] << ", " << global_point[1] << ", "
              << global_point[2] << "\n\n";

    glPopMatrix();
  }

  Vetor3D State::get_transformed_point( Vetor3D p, TransformFunction transform_func ) {
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();

    transform_func();

    float matrix[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
    glPopMatrix();

    float pos[4] = { p.x, p.y, p.z, 1.0F };
    float res[4];

    multiply_matrix_by_vector( res, matrix, pos );

    return { res[0], res[1], res[2] };
  }
}  // namespace qxgl
