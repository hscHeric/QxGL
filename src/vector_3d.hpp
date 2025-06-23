#ifndef QXGL_VECTOR_3D_HPP
#define QXGL_VECTOR_3D_HPP

#include <cmath>
#include <stdexcept>

/**
 * @namespace qxgl
 * @brief Namespace para encapsular as funcionalidades gráficas e matemáticas do projeto.
 */
namespace qxgl {

  /**
   * @namespace constants
   * @brief Contém constantes matemáticas de uso comum.
   */
  namespace constants {
    /**
     * @brief Valor da constante Pi com a precisão de um float.
     */
    inline constexpr float PI = 3.14159265358979323846F;

  }  // namespace constants

  /**
   * @brief Converte um ângulo de radianos para graus.
   * @param rad O ângulo em radianos.
   * @return O ângulo equivalente em graus.
   */
  constexpr float rad_to_deg( float rad ) noexcept {
    return ( 180.0F / constants::PI ) * rad;
  }

  /**
   * @brief Converte um ângulo de graus para radianos.
   * @param deg O ângulo em graus.
   * @return O ângulo equivalente em radianos.
   */
  constexpr float deg_to_rad( float deg ) noexcept {
    return ( constants::PI / 180.0F ) * deg;
  }

  /**
   * @class Vetor3D
   * @brief Representa e manipula um vetor tridimensional (x, y, z).
   *
   * Fornece operações matemáticas comuns para vetores, como soma, subtração,
   * produtos escalar e vetorial, normalização, cálculo de magnitude, entre outras.
   */
  class Vetor3D {
  public:
    /** @brief A coordenada X do vetor. */
    float x{ 0.0F };
    /** @brief A coordenada Y do vetor. */
    float y{ 0.0F };
    /** @brief A coordenada Z do vetor. */
    float z{ 0.0F };

    /**
     * @brief Construtor padrão.
     * @details Inicializa um vetor nulo (0, 0, 0).
     */
    constexpr Vetor3D() noexcept = default;

    /**
     * @brief Construtor com parâmetros.
     * @details Inicializa um vetor com as coordenadas especificadas.
     * @param x O valor da coordenada X.
     * @param y O valor da coordenada Y.
     * @param z O valor da coordenada Z.
     */
    constexpr Vetor3D( float x, float y, float z ) noexcept : x( x ), y( y ), z( z ) {}

    /**
     * @brief Destrutor padrão.
     */
    ~Vetor3D() = default;

    /**
     * @brief Define os componentes do vetor.
     * @param newX Novo valor para a coordenada X.
     * @param newY Novo valor para a coordenada Y.
     * @param newZ Novo valor para a coordenada Z.
     */
    void set( float newX, float newY, float newZ ) noexcept;

    /**
     * @brief Normaliza o vetor, fazendo sua magnitude ser igual a 1.
     * @details Modifica o próprio objeto. Se o vetor for nulo, nenhuma operação é realizada.
     * @see get_unit()
     */
    void normalize();

    /**
     * @brief Calcula a magnitude (comprimento ou módulo) do vetor.
     * @return A magnitude do vetor.
     * @see magnitude_squared()
     */
    [[nodiscard]] float magnitude() const noexcept;

    /**
     * @brief Calcula o quadrado da magnitude do vetor.
     * @details Esta operação é computacionalmente mais barata que `magnitude()` pois evita o
     * cálculo da raiz quadrada.
     * @return O quadrado da magnitude do vetor.
     */
    [[nodiscard]] float magnitude_squared() const noexcept;

    /**
     * @brief Retorna uma cópia normalizada deste vetor.
     * @details Não modifica o objeto original.
     * @return Um novo Vetor3D que é a versão unitária do original.
     * @see normalize()
     */
    [[nodiscard]] Vetor3D get_unit() const;

    /**
     * @brief Calcula a projeção deste vetor sobre outro vetor `v`.
     * @param v O vetor sobre o qual este vetor será projetado.
     * @return Um novo Vetor3D resultante da projeção.
     */
    [[nodiscard]] Vetor3D projected_on( const Vetor3D &v ) const;

    /**
     * @brief Calcula a distância entre este vetor (interpretado como um ponto) e outro.
     * @param v O outro vetor (ponto) para o qual a distância será calculada.
     * @return A distância escalar entre os dois pontos.
     */
    [[nodiscard]] float get_distance( const Vetor3D &v ) const;

    /**
     * @brief Adiciona um vetor a este e armazena o resultado neste vetor.
     * @param v O vetor a ser adicionado.
     * @return Uma referência para o próprio objeto modificado (`*this`).
     */
    Vetor3D &operator+=( const Vetor3D &v ) noexcept;

    /**
     * @brief Subtrai um vetor deste e armazena o resultado neste vetor.
     * @param v O vetor a ser subtraído.
     * @return Uma referência para o próprio objeto modificado (`*this`).
     */
    Vetor3D &operator-=( const Vetor3D &v ) noexcept;

    /**
     * @brief Multiplica este vetor por um escalar e armazena o resultado neste vetor.
     * @param scalar O valor escalar pelo qual o vetor será multiplicado.
     * @return Uma referência para o próprio objeto modificado (`*this`).
     */
    Vetor3D &operator*=( float scalar ) noexcept;

