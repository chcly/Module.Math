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
#include "Math/Mat4.h"
#include <cstdio>
#include "Math/Mat3.h"
#include "Quat.h"

namespace Rt2::Math
{
    const Mat4 Mat4::Identity = Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    const Mat4 Mat4::Zero     = Mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    Mat4::Mat4(
        const Real m00,
        const Real m01,
        const Real m02,
        const Real m03,
        const Real m10,
        const Real m11,
        const Real m12,
        const Real m13,
        const Real m20,
        const Real m21,
        const Real m22,
        const Real m23,
        const Real m30,
        const Real m31,
        const Real m32,
        const Real m33)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }

    Mat4::Mat4(const Real* v)
    {
        if (v != nullptr)
        {
            m[0][0] = *v++;
            m[0][1] = *v++;
            m[0][2] = *v++;
            m[0][3] = *v++;
            m[1][0] = *v++;
            m[1][1] = *v++;
            m[1][2] = *v++;
            m[1][3] = *v++;
            m[2][0] = *v++;
            m[2][1] = *v++;
            m[2][2] = *v++;
            m[2][3] = *v++;
            m[3][0] = *v++;
            m[3][1] = *v++;
            m[3][2] = *v++;
            m[3][3] = *v;
        }
    }

    Mat4 Mat4::operator*(const Mat4& lhs) const
    {
        return Mat4(
            m[0][0] * lhs.m[0][0] + m[0][1] * lhs.m[1][0] + m[0][2] * lhs.m[2][0] + m[0][3] * lhs.m[3][0],
            m[0][0] * lhs.m[0][1] + m[0][1] * lhs.m[1][1] + m[0][2] * lhs.m[2][1] + m[0][3] * lhs.m[3][1],
            m[0][0] * lhs.m[0][2] + m[0][1] * lhs.m[1][2] + m[0][2] * lhs.m[2][2] + m[0][3] * lhs.m[3][2],
            m[0][0] * lhs.m[0][3] + m[0][1] * lhs.m[1][3] + m[0][2] * lhs.m[2][3] + m[0][3] * lhs.m[3][3],

            m[1][0] * lhs.m[0][0] + m[1][1] * lhs.m[1][0] + m[1][2] * lhs.m[2][0] + m[1][3] * lhs.m[3][0],
            m[1][0] * lhs.m[0][1] + m[1][1] * lhs.m[1][1] + m[1][2] * lhs.m[2][1] + m[1][3] * lhs.m[3][1],
            m[1][0] * lhs.m[0][2] + m[1][1] * lhs.m[1][2] + m[1][2] * lhs.m[2][2] + m[1][3] * lhs.m[3][2],
            m[1][0] * lhs.m[0][3] + m[1][1] * lhs.m[1][3] + m[1][2] * lhs.m[2][3] + m[1][3] * lhs.m[3][3],

            m[2][0] * lhs.m[0][0] + m[2][1] * lhs.m[1][0] + m[2][2] * lhs.m[2][0] + m[2][3] * lhs.m[3][0],
            m[2][0] * lhs.m[0][1] + m[2][1] * lhs.m[1][1] + m[2][2] * lhs.m[2][1] + m[2][3] * lhs.m[3][1],
            m[2][0] * lhs.m[0][2] + m[2][1] * lhs.m[1][2] + m[2][2] * lhs.m[2][2] + m[2][3] * lhs.m[3][2],
            m[2][0] * lhs.m[0][3] + m[2][1] * lhs.m[1][3] + m[2][2] * lhs.m[2][3] + m[2][3] * lhs.m[3][3],

            m[3][0] * lhs.m[0][0] + m[3][1] * lhs.m[1][0] + m[3][2] * lhs.m[2][0] + m[3][3] * lhs.m[3][0],
            m[3][0] * lhs.m[0][1] + m[3][1] * lhs.m[1][1] + m[3][2] * lhs.m[2][1] + m[3][3] * lhs.m[3][1],
            m[3][0] * lhs.m[0][2] + m[3][1] * lhs.m[1][2] + m[3][2] * lhs.m[2][2] + m[3][3] * lhs.m[3][2],
            m[3][0] * lhs.m[0][3] + m[3][1] * lhs.m[1][3] + m[3][2] * lhs.m[2][3] + m[3][3] * lhs.m[3][3]);
    }

    void Mat4::mulAssign(const Mat4& lhs, const Mat4& rhs)
    {
        m[0][0] = lhs.m[0][0] * rhs.m[0][0] + lhs.m[0][1] * rhs.m[1][0] + lhs.m[0][2] * rhs.m[2][0] + lhs.m[0][3] * rhs.m[3][0];
        m[0][1] = lhs.m[0][0] * rhs.m[0][1] + lhs.m[0][1] * rhs.m[1][1] + lhs.m[0][2] * rhs.m[2][1] + lhs.m[0][3] * rhs.m[3][1];
        m[0][2] = lhs.m[0][0] * rhs.m[0][2] + lhs.m[0][1] * rhs.m[1][2] + lhs.m[0][2] * rhs.m[2][2] + lhs.m[0][3] * rhs.m[3][2];
        m[0][3] = lhs.m[0][0] * rhs.m[0][3] + lhs.m[0][1] * rhs.m[1][3] + lhs.m[0][2] * rhs.m[2][3] + lhs.m[0][3] * rhs.m[3][3];

        m[1][0] = lhs.m[1][0] * rhs.m[0][0] + lhs.m[1][1] * rhs.m[1][0] + lhs.m[1][2] * rhs.m[2][0] + lhs.m[1][3] * rhs.m[3][0];
        m[1][1] = lhs.m[1][0] * rhs.m[0][1] + lhs.m[1][1] * rhs.m[1][1] + lhs.m[1][2] * rhs.m[2][1] + lhs.m[1][3] * rhs.m[3][1];
        m[1][2] = lhs.m[1][0] * rhs.m[0][2] + lhs.m[1][1] * rhs.m[1][2] + lhs.m[1][2] * rhs.m[2][2] + lhs.m[1][3] * rhs.m[3][2];
        m[1][3] = lhs.m[1][0] * rhs.m[0][3] + lhs.m[1][1] * rhs.m[1][3] + lhs.m[1][2] * rhs.m[2][3] + lhs.m[1][3] * rhs.m[3][3];

        m[2][0] = lhs.m[2][0] * rhs.m[0][0] + lhs.m[2][1] * rhs.m[1][0] + lhs.m[2][2] * rhs.m[2][0] + lhs.m[2][3] * rhs.m[3][0];
        m[2][1] = lhs.m[2][0] * rhs.m[0][1] + lhs.m[2][1] * rhs.m[1][1] + lhs.m[2][2] * rhs.m[2][1] + lhs.m[2][3] * rhs.m[3][1];
        m[2][2] = lhs.m[2][0] * rhs.m[0][2] + lhs.m[2][1] * rhs.m[1][2] + lhs.m[2][2] * rhs.m[2][2] + lhs.m[2][3] * rhs.m[3][2];
        m[2][3] = lhs.m[2][0] * rhs.m[0][3] + lhs.m[2][1] * rhs.m[1][3] + lhs.m[2][2] * rhs.m[2][3] + lhs.m[2][3] * rhs.m[3][3];

        m[3][0] = lhs.m[3][0] * rhs.m[0][0] + lhs.m[3][1] * rhs.m[1][0] + lhs.m[3][2] * rhs.m[2][0] + lhs.m[3][3] * rhs.m[3][0];
        m[3][1] = lhs.m[3][0] * rhs.m[0][1] + lhs.m[3][1] * rhs.m[1][1] + lhs.m[3][2] * rhs.m[2][1] + lhs.m[3][3] * rhs.m[3][1];
        m[3][2] = lhs.m[3][0] * rhs.m[0][2] + lhs.m[3][1] * rhs.m[1][2] + lhs.m[3][2] * rhs.m[2][2] + lhs.m[3][3] * rhs.m[3][2];
        m[3][3] = lhs.m[3][0] * rhs.m[0][3] + lhs.m[3][1] * rhs.m[1][3] + lhs.m[3][2] * rhs.m[2][3] + lhs.m[3][3] * rhs.m[3][3];
    }

    void Mat4::merge(Mat4& d, const Mat4& lhs, const Mat4& rhs)
    {
        d.m[0][0] = lhs.m[0][0] * rhs.m[0][0] + lhs.m[0][1] * rhs.m[1][0] + lhs.m[0][2] * rhs.m[2][0] + lhs.m[0][3] * rhs.m[3][0];
        d.m[0][1] = lhs.m[0][0] * rhs.m[0][1] + lhs.m[0][1] * rhs.m[1][1] + lhs.m[0][2] * rhs.m[2][1] + lhs.m[0][3] * rhs.m[3][1];
        d.m[0][2] = lhs.m[0][0] * rhs.m[0][2] + lhs.m[0][1] * rhs.m[1][2] + lhs.m[0][2] * rhs.m[2][2] + lhs.m[0][3] * rhs.m[3][2];
        d.m[0][3] = lhs.m[0][0] * rhs.m[0][3] + lhs.m[0][1] * rhs.m[1][3] + lhs.m[0][2] * rhs.m[2][3] + lhs.m[0][3] * rhs.m[3][3];

        d.m[1][0] = lhs.m[1][0] * rhs.m[0][0] + lhs.m[1][1] * rhs.m[1][0] + lhs.m[1][2] * rhs.m[2][0] + lhs.m[1][3] * rhs.m[3][0];
        d.m[1][1] = lhs.m[1][0] * rhs.m[0][1] + lhs.m[1][1] * rhs.m[1][1] + lhs.m[1][2] * rhs.m[2][1] + lhs.m[1][3] * rhs.m[3][1];
        d.m[1][2] = lhs.m[1][0] * rhs.m[0][2] + lhs.m[1][1] * rhs.m[1][2] + lhs.m[1][2] * rhs.m[2][2] + lhs.m[1][3] * rhs.m[3][2];
        d.m[1][3] = lhs.m[1][0] * rhs.m[0][3] + lhs.m[1][1] * rhs.m[1][3] + lhs.m[1][2] * rhs.m[2][3] + lhs.m[1][3] * rhs.m[3][3];

        d.m[2][0] = lhs.m[2][0] * rhs.m[0][0] + lhs.m[2][1] * rhs.m[1][0] + lhs.m[2][2] * rhs.m[2][0] + lhs.m[2][3] * rhs.m[3][0];
        d.m[2][1] = lhs.m[2][0] * rhs.m[0][1] + lhs.m[2][1] * rhs.m[1][1] + lhs.m[2][2] * rhs.m[2][1] + lhs.m[2][3] * rhs.m[3][1];
        d.m[2][2] = lhs.m[2][0] * rhs.m[0][2] + lhs.m[2][1] * rhs.m[1][2] + lhs.m[2][2] * rhs.m[2][2] + lhs.m[2][3] * rhs.m[3][2];
        d.m[2][3] = lhs.m[2][0] * rhs.m[0][3] + lhs.m[2][1] * rhs.m[1][3] + lhs.m[2][2] * rhs.m[2][3] + lhs.m[2][3] * rhs.m[3][3];

        d.m[3][0] = lhs.m[3][0] * rhs.m[0][0] + lhs.m[3][1] * rhs.m[1][0] + lhs.m[3][2] * rhs.m[2][0] + lhs.m[3][3] * rhs.m[3][0];
        d.m[3][1] = lhs.m[3][0] * rhs.m[0][1] + lhs.m[3][1] * rhs.m[1][1] + lhs.m[3][2] * rhs.m[2][1] + lhs.m[3][3] * rhs.m[3][1];
        d.m[3][2] = lhs.m[3][0] * rhs.m[0][2] + lhs.m[3][1] * rhs.m[1][2] + lhs.m[3][2] * rhs.m[2][2] + lhs.m[3][3] * rhs.m[3][2];
        d.m[3][3] = lhs.m[3][0] * rhs.m[0][3] + lhs.m[3][1] * rhs.m[1][3] + lhs.m[3][2] * rhs.m[2][3] + lhs.m[3][3] * rhs.m[3][3];
    }

    Mat4& Mat4::transpose()
    {
        *this = transposed();
        return *this;
    }

    Mat4 Mat4::transposed() const
    {
        return Mat4(m[0][0], m[1][0], m[2][0], m[3][0], m[0][1], m[1][1], m[2][1], m[3][1], m[0][2], m[1][2], m[2][2], m[3][2], m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    void Mat4::setTrans(const Vec3& v)
    {
        m[0][3] = v.x;
        m[1][3] = v.y;
        m[2][3] = v.z;
        m[3][3] = 1;
    }

    void Mat4::setTrans(Real x, Real y, Real z)
    {
        m[0][3] = x;
        m[1][3] = y;
        m[2][3] = z;
        m[3][3] = 1;
    }

    void Mat4::setScale(const Vec3& v)
    {
        m[0][0] = v.x;
        m[1][1] = v.y;
        m[2][2] = v.z;
        m[3][3] = 1;
    }

    void Mat4::setScale(Real x, Real y, Real z)
    {
        m[0][0] = x;
        m[1][1] = y;
        m[2][2] = z;
        m[3][3] = 1;
    }

    Vec3 Mat4::getTrans() const
    {
        return Vec3(m[0][3], m[1][3], m[2][3]);
    }

    Vec3 Mat4::getScale() const
    {
        return Vec3(m[0][0], m[1][1], m[2][2]);
    }

    void Mat4::makeIdentity()
    {
        m[0][0] = 1;
        m[0][1] = 0;
        m[0][2] = 0;
        m[0][3] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
        m[1][2] = 0;
        m[1][3] = 0;
        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 1;
        m[2][3] = 0;
        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1;
    }

    void Mat4::makeTransform(const Vec3& loc, const Vec3& scale, const Quat& rot)
    {
        Mat3 m3;

        m3.fromQuaternion(rot);
        makeTransform(loc, scale, m3);
    }

    void Mat4::makeInverseTransform(const Vec3& loc, const Vec3& scale, const Quat& rot)
    {
        Mat3 m3;
        m3.fromQuaternion(rot.inverse());
        makeInverseTransform(loc, scale, m3);
    }

    void Mat4::makeTransform(const Vec3& loc, const Vec3& scale, const Mat3& rot)
    {
        m[0][0] = scale.x * rot.m[0][0];
        m[0][1] = scale.y * rot.m[0][1];
        m[0][2] = scale.z * rot.m[0][2];
        m[0][3] = loc.x;

        m[1][0] = scale.x * rot.m[1][0];
        m[1][1] = scale.y * rot.m[1][1];
        m[1][2] = scale.z * rot.m[1][2];
        m[1][3] = loc.y;

        m[2][0] = scale.x * rot.m[2][0];
        m[2][1] = scale.y * rot.m[2][1];
        m[2][2] = scale.z * rot.m[2][2];
        m[2][3] = loc.z;

        m[3][0] = m[3][1] = m[3][2] = 0;
        m[3][3]                     = 1;
    }

    void Mat4::makeInverseTransform(const Vec3& loc, const Vec3& scale, const Mat3& rot)
    {
        const Vec3 is = 1.0 / scale;

        m[0][0] = is.x * rot.m[0][0];
        m[0][1] = is.y * rot.m[0][1];
        m[0][2] = is.z * rot.m[0][2];
        m[0][3] = -loc.x;

        m[1][0] = is.x * rot.m[1][0];
        m[1][1] = is.y * rot.m[1][1];
        m[1][2] = is.z * rot.m[1][2];
        m[1][3] = -loc.y;

        m[2][0] = is.x * rot.m[2][0];
        m[2][1] = is.y * rot.m[2][1];
        m[2][2] = is.z * rot.m[2][2];
        m[2][3] = -loc.z;

        m[3][0] = m[3][1] = m[3][2] = 0;
        m[3][3]                     = 1;
    }

    Real Mat4::det() const
    {
        return m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] - m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
               m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
               m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
               m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
               m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] - m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
               m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
    }

    Mat4 Mat4::inverted() const
    {
        Mat4 r;

        Real d = det();
        if (isZero(d))
            return Identity;

        d = Real(1.0) / d;

        r.m[0][0] = d * (m[1][2] * m[2][3] * m[3][1] - m[1][3] * m[2][2] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] + m[1][1] * m[2][2] * m[3][3]);
        r.m[1][0] = d * (m[0][3] * m[2][2] * m[3][1] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2] + m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] - m[0][1] * m[2][2] * m[3][3]);
        r.m[2][0] = d * (m[0][2] * m[1][3] * m[3][1] - m[0][3] * m[1][2] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] - m[0][2] * m[1][1] * m[3][3] + m[0][1] * m[1][2] * m[3][3]);
        r.m[3][0] = d * (m[0][3] * m[1][2] * m[2][1] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2] + m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] - m[0][1] * m[1][2] * m[2][3]);
        r.m[0][1] = d * (m[1][3] * m[2][2] * m[3][0] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2] + m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] - m[1][0] * m[2][2] * m[3][3]);
        r.m[1][1] = d * (m[0][2] * m[2][3] * m[3][0] - m[0][3] * m[2][2] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] + m[0][0] * m[2][2] * m[3][3]);
        r.m[2][1] = d * (m[0][3] * m[1][2] * m[3][0] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2] + m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] - m[0][0] * m[1][2] * m[3][3]);
        r.m[3][1] = d * (m[0][2] * m[1][3] * m[2][0] - m[0][3] * m[1][2] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] + m[0][0] * m[1][2] * m[2][3]);
        r.m[0][2] = d * (m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][1] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] + m[1][0] * m[2][1] * m[3][3]);
        r.m[1][2] = d * (m[0][3] * m[2][1] * m[3][0] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1] + m[0][0] * m[2][3] * m[3][1] + m[0][1] * m[2][0] * m[3][3] - m[0][0] * m[2][1] * m[3][3]);
        r.m[2][2] = d * (m[0][1] * m[1][3] * m[3][0] - m[0][3] * m[1][1] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] + m[0][0] * m[1][1] * m[3][3]);
        r.m[3][2] = d * (m[0][3] * m[1][1] * m[2][0] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1] + m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] - m[0][0] * m[1][1] * m[2][3]);
        r.m[0][3] = d * (m[1][2] * m[2][1] * m[3][0] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1] + m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] - m[1][0] * m[2][1] * m[3][2]);
        r.m[1][3] = d * (m[0][1] * m[2][2] * m[3][0] - m[0][2] * m[2][1] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] + m[0][0] * m[2][1] * m[3][2]);
        r.m[2][3] = d * (m[0][2] * m[1][1] * m[3][0] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1] + m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] - m[0][0] * m[1][1] * m[3][2]);
        r.m[3][3] = d * (m[0][1] * m[1][2] * m[2][0] - m[0][2] * m[1][1] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] + m[0][0] * m[1][1] * m[2][2]);

        return r;
    }

    void Mat4::print() const
    {
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[0][0], (double)m[0][1], (double)m[0][2], (double)m[0][3]);
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[1][0], (double)m[1][1], (double)m[1][2], (double)m[1][3]);
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[2][0], (double)m[2][1], (double)m[2][2], (double)m[2][3]);
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[3][0], (double)m[3][1], (double)m[3][2], (double)m[3][3]);
    }

}  // namespace Rt2::Math
