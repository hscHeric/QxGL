#ifndef QXGL_CAMERA_HPP
#define QXGL_CAMERA_HPP

#include "vector_3d.hpp"

#include <GL/gl.h>

namespace qxgl {

  /**
   * @enum CameraStyle
   * @brief Define os diferentes tipos ou modos de comportamento da câmera.
   */
  enum class CameraStyle {
    DIST,  ///< Estilo de câmera focado em distância.
    GAME   ///< Estilo de câmera para navegação em jogos.
  };

  /**
   * @class Camera
   * @brief Classe base abstrata que define a interface para todos os tipos de câmera.
   * @details Fornece a estrutura base (eye, center, up) e uma interface virtual pura
   * para manipulações como zoom, rotação e translação, que devem ser
   * implementadas por classes derivadas concretas.
   */
  class Camera {
  protected:
    /** @brief A posição da câmera no espaço (o "olho"). */
    qxgl::Vetor3D eye_{ 0.0F, 1.0F, 10.0F };

    /** @brief O ponto para o qual a câmera está olhando (o "alvo" ou "centro"). */
    qxgl::Vetor3D center_{ 0.0F, 1.0F, 0.0F };

    /** @brief O vetor que aponta para "cima" no sistema de coordenadas da câmera. */
    qxgl::Vetor3D up_{ 0.0F, 1.0F, 0.0F };

    /** @brief O estilo de comportamento da câmera. */
    CameraStyle style_{ CameraStyle::GAME };

  public:
    /**
     * @brief Construtor padrão.
     * @details Inicializa a câmera em uma posição e orientação padrão.
     */
    Camera();

    /**
     * @brief Construtor que inicializa a câmera com vetores pré-definidos.
     * @param eye O vetor da posição da câmera.
     * @param center O vetor do ponto de foco.
     * @param up O vetor "up" da câmera.
     */
    Camera( const Vetor3D &eye, const Vetor3D &center, const Vetor3D &up );

    /**
     * @brief Construtor que inicializa a câmera com componentes float individuais.
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
     * @brief Destrutor virtual padrão.
     * @details É crucial que o destrutor de uma classe base polimórfica seja virtual
     * para garantir que os destrutores das classes derivadas sejam chamados
     * corretamente, evitando vazamentos de memória.
     */
    virtual ~Camera() = default;

    /**
     * @brief Aplica zoom na câmera. (Interface Pura Virtual)
     * @param win_y Posição Y atual do mouse.
     * @param last_y Posição Y anterior do mouse.
     */
    virtual void zoom( GLfloat win_y, GLfloat last_y ) = 0;

    /**
     * @brief Move a câmera no seu eixo X local (strafe). (Interface Pura Virtual)
     */
    virtual void translate_x( GLfloat win_x, GLfloat last_x ) = 0;

    /**
     * @brief Move a câmera no seu eixo Y local (elevação). (Interface Pura Virtual)
     */
    virtual void translate_y( GLfloat win_y, GLfloat last_y ) = 0;

    /**
     * @brief Rotaciona a câmera em torno do seu eixo X local (pitch). (Interface Pura Virtual)
     */
    virtual void rotate_x( GLfloat win_y, GLfloat last_y ) = 0;

    /**
     * @brief Rotaciona a câmera em torno do seu eixo Y global/local (yaw). (Interface Pura Virtual)
     */
    virtual void rotate_y( GLfloat win_x, GLfloat last_x ) = 0;

    /**
     * @brief Rotaciona a câmera em torno do seu eixo Z local (roll). (Interface Pura Virtual)
     */
    virtual void rotate_z( GLfloat win_x, GLfloat last_x ) = 0;

    /**
     * @brief Converte coordenadas 2D da tela para um ponto 3D no mundo. (Interface Pura Virtual)
     * @return Um Vetor3D representando o ponto no espaço 3D.
     */
    virtual Vetor3D get_picked_point( GLfloat x, GLfloat y ) = 0;

    /**
     * @brief Ajusta a distância entre 'center' e 'eye' para 1.0, mantendo a direção.
     */
    void normalize_distance();

    /**
     * @brief Define a distância exata entre 'center' e 'eye' para um valor 'r'.
     * @param r A nova distância desejada.
     */
    void set_distance( GLfloat r );

    /**
     * @brief Retorna a posição da câmera (eye).
     * @return Uma referência constante para o vetor eye.
     */
    [[nodiscard]] const Vetor3D &get_eye() const {
      return eye_;
    }

    /**
     * @brief Retorna o ponto de foco da câmera (center).
     * @return Uma referência constante para o vetor center.
     */
    [[nodiscard]] const Vetor3D &get_center() const {
      return center_;
    }

    /**
     * @brief Retorna o vetor "up" da câmera.
     * @return Uma referência constante para o vetor up.
     */
    [[nodiscard]] const Vetor3D &get_up() const {
      return up_;
    }
  };

}  // namespace qxgl

#endif  // QXGL_CAMERA_HPP
