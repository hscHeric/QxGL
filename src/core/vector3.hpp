#ifndef QXGL_VECTOR3_HPP
#define QXGL_VECTOR3_HPP

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace qxgl {

  /**
   * @brief Converte radianos para graus.
   * @param rad Valor em radianos.
   * @return Valor equivalente em graus.
   */
  constexpr float radToDeg( float rad ) {
    return ( 180.0F / glm::pi<float>() ) * rad;
  }

  /**
   * @brief Converte graus para radianos.
   * @param deg Valor em graus.
   * @return Valor equivalente em radianos.
   */
  constexpr float degToRad( float deg ) {
    return ( glm::pi<float>() / 180.0F ) * deg;
  }

  class Vector3 {
  public:
    /// Valor interno armazenado como glm::vec3
    glm::vec3 value;

    /// Construtor padrão. Inicializa como vetor nulo (0, 0, 0).
    Vector3() : value( 0.0F, 0.0F, 0.0F ) {}

    Vector3( const Vector3 & )            = default;
    Vector3 &operator=( const Vector3 & ) = default;

    /// Construtor com coordenadas x, y e z.
    Vector3( float x, float y, float z ) : value( x, y, z ) {}

    /// Construtor a partir de um vetor glm::vec3.
    Vector3( const glm::vec3 &vec ) : value( vec ) {}

    /// Destrutor padrão.
    ~Vector3() = default;

    /// Define os valores do vetor manualmente.
    void set( float x, float y, float z ) {
      value = glm::vec3( x, y, z );
    }

    /// Retorna o comprimento (módulo) do vetor.
    [[nodiscard]] float length() const {
      return glm::length( value );
    }

    /// Retorna o quadrado do comprimento (sem raiz).
    [[nodiscard]] float lengthSquared() const {
      return glm::dot( value, value );
    }

    /// Normaliza o vetor (módulo passa a ser 1).
    void normalize() {
      value = glm::normalize( value );
    }

    /// Retorna um novo vetor normalizado (unitário).
    [[nodiscard]] Vector3 unit() const {
      return ( glm::normalize( value ) );
    }

    /// Retorna a projeção deste vetor sobre outro vetor.
    [[nodiscard]] Vector3 projectOnto( const Vector3 &v ) const {
      glm::vec3 u = v.value;
      return ( glm::dot( value, u ) / glm::dot( u, u ) * u );
    }

    /// Atribui ao vetor os valores de outro vetor.
    void assign( const Vector3 &v ) {
      value = v.value;
    }

    /// Soma este vetor com outro e retorna o resultado.
    [[nodiscard]] Vector3 add( const Vector3 &v ) const {
      return ( value + v.value );
    }

    /// Soma (in-place) este vetor com outro.
    void addInPlace( const Vector3 &v ) {
      value += v.value;
    }

    /// Subtrai outro vetor deste e retorna o resultado.
    [[nodiscard]] Vector3 subtract( const Vector3 &v ) const {
      return ( value - v.value );
    }

    /// Multiplica o vetor por um escalar e retorna o resultado.
    [[nodiscard]] Vector3 multiply( float scalar ) const {
      return ( value * scalar );
    }

    /// Retorna a distância entre este vetor e outro vetor.
    [[nodiscard]] float distanceTo( const Vector3 &v ) const {
      return glm::length( value - v.value );
    }

    /// Retorna o produto vetorial com outro vetor.
    [[nodiscard]] Vector3 cross( const Vector3 &v ) const {
      return ( glm::cross( value, v.value ) );
    }

    /// Retorna o produto escalar com outro vetor.
    [[nodiscard]] float dot( const Vector3 &v ) const {
      return glm::dot( value, v.value );
    }

    /// Operador de soma vetorial.
    Vector3 operator+( const Vector3 &v ) const {
      return ( value + v.value );
    }

    /// Operador de subtração vetorial.
    Vector3 operator-( const Vector3 &v ) const {
      return ( value - v.value );
    }

    /// Operador de multiplicação por escalar.
    Vector3 operator*( float scalar ) const {
      return ( value * scalar );
    }

    /// Operador de produto escalar entre vetores.
    float operator*( const Vector3 &v ) const {
      return glm::dot( value, v.value );
    }

    /// Operador de produto vetorial (usando ^).
    Vector3 operator^( const Vector3 &v ) const {
      return ( glm::cross( value, v.value ) );
    }

    /// Operador de normalização (!v retorna o vetor unitário).
    Vector3 operator!() const {
      return this->unit();
    }

    /// Retorna referência ao glm::vec3 encapsulado.
    glm::vec3 &glm() {
      return value;
    }

    /// Retorna referência constante ao glm::vec3 encapsulado.
    [[nodiscard]] const glm::vec3 &glm() const {
      return value;
    }
  };
}  // namespace qxgl
#endif  // !QXGL_VECTOR3D_HPP