    /**
     * @brief Divide este vetor por um escalar e armazena o resultado neste vetor.
     * @param scalar O valor escalar pelo qual o vetor será dividido.
     * @return Uma referência para o próprio objeto modificado (`*this`).
     * @exception std::runtime_error Se `scalar` for zero.
     */
    Vetor3D &operator/=( float scalar );

    /**
     * @brief Operador unário para normalizar o vetor in-place.
     * @details É um atalho para o método `normalize()`.
     * @return Uma referência para o próprio objeto modificado (`*this`).
     */
    Vetor3D &operator!();
  };

  /**
   * @brief Soma dois vetores.
   * @relates Vetor3D
   * @param lhs O vetor à esquerda do operador.
   * @param rhs O vetor à direita do operador.
   * @return Um novo Vetor3D que é a soma de `lhs` e `rhs`.
   */
  inline Vetor3D operator+( const Vetor3D &lhs, const Vetor3D &rhs ) noexcept {
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
  }

  /**
   * @brief Subtrai um vetor de outro.
   * @relates Vetor3D
   * @param lhs O vetor à esquerda do operador (minuendo).
   * @param rhs O vetor à direita do operador (subtraendo).
   * @return Um novo Vetor3D que é a diferença entre `lhs` e `rhs`.
   */
  inline Vetor3D operator-( const Vetor3D &lhs, const Vetor3D &rhs ) noexcept {
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
  }

  /**
   * @brief Calcula o produto escalar (dot product) entre dois vetores.
   * @relates Vetor3D
   * @param lhs O vetor à esquerda do operador.
   * @param rhs O vetor à direita do operador.
   * @return O resultado escalar do produto.
   */
  inline float operator*( const Vetor3D &lhs, const Vetor3D &rhs ) noexcept {
    return ( lhs.x * rhs.x ) + ( lhs.y * rhs.y ) + ( lhs.z * rhs.z );
  }

  /**
   * @brief Calcula o produto vetorial (cross product) entre dois vetores.
   * @relates Vetor3D
   * @param lhs O vetor à esquerda do operador.
   * @param rhs O vetor à direita do operador.
   * @return Um novo Vetor3D que é perpendicular a `lhs` e `rhs`.
   */
  inline Vetor3D operator^( const Vetor3D &lhs, const Vetor3D &rhs ) noexcept {
    return { ( lhs.y * rhs.z ) - ( lhs.z * rhs.y ),
             ( lhs.z * rhs.x ) - ( lhs.x * rhs.z ),
             ( lhs.x * rhs.y ) - ( lhs.y * rhs.x ) };
  }

  /**
   * @brief Multiplica um vetor por um escalar.
   * @relates Vetor3D
   * @param v O vetor a ser multiplicado.
   * @param scalar O valor escalar.
   * @return Um novo Vetor3D resultante da multiplicação.
   */
  inline Vetor3D operator*( const Vetor3D &v, float scalar ) noexcept {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
  }

  /**
   * @brief Multiplica um escalar por um vetor (propriedade comutativa).
   * @relates Vetor3D
   * @param scalar O valor escalar.
   * @param v O vetor a ser multiplicado.
   * @return Um novo Vetor3D resultante da multiplicação.
   */
  inline Vetor3D operator*( float scalar, const Vetor3D &v ) noexcept {
    return v * scalar;
  }

  /**
   * @brief Divide um vetor por um escalar.
   * @relates Vetor3D
   * @param v O vetor a ser dividido.
   * @param scalar O divisor.
   * @return Um novo Vetor3D resultante da divisão.
   * @exception std::runtime_error Se `scalar` for zero.
   */
  inline Vetor3D operator/( const Vetor3D &v, float scalar ) {
    if ( scalar == 0.0F ) {
      throw std::runtime_error( "Divisão por zero ao escalar vetor." );
    }
    return { v.x / scalar, v.y / scalar, v.z / scalar };
  }

  inline void Vetor3D::set( float newX, float newY, float newZ ) noexcept {
    x = newX;
    y = newY;
    z = newZ;
  }

  inline float Vetor3D::magnitude() const noexcept {
    return std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
  }

  inline float Vetor3D::magnitude_squared() const noexcept {
    return ( x * x ) + ( y * y ) + ( z * z );
  }

  inline void Vetor3D::normalize() {
    float m = magnitude();
    if ( m > 0.0F ) {
      ( *this ) /= m;
    }
  }

  inline Vetor3D Vetor3D::get_unit() const {
    Vetor3D u = *this;
    u.normalize();
    return u;
  }

  inline Vetor3D Vetor3D::projected_on( const Vetor3D &v ) const {
    Vetor3D v_unit = v.get_unit();
    return v_unit * ( *this * v_unit );
  }

  inline float Vetor3D::get_distance( const Vetor3D &v ) const {
    return ( *this - v ).magnitude();
  }

  inline Vetor3D &Vetor3D::operator+=( const Vetor3D &v ) noexcept {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  inline Vetor3D &Vetor3D::operator-=( const Vetor3D &v ) noexcept {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  inline Vetor3D &Vetor3D::operator*=( float scalar ) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  inline Vetor3D &Vetor3D::operator/=( float scalar ) {
    if ( scalar == 0.0F ) {
      throw std::runtime_error( "Divisão por zero em atribuição composta." );
    }
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  inline Vetor3D &Vetor3D::operator!() {
    this->normalize();
    return *this;
  }

}  // namespace qxgl
#endif  // QXGL_VECTOR_3D_HPP
