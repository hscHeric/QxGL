#include "models_loader.hpp"

#include <GL/glut.h>
#include <iostream>
#include <string>

namespace qxgl {

  Model3D::Model3D( const std::string &filepath ) {
    const auto IMPORT_FLAGS = aiProcess_Triangulate | aiProcess_FlipUVs |
                              aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices |
                              aiProcess_PreTransformVertices;

    scene_ = importer_.ReadFile( filepath, IMPORT_FLAGS );

    if ( scene_ == nullptr ) {
      const std::string ERROR_STRING_1 = importer_.GetErrorString();
      const std::string FALLBACK_PATH  = "../" + filepath;

      scene_ = importer_.ReadFile( FALLBACK_PATH, IMPORT_FLAGS );

      if ( scene_ == nullptr ) {
        std::cerr << "Erro ao carregar modelo de '" << filepath << "': " << ERROR_STRING_1 << '\n';
        std::cerr << "Tentativa em '" << FALLBACK_PATH
                  << "' tambem falhou: " << importer_.GetErrorString() << '\n';
      }
    }
  }

  void Model3D::draw( bool use_original_colors ) const {
    if ( scene_ != nullptr ) {
      draw_node( scene_->mRootNode, use_original_colors );
    }
  }

  void Model3D::apply_material( const aiMaterial *material ) const {
    aiColor4D diffuse;
    aiColor4D specular;
    aiColor4D ambient;
    aiColor4D emissive;
    float     shininess = 1.0F;

    if ( AI_SUCCESS == aiGetMaterialColor( material, AI_MATKEY_COLOR_DIFFUSE, &diffuse ) ) {
      glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, reinterpret_cast<float *>( &diffuse ) );
    }
    if ( AI_SUCCESS == aiGetMaterialColor( material, AI_MATKEY_COLOR_SPECULAR, &specular ) ) {
      glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, reinterpret_cast<float *>( &specular ) );
    }
    if ( AI_SUCCESS == aiGetMaterialColor( material, AI_MATKEY_COLOR_AMBIENT, &ambient ) ) {
      glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, reinterpret_cast<float *>( &ambient ) );
    }
    if ( AI_SUCCESS == aiGetMaterialColor( material, AI_MATKEY_COLOR_EMISSIVE, &emissive ) ) {
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, reinterpret_cast<float *>( &emissive ) );
    }
    if ( AI_SUCCESS == aiGetMaterialFloat( material, AI_MATKEY_SHININESS, &shininess ) ) {
      glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
    }
  }

  void Model3D::draw_mesh( const aiMesh *mesh, bool use_original_colors ) const {
    glBegin( GL_TRIANGLES );
    for ( unsigned int i = 0; i < mesh->mNumFaces; ++i ) {
      const aiFace &face = mesh->mFaces[i];
      for ( unsigned int j = 0; j < face.mNumIndices; ++j ) {
        const int INDEX = face.mIndices[j];

        if ( use_original_colors && mesh->HasVertexColors( 0 ) ) {
          glColor4fv( reinterpret_cast<const GLfloat *>( &mesh->mColors[0][INDEX] ) );
        }
        if ( mesh->HasNormals() ) {
          glNormal3fv( &mesh->mNormals[INDEX].x );
        }
        glVertex3fv( &mesh->mVertices[INDEX].x );
      }
    }
    glEnd();
  }

  void Model3D::draw_node( const aiNode *node, bool use_original_colors ) const {
    glPushMatrix();

    // Aplica a transformação do nó
    aiMatrix4x4 transform = node->mTransformation;
    transform.Transpose();  // OpenGL usa matrizes em column-major
    glMultMatrixf( reinterpret_cast<float *>( &transform ) );

    // Desenha todas as malhas deste nó
    for ( unsigned int i = 0; i < node->mNumMeshes; ++i ) {
      const aiMesh *mesh = scene_->mMeshes[node->mMeshes[i]];

      if ( use_original_colors ) {
        const aiMaterial *material = scene_->mMaterials[mesh->mMaterialIndex];
        apply_material( material );
      }
      draw_mesh( mesh, use_original_colors );
    }

    for ( unsigned int i = 0; i < node->mNumChildren; ++i ) {
      draw_node( node->mChildren[i], use_original_colors );
    }

    glPopMatrix();
  }

}  // namespace qxgl
