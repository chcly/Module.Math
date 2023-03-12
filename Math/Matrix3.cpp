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
#include "Math/Matrix3.h"
#include <cstdio>
#include "Matrix4.h"
#include "Quaternion.h"

namespace Rt2::Math
{
    const Matrix3 Matrix3::Identity = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    const Matrix3 Matrix3::Zero     = Matrix3(0, 0, 0, 0, 0, 0, 0, 0, 0);

    Matrix3::Matrix3(const Scalar m00,
                     const Scalar m01,
                     const Scalar m02,
                     const Scalar m10,
                     const Scalar m11,
                     const Scalar m12,
                     const Scalar m20,
                     const Scalar m21,
                     const Scalar m22)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
    }

    Matrix3::Matrix3(const Scalar* v)
    {
        if (v != nullptr)
        {
            m[0][0] = *v++;
            m[0][1] = *v++;
            m[0][2] = *v++;
            m[1][0] = *v++;
            m[1][1] = *v++;
            m[1][2] = *v++;
            m[2][0] = *v++;
            m[2][1] = *v++;
            m[2][2] = *v;
        }
    }

    Matrix3 Matrix3::operator*(const Matrix3& lhs) const
    {
        return {
            m[0][0] * lhs.m[0][0] + m[0][1] * lhs.m[1][0] + m[0][2] * lhs.m[2][0],
            m[0][0] * lhs.m[0][1] + m[0][1] * lhs.m[1][1] + m[0][2] * lhs.m[2][1],
            m[0][0] * lhs.m[0][2] + m[0][1] * lhs.m[1][2] + m[0][2] * lhs.m[2][2],

            m[1][0] * lhs.m[0][0] + m[1][1] * lhs.m[1][0] + m[1][2] * lhs.m[2][0],
            m[1][0] * lhs.m[0][1] + m[1][1] * lhs.m[1][1] + m[1][2] * lhs.m[2][1],
            m[1][0] * lhs.m[0][2] + m[1][1] * lhs.m[1][2] + m[1][2] * lhs.m[2][2],

            m[2][0] * lhs.m[0][0] + m[2][1] * lhs.m[1][0] + m[2][2] * lhs.m[2][0],
            m[2][0] * lhs.m[0][1] + m[2][1] * lhs.m[1][1] + m[2][2] * lhs.m[2][1],
            m[2][0] * lhs.m[0][2] + m[2][1] * lhs.m[1][2] + m[2][2] * lhs.m[2][2],
        };
    }

    Vector3 Matrix3::operator*(const Vector3& v) const
    {
        Vector3 r{
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z,
        };

        if (IsZero(r.x, RT_EPSILON))
            r.x = 0;
        if (IsZero(r.y, RT_EPSILON))
            r.y = 0;
        if (IsZero(r.z, RT_EPSILON))
            r.z = 0;
        return r;
    }

    bool Matrix3::operator==(const Matrix3& rhs) const
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (!Eq(m[i][j], rhs.m[i][j]))
                    return false;
            }
        }
        return true;
    }

    Matrix3 Matrix3::transposed() const
    {
        return {
            m[0][0],
            m[1][0],
            m[2][0],
            m[0][1],
            m[1][1],
            m[2][1],
            m[0][2],
            m[1][2],
            m[2][2],
        };
    }

    Vector3 Matrix3::row(const int idx) const
    {
        if (idx < 3 && idx >= 0)
            return Vector3(m[0][idx], m[1][idx], m[2][idx]);
        return Vector3::Zero;
    }

    Vector3 Matrix3::col(const int idx) const
    {
        if (idx < 3 && idx >= 0)
            return Vector3(m[idx][0], m[idx][1], m[idx][2]);
        return Vector3::Zero;
    }

    void Matrix3::makeIdentity()
    {
        m[0][0] = 1;
        m[0][1] = 0;
        m[0][2] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
        m[1][2] = 0;
        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 1;
    }

    void Matrix3::fromAngles(const Scalar pitch, const Scalar yaw, const Scalar roll)
    {
        Scalar s0, c0, s1, c1, s2, c2;
        SinCos(pitch, s0, c0);
        SinCos(yaw, s1, c1);
        SinCos(roll, s2, c2);

        const Scalar s2c0 = s2 * c0;
        const Scalar s2s0 = s2 * s0;

        m[0][0] = c1 * c2;
        m[0][1] = -c1 * s2c0 + s1 * s0;
        m[0][2] = c1 * s2s0 + s1 * c0;
        m[1][0] = s2;
        m[1][1] = c2 * c0;
        m[1][2] = -c2 * s0;
        m[2][0] = -s1 * c2;
        m[2][1] = s1 * s2c0 + c1 * s0;
        m[2][2] = -s1 * s2s0 + c1 * c0;
    }

    void Matrix3::fromQuaternion(const Quaternion& q)
    {
        const Scalar qx2 = q.x * q.x;
        const Scalar qy2 = q.y * q.y;
        const Scalar qz2 = q.z * q.z;

        const Scalar qxy = q.x * q.y;
        const Scalar qxz = q.x * q.z;
        const Scalar qyz = q.y * q.z;

        const Scalar qwx = q.w * q.x;
        const Scalar qwy = q.w * q.y;
        const Scalar qwz = q.w * q.z;

        m[0][0] = Scalar(1.0) - Scalar(2.0) * (qy2 + qz2);
        m[0][1] = Scalar(2.0) * (qxy - qwz);
        m[0][2] = Scalar(2.0) * (qxz + qwy);

        m[1][0] = Scalar(2.0) * (qxy + qwz);
        m[1][1] = Scalar(1.0) - Scalar(2.0) * (qx2 + qz2);
        m[1][2] = Scalar(2.0) * (qyz - qwx);

        m[2][0] = Scalar(2.0) * (qxz - qwy);
        m[2][1] = Scalar(2.0) * (qyz + qwx);
        m[2][2] = Scalar(1.0) - Scalar(2.0) * (qx2 + qy2);
    }

    void Matrix3::fromMat4(const Matrix4& mat4By4)
    {
        m[0][0] = mat4By4.m[0][0];
        m[0][1] = mat4By4.m[0][1];
        m[0][2] = mat4By4.m[0][2];

        m[1][0] = mat4By4.m[1][0];
        m[1][1] = mat4By4.m[1][1];
        m[1][2] = mat4By4.m[1][2];

        m[2][0] = mat4By4.m[2][0];
        m[2][1] = mat4By4.m[2][1];
        m[2][2] = mat4By4.m[2][2];
    }

    void Matrix3::makeRotZ(Scalar theta)
    {
        Scalar s, c;
        SinCos(theta, s, c);
        makeIdentity();

        m[1][1] = m[0][0] = c;
        m[0][1]           = -s;
        m[1][0]           = s;
    }

    void Matrix3::makeRotY(Scalar theta)
    {
        Scalar s, c;
        SinCos(theta, s, c);
        makeIdentity();

        m[2][2] = m[0][0] = c;
        m[0][2] = -s;
        m[2][0] = s;
    }

    void Matrix3::makeRotX(Scalar theta)
    {
        Scalar s, c;
        SinCos(theta, s, c);
        makeIdentity();

        m[1][1] = m[2][2] = c;
        m[1][2] = -s;
        m[2][1] = s;
    }

    void Matrix3::print() const
    {
        printf("[ %3.3f, %3.3f, %3.3f ]\n", (double)m[0][0], (double)m[0][1], (double)m[0][2]);
        printf("[ %3.3f, %3.3f, %3.3f ]\n", (double)m[1][0], (double)m[1][1], (double)m[1][2]);
        printf("[ %3.3f, %3.3f, %3.3f ]\n", (double)m[2][0], (double)m[2][1], (double)m[2][2]);
    }
}  // namespace Rt2::Math
