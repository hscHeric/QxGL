/**
 * @file Model3D.h
 * @brief Declaração da classe Model3D para carregamento e renderização de modelos 3D.
 *
 * @details Esta classe encapsula a funcionalidade da biblioteca Assimp (Open Asset Import Library)
 */
#ifndef MODEL3D_H
#define MODEL3D_H

#include <GL/glut.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

/**
 * @class Model3D
 * @brief Responsável por carregar e renderizar um modelo 3D a partir de um arquivo.
 */
class Model3D {
private:
  const aiScene *scene; /**< @brief Ponteiro para a estrutura de dados principal do Assimp, que
                           contém todos os dados do modelo. */
  Assimp::Importer
    importer; /**< @brief Objeto do Assimp que gerencia o processo de importação do arquivo. */

  /**
   * @brief Aplica as propriedades de um material (cores, brilho) ao estado atual do OpenGL.
   *
   * @details Extrai as cores difusa, especular, ambiente e emissiva, bem como o
   * fator de brilho (shininess) de um material Assimp e os define
   * usando `glMaterialfv`.
   * @param material Ponteiro para o objeto `aiMaterial` a ser aplicado.
   */
  void applyMaterial( const aiMaterial *material );

  /**
   * @brief Renderiza uma única malha (mesh) do modelo.
   *
   * @details Itera sobre as faces da malha e desenha os triângulos correspondentes
   * usando `glBegin(GL_TRIANGLES)`. Aplica normais e, opcionalmente,
   * cores de vértice, se existirem.
   * @param mesh Ponteiro para o objeto `aiMesh` a ser desenhado.
   * @param useOriginalColors Se `true`, tenta aplicar as cores dos materiais
   * e/ou dos vértices contidas no arquivo original.
   */
  void drawMesh( const aiMesh *mesh, bool useOriginalColors );

  /**
   * @brief Percorre recursivamente a hierarquia de nós do modelo e desenha cada um.
   *
   * @details Aplica a transformação local do nó, desenha todas as malhas associadas
   * a ele e, em seguida, chama a si mesma para todos os nós filhos.
   * @param node Ponteiro para o `aiNode` atual na hierarquia.
   * @param useOriginalColors Passado para `drawMesh` para determinar se as cores
   * originais devem ser usadas.
   */
  void drawNode( const aiNode *node, bool useOriginalColors );

public:
  /**
   * @brief Construtor que carrega um modelo 3D de um arquivo.
   *
   * @details Utiliza o `Assimp::Importer` para ler o arquivo especificado e processá-lo
   * com flags para triangular malhas, inverter UVs, gerar normais suaves,
   * unir vértices idênticos e pré-transformar os vértices.
   * Tenta carregar do caminho relativo e, se falhar, tenta a partir de um
   * diretório pai.
   * @param filepath Caminho para o arquivo do modelo 3D.
   */
  Model3D( const char *filepath );

  /**
   * @brief Renderiza o modelo completo na cena.
   *
   * @details Inicia o processo de renderização chamando `drawNode` a partir do
   * nó raiz da cena do Assimp.
   * @param useOriginalColors Se `true` (padrão), os materiais e cores definidos
   * no arquivo do modelo serão aplicados. Se `false`, o modelo
   * será renderizado com a cor e material atualmente
   * definidos no estado do OpenGL.
   */
  void draw( bool useOriginalColors = true );
};

#endif  // MODEL3D_H
