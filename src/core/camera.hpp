#ifndef QXGL_CAMERA_HPP
#define QXGL_CAMERA_HPP

#include "vector3.hpp"

#include <glm/mat4x4.hpp>

namespace qxgl {

  /**
   * @brief Classe base abstrata para câmeras 3D.
   *
   * Fornece interface comum para câmeras com posição, direção, vetor "up",
   * e cálculo de matrizes de visualização e projeção.
   */
  class Camera {
  protected:
    Vector3   position;          ///< Posição da câmera no mundo
    Vector3   direction;         ///< Vetor direção (para onde olha)
    Vector3   up;                ///< Vetor para cima (orientação vertical)
    glm::mat4 viewMatrix;        ///< Matriz de visualização (View)
    glm::mat4 projectionMatrix;  ///< Matriz de projeção (Perspective ou Ortográfica)

  public:
    Camera();

    Camera( const Camera & )            = default;
    Camera( Camera && )                 = delete;
    Camera &operator=( const Camera & ) = default;
    Camera &operator=( Camera && )      = delete;

    Camera( Vector3   position,
            Vector3   direction,
            Vector3   up,
            glm::mat4 viewMatrix,
            glm::mat4 projectionMatrix )
      : position( position )
      , direction( direction )
      , up( up )
      , viewMatrix( viewMatrix )
      , projectionMatrix( projectionMatrix ) {}

    virtual ~Camera() = default;

    /// Define a posição da câmera
    void setPosition( const Vector3 &pos );

    /// Define a direção da câmera
    void setDirection( const Vector3 &dir );

    /// Define o vetor "up" da câmera
    void setUp( const Vector3 &upVec );

    /// Retorna a matriz de visualização atual
    [[nodiscard]] const glm::mat4 &getViewMatrix() const;

    /// Retorna a matriz de projeção atual
    [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;

    /// Atualiza a matriz de visualização (baseada em posição/direção/up)
    virtual void updateViewMatrix();

    /// Atualiza a matriz de projeção (implementação específica da subclasse)
    virtual void updateProjectionMatrix( int width, int height ) = 0;
  };
}  // namespace qxgl
#endif  // !QXGL_CAMERA_HPP
