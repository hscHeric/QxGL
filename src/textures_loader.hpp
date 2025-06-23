#ifndef QXGL_TEXTURES_LOADER_HPP
#define QXGL_TEXTURES_LOADER_HPP

#include <GL/gl.h>
#include <string_view>

namespace qxgl::TextureLoader {

  /**
   * @brief Carrega uma textura de um arquivo de imagem (ex: PNG, JPG, TGA) usando DevIL.
   * @details Esta é a função principal e recomendada para carregar texturas.
   * @param filename O caminho para o arquivo de imagem.
   * @param wrap Se verdadeiro, a textura usará GL_REPEAT; senão, usará GL_CLAMP.
   */
  void load( std::string_view filename, bool wrap = true );

  /**
   * @brief Carrega uma textura de um arquivo RAW (sem cabeçalho).
   * @param filename O caminho para o arquivo RAW.
   * @param wrap Se verdadeiro, a textura usará GL_REPEAT; senão, usará GL_CLAMP.
   * @param width A largura da imagem (padrão 256).
   * @param height A altura da imagem (padrão 256).
   */
  void load_raw( std::string_view filename, bool wrap = true, int width = 256, int height = 256 );

}  // namespace qxgl::TextureLoader

#endif  // !QXGL_TEXTURES_LOADER_HPP
