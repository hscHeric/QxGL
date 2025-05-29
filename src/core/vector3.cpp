#include "vector3.hpp"

#include <cmath>

namespace qxgl {

  Vector3::Vector3() : x( 0.0F ), y( 0.0F ), z( 0.0F ) {}

  Vector3::Vector3( float x, float y, float z ) : x( x ), y( y ), z( z ) {}

  float Vector3::length() const {
    return std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
  }

  float Vector3::lengthSquared() const {
    return ( x * x ) + ( y * y ) + ( z * z );
  }

  void Vector3::normalize() {
    float len = length();
    if ( len != 0.0F ) {
      x /= len;
      y /= len;
      z /= len;
    }
  }

  Vector3 Vector3::unit() const {
    float len = length();
    if ( len == 0.0F ) {
      return { 0.0F, 0.0F, 0.0F };
    }
    return { x / len, y / len, z / len };
  }

  Vector3 Vector3::projectOnto( const Vector3 &v ) const {
    float dotProd = this->dot( v );
    float denom   = v.dot( v );
    if ( denom == 0.0F ) {
      return {};
    }
    float scalar = dotProd / denom;
    return v.multiply( scalar );
  }

  void Vector3::assign( const Vector3 &v ) {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  Vector3 Vector3::add( const Vector3 &v ) const {
    return { x + v.x, y + v.y, z + v.z };
  }

  void Vector3::addInPlace( const Vector3 &v ) {
    x += v.x;
    y += v.y;
    z += v.z;
  }

  Vector3 Vector3::subtract( const Vector3 &v ) const {
    return { x - v.x, y - v.y, z - v.z };
  }

  Vector3 Vector3::multiply( float scalar ) const {
    return { x * scalar, y * scalar, z * scalar };
  }

  float Vector3::distanceTo( const Vector3 &v ) const {
    float dx = x - v.x;
    float dy = y - v.y;
    float dz = z - v.z;
    return std::sqrt( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) );
  }

  Vector3 Vector3::cross( const Vector3 &v ) const {
    return { ( y * v.z ) - ( z * v.y ), ( z * v.x ) - ( x * v.z ), ( x * v.y ) - ( y * v.x ) };
  }

  float Vector3::dot( const Vector3 &v ) const {
    return ( x * v.x ) + ( y * v.y ) + ( z * v.z );
  }

  Vector3 Vector3::operator+( const Vector3 &v ) const {
    return this->add( v );
  }

  Vector3 Vector3::operator-( const Vector3 &v ) const {
    return this->subtract( v );
  }

  Vector3 Vector3::operator*( float scalar ) const {
    return this->multiply( scalar );
  }

  float Vector3::operator*( const Vector3 &v ) const {
    return this->dot( v );
  }

  Vector3 Vector3::operator^( const Vector3 &v ) const {
    return this->cross( v );
  }

  Vector3 Vector3::operator!() const {
    return this->unit();
  }
}  // namespace qxgl
