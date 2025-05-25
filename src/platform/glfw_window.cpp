#include "glfw_window.hpp"

#include <GL/glew.h>
#include <stdexcept>

namespace qxgl {

  GLFWWindow::GLFWWindow( int w, int h, const std::string &t )
    : width( w ), height( h ), title( t ), window( nullptr ) {
    if ( glfwInit() == 0 ) {
      throw std::runtime_error( "Erro ao inicializar GLFW." );
    }

    // Configuração mínima do contexto OpenGL
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    window = glfwCreateWindow( width, height, title.c_str(), nullptr, nullptr );
    if ( window == nullptr ) {
      glfwTerminate();
      throw std::runtime_error( "Erro ao criar janela GLFW." );
    }

    glfwMakeContextCurrent( window );

    glewExperimental = GL_TRUE;
    if ( glewInit() != GLEW_OK ) {
      glfwDestroyWindow( window );
      glfwTerminate();
      throw std::runtime_error( "Erro ao inicializar GLEW." );
    }

    glViewport( 0, 0, width, height );
  }

  GLFWWindow::~GLFWWindow() {
    if ( window != nullptr ) {
      glfwDestroyWindow( window );
    }
    glfwTerminate();
  }

  bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose( window ) != 0;
  }

  void GLFWWindow::pollEvents() const {
    glfwPollEvents();
  }

  void GLFWWindow::swapBuffers() const {
    glfwSwapBuffers( window );
  }

  GLFWwindow *GLFWWindow::getGLFWwindow() const {
    return window;
  }

  void GLFWWindow::getFramebufferSize( int &outWidth, int &outHeight ) const {
    glfwGetFramebufferSize( window, &outWidth, &outHeight );
  }

}  // namespace qxgl
