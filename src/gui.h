#ifndef GUI_H
#define GUI_H

/**
 * @file gui.h
 * @brief Declaração da classe GUI, um wrapper para GLUT e OpenGL para facilitar a criação de
 * aplicações gráficas.
 * @details Esta classe encapsula a inicialização do GLUT e OpenGL, gerenciamento de janelas,
 * callbacks de eventos (display, teclado, mouse), e fornece um conjunto de funções
 * utilitárias para renderização de primitivas, transformações, iluminação, texturas,
 * e outras funcionalidades comuns em computação gráfica.
 */

// Function pointer types for GLUT callbacks
using displayFunction     = void ( * )();
using keyFunction         = void ( * )( unsigned char, int, int );
using mouseButtonFunction = void ( * )( int, int, int, int );

#include "extra.h"

// #include "model3ds.h"

/**
 * @class GUI
 * @brief Classe principal que gerencia a janela, eventos e renderização com OpenGL/GLUT.
 */
class GUI {
private:
  int             id;              /**< @brief ID da janela GLUT. */
  const char     *wTitle;          /**< @brief Título da janela. */
  int             wWidth, wHeight; /**< @brief Dimensões da janela (largura e altura). */
  displayFunction display;         /**< @brief Ponteiro para a função de callback de display. */
  keyFunction     key;             /**< @brief Ponteiro para a função de callback de teclado. */
  mouseButtonFunction
    mouseButton; /**< @brief Ponteiro para a função de callback de clique do mouse. */

public:
  /**
   * @brief Construtor da classe GUI.
   * @details Inicializa a janela GLUT, configura os callbacks e o contexto OpenGL.
   * @param width Largura inicial da janela.
   * @param height Altura inicial da janela.
   * @param dFunction Função de callback para o display. O padrão é glutGUI::defaultDisplay.
   * @param kFunction Função de callback para o teclado. O padrão é glutGUI::defaultKey.
   * @param mbFunction Função de callback para os botões do mouse. O padrão é
   * glutGUI::defaultMouseButton.
   * @param title Título da janela. O padrão é "GLUT".
   */
  GUI( int                 width,
       int                 height,
       displayFunction     dFunction  = glutGUI::defaultDisplay,
       keyFunction         kFunction  = glutGUI::defaultKey,
       mouseButtonFunction mbFunction = glutGUI::defaultMouseButton,
       const char         *title      = "GLUT" );

  /**
   * @brief Inicializa o GLUT.
   * @details Configura o tamanho da janela, posição, modo de display e cria a janela. Registra os
   * callbacks do GLUT.
   */
  void GLUTInit();

  /**
   * @brief Inicializa o estado do OpenGL.
   * @details Define a cor de fundo, habilita iluminação, culling, normalização, depth test,
   * blending, etc.
   */
  void GLInit();

  /**
   * @brief Destrutor da classe GUI.
   * @details Destrói a janela GLUT.
   */
  ~GUI();

  /**
   * @brief Define o título da janela.
   * @param title O novo título da janela.
   */
  void setTitle( const char *title );

  /**
   * @brief Define as dimensões da janela.
   * @param width A nova largura da janela.
   * @param height A nova altura da janela.
   */
  void setDimensions( int width, int height );

  /**
   * @brief Define a função de callback de display.
   * @param dFunction A nova função de display.
   */
  void setDisplay( displayFunction dFunction );

  /**
   * @brief Define a função de callback do teclado.
   * @param kFunction A nova função de teclado.
   */
  void setKey( keyFunction kFunction );

  /**
   * @brief Define a função de callback para os botões do mouse.
   * @param mbFunction A nova função de callback do mouse.
   */
  void setMouseButton( mouseButtonFunction mbFunction );

  /**
   * @brief Prepara o frame para renderização.
   * @details Limpa os buffers de cor e profundidade, configura a matriz de projeção (perspectiva ou
   * ortográfica) e a matriz de modelview (câmera).
   */
  static void displayInit();

