#pragma once
#include "../Prerequisites.h"
#include <Vectors/Vector2.h>
#include <Math/EngineMath.h>

namespace EU {

    /**
     * @class Matrix2x2
     * @brief Represents a 2x2 matrix with basic linear algebra operations.
     *
     * Supports matrix addition, subtraction, scalar and matrix multiplication,
     * determinant, transpose, inverse, and standard transformations like scaling and rotation.
     */
    class Matrix2x2 {
    public:
        float m[2][2]; ///< Stores matrix elements in row-major order

        /**
         * @brief Default constructor. Initializes as identity matrix.
         */
        Matrix2x2() {
            setIdentity();
        }

        /**
         * @brief Constructor with individual elements.
         * @param m00 Element at row 0, column 0.
         * @param m01 Element at row 0, column 1.
         * @param m10 Element at row 1, column 0.
         * @param m11 Element at row 1, column 1.
         */
        Matrix2x2(float m00, float m01, float m10, float m11) {
            m[0][0] = m00; m[0][1] = m01;
            m[1][0] = m10; m[1][1] = m11;
        }

        /**
         * @brief Adds two matrices.
         * @param other Matrix to add.
         * @return Resulting matrix.
         */
        Matrix2x2 operator+(const Matrix2x2& other) const {
            Matrix2x2 r;
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    r.m[i][j] = m[i][j] + other.m[i][j];
            return r;
        }

        /**
         * @brief Subtracts another matrix from this one.
         * @param other Matrix to subtract.
         * @return Resulting matrix.
         */
        Matrix2x2 operator-(const Matrix2x2& other) const {
            Matrix2x2 r;
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    r.m[i][j] = m[i][j] - other.m[i][j];
            return r;
        }

        /**
         * @brief Multiplies this matrix by a scalar.
         * @param sca Scalar value.
         * @return Scaled matrix.
         */
        Matrix2x2 operator*(float sca) const {
            Matrix2x2 r;
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    r.m[i][j] = m[i][j] * sca;
            return r;
        }

        /**
         * @brief In-place scalar multiplication.
         * @param sca Scalar value.
         * @return Reference to this matrix after scaling.
         */
        Matrix2x2& operator*=(float sca) {
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    m[i][j] *= sca;
            return *this;
        }

        /**
         * @brief Multiplies this matrix by another matrix.
         * @param other Matrix to multiply with.
         * @return Resulting matrix.
         */
        Matrix2x2 operator*(const Matrix2x2& other) const {
            Matrix2x2 r = zero();
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    for (int k = 0; k < 2; ++k)
                        r.m[i][j] += m[i][k] * other.m[k][j];
            return r;
        }

        /**
         * @brief Multiplies this matrix with a 2D vector.
         * @param vec Input vector.
         * @return Transformed vector.
         */
        CVector2 operator*(const CVector2& vec) const {
            float x = m[0][0] * vec.x + m[0][1] * vec.y;
            float y = m[1][0] * vec.x + m[1][1] * vec.y;
            return CVector2(x, y);
        }

        /**
         * @brief In-place matrix addition.
         * @param other Matrix to add.
         * @return Reference to this matrix.
         */
        Matrix2x2& operator+=(const Matrix2x2& other) {
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    m[i][j] += other.m[i][j];
            return *this;
        }

        /**
         * @brief In-place matrix subtraction.
         * @param other Matrix to subtract.
         * @return Reference to this matrix.
         */
        Matrix2x2& operator-=(const Matrix2x2& other) {
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    m[i][j] -= other.m[i][j];
            return *this;
        }

        /**
         * @brief Accesses an element (writable).
         * @param row Row index.
         * @param col Column index.
         * @return Reference to element.
         */
        float& operator()(int row, int col) {
            return m[row][col];
        }

        /**
         * @brief Accesses an element (read-only).
         * @param row Row index.
         * @param col Column index.
         * @return Const reference to element.
         */
        const float& operator()(int row, int col) const {
            return m[row][col];
        }

        /**
         * @brief Calculates the determinant of the matrix.
         * @return Determinant value.
         */
        float determinant() const {
            return m[0][0] * m[1][1] - m[0][1] * m[1][0];
        }

        /**
         * @brief Returns the transposed version of the matrix.
         * @return Transposed matrix.
         */
        Matrix2x2 transpose() const {
            return Matrix2x2(
                m[0][0], m[1][0],
                m[0][1], m[1][1]
            );
        }

        /**
         * @brief Returns the inverse of the matrix, or identity if not invertible.
         * @return Inverted matrix.
         */
        Matrix2x2 inverse() const {
            float det = determinant();
            if (det == 0.f) return Matrix2x2(); // returns identity
            float invDet = 1.f / det;
            return Matrix2x2(
                m[1][1] * invDet, -m[0][1] * invDet,
                -m[1][0] * invDet, m[0][0] * invDet
            );
        }

        /**
         * @brief Sets this matrix as the identity matrix.
         */
        void setIdentity() {
            m[0][0] = 1.f; m[0][1] = 0.f;
            m[1][0] = 0.f; m[1][1] = 1.f;
        }

        /**
         * @brief Sets this matrix as a 2D scaling matrix.
         * @param scaleX Scale factor on X-axis.
         * @param scaleY Scale factor on Y-axis.
         */
        void setScale(float scaleX, float scaleY) {
            m[0][0] = scaleX; m[0][1] = 0.f;
            m[1][0] = 0.f;    m[1][1] = scaleY;
        }

        /**
         * @brief Sets this matrix as a 2D rotation matrix.
         * @param radians Angle in radians.
         */
        void setRotation(float radians) {
            float c = EU::Math::cos(radians);
            float s = EU::Math::sin(radians);
            m[0][0] = c;  m[0][1] = -s;
            m[1][0] = s;  m[1][1] = c;
        }

        /**
         * @brief Returns a matrix filled with zeros.
         * @return Zero matrix.
         */
        static Matrix2x2 zero() {
            return Matrix2x2(
                0.f, 0.f,
                0.f, 0.f
            );
        }

        /**
         * @brief Returns the identity matrix.
         * @return Identity matrix.
         */
        static Matrix2x2 identity() {
            return Matrix2x2();
        }
    };
}
