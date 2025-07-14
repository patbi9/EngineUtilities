#pragma once

#include "../Prerequisites.h"
using namespace EngineMath;
#include <Math/EngineMath.h>

/**
 * @class CVector3
 * @brief Represents a 3D vector with arithmetic, geometric, and utility operations.
 *
 * Provides vector math operations (addition, subtraction, scalar multiplication/division),
 * geometric functions like dot and cross products, normalization, distance,
 * interpolation, and utility methods for transformations and debugging.
 */
class CVector3 {
public:
    float x; ///< X component
    float y; ///< Y component
    float z; ///< Z component

    /** @brief Default constructor. Initializes to (0, 0, 0). */
    CVector3() : x(0.f), y(0.f), z(0.f) {}

    /** @brief Constructs a vector with given x, y, z values. */
    CVector3(float x, float y, float z) : x(x), y(y), z(z) {}

    /** @brief Adds two vectors. */
    CVector3 operator+(const CVector3& otro) const {
        return CVector3(x + otro.x, y + otro.y, z + otro.z);
    }

    /** @brief Subtracts one vector from another. */
    CVector3 operator-(const CVector3& otro) const {
        return CVector3(x - otro.x, y - otro.y, z - otro.z);
    }

    /** @brief Multiplies the vector by a scalar. */
    CVector3 operator*(float sca) const {
        return CVector3(x * sca, y * sca, z * sca);
    }

    /** @brief Divides the vector by a scalar. */
    CVector3 operator/(float sca) const {
        return CVector3(x / sca, y / sca, z / sca);
    }

    /** @brief In-place vector addition. */
    CVector3& operator+=(const CVector3& otro) {
        x += otro.x; y += otro.y; z += otro.z;
        return *this;
    }

    /** @brief In-place vector subtraction. */
    CVector3& operator-=(const CVector3& otro) {
        x -= otro.x; y -= otro.y; z -= otro.z;
        return *this;
    }

    /** @brief In-place scalar multiplication. */
    CVector3& operator*=(float sca) {
        x *= sca; y *= sca; z *= sca;
        return *this;
    }

    /** @brief In-place scalar division. */
    CVector3& operator/=(float sca) {
        x /= sca; y /= sca; z /= sca;
        return *this;
    }

    /** @brief Equality comparison. */
    bool operator==(const CVector3& otro) const {
        return x == otro.x && y == otro.y && z == otro.z;
    }

    /** @brief Inequality comparison. */
    bool operator!=(const CVector3& otro) const {
        return !(*this == otro);
    }

    /** @brief Access vector component by index (0 = x, 1 = y, 2 = z). */
    float& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        return z;
    }

    /** @brief Const access to vector component by index. */
    const float& operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        return z;
    }

    /** @brief Returns the magnitude (length) of the vector. */
    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    /** @brief Returns the squared magnitude (avoids sqrt). */
    float lengthSquared() const {
        return x * x + y * y + z * z;
    }

    /** @brief Computes the dot product with another vector. */
    float dot(const CVector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    /** @brief Computes the cross product with another vector. */
    CVector3 cross(const CVector3& otro) const {
        return CVector3(
            y * otro.z - z * otro.y,
            z * otro.x - x * otro.z,
            x * otro.y - y * otro.x
        );
    }

    /** @brief Returns a normalized copy of the vector. */
    CVector3 normalized() const {
        float len = length();
        if (len == 0.f) return CVector3(0.f, 0.f, 0.f);
        return CVector3(x / len, y / len, z / len);
    }

    /** @brief Normalizes the vector in-place. */
    void normalize() {
        float len = length();
        if (len != 0.f) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    /**
     * @brief Calculates the distance between two vectors.
     * @param a First point.
     * @param b Second point.
     * @return Euclidean distance between a and b.
     */
    static float distance(const CVector3& a, const CVector3& b) {
        return (a - b).length();
    }

    /**
     * @brief Linearly interpolates between two vectors.
     * @param a Starting vector.
     * @param b Ending vector.
     * @param t Interpolation factor [0, 1].
     * @return Interpolated vector.
     */
    static CVector3 lerp(const CVector3& a, const CVector3& b, float t) {
        if (t < 0.f) t = 0.f;
        if (t > 1.f) t = 1.f;
        return a + (b - a) * t;
    }

    /** @brief Returns the zero vector (0, 0, 0). */
    static CVector3 zero() {
        return CVector3(0.f, 0.f, 0.f);
    }

    /** @brief Returns the unit vector (1, 1, 1). */
    static CVector3 one() {
        return CVector3(1.f, 1.f, 1.f);
    }

    // --- Transformation Utilities (for debugging and manipulation) ---

    /** @brief Sets this vector as a position. */
    void setPosition(const CVector3& pos) {
        x = pos.x; y = pos.y; z = pos.z;
    }

    /** @brief Moves this vector by an offset. */
    void move(const CVector3& ofs) {
        x += ofs.x; y += ofs.y; z += ofs.z;
    }

    /** @brief Sets this vector as a scale. */
    void setScale(const CVector3& fac) {
        x = fac.x; y = fac.y; z = fac.z;
    }

    /** @brief Scales this vector component-wise. */
    void scale(const CVector3& fac) {
        x *= fac.x; y *= fac.y; z *= fac.z;
    }

    /** @brief Sets this vector as an origin. */
    void setOrigin(const CVector3& ori) {
        x = ori.x; y = ori.y; z = ori.z;
    }

private:
    // No internal data other than x, y, z
};
