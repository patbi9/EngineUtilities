#pragma once

#include "../Prerequisites.h"
#include <Vectors/Vector3.h>
#include <Vectors/Vector4.h>
#include <Math/EngineMath.h>

namespace EU {

    /**
     * @class Matrix4x4
     * @brief Represents a 4x4 matrix with support for linear algebra and geometric transformations.
     *
     * Includes matrix addition, subtraction, scalar and matrix multiplication,
     * transformation of 3D/4D vectors, transposition, and generation of identity,
     * scaling, translation, and rotation matrices.
     */
    class Matrix4x4 {
    public:
        float m[4][4]; ///< Matrix elements in row-major order

        /**
         * @brief Default constructor. Initializes to identity matrix.
         */
        Matrix4x4() {
            setIdentity();
        }

        /**
         * @brief Constructor with element-wise initialization.
         */
        Matrix4x4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33) {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
            m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
        }

        /**
         * @brief Adds two matrices.
         */
        Matrix4x4 operator+(const Matrix4x4& otro) const {
            Matrix4x4 r;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    r.m[i][j] = m[i][j] + otro.m[i][j];
            return r;
        }

        /**
         * @brief Subtracts two matrices.
         */
        Matrix4x4 operator-(const Matrix4x4& otro) const {
            Matrix4x4 r;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    r.m[i][j] = m[i][j] - otro.m[i][j];
            return r;
        }

        /**
         * @brief Multiplies the matrix by a scalar.
         */
        Matrix4x4 operator*(float sca) const {
            Matrix4x4 r;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    r.m[i][j] = m[i][j] * sca;
            return r;
        }

        /**
         * @brief Matrix multiplication.
         */
        Matrix4x4 operator*(const Matrix4x4& otro) const {
            Matrix4x4 r = zero();
            for (int fil = 0; fil < 4; ++fil)
                for (int col = 0; col < 4; ++col)
                    for (int k = 0; k < 4; ++k)
                        r.m[fil][col] += m[fil][k] * otro.m[k][col];
            return r;
        }

        /**
         * @brief Transforms a 4D vector.
         */
        CVector4 operator*(const CVector4& vec) const {
            return CVector4(
                m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3] * vec.w,
                m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3] * vec.w,
                m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3] * vec.w,
                m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3] * vec.w
            );
        }

        /**
         * @brief Transforms a 3D vector using homogeneous coordinates.
         */
        CVector3 operator*(const CVector3& vec) const {
            float x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3];
            float y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3];
            float z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3];
            float w = m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3];
            if (w != 0.0f) {
                x /= w;
                y /= w;
                z /= w;
            }
            return CVector3(x, y, z);
        }

        /**
         * @brief Adds another matrix in-place.
         */
        Matrix4x4& operator+=(const Matrix4x4& otro) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] += otro.m[i][j];
            return *this;
        }

        /**
         * @brief Subtracts another matrix in-place.
         */
        Matrix4x4& operator-=(const Matrix4x4& otro) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] -= otro.m[i][j];
            return *this;
        }

        /**
         * @brief Multiplies this matrix by a scalar in-place.
         */
        Matrix4x4& operator*=(float sca) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] *= sca;
            return *this;
        }

        /**
         * @brief Accesses a matrix element by row and column.
         */
        float& operator()(int fil, int col) {
            return m[fil][col];
        }

        /**
         * @brief Const access to a matrix element by row and column.
         */
        const float& operator()(int fil, int col) const {
            return m[fil][col];
        }

        /**
         * @brief Returns the transpose of this matrix.
         */
        Matrix4x4 transpose() const {
            return Matrix4x4(
                m[0][0], m[1][0], m[2][0], m[3][0],
                m[0][1], m[1][1], m[2][1], m[3][1],
                m[0][2], m[1][2], m[2][2], m[3][2],
                m[0][3], m[1][3], m[2][3], m[3][3]
            );
        }

        /**
         * @brief Sets this matrix to identity.
         */
        void setIdentity() {
            m[0][0] = 1.f; m[0][1] = 0.f; m[0][2] = 0.f; m[0][3] = 0.f;
            m[1][0] = 0.f; m[1][1] = 1.f; m[1][2] = 0.f; m[1][3] = 0.f;
            m[2][0] = 0.f; m[2][1] = 0.f; m[2][2] = 1.f; m[2][3] = 0.f;
            m[3][0] = 0.f; m[3][1] = 0.f; m[3][2] = 1.f; m[3][3] = 0.f;
        }

        /**
         * @brief Converts this matrix to a scaling matrix.
         */
        void setScale(float scaX, float scaY, float scaZ) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = 0.0f;
            m[0][0] = scaX;
            m[1][1] = scaY;
            m[2][2] = scaZ;
            m[3][3] = 1.0f;
        }

        /**
         * @brief Converts this matrix to a translation matrix.
         */
        void setTranslation(float tx, float ty, float tz) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = 0.0f;
            m[0][0] = 1.0f;
            m[1][1] = 1.0f;
            m[2][2] = 1.0f;
            m[3][3] = 1.0f;
            m[0][3] = tx;
            m[1][3] = ty;
            m[2][3] = tz;
        }

        /**
         * @brief Converts this matrix to a rotation matrix around the Z axis.
         */
        void setRotation(float radians) {
            float c = EU::Math::cos(radians);
            float s = EU::Math::sin(radians);
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = 0.0f;
            m[0][0] = c;
            m[0][1] = -s;
            m[1][0] = s;
            m[1][1] = c;
            m[2][2] = 1.0f;
            m[3][3] = 1.0f;
        }

        /**
         * @brief Returns an identity matrix.
         */
        static Matrix4x4 identity() {
            return Matrix4x4(
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }

        /**
         * @brief Returns a matrix filled with zeros.
         */
        static Matrix4x4 zero() {
            return Matrix4x4(
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f
            );
        }
    };
}
