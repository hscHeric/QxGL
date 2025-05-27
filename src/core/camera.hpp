#ifndef QXGL_CAMERA_HPP
#define QXGL_CAMERA_HPP

#include "vector3.hpp"

#include <glm/mat4x4.hpp>

namespace qxgl {

  /**
   * @class Camera
   * @brief Classe base abstrata para câmeras 3D.
   *
   * Esta classe fornece uma interface comum para câmeras que possuem
   * posição, direção e vetor "up" (orientação vertical),
   * além do cálculo das matrizes de visualização (view) e projeção.
   *
   * As subclasses devem implementar a projeção específica.
   */
  class Camera {
  protected:
    Vector3   position;          ///< Posição da câmera no espaço mundial.
    Vector3   direction;         ///< Vetor direção que indica para onde a câmera está olhando.
    Vector3   up;                ///< Vetor "up" que define a orientação vertical da câmera.
    glm::mat4 viewMatrix;        ///< Matriz de visualização (View Matrix).
    glm::mat4 projectionMatrix;  ///< Matriz de projeção (Perspective ou Orthographic).

  public:
    /**
     * @brief Construtor padrão.
     * Inicializa os vetores posição, direção e up com valores padrão.
     * Inicializa as matrizes view e projection como matrizes identidade.
     */
    Camera();

    Camera( const Camera & )            = default;  ///< Construtor de cópia padrão.
    Camera( Camera && )                 = delete;   ///< Construtor de movimentação deletado.
    Camera &operator=( const Camera & ) = default;  ///< Operador de atribuição por cópia padrão.
    Camera &operator=( Camera && ) = delete;  ///< Operador de atribuição por movimentação deletado.

    /**
     * @brief Construtor completo.
     * @param position Posição inicial da câmera.
     * @param direction Vetor direção inicial da câmera.
     * @param up Vetor "up" inicial da câmera.
     * @param viewMatrix Matriz de visualização inicial.
     * @param projectionMatrix Matriz de projeção inicial.
     */
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

    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~Camera() = default;

    /**
     * @brief Define a posição da câmera.
     * @param pos Nova posição da câmera.
     */
    void setPosition( const Vector3 &pos );

    /**
     * @brief Define a direção para onde a câmera está olhando.
     * @param dir Novo vetor direção.
     */
    void setDirection( const Vector3 &dir );

    /**
     * @brief Define o vetor "up" da câmera (orientação vertical).
     * @param upVec Novo vetor "up".
     */
    void setUp( const Vector3 &upVec );

    /**
     * @brief Obtém a matriz de visualização atual.
     * @return Referência constante para a matriz de visualização.
     */
    [[nodiscard]] const glm::mat4 &getViewMatrix() const;

    /**
     * @brief Obtém a matriz de projeção atual.
     * @return Referência constante para a matriz de projeção.
     */
    [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;

    /**
     * @brief Atualiza a matriz de visualização com base nos vetores posição, direção e up.
     *
     * Esta função deve ser chamada sempre que houver alteração na posição, direção ou vetor up.
     */
    virtual void updateViewMatrix();

    /**
     * @brief Atualiza a matriz de projeção.
     *
     * Implementação específica deve ser fornecida pelas subclasses (ex: câmera perspectiva ou
     * ortográfica).
     *
     * @param width Largura da viewport.
     * @param height Altura da viewport.
     */
    virtual void updateProjectionMatrix( int width, int height ) = 0;
  };

}  // namespace qxgl

#endif  // QXGL_CAMERA_HPP
