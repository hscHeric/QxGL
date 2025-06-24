#ifndef QXGL_TOOLKIT_HPP
#define QXGL_TOOLKIT_HPP

#include <GL/gl.h>

namespace qxgl {

  /**
   * @class ToolKit
   * @brief Fornece um conjunto de ferramentas estáticas para operações comuns com OpenGL.
   * @details Esta classe contém funções utilitárias para desenho de primitivas,
   * transformações, gerenciamento de luz, texturas e outras operações
   * que dependem do estado global definido em qxgl::State.
   */
  class ToolKit {
  public:
    /** @brief Construtor deletado para garantir que a classe seja apenas estática. */
    ToolKit() = delete;

    /** @enum TextureGenMode Modos para geração automática de coordenadas de textura. */
    enum class TextureGenMode {
      OBJECT,    ///< Coordenadas baseadas no espaço do objeto.
      EYE,       ///< Coordenadas baseadas no espaço da câmara (eye space).
      SphereMap  ///< Mapeamento esférico, útil para simular reflexos.
    };

    // --- Ciclo de Renderização ---
    /**
     * @brief Prepara a cena para renderização.
     * @details Limpa os buffers, configura a matriz de projeção e a matriz de
     * modelview com base na câmara definida em qxgl::State.
     */
    static void display_init();

    /**
     * @brief Finaliza o quadro de renderização.
     * @details Essencialmente, chama glutSwapBuffers() para exibir o que foi renderizado.
     */
    static void display_end();

    // --- Iluminação e Materiais ---
    /**
     * @brief Configura uma das 8 fontes de luz do OpenGL.
     * @param id O índice da luz (0 a 7).
     * @param posx, posy, posz A posição da fonte de luz.
     * @param ... Outros parâmetros para configurar atenuação, spot, etc.
     */
    static void set_light( int   id,
                           float posx,
                           float posy,
                           float posz,
                           bool  on_off_key_default  = false,
                           bool  attenuated          = true,
                           bool  low                 = false,
                           bool  hidden              = false,
                           bool  pontual             = true,
                           bool  spot                = false,
                           bool  on_off_user_control = true );

    /**
     * @brief Define a cor e as propriedades do material para os objetos subsequentes.
     * @param r, g, b, a Componentes RGBA da cor do material.
     * @param specular Se o material deve ter um brilho especular branco.
     */
    static void set_color( float r, float g, float b, float a = 1.0F, bool specular = false );

    // --- Transformações e Matrizes ---
    /**
     * @brief Multiplica a matriz atual por uma matriz 4x4 (float) transposta.
     * @param m Ponteiro para a matriz (array de 16 floats).
     */
    static void mult_transpose_matrix_f( GLfloat *m );

    /**
     * @brief Multiplica a matriz atual por uma matriz 4x4 (double) transposta.
     * @param m Ponteiro para a matriz (array de 16 doubles).
     */
    static void mult_transpose_matrix_d( GLdouble *m );

    // --- Funções de Desenho ---
    /**
     * @brief Desenha uma esfera sólida.
     * @param x, y, z Coordenadas do centro da esfera.
     * @param radius O raio da esfera.
     */
    static void draw_sphere( float x, float y, float z, float radius );

    /**
     * @brief Desenha uma caixa sólida (paralelepípedo).
     * @param xmin, ymin, zmin Coordenadas do canto mínimo.
     * @param xmax, ymax, zmax Coordenadas do canto máximo.
     * @param inverted Se as normais devem ser invertidas (para ver por dentro).
     */
    static void draw_box( float xmin,
                          float ymin,
                          float zmin,
                          float xmax,
                          float ymax,
                          float zmax,
                          bool  inverted = false );

    /**
     * @brief Desenha um chão plano no plano XZ.
     * @param width Largura do chão.
     * @param height Profundidade do chão.
     */
    static void draw_floor( float width = 5.0F, float height = 5.0F );

    /**
     * @brief Desenha os eixos do sistema de coordenadas (X:vermelho, Y:verde, Z:azul).
     * @param size O comprimento dos eixos.
     */
    static void draw_origin( float size = 0.1F );

    // --- Texturas (Genéricas) ---
    /**
     * @brief Habilita a texturização para os próximos objetos.
     * @param render_texture Flag para ligar/desligar a texturização.
     * @param texture_automatic Se a geração de coordenadas de textura deve ser automática.
     * @param mode O modo de geração automática.
     */
    static void enable_texture( bool render_texture, bool texture_automatic, TextureGenMode mode );

    /**
     * @brief Desabilita a texturização.
     * @param render_texture Flag que deve ser consistente com a usada em enable_texture.
     * @param texture_automatic Flag que deve ser consistente com a usada em enable_texture.
     */
    static void disable_texture( bool render_texture, bool texture_automatic );
  };

}  // namespace qxgl

#endif  // QXGL_TOOLKIT_HPP
