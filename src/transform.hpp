#include "gui.hpp"

class Transform {
public:
  qxgl::Vetor3D pos             = qxgl::Vetor3D( 0.0, 0.0, 0.0 );
  qxgl::Vetor3D rot             = qxgl::Vetor3D( 0.0, 0.0, 0.0 );
  qxgl::Vetor3D esc             = qxgl::Vetor3D( 1.0, 1.0, 1.0 );
  bool          showLocalOrigin = true;

  void apply();
  void apply2D();
  void updateByMouse();
  void updateByMouse2D();
  void reset();
};
