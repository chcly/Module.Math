/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#pragma once

#include "Math/Vector3.h"

namespace Rt2::Math
{
    class Matrix3;
    class Quaternion;

    class Matrix4
    {
    public:
        Scalar m[4][4]{};

        static const Matrix4 Identity;
        static const Matrix4 Zero;

    public:
        Matrix4() = default;

        Matrix4(const Matrix4& v) = default;

        Matrix4(Scalar m00,
                Scalar m01,
                Scalar m02,
                Scalar m03,
                Scalar m10,
                Scalar m11,
                Scalar m12,
                Scalar m13,
                Scalar m20,
                Scalar m21,
                Scalar m22,
                Scalar m23,
                Scalar m30,
                Scalar m31,
                Scalar m32,
                Scalar m33);

        explicit Matrix4(const Scalar* v);

        Matrix4 operator*(const Matrix4& lhs) const;

        Matrix4& transpose();

        Matrix4 transposed() const;

        void setTrans(const Vector3& v);

        void setTrans(Scalar x, Scalar y, Scalar z);

        void setScale(const Vector3& v);

        void setScale(Scalar x, Scalar y, Scalar z);

        Vector3 getScale() const;

        Vector3 getTrans() const;

        void makeIdentity();

        Scalar det() const;

        Matrix4 inverted() const;

        void mulAssign(const Matrix4& lhs, const Matrix4& rhs);

        void makeTransform(const Vector3& loc, const Vector3& scale, const Quaternion& rot);

        void makeTransform(const Vector3& loc, const Vector3& scale, const Matrix3& rot);

        void makeInverseTransform(const Vector3& loc, const Vector3& scale, const Quaternion& rot);

        void makeInverseTransform(const Vector3& loc, const Vector3& scale, const Matrix3& rot);

        static void merge(Matrix4& d, const Matrix4& lhs, const Matrix4& rhs);

        void print() const;
    };
}  // namespace Rt2::Math
