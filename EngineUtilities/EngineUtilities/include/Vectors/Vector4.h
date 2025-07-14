#pragma once

//#include "../Prerequisites.h"
#include <Math/EngineMath.h>
using namespace EngineMath;

/**
 * @class CVector4
 * @brief Represents a 4D vector with arithmetic, geometric, and utility operations.
 *
 * Supports vector arithmetic, dot product, normalization, distance calculation,
 * interpolation, and transformation helpers. Useful for operations in homogeneous coordinates.
 */
class CVector4 {
public:
 float x; ///< X component
 float y; ///< Y component
 float z; ///< Z component
 float w; ///< W component

 /** @brief Default constructor. Initializes all components to 0. */
 CVector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}
 /** @brief Parameterized constructor. */
 CVector4(float x, float y, float z, float w)
  : x(x), y(y), z(z), w(w) {
 }

 /** @brief Adds two vectors. */
 CVector4 operator+(const CVector4& otro) const {
  return CVector4(x + otro.x, y + otro.y, z + otro.z, w + otro.w);
 }

 /** @brief Subtracts two vectors. */
 CVector4 operator-(const CVector4& otro) const {
  return CVector4(x - otro.x, y - otro.y, z - otro.z, w - otro.w);
 }

 /** @brief Multiplies the vector by a scalar. */
 CVector4 operator*(float fac) const {
  return CVector4(x * fac, y * fac, z * fac, w * fac);
 }

 /** @brief Divides the vector by a scalar. */
 CVector4 operator/(float fac) const {
  return CVector4(x / fac, y / fac, z / fac, w / fac);
 }

 /** @brief In-place addition. */
 CVector4& operator+=(const CVector4& otro) {
  x += otro.x; y += otro.y; z += otro.z; w += otro.w;
  return *this;
 }

 /** @brief In-place subtraction. */
 CVector4& operator-=(const CVector4& otro) {
  x -= otro.x; y -= otro.y; z -= otro.z; w -= otro.w;
  return *this;
 }

 /** @brief In-place scalar multiplication. */
 CVector4& operator*=(float fac) {
  x *= fac; y *= fac; z *= fac; w *= fac;
  return *this;
 }

 /** @brief In-place scalar division. */
 CVector4& operator/=(float fac) {
  x /= fac; y /= fac; z /= fac; w /= fac;
  return *this;
 }

 /** @brief Equality comparison. */
 bool operator==(const CVector4& otro) const {
  return x == otro.x && y == otro.y && z == otro.z && w == otro.w;
 }

 /** @brief Inequality comparison. */
 bool operator!=(const CVector4& otro) const {
  return !(*this == otro);
 }

 /** @brief Access component by index (0 = x, 1 = y, 2 = z, 3 = w). */
 float& operator[](int i) {
  switch (i) {
   case 0: return x;
   case 1: return y;
   case 2: return z;
   default: return w;
  }
 }

 /** @brief Const access to component by index. */
 const float& operator[](int i) const {
  switch (i) {
   case 0: return x;
   case 1: return y;
   case 2: return z;
   default: return w;
  }
 }

 /** @brief Returns the vector's magnitude. */
 float length() const {
  return sqrt(x * x + y * y + z * z + w * w);
 }

 /** @brief Returns the squared magnitude (avoids sqrt). */
 float lengthSquared() const {
  return x * x + y * y + z * z + w * w;
 }

 /** @brief Computes the dot product with another vector. */
 float dot(const CVector4& other) const {
  return x * other.x + y * other.y + z * other.z + w * other.w;
 }

 /** @brief Returns a normalized copy of this vector. */
 CVector4 normalized() const {
  float len = length();
  if (len == 0.f) return CVector4(0.f, 0.f, 0.f, 0.f);
  return CVector4(x / len, y / len, z / len, w / len);
 }

 /** @brief Normalizes this vector in-place. */
 void normalize() {
  float len = length();
  if (len != 0.f) {
   x /= len; y /= len; z /= len; w /= len;
  }
 }

 /**
  * @brief Calculates the distance between two 4D vectors.
  * @param a First vector.
  * @param b Second vector.
  * @return Euclidean distance.
  */
 static float distance(const CVector4& a, const CVector4& b) {
  return (a - b).length();
 }

 /**
  * @brief Linearly interpolates between two vectors.
  * @param a Start vector.
  * @param b End vector.
  * @param t Interpolation factor [0, 1].
  * @return Interpolated vector.
  */
 static CVector4 lerp(const CVector4& a, const CVector4& b, float t) {
  if (t < 0.f) t = 0.f;
  if (t > 1.f) t = 1.f;
  return a + (b - a) * t;
 }

 /** @brief Returns a vector (0, 0, 0, 0). */
 static CVector4 zero() {
  return CVector4(0.f, 0.f, 0.f, 0.f);
 }
 /** @brief Returns a vector (1, 1, 1, 1). */
 static CVector4 one() {
  return CVector4(1.f, 1.f, 1.f, 1.f);
 }

 // --- Transformation Helpers (for debugging or simulation) ---

 /** @brief Sets this vector as a position. */
 void setPosition(const CVector4& pos) {
  x = pos.x; y = pos.y; z = pos.z; w = pos.w;
 }

    /** @brief Moves this vector by an offset. */
    void move(const CVector4& ofs) {
        x += ofs.x; y += ofs.y; z += ofs.z; w += ofs.w;
    }

    /** @brief Sets this vector as a scale. */
    void setScale(const CVector4& fac) {
        x = fac.x; y = fac.y; z = fac.z; w = fac.w;
    }

    /** @brief Scales this vector component-wise. */
    void scale(const CVector4& fac) {
        x *= fac.x; y *= fac.y; z *= fac.z; w *= fac.w;
    }

    /** @brief Sets this vector as an origin point. */
    void setOrigin(const CVector4& ori) {
        x = ori.x; y = ori.y; z = ori.z; w = ori.w;
    }
};
