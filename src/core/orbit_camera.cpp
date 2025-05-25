#include "orbit_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace qxgl {

  OrbitCamera::OrbitCamera()
    : target( 0.0F, 0.0F, 0.0F ), distance( 10.0F ), azimuth( 0.0F ), elevation( 20.0F ) {
    updateViewMatrix();
  }

  void OrbitCamera::setTarget( const Vector3 &t ) {
    target = t;
    updateViewMatrix();
  }

  void OrbitCamera::setDistance( float d ) {
    distance = std::max( d, 0.1F );  // Evita distância negativa ou zero
    updateViewMatrix();
  }

  void OrbitCamera::rotate( float deltaAzimuth, float deltaElevation ) {
    azimuth += deltaAzimuth;
    elevation += deltaElevation;

    elevation = glm::clamp( elevation, -89.0F, 89.0F );  // evita "flip" na vertical

    updateViewMatrix();
  }

  void OrbitCamera::updateViewMatrix() {
    float radAzimuth   = degToRad( azimuth );
    float radElevation = degToRad( elevation );

    // Converte coordenadas esféricas para cartesianas
    float x = distance * cos( radElevation ) * sin( radAzimuth );
    float y = distance * sin( radElevation );
    float z = distance * cos( radElevation ) * cos( radAzimuth );

    position  = Vector3( x, y, z ) + target;
    direction = ( target - position ).unit();
    up        = Vector3( 0.0F, 1.0F, 0.0F );

    viewMatrix = glm::lookAt( position.glm(), target.glm(), up.glm() );
  }

  void OrbitCamera::updateProjectionMatrix( int width, int height ) {
    float aspect     = static_cast<float>( width ) / static_cast<float>( height );
    projectionMatrix = glm::perspective( glm::radians( 45.0F ),  // campo de visão
                                         aspect,
                                         0.1F,
                                         1000.0F );
  }

}  // namespace qxgl
