#pragma once
//#include "../Prerequisites.h"
#include <Math/EngineMath.h>
#include <Vectors/Vector2.h>
using namespace EngineMath;

/**
 * @class CVector2
 * @brief Represents a 2D vector with basic arithmetic and geometric operations.
 *
 * Includes vector arithmetic, normalization, dot and cross products, linear interpolation,
 * distance calculation, and common utility methods for transformations.
 */
class CVector2 {
public:
 float x; ///< X component of the vector
 float y; ///< Y component of the vector

 /** @brief Default constructor. Initializes vector to (0, 0). */
 CVector2() : x(0.f), y(0.f) {}

 /** @brief Parameterized constructor. */
 CVector2(float x, float y) : x(x), y(y) {}

 /** @brief Adds two vectors. */
 CVector2 
  operator+(const CVector2& otro) const {
  return CVector2(x + otro.x, y + otro.y);
 }

 /** @brief Subtracts two vectors. */
 CVector2 
  operator-(const CVector2& otro) const {
  return CVector2(x - otro.x, y - otro.y);
 }

 /** @brief Multiplies the vector by a scalar. */
 CVector2 
  operator*(float fac) const {
  return CVector2(x * fac, y * fac);
 }

 /** @brief Divides the vector by a scalar. */
 CVector2 
  operator/(float fac) const {
  return CVector2(x / fac, y / fac);
 }

 /** @brief Adds another vector to this one (in-place). */
 CVector2& 
  operator+=(const CVector2& otro) {
  x += otro.x;
  y += otro.y;
  return *this;
 }

 /** @brief Subtracts another vector from this one (in-place). */
 CVector2& 
  operator-=(const CVector2& otro) {
  x -= otro.x;
  y -= otro.y;
  return *this;
 }

 /** @brief Multiplies this vector by a scalar (in-place). */
 CVector2& 
  operator*=(float fac) {
  x *= fac;
  y *= fac;
  return *this;
 }

 /** @brief Divides this vector by a scalar (in-place). */
 CVector2& 
  operator/=(float fac) {
  x /= fac;
  y /= fac;
  return *this;
 }

 /** @brief Checks if two vectors are equal. */
 bool 
  operator==(const CVector2& otro) const {
  return x == otro.x && y == otro.y;
 }

 /** @brief Checks if two vectors are not equal. */
 bool 
  operator!=(const CVector2& otro) const {
  return !(*this == otro);
 }

 /** @brief Accesses a vector component by index (0 = x, 1 = y). */
 float& 
 operator[](int i) {
  return i == 0 ? x : y;
 }

 /** @brief Const access to a vector component by index. */
 const float& 
 operator[](int index) const {
  return index == 0 ? x : y;
 }

 /** @brief Returns the magnitude (length) of the vector. */
 float 
  length() const {
  return sqrt(x * x + y * y);
 }
 /** @brief Returns the squared length of the vector (avoids sqrt). */
 float 
  lengthSquared() const {
  return x * x + y * y;
 }

 /** @brief Computes the dot product between two vectors. */
 float 
  dot(const CVector2& otro) const {
  return x * otro.x + y * otro.y;
 }

 /** @brief Computes the 2D cross product (scalar). */
 float 
  cross(const CVector2& otro) const {
  return x * otro.y - y * otro.x;
 }

 /** @brief Returns a normalized copy of this vector. */
 CVector2 
  normalized() const {
  float len = length();
  if (len == 0.f)
   return CVector2(0.f, 0.f);
    return CVector2(x / len, y / len);
 }

 /** @brief Normalizes this vector in-place. */
 void 
  normalize() {
  float len = length();
  if (len != 0.f) {
   x /= len;
   y /= len;
  }
 }

 /**
  * @brief Computes the distance between two points.
  * @param a First point.
  * @param b Second point.
  * @return Distance between a and b.
  */
 static float 
  distance(const CVector2& a, const CVector2& b) {
  return (a - b).length();
 }

 /**
  * @brief Linearly interpolates between two vectors.
  * @param a Starting vector.
  * @param b Ending vector.
  * @param t Interpolation factor [0, 1].
  * @return Interpolated vector.
  */
 static CVector2
  lerp(const CVector2& a, const CVector2& b, float t) {
  if (t < 0.f) t = 0.f;
  if (t > 1.f) t = 1.f;
  return a + (b - a) * t;
 }
 /** @brief Returns a vector (0, 0). */
 static CVector2 
  zero() {
  return CVector2(0.f, 0.f);
 }

 /** @brief Returns a vector (1, 1). */
 static CVector2 
  one() {
  return CVector2(1.f, 1.f);
 }

 // Debug-style transform emulation methods:

 /** @brief Sets this vector to a position value. */
 void 
  setPosition(const CVector2& position) {
  x = position.x;
  y = position.y;
 }

 /** @brief Moves this vector by an offset. */
 void
  move(const CVector2& ofs) {
  x += ofs.x;
  y += ofs.y;
 }

 /** @brief Sets this vector as a scale. */
 void
  setScale(const CVector2& fac) {
  x = fac.x;
  y = fac.y;
 }

 /** @brief Scales this vector component-wise. */
 void 
  scale(const CVector2& fac) {
  x *= fac.x;
  y *= fac.y;
 }

 /** @brief Sets this vector as an origin point. */
 void 
  setOrigin(const CVector2& origin) {
  x = origin.x;
  y = origin.y;
 }
};
