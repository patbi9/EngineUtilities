#pragma once

//#include "../Prerequisites.h"
#include <Vectors/Vector3.h>
#include <Math/EngineMath.h>
using namespace EngineMath;

namespace EU {

 /**
  * @class Quaternion
  * @brief Represents a quaternion used for 3D rotations and orientation.
  *
  * Supports quaternion multiplication, normalization, inversion, vector rotation,
  * construction from axis-angle, and linear interpolation.
  */
 class 
  Quaternion {
  public:
  float x; ///< X component
  float y; ///< Y component
  float z; ///< Z component
  float w; ///< W component (real part)

  /**
   * @brief Default constructor. Initializes to identity quaternion (no rotation).
   */
  Quaternion() : x(0.f), y(0.f), z(0.f), w(1.f) {}

  /**
   * @brief Constructs a quaternion with specified components.
   * @param x X component
   * @param y Y component
   * @param z Z component
   * @param w W component
   */
  Quaternion(float x, float y, float z, float w)
   : x(x), y(y), z(z), w(w) {
  }

  /**
   * @brief Multiplies this quaternion with another.
   * @param otro The other quaternion.
   * @return Resulting quaternion.
   */
  Quaternion 
   operator*(const Quaternion& otro) const {
   return Quaternion(
   w * otro.x + x * otro.w + y * otro.z - z * otro.y,
   w * otro.y - x * otro.z + y * otro.w + z * otro.x,
   w * otro.z + x * otro.y - y * otro.x + z * otro.w,
   w * otro.w - x * otro.x - y * otro.y - z * otro.z
   );
  }

  /**
   * @brief In-place multiplication of this quaternion with another.
   * @param otro The other quaternion.
   * @return Reference to this quaternion after multiplication.
   */
  Quaternion& 
   operator*=(const Quaternion& otro) {
   *this = *this * otro;
   return *this;
  }

  /**
   * @brief Compares two quaternions for equality.
   */
  bool 
   operator==(const Quaternion& otro) const {
   return x == otro.x && y == otro.y && z == otro.z && w == otro.w;
  }

  /**
   * @brief Compares two quaternions for inequality.
   */
  bool 
   operator!=(const Quaternion& otro) const {
   return !(*this == otro);
  }

  /**
   * @brief Computes the magnitude (length) of the quaternion.
   */
  float 
   length() const {
   return sqrt(x * x + y * y + z * z + w * w);
  }

  /**
   * @brief Normalizes this quaternion in-place.
   */
  void 
   normalize() {
   float len = length();
   if (len == 0.f) return;
   x /= len;
   y /= len;
   z /= len;
   w /= len;
  }

  /**
   * @brief Returns a normalized copy of this quaternion.
   * @return Normalized quaternion.
   */
  Quaternion 
   normalized() const {
   float len = length();
   if (len == 0.f) return Quaternion(0.f, 0.f, 0.f, 1.f);
   return Quaternion(x / len, y / len, z / len, w / len);
  }

  /**
   * @brief Returns the inverse of this quaternion.
   * @return Inverted quaternion.
   */
  Quaternion 
   inverse() const {
   float lenSq = x * x + y * y + z * z + w * w;
   if (lenSq == 0.f) return Quaternion(); // Identity fallback
   return Quaternion(-x / lenSq, -y / lenSq, -z / lenSq, w / lenSq);
  }

  /**
   * @brief Creates a quaternion from an axis and an angle (in radians).
   * @param axis The rotation axis (should be normalized).
   * @param angle The rotation angle in radians.
   * @return Resulting quaternion.
   */
  static Quaternion
   fromAxisAngle(const CVector3& axis, float angle) {
   float halfAngle = angle * 0.5f;
   float s = sin(halfAngle);
   float c = cos(halfAngle);
   return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
  }

  /**
   * @brief Rotates a 3D vector using this quaternion.
   * @param v Vector to rotate.
   * @return Rotated vector.
   */
  CVector3
   rotate(const CVector3& v) const {
   Quaternion qv(v.x, v.y, v.z, 0.f);
   Quaternion result = (*this) * qv * inverse();
   return CVector3(result.x, result.y, result.z);
  }

  /**
   * @brief Performs linear interpolation (lerp) between two quaternions.
   * @param a Start quaternion.
   * @param b End quaternion.
   * @param t Interpolation factor [0, 1].
   * @return Interpolated quaternion (normalized).
   */
  static Quaternion 
   lerp(const Quaternion& a, const Quaternion& b, float t) {
   t = (t < 0.f) ? 0.f : ((t > 1.f) ? 1.f : t);
   return Quaternion(
    a.x + (b.x - a.x) * t,
    a.y + (b.y - a.y) * t,
    a.z + (b.z - a.z) * t,
    a.w + (b.w - a.w) * t
    ).normalized();
  }

  /**
   * @brief Returns the identity quaternion (no rotation).
   */
  static Quaternion identity() {
   return Quaternion(0.f, 0.f, 0.f, 1.f);
  }
 };
}
