#ifndef QXGL_VECTOR3_HPP
#define QXGL_VECTOR3_HPP

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace qxgl {

  /**
   * @brief Converte um valor de radianos para graus.
   * @param rad Valor em radianos.
   * @return Valor equivalente em graus.
   */
  constexpr float radToDeg( float rad ) {
    return ( 180.0F / glm::pi<float>() ) * rad;
  }

  /**
   * @brief Converte um valor de graus para radianos.
   * @param deg Valor em graus.
   * @return Valor equivalente em radianos.
   */
  constexpr float degToRad( float deg ) {
    return ( glm::pi<float>() / 180.0F ) * deg;
  }

  /**
   * @class Vector3
   * @brief Classe utilitária para vetores 3D, encapsulando glm::vec3 com funcionalidades
   * adicionais.
   */
  class Vector3 {
  public:
    /// Valor interno representado como glm::vec3.
    glm::vec3 value;

    /// @brief Construtor padrão. Inicializa como vetor nulo (0, 0, 0).
    Vector3() : value( 0.0F, 0.0F, 0.0F ) {}

    Vector3( Vector3 && )                 = delete;
    Vector3 &operator=( Vector3 && )      = delete;
    Vector3( const Vector3 & )            = default;
    Vector3 &operator=( const Vector3 & ) = default;

    /**
     * @brief Construtor a partir de componentes individuais.
     * @param x Componente X.
     * @param y Componente Y.
     * @param z Componente Z.
     */
    Vector3( float x, float y, float z ) : value( x, y, z ) {}

    /**
     * @brief Construtor a partir de um glm::vec3.
     * @param vec Vetor glm.
     */
    Vector3( const glm::vec3 &vec ) : value( vec ) {}

    /// @brief Destrutor padrão.
    ~Vector3() = default;

    /**
     * @brief Define manualmente os valores do vetor.
     * @param x Componente X.
     * @param y Componente Y.
     * @param z Componente Z.
     */
    void set( float x, float y, float z ) {
      value = glm::vec3( x, y, z );
    }

    /**
     * @brief Retorna o comprimento (magnitude) do vetor.
     * @return Comprimento do vetor.
     */
    [[nodiscard]] float length() const {
      return glm::length( value );
    }

    /**
     * @brief Retorna o quadrado do comprimento do vetor (evita cálculo de raiz).
     * @return Quadrado da magnitude do vetor.
     */
    [[nodiscard]] float lengthSquared() const {
      return glm::dot( value, value );
    }

    /**
     * @brief Normaliza o vetor (magnitude passa a ser 1).
     */
    void normalize() {
      value = glm::normalize( value );
    }

    /**
     * @brief Retorna uma cópia normalizada do vetor.
     * @return Vetor unitário.
     */
    [[nodiscard]] Vector3 unit() const {
      return glm::normalize( value );
    }

    /**
     * @brief Retorna a projeção deste vetor sobre outro.
     * @param v Vetor base da projeção.
     * @return Vetor projetado.
     */
    [[nodiscard]] Vector3 projectOnto( const Vector3 &v ) const {
      glm::vec3 u = v.value;
      return ( glm::dot( value, u ) / glm::dot( u, u ) ) * u;
    }

    /**
     * @brief Atribui os valores de outro vetor.
     * @param v Vetor de origem.
     */
    void assign( const Vector3 &v ) {
      value = v.value;
    }

    /**
     * @brief Soma este vetor com outro.
     * @param v Vetor a ser somado.
     * @return Resultado da soma.
     */
    [[nodiscard]] Vector3 add( const Vector3 &v ) const {
      return value + v.value;
    }

    /**
     * @brief Soma outro vetor a este (in-place).
     * @param v Vetor a ser somado.
     */
    void addInPlace( const Vector3 &v ) {
      value += v.value;
    }

    /**
     * @brief Subtrai outro vetor deste.
     * @param v Vetor a ser subtraído.
     * @return Resultado da subtração.
     */
    [[nodiscard]] Vector3 subtract( const Vector3 &v ) const {
      return value - v.value;
    }

    /**
     * @brief Multiplica o vetor por um escalar.
     * @param scalar Escalar multiplicador.
     * @return Vetor escalado.
     */
    [[nodiscard]] Vector3 multiply( float scalar ) const {
      return value * scalar;
    }

    /**
     * @brief Calcula a distância deste vetor para outro.
     * @param v Vetor de destino.
     * @return Distância euclidiana entre os vetores.
     */
    [[nodiscard]] float distanceTo( const Vector3 &v ) const {
      return glm::length( value - v.value );
    }

    /**
     * @brief Produto vetorial entre este vetor e outro.
     * @param v Vetor a ser cruzado.
     * @return Vetor resultante do produto vetorial.
     */
    [[nodiscard]] Vector3 cross( const Vector3 &v ) const {
      return glm::cross( value, v.value );
    }

    /**
     * @brief Produto escalar entre este vetor e outro.
     * @param v Vetor a ser multiplicado.
     * @return Resultado do produto escalar.
     */
    [[nodiscard]] float dot( const Vector3 &v ) const {
      return glm::dot( value, v.value );
    }

    /// Operador de soma vetorial.
    Vector3 operator+( const Vector3 &v ) const {
      return value + v.value;
    }

    /// Operador de subtração vetorial.
    Vector3 operator-( const Vector3 &v ) const {
      return value - v.value;
    }

    /// Operador de multiplicação por escalar.
    Vector3 operator*( float scalar ) const {
      return value * scalar;
    }

    /// Operador de produto escalar.
    float operator*( const Vector3 &v ) const {
      return glm::dot( value, v.value );
    }

    /// Operador de produto vetorial (sintaxe ^).
    Vector3 operator^( const Vector3 &v ) const {
      return glm::cross( value, v.value );
    }

    /// Operador de normalização (!v retorna vetor unitário).
    Vector3 operator!() const {
      return this->unit();
    }

    /**
     * @brief Acesso ao valor interno glm::vec3.
     * @return Referência modificável ao vetor interno.
     */
    glm::vec3 &glm() {
      return value;
    }

    /**
     * @brief Acesso constante ao valor interno glm::vec3.
     * @return Referência constante ao vetor interno.
     */
    [[nodiscard]] const glm::vec3 &glm() const {
      return value;
    }
  };

}  // namespace qxgl

#endif  // QXGL_VECTOR3_HPP
