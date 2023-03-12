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
#include "Math/Matrix4.h"
#include <cstdio>
#include "Math/Matrix3.h"
#include "Quaternion.h"

namespace Rt2::Math
{
    const Matrix4 Matrix4::Identity = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    const Matrix4 Matrix4::Zero     = Matrix4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    Matrix4::Matrix4(
        Scalar m00,
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
        Scalar m33)
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

    Matrix4::Matrix4(const Scalar* v)
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

    Matrix4 Matrix4::operator*(const Matrix4& lhs) const
    {
        return Matrix4(
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

    void Matrix4::mulAssign(const Matrix4& lhs, const Matrix4& rhs)
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

    void Matrix4::merge(Matrix4& d, const Matrix4& lhs, const Matrix4& rhs)
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

    Matrix4& Matrix4::transpose()
    {
        *this = transposed();
        return *this;
    }

    Matrix4 Matrix4::transposed() const
    {
        return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0], m[0][1], m[1][1], m[2][1], m[3][1], m[0][2], m[1][2], m[2][2], m[3][2], m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    void Matrix4::setTrans(const Vector3& v)
    {
        m[0][3] = v.x;
        m[1][3] = v.y;
        m[2][3] = v.z;
        m[3][3] = 1;
    }

    void Matrix4::setTrans(Scalar x, Scalar y, Scalar z)
    {
        m[0][3] = x;
        m[1][3] = y;
        m[2][3] = z;
        m[3][3] = 1;
    }

    void Matrix4::setScale(const Vector3& v)
    {
        m[0][0] = v.x;
        m[1][1] = v.y;
        m[2][2] = v.z;
        m[3][3] = 1;
    }

    void Matrix4::setScale(Scalar x, Scalar y, Scalar z)
    {
        m[0][0] = x;
        m[1][1] = y;
        m[2][2] = z;
        m[3][3] = 1;
    }

    Vector3 Matrix4::getTrans() const
    {
        return Vector3(m[0][3], m[1][3], m[2][3]);
    }

    Vector3 Matrix4::getScale() const
    {
        return Vector3(m[0][0], m[1][1], m[2][2]);
    }

    void Matrix4::makeIdentity()
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

    void Matrix4::makeTransform(const Vector3& loc, const Vector3& scale, const Quaternion& rot)
    {
        Matrix3 m3;

        m3.fromQuaternion(rot);
        makeTransform(loc, scale, m3);
    }

    void Matrix4::makeInverseTransform(const Vector3& loc, const Vector3& scale, const Quaternion& rot)
    {
        Matrix3 m3;
        m3.fromQuaternion(rot.inverse());
        makeInverseTransform(loc, scale, m3);
    }

    void Matrix4::makeTransform(const Vector3& loc, const Vector3& scale, const Matrix3& rot)
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

    void Matrix4::makeInverseTransform(const Vector3& loc, const Vector3& scale, const Matrix3& rot)
    {
        const Vector3 is = 1.0 / scale;

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

    Scalar Matrix4::det() const
    {
        return m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] - m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
               m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
               m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
               m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
               m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] - m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
               m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
    }

    Matrix4 Matrix4::inverted() const
    {
        Matrix4 r;

        Scalar d = det();
        if (IsZero(d))
            return Identity;

        d = Scalar(1.0) / d;

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

    void Matrix4::print() const
    {
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[0][0], (double)m[0][1], (double)m[0][2], (double)m[0][3]);
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[1][0], (double)m[1][1], (double)m[1][2], (double)m[1][3]);
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[2][0], (double)m[2][1], (double)m[2][2], (double)m[2][3]);
        printf("[ %3.3f, %3.3f, %3.3f, %3.3f ]\n", (double)m[3][0], (double)m[3][1], (double)m[3][2], (double)m[3][3]);
    }

}  // namespace Rt2::Math
