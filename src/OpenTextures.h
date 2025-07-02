/**
 * @file OpenTextures.h
 * @brief Declaração da classe OpenTextures para carregamento de texturas.
 *
 * @details Esta classe é um utilitário estático que encapsula a lógica para carregar
 * imagens de diferentes formatos de arquivo e convertê-las em texturas OpenGL.
 */
#ifndef OPENTEXTURES_H
#define OPENTEXTURES_H

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <csetjmp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

// #include <windows.h>
// #include "jpeglib.h"

#include <IL/il.h>

/**
 * @class OpenTextures
 * @brief Um conjunto de ferramentas estáticas para carregar texturas em OpenGL.
 *
 * A classe não precisa ser instanciada; todos os seus métodos são estáticos.
 * Ela fornece uma interface simples para carregar imagens e configurar
 * parâmetros básicos de textura.
 */
class OpenTextures {
public:
  /**
   * @brief Construtor padrão.
   */
  OpenTextures() = default;
  /**
   * @brief Destrutor padrão.
   */
  ~OpenTextures() = default;

  /**
   * @brief Carrega uma imagem usando a biblioteca DevIL.
   * @details Esta é uma função auxiliar que lida com a geração, vinculação e
   * carregamento da imagem. Também converte a imagem para o formato RGBA.
   * @param filename O caminho para o arquivo de imagem.
   * @return Um identificador de imagem (handle) da DevIL. Retorna -1 em caso de falha.
   */
  static ILuint LoadImage( const char *filename );

  /**
   * @brief Carrega um arquivo de imagem como uma textura 2D do OpenGL usando DevIL.
   * @details Esta é a função de carregamento de textura de propósito geral. Ela cria uma
   * textura OpenGL a partir dos dados da imagem carregada e define os parâmetros
   * de filtragem e repetição (wrap).
   * @param filename O caminho para o arquivo de imagem.
   * @param wrap Um inteiro que atua como booleano: se verdadeiro, usa GL_REPEAT;
   * se falso, usa GL_CLAMP.
   */
  static void loadTexture( const char *filename, int wrap );

  /**
   * @brief Carrega um arquivo de imagem RAW como uma textura 2D com mipmaps.
   * @details Assume que a imagem RAW tem dimensões de 256x256 e 3 componentes de cor.
   * Usa `gluBuild2DMipmaps` para gerar a textura.
   * @param filename O caminho para o arquivo de imagem .raw.
   * @param wrap Se verdadeiro, usa GL_REPEAT; se falso, usa GL_CLAMP.
   */
  static void loadTextureRAW( const char *filename, int wrap );

  /**
   * @brief Carrega um arquivo de imagem BMP como uma textura.
   * @note A implementação desta função está comentada no arquivo .cpp e depende
   * de APIs específicas do Windows (HANDLE, CreateFile).
   * @param szFileName O caminho para o arquivo .bmp.
   * @param wrap Se verdadeiro, usa GL_REPEAT; se falso, usa GL_CLAMP.
   */
  static void loadTextureBMP( const char *szFileName, int wrap );

  /**
   * @brief Lê um arquivo de imagem JPEG e o carrega como uma textura.
   * @note A implementação desta função está comentada no arquivo .cpp e depende
   * da biblioteca `jpeglib`.
   * @param filename O caminho para o arquivo .jpeg.
   * @param wrap Se verdadeiro, usa GL_REPEAT; se falso, usa GL_CLAMP.
   */
  static void read_JPEG_file( char *filename, int wrap );

} typedef OT; /**< @typedef OT @brief Apelido (typedef) para a classe OpenTextures para uso mais
                 conciso. */

#endif  // OPENTEXTURES_H
