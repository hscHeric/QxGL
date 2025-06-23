#ifndef QXGL_GAME_CAMERA_HPP
#define QXGL_GAME_CAMERA_HPP

#include "camera.hpp"

namespace qxgl {

  /**
   * @class GameCamera
   * @brief Uma implementação de câmera projetada para navegação em primeira pessoa ou estilo de
   * jogo.
   * @details Implementa a interface virtual da classe qxgl::Camera para fornecer
   * funcionalidades de zoom, translação (strafe) e rotação livre (free-look).
   */
  class GameCamera : public qxgl::Camera {
  public:
    /**
     * @brief Construtor padrão para a GameCamera.
     */
    GameCamera();

    /**
     * @brief Construtor que inicializa a GameCamera com vetores.
     */
    GameCamera( const Vetor3D &eye, const Vetor3D &center, const Vetor3D &up );

    /**
     * @brief Construtor que inicializa a GameCamera com componentes float.
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
     * @brief Destrutor padrão, sobrescrevendo o da classe base.
     */
    ~GameCamera() override = default;

    /** @brief {@inheritDoc} */
    void zoom( GLfloat win_y, GLfloat last_y ) override;

    /** @brief {@inheritDoc} */
    void translate_x( GLfloat win_x, GLfloat last_x ) override;

    /** @brief {@inheritDoc} */
    void translate_y( GLfloat win_y, GLfloat last_y ) override;

    /** @brief {@inheritDoc} */
    void rotate_x( GLfloat win_y, GLfloat last_y ) override;

    /** @brief {@inheritDoc} */
    void rotate_y( GLfloat win_x, GLfloat last_x ) override;

    /** @brief {@inheritDoc} */
    void rotate_z( GLfloat win_x, GLfloat last_x ) override;

    /** @brief {@inheritDoc} */
    Vetor3D get_picked_point( GLfloat x, GLfloat y ) override;
  };

}  // namespace qxgl

#endif  // QXGL_GAME_CAMERA_HPP
