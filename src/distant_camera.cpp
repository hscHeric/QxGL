#include "distant_camera.hpp"

namespace qxgl {

  DistantCamera::DistantCamera() : Camera() {
    style_    = CameraStyle::DIST;
    center_.z = 0.0F;
  }

  DistantCamera::DistantCamera( const Vetor3D &eye, const Vetor3D &center, const Vetor3D &up )
    : Camera( eye, center, up ) {
    style_ = CameraStyle::DIST;
  }

  DistantCamera::DistantCamera( GLfloat ex,
                                GLfloat ey,
                                GLfloat ez,
                                GLfloat cx,
                                GLfloat cy,
                                GLfloat cz,
                                GLfloat ux,
                                GLfloat uy,
                                GLfloat uz )
    : Camera( ex, ey, ez, cx, cy, cz, ux, uy, uz ) {
    style_ = CameraStyle::DIST;
  }

  void DistantCamera::zoom( GLfloat win_y, GLfloat last_y ) {
    const auto  DIRECTION_TO_CENTER = ( center_ - eye_ ).get_unit();
    const float DELTA               = ( win_y - last_y ) / 20.0F;

    const auto NEW_EYE_POS = eye_ + ( DIRECTION_TO_CENTER * DELTA );

    if ( ( ( center_ - NEW_EYE_POS ) * DIRECTION_TO_CENTER ) >= 0.0001F ) {
      eye_ = NEW_EYE_POS;
    }
  }

  void DistantCamera::translate_x( GLfloat win_x, GLfloat last_x ) {
    const auto  VIEW_VEC  = center_ - eye_;
    const auto  RIGHT_VEC = ( VIEW_VEC ^ up_ ).get_unit();
    const float DELTA     = VIEW_VEC.magnitude() * ( last_x - win_x ) / 300.0F;

    const auto DISPLACEMENT = RIGHT_VEC * DELTA;

    eye_ += DISPLACEMENT;
    center_ += DISPLACEMENT;
  }

  void DistantCamera::translate_y( GLfloat win_y, GLfloat last_y ) {
    const auto  VIEW_VEC = center_ - eye_;
    const float DELTA    = VIEW_VEC.magnitude() * ( last_y - win_y ) / 300.0F;

    const auto DISPLACEMENT = up_ * DELTA;

    eye_ -= DISPLACEMENT;
    center_ -= DISPLACEMENT;
  }

  void DistantCamera::rotate_x( GLfloat win_y, GLfloat last_y ) {
    auto        view_vec_from_center = eye_ - center_;
    const float RADIUS               = view_vec_from_center.magnitude();
    const float DELTA = ( ( ( 1.0F / 30.0F ) * RADIUS ) * ( win_y - last_y ) / 5.0F );

    eye_ += up_ * DELTA;

    view_vec_from_center = ( eye_ - center_ ).get_unit() * RADIUS;
    eye_                 = center_ + view_vec_from_center;

    const auto RIGHT_VEC = up_ ^ view_vec_from_center;
    up_                  = ( view_vec_from_center ^ RIGHT_VEC ).get_unit();
  }

  void DistantCamera::rotate_y( GLfloat win_x, GLfloat last_x ) {
    auto        view_vec_from_center = eye_ - center_;
    const float RADIUS               = view_vec_from_center.magnitude();
    const auto  RIGHT_VEC            = ( up_ ^ view_vec_from_center ).get_unit();

    const float POLE_FACTOR = up_ * Vetor3D( 0.0F, 1.0F, 0.0F );
    const float DELTA =
      ( ( ( ( 1.0F / 30.0F ) * RADIUS * POLE_FACTOR ) * ( last_x - win_x ) ) / 5.0F );

    eye_ += RIGHT_VEC * DELTA;

    view_vec_from_center = ( eye_ - center_ ).get_unit() * RADIUS;
    eye_                 = center_ + view_vec_from_center;

    Vetor3D world_up;
    if ( up_.y >= 0.0F ) {
      world_up = Vetor3D( 0.0F, 1.0F, 0.0F );
    } else {
      world_up = Vetor3D( 0.0F, -1.0F, 0.0F );
    }
    const auto NEW_RIGHT_VEC = world_up ^ view_vec_from_center;
    up_                      = ( view_vec_from_center ^ NEW_RIGHT_VEC ).get_unit();
  }

  void DistantCamera::rotate_z( GLfloat win_x, GLfloat last_x ) {
    const auto  RIGHT_VEC = ( ( center_ - eye_ ) ^ up_ ).get_unit();
    const float DELTA     = ( last_x - win_x ) / 300.0F;

    up_ += RIGHT_VEC * DELTA;
    up_.normalize();
  }

  Vetor3D DistantCamera::get_picked_point( GLfloat x, GLfloat y ) {
    const auto Z_AXIS = ( eye_ - center_ ).get_unit();
    const auto X_AXIS = ( up_ ^ Z_AXIS ).get_unit();

    const auto WORLD_OFFSET = ( X_AXIS * x ) + ( up_ * y ) - ( Z_AXIS * 1.0F );

    return eye_ + WORLD_OFFSET;
  }

}  // namespace qxgl
