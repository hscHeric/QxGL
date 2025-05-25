#ifndef QXGL_GLFW_WINDOW_HPP
#define QXGL_GLFW_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace qxgl {

  /**
   * @brief Interface para criação e controle de uma janela GLFW com OpenGL.
   */
  class GLFWWindow {
  private:
    GLFWwindow *window;
    int         width;
    int         height;
    std::string title;

  public:
    /// Construtor: cria e inicializa a janela
    GLFWWindow( int width, int height, const std::string &title );

    /// Destrutor: encerra GLFW
    ~GLFWWindow();

    /// Verifica se a janela deve ser fechada
    [[nodiscard]] bool shouldClose() const;

    /// Processa eventos do sistema (teclado, mouse etc.)
    void pollEvents() const;

    /// Troca os buffers (swap)
    void swapBuffers() const;

    /// Retorna ponteiro para o GLFWwindow interno
    [[nodiscard]] GLFWwindow *getGLFWwindow() const;

    /// Retorna largura e altura atuais do framebuffer
    void getFramebufferSize( int &outWidth, int &outHeight ) const;
  };
}  // namespace qxgl
#endif  // !QXGL_GLFW_WINDOW_HPP