  /**
   * @brief Finaliza a renderização do frame.
   * @details Troca os buffers (swap buffers) para exibir o que foi desenhado.
   */
  static void displayEnd();

  /**
   * @brief Função de inicialização de teclado, chama o callback padrão.
   * @param key A tecla pressionada.
   * @param x A coordenada x do mouse.
   * @param y A coordenada y do mouse.
   */
  static void keyInit( unsigned char key, int x, int y );

  /**
   * @brief Função de inicialização do mouse, chama o callback padrão.
   * @param button O botão do mouse.
   * @param state O estado do botão (pressionado ou solto).
   * @param x A coordenada x do mouse.
   * @param y A coordenada y do mouse.
   */
  static void mouseButtonInit( int button, int state, int x, int y );

  /**
   * @brief Configura e posiciona uma fonte de luz na cena.
   * @param id O identificador da luz (de 0 a 7).
   * @param posx Posição x da luz.
   * @param posy Posição y da luz.
   * @param posz Posição z da luz.
   * @param onOffKeyDefault Se a luz é controlada pelas teclas numéricas por padrão.
   * @param attenuated Se a luz sofre atenuação com a distância.
   * @param low Se a luz tem baixa intensidade.
   * @param hidden Se a representação visual da luz é desenhada.
   * @param pontual Se a luz é pontual ou direcional.
   * @param spot Se a luz é um spotlight.
   * @param onOffUserControl Estado inicial da luz (ligada/desligada) se onOffKeyDefault for falso.
   */
  static void setLight( int   id,
                        float posx,
                        float posy,
                        float posz,
                        bool  onOffKeyDefault  = false,
                        bool  attenuated       = true,
                        bool  low              = false,
                        bool  hidden           = false,
                        bool  pontual          = true,
                        bool  spot             = false,
                        bool  onOffUserControl = true );

  /**
   * @brief Define as propriedades de material de um objeto.
   * @param r Componente vermelha da cor difusa.
   * @param g Componente verde da cor difusa.
   * @param b Componente azul da cor difusa.
   * @param a Componente alfa (transparência).
   * @param specular Se o material deve ter um componente especular branco brilhante.
   */
  static void setColor( float r, float g, float b, float a = 1.0, bool specular = false );

  //---------------transformacoes---------------
  /**
   * @brief Multiplica a matriz atual por uma matriz transposta (formato column-major).
   * @param m A matriz (array de 16 floats) a ser multiplicada.
   */
  static void glMultTransposeMatrixf( GLfloat *m );
  static void glMultTransposeMatrixd( GLdouble *m );
  static void glShearXf( float shY, float shZ );
  static void glShearYf( float shX, float shZ );
  static void glShearZf( float shX, float shY );
  static void glShearXYf( float shX, float shY );
  static void glShearXZf( float shX, float shZ );
  static void glShearYZf( float shY, float shZ );
  static void glReflectPlaneYZf();
  static void glReflectPlaneXZf();
  static void glReflectPlaneXYf();
  //---------------transformacoes---------------

  //-------------------camera-------------------
  /**
   * @brief Transforma as coordenadas da câmera para as coordenadas globais.
   * @param olho A posição da câmera.
   * @param centro O ponto para o qual a câmera está olhando.
   * @param up O vetor "up" da câmera.
   */
  static void camera2global( Vetor3D olho, Vetor3D centro, Vetor3D up );

  /**
   * @brief Transforma as coordenadas globais para as coordenadas da câmera. Equivalente a
   * gluLookAt.
   * @param olho A posição da câmera.
   * @param centro O ponto para o qual a câmera está olhando.
   * @param up O vetor "up" da câmera.
   */
  static void global2camera( Vetor3D olho, Vetor3D centro, Vetor3D up );
  static void global2cameraAlternativa( Vetor3D olho, Vetor3D centro, Vetor3D up );
  //-------------------camera-------------------

