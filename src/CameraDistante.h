/**
 * @file CameraDistante.h
 * @brief Declaração da classe CameraDistante, uma implementação de câmera orbital.
 *
 * @details Este arquivo contém a definição da classe CameraDistante, que herda
 * da classe abstrata Camera. Ela implementa um comportamento de câmera
 * orbital, onde a câmera gira em torno de um ponto de interesse central.
 */
#ifndef CAMERADISTANTE_H
#define CAMERADISTANTE_H

#include "Camera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

/**
 * @class CameraDistante
 * @brief Implementação concreta de uma câmera orbital.
 *
 * @details Esta câmera permite ao usuário orbitar em torno de um ponto central (c),
 * aproximar/afastar (zoom) e mover lateralmente (pan/translate). É ideal
 * para visualizar um objeto ou uma cena a partir de uma perspectiva externa.
 * Herda da classe base abstrata Camera e implementa suas funções virtuais.
 * @see Camera
 */
class CameraDistante : public Camera {
public:
  /**
   * @brief Construtor padrão.
   * Inicializa a câmera com valores padrão e define o estilo como CAMDIST.
   */
  CameraDistante();

  /**
   * @brief Construtor que inicializa a câmera com vetores.
   * @param e Vetor da posição do olho (eye).
   * @param c Vetor do ponto central (alvo).
   * @param u Vetor de orientação "up".
   */
  CameraDistante( Vetor3D e, Vetor3D c, Vetor3D u );

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
  CameraDistante( GLfloat ex,
                  GLfloat ey,
                  GLfloat ez,
                  GLfloat cx,
                  GLfloat cy,
                  GLfloat cz,
                  GLfloat ux,
                  GLfloat uy,
                  GLfloat uz );

  /**
   * @brief Destrutor da classe CameraDistante.
   */
  ~CameraDistante() {};

  /**
   * @brief Aproxima ou afasta a câmera do ponto central.
   *
   * Move o ponto 'e' (eye) ao longo do vetor de visão em direção
   * ou para longe do ponto 'c' (center).
   * @param dx Variação do mouse no eixo X (geralmente não utilizado para zoom).
   * @param dy Variação do mouse no eixo Y, usada para controlar a intensidade do zoom.
   */
  void zoom( GLfloat /*dx*/, GLfloat /*dy*/ ) override;

  /**
   * @brief Move a câmera e seu alvo horizontalmente.
   *
   * Translada os pontos 'e' e 'c' juntos ao longo do eixo X local da câmera.
   * @param dx Variação do mouse no eixo X, usada para controlar o movimento.
   * @param dy Variação do mouse no eixo Y (geralmente não utilizado).
   */
  void translatex( GLfloat /*dx*/, GLfloat /*dy*/ ) override;

  /**
   * @brief Move a câmera e seu alvo verticalmente.
   *
   * Translada os pontos 'e' e 'c' juntos ao longo do eixo Y local da câmera.
   * @param dx Variação do mouse no eixo X (geralmente não utilizado).
   * @param dy Variação do mouse no eixo Y, usada para controlar o movimento.
   */
  void translatey( GLfloat /*dx*/, GLfloat /*dy*/ ) override;

  /**
   * @brief Orbita a câmera verticalmente ao redor do ponto central 'c'.
   * @param dx Variação do mouse no eixo X (geralmente não utilizado).
   * @param dy Variação do mouse no eixo Y, usada para controlar a rotação.
   */
  void rotatex( GLfloat /*dx*/, GLfloat /*dy*/ ) override;

  /**
   * @brief Orbita a câmera horizontalmente (yaw) ao redor do ponto central 'c'.
   * @param dx Variação do mouse no eixo X, usada para controlar a rotação.
   * @param dy Variação do mouse no eixo Y (geralmente não utilizado).
   */
  void rotatey( GLfloat /*dx*/, GLfloat /*dy*/ ) override;

  /**
   * @brief Rola a câmera em torno de seu próprio eixo de visão.
   * @param dx Variação do mouse no eixo X, usada para controlar a rotação.
   * @param dy Variação do mouse no eixo Y (geralmente não utilizado).
   */
  void rotatez( GLfloat /*dx*/, GLfloat /*dy*/ ) override;

  /**
   * @brief Implementação do método de picking para a câmera orbital.
   *
   * Calcula o raio que vai da posição da câmera através do pixel
   * especificado na tela para determinar o ponto 3D correspondente.
   * @param x_tela Coordenada X na janela/tela.
   * @param y_tela Coordenada Y na janela/tela.
   * @return Vetor3D O ponto correspondente no espaço 3D.
   */
  Vetor3D getPickedPoint( GLfloat /*x_tela*/, GLfloat /*y_tela*/ ) override;
};

#endif
