/**
 * @file CameraJogo.h
 * @brief Declaração da classe CameraJogo, uma implementação de câmera em primeira pessoa.
 *
 * @details Este arquivo define a classe CameraJogo, que herda da classe base
 * abstrata Camera. Ela implementa um controle de câmera no estilo "free-look"
 * ou "primeira pessoa", comum em jogos, permitindo que o usuário se mova e
 * olhe livremente pelo ambiente 3D.
 */
#ifndef CAMERAJOGO_H
#define CAMERAJOGO_H

#include "Camera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

/**
 * @class CameraJogo
 * @brief Implementação concreta de uma câmera em primeira pessoa (FPS).
 *
 * @details Esta câmera simula um ponto de vista onde o usuário pode rotacionar a
 * visão em torno de sua própria posição e se mover pelo
 * cenário. Ela implementa a interface da classe
 * base abstrata Camera.
 * @see Camera
 */
class CameraJogo : public Camera {
public:
  /**
   * @brief Construtor padrão.
   * Inicializa a câmera com valores padrão e define o estilo como CAMJOGO.
   */
  CameraJogo();

  /**
   * @brief Construtor que inicializa a câmera com vetores.
   * @param e Vetor da posição do olho (eye).
   * @param c Vetor do ponto central (alvo).
   * @param u Vetor de orientação "up".
   */
  CameraJogo( Vetor3D e, Vetor3D c, Vetor3D u );

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
  CameraJogo( GLfloat ex,
              GLfloat ey,
              GLfloat ez,
              GLfloat cx,
              GLfloat cy,
              GLfloat cz,
              GLfloat ux,
              GLfloat uy,
              GLfloat uz );

  /**
   * @brief Destrutor da classe CameraJogo.
   */
  ~CameraJogo() = default;

  /**
   * @brief Move a câmera para frente ou para trás.
   *
   * Translada a câmera ao longo de seu vetor de visão.
   * @param win_y Posição Y atual do cursor do mouse.
   * @param last_y Posição Y anterior do cursor do mouse.
   */
  void zoom( GLfloat win_y, GLfloat last_y ) override;

  /**
   * @brief Move a câmera para a esquerda ou direita.
   *
   * Translada a câmera ao longo de seu eixo X local.
   * @param win_x Posição X atual do cursor do mouse.
   * @param last_x Posição X anterior do cursor do mouse.
   */
  void translatex( GLfloat win_x, GLfloat last_x ) override;

  /**
   * @brief Move a câmera para cima ou para baixo.
   *
   * Translada a câmera ao longo de seu eixo Y local (vetor up).
   * @param win_y Posição Y atual do cursor do mouse.
   * @param last_y Posição Y anterior do cursor do mouse.
   */
  void translatey( GLfloat win_y, GLfloat last_y ) override;

  /**
   * @brief Rotaciona a visão da câmera para cima ou para baixo.
   *
   * Pivota a direção da câmera em torno de seu eixo X local, sem mover a posição da câmera.
   * @param win_y Posição Y atual do cursor do mouse.
   * @param last_y Posição Y anterior do cursor do mouse.
   */
  void rotatex( GLfloat win_y, GLfloat last_y ) override;

  /**
   * @brief Rotaciona a visão da câmera para a esquerda ou direita.
   *
   * Pivota a direção da câmera em torno do eixo Y global, mantendo a posição da câmera fixa.
   * @param win_x Posição X atual do cursor do mouse.
   * @param last_x Posição X anterior do cursor do mouse.
   */
  void rotatey( GLfloat win_x, GLfloat last_x ) override;

  /**
   * @brief Inclina (roll) a câmera para os lados.
   *
   * Rotaciona a câmera em torno de seu próprio eixo de visão (vetor Z local).
   * @param win_x Posição X atual do cursor do mouse.
   * @param last_x Posição X anterior do cursor do mouse.
   */
  void rotatez( GLfloat win_x, GLfloat last_x ) override;

  /**
   * @brief Implementação do método de picking para a câmera de jogo.
   *
   * Calcula um ponto no espaço 3D a partir das coordenadas 2D da tela,
   * projetando um raio a partir da câmera.
   * @param x Coordenada X local da câmera (geralmente vinda do mouse).
   * @param y Coordenada Y local da câmera (geralmente vinda do mouse).
   * @return Vetor3D O ponto correspondente no espaço 3D.
   */
  Vetor3D getPickedPoint( GLfloat x, GLfloat y ) override;
};
#endif
