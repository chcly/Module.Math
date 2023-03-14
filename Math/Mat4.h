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

#include "Math/Vec3.h"

namespace Rt2::Math
{
    class Mat3;
    class Quat;

    class Mat4
    {
    public:
        Real m[4][4]{};

        static const Mat4 Identity;
        static const Mat4 Zero;

    public:
        Mat4() = default;

        Mat4(const Mat4& v) = default;

        Mat4(Real m00,
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

        explicit Mat4(const Real* v);

        Mat4 operator*(const Mat4& lhs) const;

        Mat4& transpose();

        Mat4 transposed() const;

        void setTrans(const Vec3& v);

        void setTrans(Real x, Real y, Real z);

        void setScale(const Vec3& v);

        void setScale(Real x, Real y, Real z);

        Vec3 getScale() const;

        Vec3 getTrans() const;

        void makeIdentity();

        Real det() const;

        Mat4 inverted() const;

        void mulAssign(const Mat4& lhs, const Mat4& rhs);

        void makeTransform(const Vec3& loc, const Vec3& scale, const Quat& rot);

        void makeTransform(const Vec3& loc, const Vec3& scale, const Mat3& rot);

        void makeInverseTransform(const Vec3& loc, const Vec3& scale, const Quat& rot);

        void makeInverseTransform(const Vec3& loc, const Vec3& scale, const Mat3& rot);

        static void merge(Mat4& d, const Mat4& lhs, const Mat4& rhs);

        void print() const;
    };
}  // namespace Rt2::Math
