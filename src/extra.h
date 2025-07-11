#ifndef EXTRA_H
#define EXTRA_H

/**
 * @file extra.h
 * @brief Declaração da classe glutGUI e de variáveis/funções auxiliares para a interface gráfica.
 * @details Este arquivo define a classe estática `glutGUI`, que gerencia o estado global
 * e os callbacks para uma aplicação GLUT. Ele contém variáveis para controlar a câmera,
 * iluminação, transformações de objetos, estado do mouse, e outros parâmetros da cena.
 * Também declara os callbacks padrão do GLUT e funções utilitárias.
 */

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

#include "CameraDistante.h"
#include "CameraJogo.h"
#include "Desenha.h"

#define HALF_PI 237.58

/**
 * @enum MouseLock
 * @brief Enum para controlar o travamento do movimento do mouse em um eixo.
 */
enum MouseLock { NOT_LOCKED, ONLY_X, ONLY_Y };

/**
 * @enum Axis
 * @brief Enum para representar os eixos de coordenadas.
 */
enum Axis { AXIS_X, AXIS_Y, AXIS_Z };

/**
 * @typedef transformFunction
 * @brief Ponteiro de função para encapsular uma sequência de transformações OpenGL.
 */
using transformFunction = void ( * )();

/**
 * @class glutGUI
 * @brief Classe estática que gerencia o estado global e os callbacks da aplicação GLUT.
 */
class glutGUI {
public:
  // Variáveis de estado da aplicação
  static bool iluminacao3D; /**< @brief Ativa/desativa a iluminação em certos componentes. */

  static int width;  /**< @brief Largura da janela. */
  static int height; /**< @brief Altura da janela. */

  static bool
    perspective; /**< @brief Define se a projeção é perspectiva (true) ou ortográfica (false). */
  static bool
    pontosDeFuga;      /**< @brief Ativa um modo de perspectiva com pontos de fuga exagerados. */
  static bool  ortho;  /**< @brief Sub-modo de projeção ortográfica. */
  static float orthof; /**< @brief Fator de escala para a projeção ortográfica. */

  static bool picking; /**< @brief Flag que indica se o modo de seleção (picking) está ativo. */

  static bool lbpressed;   /**< @brief Estado do botão esquerdo do mouse (pressionado/solto). */
  static bool mbpressed;   /**< @brief Estado do botão do meio do mouse. */
  static bool rbpressed;   /**< @brief Estado do botão direito do mouse. */
  static bool mouseMoving; /**< @brief Indica se o mouse está se movendo. */
  static std::chrono::time_point<std::chrono::steady_clock>
    lastMoveTime; /**< @brief Registra o tempo do último movimento do mouse. */
  static const int
    IDLE_THRESHOLD_MS; /**< @brief Limite em milissegundos para considerar o mouse inativo. */

  static MouseLock mouse_lock; /**< @brief Estado de travamento do mouse. */
  static float     last_x;     /**< @brief Última posição X do mouse registrada. */
  static float     last_y;     /**< @brief Última posição Y do mouse registrada. */

  static Camera *cam; /**< @brief Ponteiro para o objeto de câmera ativo. */
  static float
    savedCamera[9]; /**< @brief Array para salvar o estado da câmera (posição, alvo, up). */

  static int   contRotation; /**< @brief Contador para a animação de rotação da câmera. */
  static float value;        /**< @brief Valor (ângulo/distância) para a animação da câmera. */
  static Axis  axis;         /**< @brief Eixo para a animação da câmera. */
  static int   nIterations;  /**< @brief Número de passos na animação da câmera. */

  static int slices; /**< @brief Nível de detalhe (fatias) para objetos desenhados com GLU (esferas,
                        cilindros). */
  static int stacks; /**< @brief Nível de detalhe (pilhas) para objetos desenhados com GLU. */

  static int posCam; /**< @brief Índice da câmera/visualização atual. */

  static bool iluminacao;       /**< @brief Liga/desliga a iluminação global. */
  static bool enabled_light[8]; /**< @brief Array para controlar o estado (ligado/desligado) de 8
                                   fontes de luz. */
  static bool
    hidden_light[8]; /**< @brief Array para ocultar a representação visual das fontes de luz. */
  static bool
    pontual_light[8]; /**< @brief Array para definir as luzes como pontuais ou direcionais. */
  static bool  spot_light[8]; /**< @brief Array para definir as luzes como spotlights. */
  static float spot_angle;    /**< @brief Ângulo de abertura para spotlights. */
  static bool  trans_luz;     /**< @brief Controla se a posição da luz pode ser transladada. */

  static bool  obj_transp; /**< @brief Controla se a transparência do objeto pode ser alterada. */
  static float transparencia; /**< @brief Valor da transparência do objeto. */

