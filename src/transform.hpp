#ifndef QXGL_TRANSFORM_HPP
#define QXGL_TRANSFORM_HPP

#include "vector_3d.hpp"

namespace qxgl {
  class Transform {
    qxgl::Vetor3D position{ 0.0F, 0.0F, 0.0F };
    qxgl::Vetor3D rotation{ 0.0F, 0.0F, 0.0F };
    qxgl::Vetor3D scale{ 1.0F, 1.0F, 1.0F };
    bool          show_local_origin{ true };

    /**
     * @brief Aplica as transformações 3D (escala, rotação, translação) na pilha de matrizes do
     * OpenGL.
     * @details A ordem de aplicação é Escala -> Rotação -> Translação.
     */
    void apply() const;

    /**
     * @brief Aplica as transformações 2D no plano XY.
     */
    void apply_2d() const;

    /**
     * @brief Atualiza os parâmetros de transformação 3D com base na entrada do mouse.
     */
    void update_by_mouse();

    /**
     * @brief Atualiza os parâmetros de transformação 2D com base na entrada do mouse.
     */
    void update_by_mouse_2d();

    /**
     * @brief Reseta todos os parâmetros de transformação para seus valores padrão.
     */
    void reset();
  };
}  // namespace qxgl

#endif  // !QXGL_TRANSFORM_HPP
