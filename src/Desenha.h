/**
 * @file Desenha.h
 * @brief Declaração da classe Desenha, uma biblioteca de utilitários para renderização com OpenGL.
 *
 * @details Esta classe estática fornece um conjunto de funções para desenhar primitivas geométrica.
 */
#ifndef DESENHA_H
#define DESENHA_H

#include "Vetor3D.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class Desenha {
public:
  /**
   * @brief Construtor padrão.
   */
  Desenha() = default;
  /**
   * @brief Destrutor padrão.
   */
  ~Desenha() = default;

  /**
   * @brief Desenha uma caixa sólida com 6 faces (um paralelepípedo).
   * @details Renderiza a caixa usando GL_QUADS, definindo normais e coordenadas de textura para
   * cada face.
   * @param xmin Coordenada X do canto mínimo.
   * @param ymin Coordenada Y do canto mínimo.
   * @param zmin Coordenada Z do canto mínimo.
   * @param xmax Coordenada X do canto máximo.
   * @param ymax Coordenada Y do canto máximo.
   * @param zmax Coordenada Z do canto máximo.
   */
  static void
    drawBox( GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax );

  /**
   * @brief Desenha o contorno de uma caixa em aramado (wireframe).
   * @details Utiliza GL_LINES para conectar os 8 vértices da caixa.
   * @param xmin Coordenada X do canto mínimo.
   * @param ymin Coordenada Y do canto mínimo.
   * @param zmin Coordenada Z do canto mínimo.
   * @param xmax Coordenada X do canto máximo.
   * @param ymax Coordenada Y do canto máximo.
   * @param zmax Coordenada Z do canto máximo.
   */
  static void drawWireBox(
    GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax );

  /**
   * @brief Desenha uma caixa de seleção em aramado com cantos destacados.
   * @details Útil para indicar um objeto selecionado na cena. As linhas não são contínuas.
   * @note Esta função não define normais. A cor deve ser definida externamente com glColor,
   * preferencialmente com a iluminação (GL_LIGHTING) desabilitada.
   * @param xmin Coordenada X do canto mínimo.
   * @param ymin Coordenada Y do canto mínimo.
   * @param zmin Coordenada Z do canto mínimo.
   * @param xmax Coordenada X do canto máximo.
   * @param ymax Coordenada Y do canto máximo.
   * @param zmax Coordenada Z do canto máximo.
   */
  static void drawSelectedBox(
    GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax );

  /**
   * @brief Desenha um único quadrado em aramado no plano XZ.
   * @details Usado como bloco de construção para a função drawGrid.
   * @param xmin Coordenada X inicial do quadrado.
   * @param y A altura (coordenada Y) onde o quadrado será desenhado.
   * @param zmin Coordenada Z inicial do quadrado.
   * @param lado O comprimento do lado do quadrado.
   */
  static void drawQuad( GLfloat xmin, GLfloat y, GLfloat zmin, GLfloat lado );

  /**
   * @brief Desenha uma grade 2D no plano XZ.
   * @details A grade é centrada na origem.
   * @param meionx Número de quadrados na metade do eixo X.
   * @param y A altura (coordenada Y) onde a grade será desenhada.
   * @param meionz Número de quadrados na metade do eixo Z.
   * @param dimensao O tamanho do lado de cada quadrado da grade.
   */
  static void drawGrid( int meionx, GLfloat y, int meionz, int dimensao );

  /**
   * @brief Desenha um cilindro com as duas extremidades fechadas por discos.
   * @details Utiliza um objeto GLUquadric para renderizar o cilindro e os discos.
   * @param quad Ponteiro para um objeto GLUquadric.
   * @param base Raio da base do cilindro.
   * @param top Raio do topo do cilindro.
   * @param height Altura do cilindro.
   * @param slices Número de subdivisões ao redor do eixo Z (afeta a suavidade).
   * @param stacks Número de subdivisões ao longo do eixo Z (afeta a suavidade).
   */
  static void gluClosedCylinder(
    GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks );

  /**
   * @brief Desenha uma cápsula (um cilindro com uma esfera em cada ponta).
   * @details Utiliza um objeto GLUquadric para renderizar o cilindro e as esferas.
   * @param quad Ponteiro para um objeto GLUquadric.
   * @param base Raio da base da cápsula.
   * @param top Raio do topo da cápsula.
   * @param height Altura da seção cilíndrica.
   * @param slices Número de subdivisões (afeta a suavidade).
   * @param stacks Número de subdivisões (afeta a suavidade).
   */
  static void gluCapsule(
    GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks );

  /**
   * @brief Desenha uma seta indicando uma direção de um ponto a outro.
   * @note A implementação desta função não foi fornecida no arquivo .cpp.
   * @param from Ponto de origem da seta.
   * @param to Ponto de destino da seta.
   * @param larg Largura da seta (parâmetro opcional).
   */
  static void drawArrow( Vetor3D from, Vetor3D to, GLfloat larg = 0.0 );

  /**
   * @brief Desenha uma seta com duas pontas.
   * @note A implementação desta função não foi fornecida no arquivo .cpp.
   * @param from Ponto de uma extremidade.
   * @param to Ponto da outra extremidade.
   * @param larg Largura da seta (parâmetro opcional).
   */
  static void drawDoubleArrow( Vetor3D from, Vetor3D to, GLfloat larg = 0.0 );

  /**
   * @brief Desenha os três eixos do sistema de coordenadas (X, Y, Z).
   * @details Renderiza os eixos X em vermelho, Y em verde e Z em azul, com pequenos cones nas
   * pontas.
   * @param tam O comprimento de cada eixo a partir da origem.
   */
  static void drawEixos( GLfloat tam );

  /**
   * @brief Aplica uma matriz de transformação (posição e rotação) do motor de física ODE.
   * @details Converte a matriz de rotação e o vetor de posição do formato da ODE para uma matriz de
   * modelo (modelview) do OpenGL e a multiplica pela matriz atual.
   * @param pos Ponteiro para um array dReal[3] com a posição (x, y, z).
   * @param R Ponteiro para um array dReal[12] com a matriz de rotação 3x3 (row-major).
   */
  static void setTransformODE( const dReal *pos, const dReal *R );
};

#endif  // DESENHA_H