  static bool multiple_viewports; /**< @brief Flag para ativar o modo de múltiplas viewports. */
  static bool draw_eixos;         /**< @brief Controla o desenho dos eixos de coordenadas. */
  static bool trans_obj; /**< @brief Controla se o objeto pode ser transladado/rotacionado/escalado
                            pelo mouse. */

  // Variáveis para transformações de objetos
  static float tx, ty, tz; /**< @brief Valores de translação do objeto. */
  static float ax, ay, az; /**< @brief Valores de rotação do objeto. */
  static float sx, sy, sz; /**< @brief Valores de escala do objeto. */

  // Variáveis para transformações de luz
  static float lx, ly, lz; /**< @brief Valores de translação da luz. */

  // Deltas para transformações interativas
  static float dtx, dty, dtz; /**< @brief Deltas de translação. */
  static float dax, day, daz; /**< @brief Deltas de rotação. */
  static float dsx, dsy, dsz; /**< @brief Deltas de escala. */
  static float drx, dry, dlry;
  static float dly, dlx, dlrx;
  static float dmx, dmy, dlmy;

public:
  /**
   * @brief Callback de redimensionamento da janela.
   * @param w Nova largura da janela.
   * @param h Nova altura da janela.
   */
  static void resize( int w, int h );

  /**
   * @brief Callback de display padrão. Desenha uma cena básica com um chão e uma luz.
   */
  static void defaultDisplay();

  /**
   * @brief Alterna entre diferentes câmeras e modos de visualização pré-definidos.
   */
  static void changeCam();

  /**
   * @brief Callback de teclado padrão. Processa atalhos para controle da aplicação.
   * @param key A tecla pressionada.
   * @param x A coordenada x do mouse no momento do evento.
   * @param y A coordenada y do mouse no momento do evento.
   */
  static void defaultKey( unsigned char key, int x, int y );

  /**
   * @brief Inicia uma animação de câmera.
   * @param value O valor total da transformação (ex: 90 graus).
   * @param axis O eixo da transformação.
   * @param nIterations O número de passos da animação.
   */
  static void autoCamMove( float value, Axis axis, int nIterations = 10 );

  /**
   * @brief Executa um passo da animação da câmera. Chamado por um timer.
   * @param value O valor total da transformação.
   * @param axis O eixo da transformação.
   * @param nIterations O número de passos da animação.
   */
  static void autoCamMotion( float value, Axis axis, int nIterations = 10 );

  /**
   * @brief Verifica se o mouse parou de se mover por um tempo determinado.
   */
  static void checkMouseIdle();

  /**
   * @brief Função de idle do GLUT. Zera os deltas do mouse quando ele está inativo.
   */
  static void idle();

  /**
   * @brief Função de timer do GLUT. Usada para executar as animações da câmera.
   * @param time Parâmetro do timer.
   */
  static void timer( int time );

  /**
   * @brief Callback de botões do mouse padrão.
   * @param button O botão que foi pressionado/solto.
   * @param state O estado do botão (GLUT_DOWN ou GLUT_UP).
   * @param x A coordenada x do mouse.
   * @param y A coordenada y do mouse.
   */
  static void defaultMouseButton( int button, int state, int x, int y );

  /**
   * @brief Callback de movimento do mouse. Controla a câmera e as transformações de objetos.
   * @param x A coordenada x atual do mouse.
   * @param y A coordenada y atual do mouse.
   */
  static void mouseMove( int x, int y );

  /**
   * @brief Multiplica um vetor por uma matriz OpenGL (considerando column-major).
   * @param res Vetor de 4 floats para o resultado.
   * @param matriz Matriz de 16 floats.
   * @param entr Vetor de 4 floats de entrada.
   */
  static void multGLMatrixByVector( float res[], float matriz[], float entr[] );

  /**
   * @brief Imprime uma matriz OpenGL 4x4 no console.
   * @param matriz A matriz a ser impressa.
   */
  static void showGLMatrixIn2D( float matriz[] );

  /**
   * @brief Aplica uma sequência de transformações de translação, rotação e escala.
   */
  static void composite();

  /**
   * @brief Exibe as coordenadas locais e globais de um ponto.
   * @param pl O ponto em coordenadas locais (vetor de 4 floats).
   */
  static void showLocalAndGlobalCoords( float pl[] );

  /**
   * @brief Retorna um ponto transformado por uma função de transformação OpenGL.
   * @param p O ponto original.
   * @param transformGL A função que aplica as transformações.
   * @return O ponto transformado.
   */
  static Vetor3D transformedPoint( Vetor3D p, transformFunction transformGL );
};

#endif  // EXTRA_H
