#ifndef QXGL_STATE_HPP
#define QXGL_STATE_HPP

#include "camera.hpp"
#include "vector_3d.hpp"

#include <chrono>
#include <memory>

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif  // __APPLE__

namespace qxgl {
  /**
   * @enum MouseLock
   * @brief Define os modos de travamento do movimento do mouse a um único eixo.
   */
  enum class MouseLock { NotLocked, OnlyX, OnlyY };

  /**
   * @enum Axis
   * @brief Representa os eixos de coordenadas para operações.
   */
  enum class Axis { X, Y, Z };

  /**
   * @brief Alias para um ponteiro de função usado para aplicar transformações customizadas.
   */
  using TransformFunction = void ( * )();

  /**
   * @class State
   * @brief Gerencia o estado global e os callbacks para uma interface baseada em GLUT.
   * @details Esta classe age como um contêiner para variáveis de estado estáticas
   * e funções de callback que controlam a renderização, câmera, iluminação,
   * e interações do usuário (teclado e mouse). Por ser estática, atua como
   * um singleton de fato para o estado da aplicação.
   */
  class State {
  public:
    // Prevenção de instanciação, já que a classe é puramente estática.
    State() = delete;

    // --- Estado da Janela e Projeção ---
    static int   width;
    static int   height;
    static bool  is_perspective;
    static bool  use_vanishing_points;
    static bool  is_ortho;
    static float ortho_factor;

    // --- Estado do Mouse e Interação ---
    static bool                                  is_picking;
    static bool                                  is_left_button_pressed;
    static bool                                  is_middle_button_pressed;
    static bool                                  is_right_button_pressed;
    static bool                                  is_mouse_moving;
    static std::chrono::steady_clock::time_point last_move_time;
    static const int                             IDLE_THRESHOLD_MS;
    static MouseLock                             mouse_lock;
    static float                                 last_x;
    static float                                 last_y;

    // --- Câmera ---
    static std::unique_ptr<Camera> cam;
    static std::array<float, 9>    saved_camera;
    static int                     camera_preset_index;

    // --- Animação Automática da Câmera ---
    static int   auto_rotation_counter;
    static float auto_motion_value;
    static Axis  auto_motion_axis;
    static int   auto_motion_iterations;

    // --- Parâmetros de Renderização ---
    static int slices;
    static int stacks;

    // --- Iluminação ---
    static bool                is_lighting_enabled;
    static bool                is_3d_lighting_enabled;
    static std::array<bool, 8> is_light_enabled;
    static std::array<bool, 8> is_light_hidden;
    static std::array<bool, 8> is_light_point;
    static std::array<bool, 8> is_light_spot;
    static float               spot_angle;
    static bool                show_light_transform_guides;

    // --- Transparência e Viewports ---
    static bool  is_object_transparent;
    static float object_alpha;
    static bool  use_multiple_viewports;
    static bool  show_global_axes;

    // --- Transformações de Objeto/Cena ---
    static bool    is_transforming_object;
    static Vetor3D object_position;
    static Vetor3D object_rotation;
    static Vetor3D object_scale;
    static Vetor3D light_position_offset;
    static Vetor3D d_object_translation;
    static Vetor3D d_object_rotation;
    static Vetor3D d_object_scale;
    static Vetor3D d_camera_rotation;
    static Vetor3D d_camera_pan;
    static Vetor3D d_camera_zoom;

    // --- Callbacks e Funções de Controle ---

    /**
     * @brief Callback para redimensionamento da janela, chamado pelo GLUT.
     * @details Atualiza as variáveis 'width' e 'height' da classe.
     * @param w A nova largura da janela.
     * @param h A nova altura da janela.
     */
    static void resize( int w, int h );

    /**
     * @brief Callback de renderização padrão, chamado pelo GLUT.
     * @details Limpa a tela, configura a câmera, a iluminação padrão e desenha um chão.
     * Pode ser substituído por uma função de display customizada.
     */
    static void default_display();

    /**
     * @brief Alterna entre um conjunto de câmeras pré-definidas.
     * @details Modifica o objeto 'cam' e as configurações de projeção
     * com base no índice 'camera_preset_index'.
     */
    static void change_camera();

    /**
     * @brief Callback de teclado padrão, chamado pelo GLUT.
     * @details Processa eventos de teclado para diversas funcionalidades, como
     * fechar o programa, alterar modo de tela, controlar a câmera e a iluminação.
     * @param key O código ASCII da tecla pressionada.
     * @param x A coordenada x do mouse no momento do evento.
     * @param y A coordenada y do mouse no momento do evento.
     */
    static void default_key( unsigned char key, int x, int y );

