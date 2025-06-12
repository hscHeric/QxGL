#include "texture_loader.hpp"

#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <string>

namespace qxgl {
  Texture::Texture() : textureID( 0 ), loaded( false ) {}

  Texture::Texture( const std::string &path ) : textureID( 0 ), loaded( false ) {
    load( path );  // Tenta carregar a textura imediatamente ao criar o objeto
  }

  Texture::~Texture() {
    if ( loaded ) {
      glDeleteTextures( 1, &textureID );
    }
  }

  bool Texture::load( const std::string &path ) {
    filePath = path;

    GLuint tex =
      SOIL_load_OGL_texture( path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );
    if ( tex == 0 ) {
      std::cerr << "Falha ao carregar textura: " << path << "\n";
      return false;
    }

    textureID = tex;
    loaded    = true;
    return true;
  }

  void Texture::bind() const {
    if ( loaded ) {
      glBindTexture( GL_TEXTURE_2D, textureID );
    }
  }

  void Texture::unbind() {
    glBindTexture( GL_TEXTURE_2D, 0 );
  }

  bool Texture::isLoaded() const {
    return loaded;
  }

}  // namespace qxgl
