#ifndef QXGL_ORBIT_CAMERA_HPP
#define QXGL_ORBIT_CAMERA_HPP

#include "camera.hpp"

namespace qxgl {

  /**
   * @brief Câmera orbital (gira ao redor de um ponto-alvo).
   *
   * Útil para visualizações livres, orbitando em torno de uma cena central,
   * como modelos 3D ou ambientes.
   */
  class OrbitCamera : public Camera {
  private:
    Vector3 target;     ///< Ponto-alvo da órbita
    float   distance;   ///< Distância da câmera ao alvo
    float   azimuth;    ///< Ângulo horizontal em graus (em torno do eixo Y)
    float   elevation;  ///< Ângulo vertical em graus (em torno do eixo X)

  public:
    /// Construtor padrão
    OrbitCamera();

    /// Define o ponto-alvo da órbita
    void setTarget( const Vector3 &t );

    /// Define a distância da câmera até o alvo
    void setDistance( float d );

    /// Altera os ângulos de rotação (azimute e elevação)
    void rotate( float deltaAzimuth, float deltaElevation );

    /// Atualiza a matriz de visualização com base na órbita
    void updateViewMatrix() override;

    /// Atualiza a matriz de projeção (perspectiva padrão)
    void updateProjectionMatrix( int width, int height ) override;
  };
}  // namespace qxgl
#endif  // !QXGL_ORBIT_CAMERA_HPP
