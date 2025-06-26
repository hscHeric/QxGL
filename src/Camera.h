/**
 * @file Camera.h
 * @brief Declaração da classe base abstrata 'Camera'.
 *
 * @details Esta classe serve como uma interface para diferentes tipos
 * de câmeras em um ambiente (CameraJogo.h e CameraDistante.h). Ela define as operações
 * fundamentais como zoom, translação e rotação, que devem ser
 * implementadas por classes concretas.
 */
#ifndef CAMERA_H
#define CAMERA_H

/**
 * @def CAMDIST
 * @brief Identificador para um estilo de câmera orbital ou "distante".
 */
#define CAMDIST 1

/**
 * @def CAMJOGO
 * @brief Identificador para um estilo de câmera de "jogo" (ex: primeira pessoa).
 */
#define CAMJOGO 2

#include "Vetor3D.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

/**
 * @class Camera
 * @brief Classe base abstrata para representar uma câmera em uma cena 3D.
 *
 * Define a interface comum para todas as câmeras, incluindo os vetores
 * de posição, alvo e orientação, além de operações de manipulação virtuais
 * que devem ser implementadas pelas classes derivadas.
 */
class Camera {
public:
  Vetor3D e;  /**< @brief A posição da câmera no espaço (ponto do olho - eye). */
  Vetor3D c;  /**< @brief O ponto para o qual a câmera está olhando (ponto central - center). */
  Vetor3D u;  /**< @brief O vetor "up", que indica a orientação vertical da câmera. */
  int estilo; /**< @brief Define o estilo da câmera (vai utilizar as macros CAMDIST, CAMJOGO). */

  /**
   * @brief Construtor padrão.
   * Inicializa a câmera em uma posição e orientação padrão.
   */
  Camera();

  /**
   * @brief Construtor que inicializa a câmera com vetores.
   * @param e Vetor da posição do olho.
   * @param c Vetor do ponto central (alvo).
   * @param u Vetor de orientação "up".
   */
  Camera( Vetor3D e, Vetor3D c, Vetor3D u );

  /**
   * @brief Construtor que inicializa a câmera com coordenadas explícitas.
   * @param ex Coordenada x da posição.
   * @param ey Coordenada y da posição.
   * @param ez Coordenada z da posição.
   * @param cx Coordenada x do alvo.
   * @param cy Coordenada y do alvo.
   * @param cz Coordenada z do alvo.
   * @param ux Coordenada x do vetor "up".
   * @param uy Coordenada y do vetor "up".
   * @param uz Coordenada z do vetor "up".
   */
  Camera( GLfloat ex,
          GLfloat ey,
          GLfloat ez,
          GLfloat cx,
          GLfloat cy,
          GLfloat cz,
          GLfloat ux,
          GLfloat uy,
          GLfloat uz );

  /**
   * @brief Destrutor virtual padrão.
   */
  ~Camera() = default;

  /**
   * @brief Aplica um zoom na câmera. (Função virtual pura)
   * @param dx Variação no eixo x (geralmente do mouse), a ser interpretada pela implementação.
   * @param dy Variação no eixo y (geralmente do mouse), a ser interpretada pela implementação.
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual void zoom( GLfloat dx, GLfloat dy ) = 0;

  /**
   * @brief Translada a câmera no seu eixo X local. (Função virtual pura)
   * @param dx Variação no eixo x (geralmente do mouse).
   * @param dy Variação no eixo y (geralmente do mouse).
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual void translatex( GLfloat dx, GLfloat dy ) = 0;

  /**
   * @brief Translada a câmera no seu eixo Y local. (Função virtual pura)
   * @param dx Variação no eixo x (geralmente do mouse).
   * @param dy Variação no eixo y (geralmente do mouse).
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual void translatey( GLfloat dx, GLfloat dy ) = 0;

  /**
   * @brief Rotaciona a câmera em torno do seu eixo X local. (Função virtual pura)
   * @param dx Variação no eixo x (geralmente do mouse).
   * @param dy Variação no eixo y (geralmente do mouse).
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual void rotatex( GLfloat dx, GLfloat dy ) = 0;

  /**
   * @brief Rotaciona a câmera em torno do seu eixo Y local. (Função virtual pura)
   * @param dx Variação no eixo x (geralmente do mouse).
   * @param dy Variação no eixo y (geralmente do mouse).
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual void rotatey( GLfloat dx, GLfloat dy ) = 0;

  /**
   * @brief Rotaciona a câmera em torno do seu eixo Z local (roll). (Função virtual pura)
   * @param dx Variação no eixo x (geralmente do mouse).
   * @param dy Variação no eixo y (geralmente do mouse).
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual void rotatez( GLfloat dx, GLfloat dy ) = 0;

  /**
   * @brief Obtém um ponto no espaço 3D a partir de coordenadas de tela 2D (picking). (Função
   * virtual pura)
   * @param x_tela Coordenada X na janela/tela.
   * @param y_tela Coordenada Y na janela/tela.
   * @return Vetor3D O ponto correspondente no espaço 3D.
   * @note Esta função deve ser implementada por uma classe derivada.
   */
  virtual Vetor3D getPickedPoint( GLfloat x_tela, GLfloat y_tela ) = 0;

  /**
   * @brief Ajusta o vetor alvo 'c' para ficar a uma distância unitária do olho 'e'.
   *
   * Útil para converter de um modo de câmera com alvo distante para um modo
   * de primeira pessoa, onde o alvo define apenas a direção.
   */
  void adaptavetorcdisttojogo();

  /**
   * @brief Ajusta o vetor alvo 'c' para ficar a uma distância 'r' do olho 'e'.
   *
   * Útil para redefinir a distância do alvo, por exemplo, ao converter de um
   * modo de primeira pessoa para um modo orbital em torno de um ponto.
   * @param r A nova distância desejada entre o olho (e) e o alvo (c).
   */
  void adaptavetorcjogotodist( GLfloat r );
};

#endif
