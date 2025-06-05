#ifndef QXGL_GAME_CAMERA_HPP
#define QXGL_GAME_CAMERA_HPP

#include "camera.hpp"

namespace qxgl {
  /**
   * @class GameCamera
   * @brief Implementação de uma câmera para jogos, com controle de translação, rotação e zoom.
   */
  class GameCamera : public Camera {
  public:
    /**
     * @brief Construtor padrão.
     * Inicializa a câmera com posição e orientação padrão.
     */
    GameCamera();

    /**
     * @brief Construtor com parâmetros iniciais.
     * @param eye Posição do olho (câmera).
     * @param center Ponto de foco.
     * @param up Vetor para cima.
     */
    GameCamera( const Vector3 &eye, const Vector3 &center, const Vector3 &up );

    /**
     * @brief Construtor com coordenadas explícitas.
     * @param ex Posição X do olho.
     * @param ey Posição Y do olho.
     * @param ez Posição Z do olho.
     * @param cx Posição X do centro.
     * @param cy Posição Y do centro.
     * @param cz Posição Z do centro.
     * @param ux Vetor X de orientação para cima.
     * @param uy Vetor Y de orientação para cima.
     * @param uz Vetor Z de orientação para cima.
     */
    GameCamera( GLfloat ex,
                GLfloat ey,
                GLfloat ez,
                GLfloat cx,
                GLfloat cy,
                GLfloat cz,
                GLfloat ux,
                GLfloat uy,
                GLfloat uz );

    /**
     * @brief Zoom (aproximação ou afastamento da câmera).
     * @param delta Quantidade de zoom.
     * @param scale Escala de sensibilidade.
     */
    void zoom( GLfloat delta, GLfloat scale ) override;

    /**
     * @brief Translação no eixo X (horizontal).
     * @param delta Valor da translação.
     * @param scale Escala de sensibilidade.
     */
    void translateX( GLfloat delta, GLfloat scale ) override;

    /**
     * @brief Translação no eixo Y (vertical).
     * @param delta Valor da translação.
     * @param scale Escala de sensibilidade.
     */
    void translateY( GLfloat delta, GLfloat scale ) override;

    /**
     * @brief Rotação da câmera no eixo X (pitch).
     * @param angle Ângulo em graus.
     * @param scale Escala de sensibilidade.
     */
    void rotateX( GLfloat angle, GLfloat scale ) override;

    /**
     * @brief Rotação da câmera no eixo Y (yaw).
     * @param angle Ângulo em graus.
     * @param scale Escala de sensibilidade.
     */
    void rotateY( GLfloat angle, GLfloat scale ) override;

    /**
     * @brief Rotação da câmera no eixo Z (roll).
     * @param angle Ângulo em graus.
     * @param scale Escala de sensibilidade.
     */
    void rotateZ( GLfloat angle, GLfloat scale ) override;

    /**
     * @brief Converte coordenadas de tela para um ponto no espaço 3D.
     * @param screenX Posição X da tela.
     * @param screenY Posição Y da tela.
     * @return Ponto 3D no mundo.
     */
    Vector3 getPickedPoint( GLfloat screenX, GLfloat screenY ) override;
  };
}  // namespace qxgl
#endif  // !QXGL_GAME_CAMERA_HPP
