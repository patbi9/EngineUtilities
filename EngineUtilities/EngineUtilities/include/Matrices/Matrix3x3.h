#pragma once
#include <Vectors/Vector2.h>
#include <Vectors/Vector3.h>
#include <Math/EngineMath.h>

namespace EU {

    /**
     * @class Matrix3x3
     * @brief Represents a 3x3 matrix with support for linear algebra operations.
     *
     * Includes arithmetic operations, determinant, transpose, inverse,
     * adjugate, cofactors, and vector transformation in homogeneous coordinates.
     */
    class Matrix3x3 {
    public:
        float m[3][3]; ///< Matrix elements in row-major order

        /**
         * @brief Default constructor. Initializes to identity matrix.
         */
        Matrix3x3() {
            setIdentity();
        }

        /**
         * @brief Constructs a matrix with given element values.
         */
        Matrix3x3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22) {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
        }

        /**
         * @brief Adds two matrices.
         */
        Matrix3x3 operator+(const Matrix3x3& otro) const {
            Matrix3x3 r;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    r.m[i][j] = m[i][j] + otro.m[i][j];
            return r;
        }

        /**
         * @brief Adds another matrix in-place.
         */
        Matrix3x3& operator+=(const Matrix3x3& otro) {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] += otro.m[i][j];
            return *this;
        }

        /**
         * @brief Subtracts two matrices.
         */
        Matrix3x3 operator-(const Matrix3x3& otro) const {
            Matrix3x3 r;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    r.m[i][j] = m[i][j] - otro.m[i][j];
            return r;
        }

        /**
         * @brief Subtracts another matrix in-place.
         */
        Matrix3x3& operator-=(const Matrix3x3& otro) {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] -= otro.m[i][j];
            return *this;
        }

        /**
         * @brief Multiplies the matrix by a scalar.
         */
        Matrix3x3 operator*(float sca) const {
            Matrix3x3 r;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    r.m[i][j] = m[i][j] * sca;
            return r;
        }

        /**
         * @brief Multiplies the matrix by a scalar in-place.
         */
        Matrix3x3& operator*=(float sca) {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] *= sca;
            return *this;
        }

        /**
         * @brief Multiplies this matrix by another matrix.
         */
        Matrix3x3 operator*(const Matrix3x3& otro) const {
            Matrix3x3 r = zero();
            for (int fil = 0; fil < 3; ++fil)
                for (int col = 0; col < 3; ++col)
                    for (int k = 0; k < 3; ++k)
                        r.m[fil][col] += m[fil][k] * otro.m[k][col];
            return r;
        }

        /**
         * @brief Transforms a 2D vector using homogeneous coordinates.
         */
        CVector2 operator*(const CVector2& vec) const {
            float x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * 1.0f;
            float y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * 1.0f;
            float w = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * 1.0f;
            if (w != 0.0f) {
                x /= w;
                y /= w;
            }
            return CVector2(x, y);
        }

        /**
         * @brief Transforms a 3D vector.
         */
        CVector3 operator*(const CVector3& vec) const {
            return CVector3(
                m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z,
                m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z,
                m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z
            );
        }

        /**
         * @brief Compares two matrices for equality.
         */
        bool operator==(const Matrix3x3& otro) const {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (m[i][j] != otro.m[i][j]) return false;
            return true;
        }

        /**
         * @brief Accesses an element of the matrix.
         */
        float& operator()(int fil, int col) {
            return m[fil][col];
        }

        /**
         * @brief Const access to an element of the matrix.
         */
        const float& operator()(int fil, int col) const {
            return m[fil][col];
        }

        /**
         * @brief Computes the determinant of the matrix.
         */
        float determinant() const {
            return
                m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        }

        /**
         * @brief Returns the transposed version of the matrix.
         */
        Matrix3x3 transpose() const {
            return Matrix3x3(
                m[0][0], m[1][0], m[2][0],
                m[0][1], m[1][1], m[2][1],
                m[0][2], m[1][2], m[2][2]
            );
        }

        /**
         * @brief Computes the cofactor of a specific element.
         */
        float cofactor(int fil, int col) const {
            int r1 = (fil + 1) % 3, r2 = (fil + 2) % 3;
            int c1 = (col + 1) % 3, c2 = (col + 2) % 3;
            float minor = m[r1][c1] * m[r2][c2] - m[r1][c2] * m[r2][c1];
            return ((fil + col) % 2 == 0) ? minor : -minor;
        }

        /**
         * @brief Builds the cofactor matrix.
         */
        Matrix3x3 cofactorMatrix() const {
            return Matrix3x3(
                cofactor(0, 0), cofactor(0, 1), cofactor(0, 2),
                cofactor(1, 0), cofactor(1, 1), cofactor(1, 2),
                cofactor(2, 0), cofactor(2, 1), cofactor(2, 2)
            );
        }

        /**
         * @brief Computes the adjugate (transposed cofactor matrix).
         */
        Matrix3x3 adjugate() const {
            return cofactorMatrix().transpose();
        }

        /**
         * @brief Computes the inverse of the matrix. Returns identity if not invertible.
         */
        Matrix3x3 inverse() const {
            float det = determinant();
            if (det == 0.f) return identity();
            return adjugate() * (1.f / det);
        }

        /**
         * @brief Sets this matrix to identity.
         */
        void setIdentity() {
            m[0][0] = 1.f; m[0][1] = 0.f; m[0][2] = 0.f;
            m[1][0] = 0.f; m[1][1] = 1.f; m[1][2] = 0.f;
            m[2][0] = 0.f; m[2][1] = 0.f; m[2][2] = 1.f;
        }

        /**
         * @brief Returns an identity matrix.
         */
        static Matrix3x3 identity() {
            return Matrix3x3(
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                0.f, 0.f, 1.f
            );
        }

        /**
         * @brief Returns a zero matrix.
         */
        static Matrix3x3 zero() {
            return Matrix3x3(
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f
            );
        }
    };

}
