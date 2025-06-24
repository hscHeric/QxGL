#ifndef QXGL_WINDOW_HPP
#define QXGL_WINDOW_HPP

#include <functional>
#include <string>
#include <string_view>

namespace qxgl {

  /**
   * @class Window
   * @brief Wrapper orientado a objetos para criar e gerenciar uma janela GLUT.
   * @details Encapsula a inicialização do GLUT, a criação da janela
   * e o registro dos callbacks globais definidos na classe State.
   */
  class Window {
  public:
    using DisplayFunction     = std::function<void()>;
    using KeyFunction         = std::function<void( unsigned char, int, int )>;
    using MouseButtonFunction = std::function<void( int, int, int, int )>;

  private:
    int         id_{ -1 };
    std::string title_;

  public:
    /**
     * @brief Constrói e inicializa uma nova janela GLUT.
     * @param width A largura inicial da janela.
     * @param height A altura inicial da janela.
     * @param title O título da janela.
     * @param display_func A função de callback para renderização (opcional).
     * @param key_func A função de callback para eventos de teclado (opcional).
     * @param mouse_func A função de callback para eventos de clique do mouse (opcional).
     */
    Window( int                 width,
            int                 height,
            std::string_view    title        = "QXGL Window",
            DisplayFunction     display_func = nullptr,
            KeyFunction         key_func     = nullptr,
            MouseButtonFunction mouse_func   = nullptr );

    /** @brief Destrutor que destrói a janela GLUT associada. */
    ~Window();

    // Prevenir cópia, mas permitir movimentação.
    Window( const Window & )            = delete;
    Window &operator=( const Window & ) = delete;
    Window( Window && )                 = default;
    Window &operator=( Window && )      = default;

    /** @brief Inicia o loop principal de eventos do GLUT. Esta função bloqueia a execução. */
    void run();
  };

}  // namespace qxgl

#endif  // QXGL_WINDOW_HPP
