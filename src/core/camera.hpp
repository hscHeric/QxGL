#ifndef QXGL_CAMERA_HPP
#define QXGL_CAMERA_HPP

#include "vector3.hpp"

#include <GL/gl.h>

namespace qxgl {
  /**
   * @brief Estilo de controle da câmera.
   */
  enum CameraStyle { Orbit = 1, Game = 2 };

  /**
   * @class Camera
   * @brief Classe base abstrata para manipulação de câmeras em OpenGL.
   */
  class Camera {
  public:
    /**
     * @brief Posição do observador (olho).
     */
    Vector3 eye;

    /**
     * @brief Ponto para o qual a câmera está olhando (centro).
     */
    Vector3 center;

    /**
     * @brief Vetor "up" (para cima), definindo a orientação da câmera.
     */
    Vector3 up;

    /**
     * @brief Estilo da câmera (distante, jogo, etc.).
     */
    int style;

    /**
     * @brief Construtor padrão.
     */
    Camera();

    /**
     * @brief Construtor com vetores já definidos.
     * @param eye Posição do olho.
     * @param center Ponto de foco da câmera.
     * @param up Vetor up.
     */
    Camera( const Vector3 &eye, const Vector3 &center, const Vector3 &up );

    /**
     * @brief Construtor com coordenadas escalares.
     * @param ex Olho X.
     * @param ey Olho Y.
     * @param ez Olho Z.
     * @param cx Centro X.
     * @param cy Centro Y.
     * @param cz Centro Z.
     * @param ux Up X.
     * @param uy Up Y.
     * @param uz Up Z.
     */
    Camera( GLfloat ex,
            GLfloat ey,
            GLfloat ez,
            GLfloat cx,
            GLfloat cy,
            GLfloat cz,
            GLfloat ux,
            GLfloat uy,
            GLfloat uz );

    /**
     * @brief Destrutor virtual.
     */
    virtual ~Camera() = default;

    /**
     * @brief Zoom na direção do centro.
     * @param delta Valor de incremento.
     * @param scale Escala do zoom.
     */
    virtual void zoom( GLfloat delta, GLfloat scale ) = 0;

    /**
     * @brief Translação da câmera no eixo X.
     * @param delta Valor de incremento.
     * @param scale Escala da translação.
     */
    virtual void translateX( GLfloat delta, GLfloat scale ) = 0;

    /**
     * @brief Translação da câmera no eixo Y.
     * @param delta Valor de incremento.
     * @param scale Escala da translação.
     */
    virtual void translateY( GLfloat delta, GLfloat scale ) = 0;

    /**
     * @brief Rotação da câmera em torno do eixo X.
     * @param angle Ângulo de rotação.
     * @param scale Escala da rotação.
     */
    virtual void rotateX( GLfloat angle, GLfloat scale ) = 0;

    /**
     * @brief Rotação da câmera em torno do eixo Y.
     * @param angle Ângulo de rotação.
     * @param scale Escala da rotação.
     */
    virtual void rotateY( GLfloat angle, GLfloat scale ) = 0;

    /**
     * @brief Rotação da câmera em torno do eixo Z.
     * @param angle Ângulo de rotação.
     * @param scale Escala da rotação.
     */
    virtual void rotateZ( GLfloat angle, GLfloat scale ) = 0;

    /**
     * @brief Converte coordenadas de tela para um ponto 3D no espaço.
     * @param screenX Coordenada X da tela.
     * @param screenY Coordenada Y da tela.
     * @return Ponto 3D correspondente no espaço.
     */
    virtual Vector3 getPickedPoint( GLfloat screenX, GLfloat screenY ) = 0;

    /**
     * @brief Ajusta o vetor `center` de estilo "distante" para "jogo".
     */
    void adaptCenterFromDistToGame();

    /**
     * @brief Ajusta o vetor `center` de estilo "jogo" para "distante".
     * @param radius Raio de distância a ser ajustado.
     */
    void adaptCenterFromGameToDist( GLfloat radius );
  };
}  // namespace qxgl

#endif  // !QXGL_CAMERA_HPP
