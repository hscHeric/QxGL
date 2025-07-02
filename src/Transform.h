/**
 * @file Transform.h
 * @brief Declaração da classe Transform para gerenciar transformações de objetos.
 *
 * @details Esta classe encapsula as transformações geométricas básicas de um objeto
 * (translação, rotação e escala) em um único lugar. Ela fornece métodos para
 * aplicar essas transformações à pilha de matrizes do OpenGL, atualizá-las
 * interativamente com base na entrada do mouse e redefinir seus valores.
 */
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "gui.h"

/**
 * @class Transform
 * @brief Gerencia e aplica transformações 3D e 2D.
 */
class Transform {
public:
  Vetor3D pos = Vetor3D( 0.0, 0.0, 0.0 ); /**< @brief Vetor de translação (posição) do objeto. */
  Vetor3D rot = Vetor3D(
    0.0,
    0.0,
    0.0 ); /**< @brief Vetor de rotação (ângulos de Euler em graus para os eixos X, Y, Z). */
  Vetor3D esc = Vetor3D( 1.0, 1.0, 1.0 ); /**< @brief Vetor de escala nos eixos X, Y, Z. */
  bool    showLocalOrigin =
    true; /**< @brief Flag para controlar a exibição dos eixos de coordenadas locais do objeto. */

  /**
   * @brief Aplica as transformações 3D (translação, rotação, escala) na matriz model-view atual do
   * OpenGL.
   * @details A ordem da aplicação é: Translação, Rotação (X, Y, Z), Desenho da Origem Local
   * (opcional) e Escala.
   */
  void apply();

  /**
   * @brief Aplica as transformações 2D (translação XY, rotação Z, escala XY) na matriz model-view.
   * @details Uma versão simplificada de `apply()` para contextos 2D.
   */
  void apply2D();

  /**
   * @brief Atualiza os valores de transformação 3D com base nos deltas de movimento do mouse.
   * @details Usa as variáveis globais de delta (drx, dry, etc.) da classe `glutGUI` para
   * modificar interativamente a posição, rotação e escala.
   */
  void updateByMouse();

  /**
   * @brief Atualiza os valores de transformação 2D com base nos deltas de movimento do mouse.
   * @details Versão simplificada de `updateByMouse` para o contexto 2D.
   */
  void updateByMouse2D();

  /**
   * @brief Redefine todos os valores de transformação para seus estados iniciais.
   * @details A posição e rotação são zeradas, a escala volta para (1,1,1) e a exibição da origem
   * local é ativada.
   */
  void reset();
};

#endif  // TRANSFORM_H
