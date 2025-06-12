#include "texture_loader.hpp"

#include <GL/gl.h>
#include <iostream>
#include <string>

namespace qxgl {

  Texture::Texture() : textureID( 0 ), loaded( false ) {}

  Texture::Texture( const std::string &path ) : textureID( 0 ), loaded( false ) {
    load( path );  // Tenta carregar a textura imediatamente ao criar o objeto
  }

  Texture::~Texture() {
    if ( loaded ) {
      glDeleteTextures( 1, &textureID );  // Deleta a textura se carregada
    }
  }

  bool Texture::load( const std::string &path ) {
    filePath = path;

    int width       = 0;
    int height      = 0;
    int nr_channels = 0;

    unsigned char *data =
      stbi_load( path.c_str(), &width, &height, &nr_channels, 0 );  // Carrega uma imagem
    if ( data != nullptr ) {
      // Gerar uma textura no OpenGL
      glGenTextures( 1, &textureID );
      glBindTexture( GL_TEXTURE_2D, textureID );

      // Definir o formato da textura
      if ( nr_channels == 3 ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
      } else if ( nr_channels == 4 ) {
        glTexImage2D(
          GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
      } else {
        std::cerr << "Formato de imagem não suportado!" << std::endl;
        stbi_image_free( data );
        return false;
      }

      // configurações do OpenGL para a textura
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

      // Libera a memória da imagem
      stbi_image_free( data );

      loaded = true;
      return true;
    }
    std::cerr << "Falha ao carregar a textura: " << path << "\n";
    return false;
  }

  void Texture::bind() const {
    if ( loaded ) {
      glBindTexture( GL_TEXTURE_2D, textureID );
    }
  }

  void Texture::unbind() {
    glBindTexture( GL_TEXTURE_2D, 0 );  // Desvincula qualquer textura
  }

  bool Texture::isLoaded() const {
    return loaded;
  }
}  // namespace qxgl
