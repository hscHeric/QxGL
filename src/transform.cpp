#include "transform.hpp"

#include "gui.hpp"

#include <GL/gl.h>

namespace qxgl {
  void Transform::apply() const {
    glTranslatef( position.x, position.y, position.z );

    glRotatef( rotation.x, 1.0F, 0.0F, 0.0F );
    glRotatef( rotation.y, 0.0F, 1.0F, 0.0F );
    glRotatef( rotation.z, 0.0F, 0.0F, 1.0F );

    if ( show_local_origin ) {
      GUI::drawOrigin( 0.5 );
    }

    glScalef( scale.x, scale.y, scale.z );
  }

  void Transform::apply_2d() const {
    glTranslatef( position.x, position.y, 0.0F );
    glRotatef( rotation.z, 0.0F, 0.0F, 1.0F );

    if ( show_local_origin ) {
      GUI::drawOrigin( 0.5 );
    }

    glScalef( scale.x, scale.y, 1.0F );
  }

  void Transform::update_by_mouse() {
    const Vetor3D POS_DELTA( glutGUI::drx, glutGUI::dry, glutGUI::dlry );
    const Vetor3D ROT_DELTA( glutGUI::dly, glutGUI::dlx, glutGUI::dlrx );
    const Vetor3D SCALE_DELTA( glutGUI::dmx, glutGUI::dmy, glutGUI::dlmy );

    position += POS_DELTA * 0.05F;
    rotation += ROT_DELTA * 0.25F;
    scale += SCALE_DELTA * 0.25F;
  }

  void Transform::update_by_mouse_2d() {
    position.x += glutGUI::drx * 0.05F;
    position.y += glutGUI::dry * 0.05F;

    rotation.z += glutGUI::dlrx * 0.25F;

    scale.x += glutGUI::dmx * 0.25F;
    scale.y += glutGUI::dmy * 0.25F;
  }

  void Transform::reset() {
    *this = Transform();
  }
}  // namespace qxgl
