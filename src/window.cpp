#include "window.hpp"

#include "state.hpp"

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <utility>

namespace qxgl {

  namespace {
    Window::DisplayFunction     g_display_func;
    Window::KeyFunction         g_key_func;
    Window::MouseButtonFunction g_mouse_button_func;

    void display_wrapper() {
      if ( g_display_func ) {
        g_display_func();
      }
    }

    void key_wrapper( unsigned char key, int x, int y ) {
      if ( g_key_func ) {
        g_key_func( key, x, y );
      }
    }

    void mouse_button_wrapper( int button, int state, int x, int y ) {
      if ( g_mouse_button_func ) {
        g_mouse_button_func( button, state, x, y );
      }
    }
  }  // namespace

  Window::Window( int                 width,
                  int                 height,
                  std::string_view    title,
                  DisplayFunction     display_func,
                  KeyFunction         key_func,
                  MouseButtonFunction mouse_func )
    : title_( title ) {
    g_display_func      = display_func ? std::move( display_func ) : State::default_display;
    g_key_func          = key_func ? std::move( key_func ) : State::default_key;
    g_mouse_button_func = mouse_func ? std::move( mouse_func ) : State::default_mouse_button;

    State::width  = width;
    State::height = height;

    int    argc = 0;
    char **argv = nullptr;
    glutInit( &argc, argv );
    glutInitWindowSize( State::width, State::height );
    glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );

    id_ = glutCreateWindow( title_.c_str() );

    glutDisplayFunc( display_wrapper );
    glutKeyboardFunc( key_wrapper );
    glutMouseFunc( mouse_button_wrapper );

    glutReshapeFunc( State::resize );
    glutMotionFunc( State::mouse_move );
    glutIdleFunc( State::idle );
    glutTimerFunc( 0, State::timer, 0 );

    glClearColor( 0.7F, 0.7F, 0.7F, 1.0F );
    glEnable( GL_LIGHTING );
    glEnable( GL_CULL_FACE );
    glEnable( GL_NORMALIZE );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  }

  Window::~Window() {
    if ( id_ != -1 ) {
      glutDestroyWindow( id_ );
    }
  }

  void Window::run() {
    glutMainLoop();
  }

}  // namespace qxgl
