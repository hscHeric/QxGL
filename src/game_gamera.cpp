#include "game_camera.hpp"

namespace qxgl {

  GameCamera::GameCamera() : Camera() {
    style_    = CameraStyle::GAME;
    center_.z = eye_.z - 1.0F;
  }

  GameCamera::GameCamera( const Vetor3D &eye, const Vetor3D &center, const Vetor3D &up )
    : Camera( eye, center, up ) {
    style_ = CameraStyle::GAME;
  }

  GameCamera::GameCamera( GLfloat ex,
                          GLfloat ey,
                          GLfloat ez,
                          GLfloat cx,
                          GLfloat cy,
                          GLfloat cz,
                          GLfloat ux,
                          GLfloat uy,
                          GLfloat uz )
    : Camera( ex, ey, ez, cx, cy, cz, ux, uy, uz ) {
    style_ = CameraStyle::GAME;
  }

  void GameCamera::zoom( GLfloat win_y, GLfloat last_y ) {
    const auto  VEC   = center_ - eye_;
    const float DELTA = ( win_y - last_y ) / 20.0F;

    eye_ -= VEC * DELTA;
    center_ -= VEC * DELTA;
  }

  void GameCamera::translate_x( GLfloat win_x, GLfloat last_x ) {
    const auto  VEC   = center_ - eye_;
    const auto  X_POS = VEC ^ up_;
    const float DELTA = ( last_x - win_x ) / 30.0F;

    eye_ -= X_POS * DELTA;
    center_ -= X_POS * DELTA;
  }

  void GameCamera::translate_y( GLfloat win_y, GLfloat last_y ) {
    const float DELTA = ( last_y - win_y ) / 30.0F;

    eye_ += up_ * DELTA;
    center_ += up_ * DELTA;
  }

  void GameCamera::rotate_x( GLfloat win_y, GLfloat last_y ) {
    const float DELTA = ( last_y - win_y ) / 500.0F;
    center_ += up_ * DELTA;

    auto n = center_ - eye_;
    n.normalize();
    center_ = eye_ + n;

    const auto X_POS = n ^ up_;
    up_              = X_POS ^ n;
    up_.normalize();
  }

  void GameCamera::rotate_y( GLfloat win_x, GLfloat last_x ) {
    const auto  VEC   = center_ - eye_;
    const auto  X_POS = VEC ^ up_;
    const float DELTA = ( last_x - win_x ) / 500.0F;

    center_ -= X_POS * DELTA;

    auto n = center_ - eye_;
    n.normalize();
    center_ = eye_ + n;

    Vetor3D world_up;
    if ( up_.y >= 0.0F ) {
      world_up = Vetor3D( 0.0F, 1.0F, 0.0F );
    } else {
      world_up = Vetor3D( 0.0F, -1.0F, 0.0F );
    }

    const auto VCE   = eye_ - center_;
    const auto NEW_X = world_up ^ VCE;
    up_              = VCE ^ NEW_X;
    up_.normalize();
  }

  void GameCamera::rotate_z( GLfloat win_x, GLfloat last_x ) {
    const auto VEC   = center_ - eye_;
    auto       x_pos = VEC ^ up_;
    x_pos.normalize();

    const float DELTA = ( last_x - win_x ) / 300.0F;

    up_ -= x_pos * DELTA;
    up_.normalize();
  }

  Vetor3D GameCamera::get_picked_point( GLfloat x, GLfloat y ) {
    auto vce = eye_ - center_;
    vce.normalize();

    auto x_pos = up_ ^ vce;
    x_pos.normalize();

    float dx = ( x_pos.x * x ) + ( up_.x * y ) + ( vce.x * -1.0F );
    float dy = ( x_pos.y * x ) + ( up_.y * y ) + ( vce.y * -1.0F );
    float dz = ( x_pos.z * x ) + ( up_.z * y ) + ( vce.z * -1.0F );

    dx += eye_.x;
    dy += eye_.y;
    dz += eye_.z;

    return { dx, dy, dz };
  }

}  // namespace qxgl
