#ifndef QXGL_MODEL_3D_HPP
#define QXGL_MODEL_3D_HPP

#include <GL/gl.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>

namespace qxgl {

  /**
   * @class Model3D
   * @brief Carrega um modelo 3D de um arquivo e o renderiza usando OpenGL legado.
   * @details Utiliza a biblioteca Assimp para carregar uma vasta gama de formatos de modelo
   * e percorre a hierarquia de nós do modelo para renderização.
   */
  class Model3D {
  private:
    const aiScene   *scene_{ nullptr };
    Assimp::Importer importer_;

    /**
     * @brief Aplica o material de uma malha específica usando glMaterial.
     * @param material O ponteiro para o material do Assimp.
     */
    void apply_material( const aiMaterial *material ) const;

    /**
     * @brief Renderiza uma única malha (mesh) do modelo.
     * @param mesh A malha a ser renderizada.
     * @param use_original_colors Se verdadeiro, tenta aplicar as cores de vértice ou materiais.
     */
    void draw_mesh( const aiMesh *mesh, bool use_original_colors ) const;

    /**
     * @brief Percorre recursivamente a árvore de nós da cena para renderizar o modelo.
     * @param node O nó atual a ser renderizado.
     * @param use_original_colors Passado para a função draw_mesh.
     */
    void draw_node( const aiNode *node, bool use_original_colors ) const;

  public:
    /**
     * @brief Construtor que carrega um modelo 3D a partir de um arquivo.
     * @param filepath O caminho para o arquivo do modelo.
     */
    explicit Model3D( const std::string &filepath );

    /**
     * @brief Renderiza o modelo completo na cena.
     * @param use_original_colors Se verdadeiro, aplica os materiais e cores definidos no arquivo do
     * modelo.
     */
    void draw( bool use_original_colors = true ) const;
  };

}  // namespace qxgl

#endif  // QXGL_MODEL_3D_HPP
