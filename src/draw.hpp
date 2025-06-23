#ifndef QXGL_DRAW_HPP
#define QXGL_DRAW_HPP

#include "vector_3d.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

namespace qxgl::Drawing {

  /**
   * @brief Renderiza uma caixa 3D sólida com normais e coordenadas de textura.
   * @param xmin, ymin, zmin As coordenadas do canto mínimo da caixa.
   * @param xmax, ymax, zmax As coordenadas do canto máximo da caixa.
   */
  void
    draw_box( GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax );

  /**
   * @brief Renderiza as arestas de uma caixa 3D (wireframe).
   */
  void draw_wire_box(
    GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax );

  /**
   * @brief Renderiza as arestas de uma caixa de seleção, com cantos destacados.
   * @details Esta função não define normais. A cor deve ser definida com glColor.
   */
  void draw_selected_box(
    GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax );

  /**
   * @brief Renderiza as quatro arestas de um quadrado no plano XZ.
   */
  void draw_quad( GLfloat xmin, GLfloat y, GLfloat zmin, GLfloat side_length );

  /**
   * @brief Renderiza uma grade 2D no plano XZ.
   * @param half_nx Metade do número de quadrados na direção X.
   * @param y A altura (coordenada Y) da grade.
   * @param half_nz Metade do número de quadrados na direção Z.
   * @param dimension O tamanho de cada quadrado da grade.
   */
  void draw_grid( int half_nx, GLfloat y, int half_nz, int dimension );

  /**
   * @brief Renderiza um cilindro sólido com tampas nas duas extremidades.
   */
  void draw_closed_cylinder(
    GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks );

  /**
   * @brief Renderiza uma cápsula (um cilindro com uma esfera em cada ponta).
   */
  void draw_capsule(
    GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks );

  /**
   * @brief Renderiza os eixos X (vermelho), Y (verde) e Z (azul) com setas nas pontas.
   * @param size O comprimento de cada eixo.
   */
  void draw_axes( GLfloat size );

  /**
   * @brief Aplica uma transformação de um motor de física (como o ODE) à matriz do OpenGL.
   * @param pos Um ponteiro para um array de 3 floats representando a posição.
   * @param R Um ponteiro para um array de 12 floats representando a matriz de rotação (row-major).
   */
  void apply_ode_transform( const float *pos, const float *R );

}  // namespace qxgl::Drawing

#endif
