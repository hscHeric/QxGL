#ifndef QXGL_ORBIT_CAMERA_HPP
#define QXGL_ORBIT_CAMERA_HPP

#include "camera.hpp"

namespace qxgl {

  /**
   * @class OrbitCamera
   * @brief Câmera orbital que gira ao redor de um ponto-alvo.
   *
   * Essa câmera é útil para visualizações livres que orbitam em torno de um ponto central,
   * como em visualização de modelos 3D ou ambientes interativos.
   */
  class OrbitCamera : public Camera {
  private:
    Vector3 target;     ///< Ponto-alvo da órbita, em torno do qual a câmera gira.
    float   distance;   ///< Distância da câmera ao ponto-alvo.
    float   azimuth;    ///< Ângulo horizontal em graus, rotacionando ao redor do eixo Y.
    float   elevation;  ///< Ângulo vertical em graus, rotacionando ao redor do eixo X.

  public:
    /**
     * @brief Construtor padrão.
     * Inicializa a câmera com valores padrão para distância, ângulos e ponto-alvo.
     */
    OrbitCamera();

    /**
     * @brief Define o ponto-alvo da órbita.
     * @param t Novo ponto-alvo para a câmera orbitar.
     */
    void setTarget( const Vector3 &t );

    /**
     * @brief Define a distância da câmera ao ponto-alvo.
     * @param d Distância desejada.
     */
    void setDistance( float d );

    /**
     * @brief Altera os ângulos de rotação da câmera.
     *
     * Incrementa os ângulos azimute (horizontal) e elevação (vertical).
     * Os ângulos são fornecidos em graus.
     *
     * @param deltaAzimuth Incremento no ângulo azimute (em graus).
     * @param deltaElevation Incremento no ângulo elevação (em graus).
     */
    void rotate( float deltaAzimuth, float deltaElevation );

    /**
     * @brief Atualiza a matriz de visualização baseada na posição orbital da câmera.
     *
     * Essa função recalcula a posição da câmera com base no ponto-alvo,
     * distância, azimute e elevação, e atualiza a matriz de visualização.
     */
    void updateViewMatrix() override;

    /**
     * @brief Atualiza a matriz de projeção perspectiva.
     *
     * Implementa uma projeção perspectiva padrão, ajustada à largura e altura da viewport.
     *
     * @param width Largura da viewport.
     * @param height Altura da viewport.
     */
    void updateProjectionMatrix( int width, int height ) override;
  };

}  // namespace qxgl

#endif  // QXGL_ORBIT_CAMERA_HPP
