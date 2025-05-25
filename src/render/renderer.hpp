#ifndef QXGL_RENDERER_HPP
#define QXGL_RENDERER_HPP

#include "../core/camera.hpp"
#include "../core/vector3.hpp"

/**
 * @brief Funções utilitárias para renderização de objetos 3D .
 *
 * Este módulo permite desenhar eixos, linhas, cubos e grids usando OpenGL,
 * com suporte à aplicação de matrizes de câmera (view e projection).
 */
namespace qxgl::renderer {

  /// Define as matrizes da câmera ativa para a renderização
  void useCamera( const Camera &camera );

  /// Inicia o frame (limpa a tela e o Z-buffer)
  void beginFrame();

  /// Finaliza o frame (troca buffers, se aplicável)
  void endFrame();

  /// Desenha os eixos X, Y e Z com cores RGB distintas
  void drawAxis( float length = 1.0F );

  /// Desenha um grid no plano XZ
  void drawGrid( int size = 10, float step = 1.0F );

  /// Desenha uma linha entre dois pontos
  void drawLine( const Vector3 &from, const Vector3 &to, const glm::vec3 &color );

  /// Desenha um cubo centrado na origem
  void drawCube( float size = 1.0F );
}  // namespace qxgl::renderer
#endif  // !QXGL_RENDERER_HPP
