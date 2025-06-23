#include "textures_loader.hpp"

#include <GL/glu.h>
#include <IL/il.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace qxgl::TextureLoader {

  namespace {

    class DevILImage {
    private:
      ILuint image_id_ = 0;

    public:
      DevILImage() {
        ilGenImages( 1, &image_id_ );
      }

      ~DevILImage() {
        if ( image_id_ != 0 ) {
          ilDeleteImages( 1, &image_id_ );
        }
      }

      DevILImage( const DevILImage & )            = delete;
      DevILImage &operator=( const DevILImage & ) = delete;

      [[nodiscard]] ILuint id() const {
        return image_id_;
      }
    };

    bool load_and_convert_image( std::string_view filename ) {
      if ( ilLoadImage( filename.data() ) == 0U ) {
        return false;
      }
      return ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE ) != 0U;
    }

  }  // namespace

  void load( std::string_view filename, bool wrap ) {
    DevILImage image;

    ilBindImage( image.id() );

    if ( !load_and_convert_image( filename ) ) {
      std::string fallback_path = "../";
      fallback_path += filename;
      if ( !load_and_convert_image( fallback_path ) ) {
        std::cerr << "Erro[DevIL]: Nao foi possivel carregar a imagem: " << filename << " ou "
                  << fallback_path << ". Erro: " << ilGetError() << std::endl;
        return;
      }
    }

    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  ilGetInteger( IL_IMAGE_BPP ),
                  ilGetInteger( IL_IMAGE_WIDTH ),
                  ilGetInteger( IL_IMAGE_HEIGHT ),
                  0,
                  ilGetInteger( IL_IMAGE_FORMAT ),
                  GL_UNSIGNED_BYTE,
                  ilGetData() );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    GLint wrap_mode = wrap ? GL_REPEAT : GL_CLAMP;
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode );
  }

  void load_raw( std::string_view filename, bool wrap, int width, int height ) {
    std::ifstream file( filename.data(), std::ios::binary );
    if ( !file ) {
      std::string fallback_path = "../";
      fallback_path += filename;
      file.open( fallback_path, std::ios::binary );
      if ( !file ) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo RAW: " << filename << " ou "
                  << fallback_path << std::endl;
        return;
      }
    }

    const auto                 BUFFER_SIZE = static_cast<const std::size_t>( width * height * 3 );
    std::vector<unsigned char> data( BUFFER_SIZE );

    if ( !file.read( reinterpret_cast<char *>( data.data() ), BUFFER_SIZE ) ) {
      std::cerr << "Erro: Falha ao ler dados do arquivo RAW: " << filename << std::endl;
      return;
    }

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data() );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    GLint wrap_mode = wrap ? GL_REPEAT : GL_CLAMP;
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode );
  }

}  // namespace qxgl::TextureLoader
