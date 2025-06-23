#ifndef QXGL_DISTANT_CAMERA_HPP
#define QXGL_DISTANT_CAMERA_HPP

#include "camera.hpp"  // Inclui a classe base abstrata

namespace qxgl {

  /**
   * @class DistantCamera
   * @brief Uma implementação de câmera que orbita em torno de um ponto central (alvo).
   * @details Esta câmera mantém uma distância de um ponto de foco. A rotação move
   * a câmera ao longo de uma esfera imaginária cujo centro é o ponto de foco.
   * O zoom aproxima ou afasta a câmera deste ponto.
   */
  class DistantCamera : public qxgl::Camera {
  public:
    /**
     * @brief Construtor padrão para a DistantCamera.
     */
    DistantCamera();

    /**
     * @brief Construtor que inicializa a DistantCamera com vetores.
     */
    DistantCamera( const Vetor3D &eye, const Vetor3D &center, const Vetor3D &up );

    /**
     * @brief Construtor que inicializa a DistantCamera com componentes float.
     */
    DistantCamera( GLfloat ex,
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
    ~DistantCamera() override = default;

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

#endif  // QXGL_DISTANT_CAMERA_HPP
