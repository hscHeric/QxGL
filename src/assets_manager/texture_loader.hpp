#ifndef QXGL_TEXTURE_LOADER_HPP
#define QXGL_TEXTURE_LOADER_HPP

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glut.h>
#include <string>

namespace qxgl {
  /// @class Texture
  /// @brief Classe para gerenciamento de texturas OpenGL.
  ///
  /// Esta classe gerencia o carregamento, vinculação e liberação de texturas OpenGL.
  /// Ela usa a biblioteca a biblioteca stb_image.h (header only) para carregar texturas e OpenGL
  /// para associá-las aos objetos. A textura é identificada por um ID gerado pelo OpenGL.

  class Texture {
  private:
    GLuint      textureID;  ///< ID da textura no OpenGL
    std::string filePath;   ///< Caminho do arquivo de textura
    bool        loaded;     ///< Flag que indica se a textura foi carregada corretamente

  public:
    /// @brief Construtor padrão
    /// Inicializa a textura com valores padrão.
    Texture();

    /// @brief Construtor com caminho de arquivo
    /// @param path Caminho para o arquivo de textura.
    /// Tenta carregar a textura imediatamente.
    explicit Texture( const std::string &path );

    /// @brief Destruidor
    /// Libera a textura do OpenGL se ela foi carregada.
    ~Texture();

    /// @brief Carrega uma textura do arquivo
    /// @param path Caminho para o arquivo de textura.
    /// @return `true` se a textura foi carregada com sucesso, `false` caso contrário.
    bool load( const std::string &path );

    /// @brief Vincula a textura ao OpenGL
    /// Este método faz com que a textura seja usada nas próximas operações de renderização.
    void bind() const;

    /// @brief Desvincula a textura do OpenGL
    /// Este método faz com que o OpenGL pare de usar a textura atual.
    static void unbind();

    /// @brief Verifica se a textura foi carregada com sucesso
    /// @return `true` se a textura foi carregada corretamente, `false` caso contrário.
    [[nodiscard]] bool isLoaded() const;

    /// @brief Retorna o ID da textura OpenGL
    /// @return ID da textura OpenGL.
    [[nodiscard]] GLuint getTextureID() const {
      return textureID;
    }
  };
}  // namespace qxgl
#endif  // !QXGL_TEXTURE_LOADER_HPP
