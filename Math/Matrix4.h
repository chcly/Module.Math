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
        Real m[4][4]{};

        static const Matrix4 Identity;
        static const Matrix4 Zero;

    public:
        Matrix4() = default;

        Matrix4(const Matrix4& v) = default;

        Matrix4(Real m00,
                Real m01,
                Real m02,
                Real m03,
                Real m10,
                Real m11,
                Real m12,
                Real m13,
                Real m20,
                Real m21,
                Real m22,
                Real m23,
                Real m30,
                Real m31,
                Real m32,
                Real m33);

        explicit Matrix4(const Real* v);

        Matrix4 operator*(const Matrix4& lhs) const;

        Matrix4& transpose();

        Matrix4 transposed() const;

        void setTrans(const Vector3& v);

        void setTrans(Real x, Real y, Real z);

        void setScale(const Vector3& v);

        void setScale(Real x, Real y, Real z);

        Vector3 getScale() const;

        Vector3 getTrans() const;

        void makeIdentity();

        Real det() const;

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
