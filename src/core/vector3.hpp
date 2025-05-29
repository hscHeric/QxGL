#ifndef QXGL_VECTOR3_HPP
#define QXGL_VECTOR3_HPP

namespace qxgl {

  /**
   * @brief Constante PI para cálculos com ângulos.
   */
  constexpr float PI = 3.14159265358979323846F;

  /**
   * @brief Converte um valor de radianos para graus.
   * @param rad Valor em radianos.
   * @return Valor equivalente em graus.
   */
  constexpr float radToDeg( float rad );

  /**
   * @brief Converte um valor de graus para radianos.
   * @param deg Valor em graus.
   * @return Valor equivalente em radianos.
   */
  constexpr float degToRad( float deg );

  /**
   * @class Vector3
   * @brief Classe utilitária para vetores tridimensionais (3D), com operações vetoriais clássicas.
   */
  class Vector3 {
  public:
    /**
     * @brief Componente X do vetor.
     */
    float x;

    /**
     * @brief Componente Y do vetor.
     */
    float y;

    /**
     * @brief Componente Z do vetor.
     */
    float z;

    /**
     * @brief Construtor padrão. Inicializa o vetor com valores (0, 0, 0).
     */
    Vector3();

    Vector3( const Vector3 & )            = default;
    Vector3( Vector3 && )                 = delete;
    Vector3 &operator=( const Vector3 & ) = default;
    Vector3 &operator=( Vector3 && )      = delete;

    /**
     * @brief Construtor com valores iniciais.
     * @param x Valor da componente X.
     * @param y Valor da componente Y.
     * @param z Valor da componente Z.
     */
    Vector3( float x, float y, float z );

    /**
     * @brief Destrutor padrão.
     */
    ~Vector3() = default;

    /**
     * @brief Calcula o comprimento (norma/modulo) do vetor.
     * @return Comprimento do vetor.
     */
    [[nodiscard]] float length() const;

    /**
     * @brief Calcula o quadrado da norma do vetor (evita cálculo de raiz).
     * @return Comprimento ao quadrado do vetor.
     */
    [[nodiscard]] float lengthSquared() const;

    /**
     * @brief Normaliza o vetor atual, tornando-o unitário.
     */
    void normalize();

    /**
     * @brief Retorna uma cópia normalizada do vetor (unitário).
     * @return Vetor unitário equivalente.
     */
    [[nodiscard]] Vector3 unit() const;

    /**
     * @brief Calcula a projeção deste vetor sobre outro.
     * @param v Vetor sobre o qual será feita a projeção.
     * @return Vetor resultante da projeção.
     */
    [[nodiscard]] Vector3 projectOnto( const Vector3 &v ) const;

    /**
     * @brief Atribui os valores de outro vetor a este.
     * @param v Vetor a ser copiado.
     */
    void assign( const Vector3 &v );

    /**
     * @brief Soma este vetor com outro.
     * @param v Vetor a ser somado.
     * @return Resultado da soma vetorial.
     */
    [[nodiscard]] Vector3 add( const Vector3 &v ) const;

    /**
     * @brief Soma outro vetor a este vetor (in-place).
     * @param v Vetor a ser somado.
     */
    void addInPlace( const Vector3 &v );

    /**
     * @brief Subtrai outro vetor deste vetor.
     * @param v Vetor a ser subtraído.
     * @return Resultado da subtração vetorial.
     */
    [[nodiscard]] Vector3 subtract( const Vector3 &v ) const;

    /**
     * @brief Multiplica este vetor por um escalar.
     * @param scalar Valor escalar.
     * @return Vetor escalado.
     */
    [[nodiscard]] Vector3 multiply( float scalar ) const;

    /**
     * @brief Calcula a distância euclidiana até outro vetor.
     * @param v Vetor de destino.
     * @return Distância entre os dois vetores.
     */
    [[nodiscard]] float distanceTo( const Vector3 &v ) const;

    /**
     * @brief Produto vetorial entre este vetor e outro.
     * @param v Vetor a ser cruzado.
     * @return Vetor resultante do produto vetorial.
     */
    [[nodiscard]] Vector3 cross( const Vector3 &v ) const;

    /**
     * @brief Produto escalar entre este vetor e outro.
     * @param v Vetor a ser multiplicado.
     * @return Resultado do produto escalar.
     */
    [[nodiscard]] float dot( const Vector3 &v ) const;

    /**
     * @brief Operador de soma vetorial.
     * @param v Vetor a ser somado.
     * @return Resultado da soma vetorial.
     */
    Vector3 operator+( const Vector3 &v ) const;

    /**
     * @brief Operador de subtração vetorial.
     * @param v Vetor a ser subtraído.
     * @return Resultado da subtração vetorial.
     */
    Vector3 operator-( const Vector3 &v ) const;

    /**
     * @brief Operador de multiplicação por escalar.
     * @param scalar Valor escalar.
     * @return Vetor resultante da multiplicação.
     */
    Vector3 operator*( float scalar ) const;

    /**
     * @brief Operador de produto escalar entre dois vetores.
     * @param v Vetor a ser multiplicado.
     * @return Produto escalar entre os vetores.
     */
    float operator*( const Vector3 &v ) const;

    /**
     * @brief Operador de produto vetorial.
     * @param v Vetor a ser cruzado.
     * @return Resultado do produto vetorial.
     */
    Vector3 operator^( const Vector3 &v ) const;

    /**
     * @brief Operador de normalização. Retorna um vetor unitário equivalente.
     * @return Vetor unitário.
     */
    Vector3 operator!() const;
  };
}  // namespace qxgl

#endif  // QXGL_VECTOR3_HPP
