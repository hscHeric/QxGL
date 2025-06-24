#include "transform.hpp"

#include "state.hpp"
#include "toolkit.hpp"

#include <GL/gl.h>

namespace qxgl {

  void Transform::apply() const {
    // Aplica as transformações na ordem: Translação, Rotação, Escala.
    glTranslatef( position.x, position.y, position.z );

    // Rotações são aplicadas na ordem Y, X, Z (uma convenção comum)
    // para evitar o problema de "gimbal lock" em alguns casos.
    // A ordem original era X, Y, Z. Mantendo para preservar a lógica.
    glRotatef( rotation.x, 1.0F, 0.0F, 0.0F );
    glRotatef( rotation.y, 0.0F, 1.0F, 0.0F );
    glRotatef( rotation.z, 0.0F, 0.0F, 1.0F );

    if ( show_local_origin ) {
      ToolKit::draw_origin( 0.5F );
    }

    glScalef( scale.x, scale.y, scale.z );
  }

  void Transform::apply_2d() const {
    glTranslatef( position.x, position.y, 0.0F );
    glRotatef( rotation.z, 0.0F, 0.0F, 1.0F );

    if ( show_local_origin ) {
      ToolKit::draw_origin( 0.5F );
    }

    glScalef( scale.x, scale.y, 1.0F );
  }

  void Transform::update_by_mouse() {
    const Vetor3D &pos_delta   = State::d_camera_rotation;
    const Vetor3D &rot_delta   = State::d_camera_pan;
    const Vetor3D &scale_delta = State::d_camera_zoom;

    position += pos_delta * 0.05F;
    rotation += rot_delta * 0.25F;
    scale += scale_delta * 0.25F;
  }

  void Transform::update_by_mouse_2d() {
    // Versão 2D da atualização, também lendo da classe 'State'.
    position.x += State::d_camera_rotation.x * 0.05F;
    position.y += State::d_camera_rotation.y * 0.05F;

    rotation.z += State::d_camera_pan.z * 0.25F;

    scale.x += State::d_camera_zoom.x * 0.25F;
    scale.y += State::d_camera_zoom.y * 0.25F;
  }

  void Transform::reset() {
    *this = Transform();
  }

}  // namespace qxgl