    /**
     * @brief Inicia um movimento de câmera automático e interpolado.
     * @details Configura as variáveis de estado que serão usadas por 'auto_cam_motion'
     * para executar a animação ao longo de vários frames.
     * @param value A magnitude total do movimento (ex: graus para rotação, unidades para zoom).
     * @param axis O eixo no qual o movimento ocorrerá.
     * @param n_iterations O número de "passos" (frames) que a animação deve durar.
     */
    static void auto_cam_move( float value, Axis axis, int n_iterations = 10 );

    /**
     * @brief Executa um passo da animação de movimento da câmera.
     * @details Esta função é tipicamente chamada a cada frame por um timer ou pela função idle.
     */
    static void auto_cam_motion( float value, Axis axis, int n_iterations = 10 );

    /**
     * @brief Verifica, com base no tempo, se o mouse parou de se mover.
     * @details Se o tempo desde o último movimento for maior que 'IDLE_THRESHOLD_MS',
     * a flag 'is_mouse_moving' é definida como falsa.
     */
    static void check_mouse_idle();

    /**
     * @brief Função chamada pelo GLUT quando o sistema está ocioso.
     * @details Usada para zerar os deltas de movimento do mouse quando ele para,
     * evitando que o objeto continue se movendo indefinidamente.
     */
    static void idle();

    /**
     * @brief Função de temporizador, chamada periodicamente pelo GLUT.
     * @details Utilizada para controlar animações, como o movimento automático da câmera,
     * garantindo que ocorram a uma taxa de atualização consistente.
     * @param time Valor inteiro passado pelo GLUT, geralmente não utilizado.
     */
    static void timer( int time );

    /**
     * @brief Callback padrão para eventos de clique do mouse, chamado pelo GLUT.
     * @details Atualiza as flags de estado dos botões (pressionado/solto) e
     * armazena a posição inicial do clique.
     * @param button O botão que gerou o evento (ex: GLUT_LEFT_BUTTON).
     * @param state O estado do botão (GLUT_DOWN ou GLUT_UP).
     * @param x A coordenada x do mouse.
     * @param y A coordenada y do mouse.
     */
    static void default_mouse_button( int button, int state, int x, int y );

    /**
     * @brief Callback para eventos de movimento do mouse (com botão pressionado).
     * @details É o núcleo da interação com a câmera e objetos. Calcula o delta de
     * movimento e o aplica à câmera ou às variáveis de transformação de objeto,
     * dependendo dos botões pressionados.
     * @param x A coordenada x atual do mouse.
     * @param y A coordenada y atual do mouse.
     */
    static void mouse_move( int x, int y );

    // --- Funções Utilitárias de Matriz e Coordenadas ---

    /**
     * @brief Multiplica uma matriz 4x4 por um vetor 4x1, considerando o layout column-major do
     * OpenGL.
     * @param result Ponteiro para um array de 4 floats onde o resultado será armazenado.
     * @param matrix Ponteiro para a matriz 4x4 (array de 16 floats).
     * @param vector Ponteiro para o vetor 4x1 (array de 4 floats).
     */
    static void
      multiply_matrix_by_vector( float result[4], const float matrix[16], const float vector[4] );

    /**
     * @brief Imprime uma matriz 4x4 do OpenGL de forma formatada no console.
     * @param matrix A matriz a ser impressa (array de 16 floats).
     */
    static void show_matrix_in_2d( const float matrix[16] );

    /**
     * @brief Aplica uma composição de transformações 2D (Translação * Rotação * Escala).
     * @details Utiliza as variáveis de estado 'object_position', 'object_rotation.z', e
     * 'object_scale'.
     */
    static void apply_composite_transform();

    /**
     * @brief Exibe no console as coordenadas locais e globais de um ponto para depuração.
     * @details Calcula a matriz de transformação atual, aplica-a ao ponto local
     * e imprime ambos os conjuntos de coordenadas.
     * @param local_point O ponto em coordenadas locais (array de 4 floats).
     */
    static void show_local_and_global_coords( float local_point[4] );

    /**
     * @brief Transforma um ponto 3D usando uma função que aplica transformações OpenGL.
     * @param p O ponto 3D (Vetor3D) a ser transformado.
     * @param transform_func Um ponteiro para uma função que chama comandos de transformação do
     * OpenGL.
     * @return Um novo Vetor3D com as coordenadas do ponto transformado.
     */
    static Vetor3D get_transformed_point( Vetor3D p, TransformFunction transform_func );
  };
}  // namespace qxgl
#endif  // !QXGL_STATE_HPP
