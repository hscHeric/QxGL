/**
 * @file Vetor3D.h
 * @brief Declaração da classe Vetor3D e suas operações matemáticas.
 */
#ifndef VETOR3D_H
#define VETOR3D_H

#ifndef PI
  /**
   * @def PI
   * @brief Define o valor da constante matemática Pi.
   */
  #define PI 3.14159265359
#endif

/**
 * @def radToGrau(a)
 * @brief Converte um ângulo de radianos para graus.
 * @param a Ângulo em radianos.
 */
#define radToGrau( a ) ( ( 180.0 / PI ) * a )  // converte de radiano para grau

/**
 * @def grauToRad(a)
 * @brief Converte um ângulo de graus para radianos.
 * @param a Ângulo em graus.
 */
#define grauToRad( a ) ( ( PI / 180.0 ) * a )  // converte de grau para radiano

#include <cmath>

using dReal = float;

/**
 * @class Vetor3D
 * @brief Representa um vetor no espaço tridimensional (R^3).
 *
 * Esta classe fornece funcionalidades para manipulação de vetores 3D,
 * incluindo operações aritméticas, cálculo de módulo, normalização,
 * produtos escalar e vetorial, entre outras.
 */
class Vetor3D {
public:
  // coordenadas do vetor
  dReal x; /**< @brief Coordenada no eixo X. */
  dReal y; /**< @brief Coordenada no eixo Y. */
  dReal z; /**< @brief Coordenada no eixo Z. */

  /**
   * @brief Construtor padrão.
   *
   * Inicializa o vetor como um vetor nulo (0, 0, 0).
   */
  Vetor3D();

  /**
   * @brief Construtor com parâmetros.
   *
   * @param x Coordenada inicial no eixo X.
   * @param y Coordenada inicial no eixo Y.
   * @param z Coordenada inicial no eixo Z.
   */
  Vetor3D( dReal x, dReal y, dReal z );

  /**
   * @brief Destrutor da classe.
   */
  ~Vetor3D();

  /**
   * @brief Define as coordenadas do vetor.
   *
   * @param x Nova coordenada no eixo X.
   * @param y Nova coordenada no eixo Y.
   * @param z Nova coordenada no eixo Z.
   */
  void setVetor3D( dReal x, dReal y, dReal z );

  /**
   * @brief Calcula o módulo (magnitude ou comprimento) do vetor.
   *
   * @return O módulo do vetor.
   */
  dReal modulo();

  /**
   * @brief Calcula o quadrado do módulo do vetor. OBS: Não tira a raiz quadrada no cálculo.
   *
   * @return O quadrado do módulo.
   */
  dReal modulo2();  // quadrado do modulo (nao tira a raiz quadrada)

  /**
   * @brief Normaliza o vetor.
   *
   * Modifica o vetor atual para que ele se torne um vetor unitário (módulo 1),
   * mantendo sua direção original.
   */
  void normaliza();

  /**
   * @brief Retorna uma cópia normalizada (unitária) deste vetor.
   *
   * @return Vetor3D - Um novo vetor unitário com a mesma direção do original.
   */
  Vetor3D getUnit();

  /**
   * @brief Calcula a projeção deste vetor sobre outro vetor v.
   *
   * @param v O vetor no qual este vetor será projetado.
   * @return Vetor3D - O vetor resultante da projeção.
   */
  Vetor3D projectedOn( Vetor3D v );

  /**
   * @brief Copia os valores de um vetor v para este vetor.
   *
   * @param v O vetor de origem.
   */
  void recebe( Vetor3D v );

  /**
   * @brief Soma este vetor com um vetor v, retornando um novo vetor.
   *
   * @param v O vetor a ser somado.
   * @return Vetor3D - O resultado da soma.
   */
  Vetor3D soma( Vetor3D v );

  /**
   * @brief Adiciona um vetor v a este vetor (modifica o objeto atual).
   *
   * @param v O vetor a ser adicionado.
   */
  void add( Vetor3D v );

  /**
   * @brief Subtrai um vetor v deste vetor, retornando um novo vetor.
   *
   * @param v O vetor a ser subtraído.
   * @return Vetor3D - O resultado da subtração.
   */
  Vetor3D subtracao( Vetor3D v );

  /**
   * @brief Multiplica este vetor por um escalar, retornando um novo vetor.
   *
   * @param escalar O valor escalar pelo qual o vetor será multiplicado.
   * @return Vetor3D - O resultado da multiplicação.
   */
  Vetor3D multiplicacao( dReal escalar );

  /**
   * @brief Calcula a distância euclidiana entre este vetor (ponto) e outro.
   *
   * @param v O outro vetor (ponto) para o qual a distância será calculada.
   * @return dReal - A distância entre os dois pontos.
   */
  dReal getDistance( Vetor3D v );

  /**
   * @brief Calcula o produto vetorial (cross product) entre este vetor e v.
   *
   * @param v O segundo vetor da operação.
   * @return Vetor3D - O vetor resultante, perpendicular a ambos os vetores originais.
   */
  Vetor3D prodVetorial( Vetor3D v );

  /**
   * @brief Calcula o produto escalar (dot product) entre este vetor e v.
   *
   * @param v O segundo vetor da operação.
   * @return dReal - O valor escalar resultante.
   */
  dReal prodEscalar( Vetor3D v );

  /**
   * @brief Sobrecarga do operador de adição (+).
   * @see soma()
   */
  Vetor3D operator+( Vetor3D v );

  /**
   * @brief Sobrecarga do operador de subtração (-).
   * @see subtracao()
   */
  Vetor3D operator-( Vetor3D v );

  /**
   * @brief Sobrecarga do operador de multiplicação (*) por escalar.
   * @see multiplicacao()
   */
  Vetor3D operator*( dReal escalar );

  /**
   * @brief Sobrecarga do operador de multiplicação (*) para produto escalar.
   * @see prodEscalar()
   */
  dReal operator*( Vetor3D v );

  /**
   * @brief Sobrecarga do operador circunflexo (^) para produto vetorial.
   * @see prodVetorial()
   */
  Vetor3D operator^( Vetor3D v );

  /**
   * @brief Sobrecarga do operador de negação (!) para normalização in-place.
   * @see normaliza()
   * @return Uma referência para o próprio vetor normalizado.
   */
  Vetor3D operator!();
};

#endif
