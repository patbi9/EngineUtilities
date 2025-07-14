/**
 * @file Constants.h
 * @brief File that defines math constants used in the motor.
 *
 * Such as PI, EPSILON, radian/degree conversion, and infinites (big enough).
 * Organized inside EU::Constants namespace to keep clarity and avoid name collision.
 */

#pragma once

namespace EU {
 /**
  * @namespace Constants
  * @brief Math constants commonly used in calculus operations, geomtery, rotation, and transformations.
  */
 namespace Constants {

  /// PI
  constexpr float PI = 3.14159265358979323846f;

  /// 2PI
  constexpr float TWO_PI = 6.28318530717958647692f;

  /// PI/2
  constexpr float HALF_PI = 1.57079632679489661923f;

  /// PI/4
  constexpr float QUARTER_PI = 0.785398163397448309616f;

  /// Degree to radian conversion
  constexpr float DEG_TO_RAD = PI / 180.0f;

  /// Radian to degree conversion
  constexpr float RAD_TO_DEG = 180.0f / PI;

  /// Small tolerance value used in float comparisons
  constexpr float EPSILON = 1e-6f;

  /// Constant representing one
  constexpr float ONE = 1.0f;

  /// Constant representing zero
  constexpr float ZERO = 0.0f;

  /// Positive infinity (not really but big enough)
  constexpr float INF = 1e30f;

  /// Negative infinity (not really but big enough)
  constexpr float NEG_INF = -1e30f;

 }
} // namespace EU