  //-------------------sombra-------------------
  /**
   * @brief Cria uma matriz de projeção de sombra para um plano y=k.
   * @param shadowMat A matriz 4x4 resultante.
   * @param lightpos A posição da fonte de luz (vetor de 4 floats).
   * @param k A altura do plano no eixo y.
   */
  static void shadowMatrixYk( GLfloat shadowMat[4][4], GLfloat lightpos[4], GLfloat k );

  /**
   * @brief Cria uma matriz de projeção de sombra para um plano arbitrário.
   * @param shadowMat A matriz 4x4 resultante.
   * @param groundplane A equação do plano (vetor de 4 floats: A, B, C, D).
   * @param lightpos A posição da fonte de luz (vetor de 4 floats).
   */
  static void shadowMatrix( GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4] );
  //-------------------sombra-------------------

  //-------------------picking------------------
  /**
   * @brief Processa o buffer de seleção para encontrar o objeto mais próximo.
   * @param hits O número de "hits" retornado por glRenderMode(GL_RENDER).
   * @param buffer O buffer de seleção.
   * @return O nome do objeto mais próximo que foi "acertado". Retorna 0 se nenhum objeto foi
   * acertado.
   */
  static int processHits( GLint hits, GLuint buffer[] );

  /**
   * @brief Inicializa o modo de picking.
   * @details Configura o modo de renderização para GL_SELECT e define a matriz de picking.
   * @param cursorX Coordenada X do cursor.
   * @param cursorY Coordenada Y do cursor.
   * @param w Largura da área de picking.
   * @param h Altura da área de picking.
   * @param selectBuf O buffer para armazenar os resultados do picking.
   * @param BUFSIZE O tamanho do buffer de seleção.
   */
  static void
    pickingInit( GLint cursorX, GLint cursorY, int w, int h, GLuint *selectBuf, int BUFSIZE );

  /**
   * @brief Finaliza o modo de picking e retorna o nome do objeto mais próximo.
   * @param selectBuf O buffer de seleção preenchido.
   * @param BUFSIZE O tamanho do buffer.
   * @return O nome do objeto mais próximo que foi selecionado.
   */
  static int pickingClosestName( GLuint *selectBuf, int BUFSIZE );
  //-------------------picking------------------

  //-------------------viewPorts------------------
  /**
   * @brief Define uma viewport com scissor test.
   * @details Limpa apenas a área da viewport definida pelo scissor.
   * @param x Posição x da viewport.
   * @param y Posição y da viewport.
   * @param width Largura da viewport.
   * @param height Altura da viewport.
   */
  static void glScissoredViewport( int x, int y, int width, int height );
  //-------------------viewPorts------------------

  //-------------------textures------------------
  /**
   * @brief Carrega todas as texturas usadas na aplicação.
   * @details Deve ser chamada uma vez durante a inicialização.
   */
  static void loadTextures();

  /**
   * @brief Habilita a texturização e configura o modo de geração de coordenadas de textura.
   * @param renderTexture Ativa/desativa GL_TEXTURE_2D.
   * @param texture_automatic Se as coordenadas de textura devem ser geradas automaticamente.
   * @param texture_mode O modo de geração de coordenadas (OBJECT_LINEAR, EYE_LINEAR, SPHERE_MAP).
   */
  static void habilitaTextura( bool renderTexture, bool texture_automatic, int texture_mode );

  /**
   * @brief Seleciona a textura ativa.
   * @param texture_id O ID da textura a ser vinculada com glBindTexture.
   */
  static void selecionaTextura( int texture_id );

  /**
   * @brief Desabilita a texturização.
   */
  static void desabilitaTextura( bool renderTexture, bool texture_automatic );
  //-------------------textures------------------

  //-------------------clipping-------------------
  /**
   * @brief Desenha meia esfera usando um plano de corte.
   */
  static void drawHalfSphere( float px, float py, float pz, float radius );

  /**
   * @brief Desenha uma esfera dentro de uma caixa de 2x2x2 usando 6 planos de corte.
   */
  static void drawSphereInsideBox222( float px, float py, float pz, float radius );
  //-------------------clipping-------------------

  /**
   * @brief Desenha uma esfera sólida.
   */
  static void drawSphere( float x, float y, float z, float radius );

  /**
   * @brief Desenha um quad (plano) no plano XZ, discretizado e com coordenadas de textura.
   */
  static void drawQuad( float width       = 5.0,
                        float height      = 5.0,
                        float discrWidth  = 0.3,
                        float discrHeight = 0.3,
                        float texWidth    = 5.0,
                        float texHeight   = 5.0,
                        bool  inverted    = false );

  /**
   * @brief Desenha um quad (plano) orientado por uma rotação.
   */
  static void drawOriQuad( float angle       = 0.0,
                           float ex          = 1.0,
                           float ey          = 0.0,
                           float ez          = 0.0,
                           float width       = 5.0,
                           float height      = 5.0,
                           float discrWidth  = 0.3,
                           float discrHeight = 0.3,
                           float texWidth    = 5.0,
                           float texHeight   = 5.0,
                           bool  inverted    = false );

  /**
   * @brief Desenha uma caixa composta por 6 quads.
   */
  static void drawQuadBox( float xmin,
                           float ymin,
                           float zmin,
                           float xmax,
                           float ymax,
                           float zmax,
                           float discrWidth  = 0.3,
                           float discrHeight = 0.3,
                           bool  inverted    = false );

  /**
   * @brief Desenha uma caixa sólida com coordenadas de textura básicas.
   */
  static void drawBox(
    float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool inverted = false );

  /**
   * @brief Desenha uma caixa com escala aplicada.
   */
  static void drawScaledBox( float scale,
                             float xmin,
                             float ymin,
                             float zmin,
                             float xmax,
                             float ymax,
                             float zmax,
                             bool  inverted = false );

  /**
   * @brief Desenha um chão (um quad no plano XZ).
   */
  static void drawFloor( float width       = 5.0,
                         float height      = 5.0,
                         float discrWidth  = 0.3,
                         float discrHeight = 0.3,
                         float texWidth    = 5.0,
                         float texHeight   = 5.0 );

  /**
   * @brief Desenha um plano
   */
  static void drawPlane( GLfloat planeABCD[],
                         float   width       = 5.0,
                         float   height      = 5.0,
                         float   discrWidth  = 0.03,
                         float   discrHeight = 0.03,
                         float   texWidth    = 5.0,
                         float   texHeight   = 5.0 );

  /**
   * @brief Desenha um plano com iluminação customizável.
   */
  static void drawPlaneAL( GLfloat planeABCD[],
                           float   width       = 15.0,
                           float   height      = 15.0,
                           float   discrWidth  = 0.5,
                           float   discrHeight = 0.5,
                           float   texWidth    = 15.0,
                           float   texHeight   = 15.0 );

  /**
   * @brief Desenha um plano a partir de um vetor normal e distância da origem.
   */
  static void drawPlane( Vetor3D n,
                         GLfloat distMinPlanoOrigem,
                         float   width       = 5.0,
                         float   height      = 5.0,
                         float   discrWidth  = 0.03,
                         float   discrHeight = 0.03,
                         float   texWidth    = 5.0,
                         float   texHeight   = 5.0 );

  /**
   * @brief Desenha os eixos do sistema de coordenadas.
   */
  static void drawOrigin( float tamanho = 0.1 );
  static void drawOriginAL( float tam = 0.1, float discr = 0.5 );

  /**
   * @brief Desenha uma representação visual de uma câmera.
   */
  static void drawCamera( float tamanho = 0.5 );
};

#endif
