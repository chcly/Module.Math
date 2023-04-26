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
#include "Math/Mat3.h"
#include <cstdio>
#include "Mat4.h"
#include "Print.h"
#include "Quat.h"
#include "Utils/Console.h"

namespace Rt2::Math
{
    const Mat3 Mat3::Identity = Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    const Mat3 Mat3::Zero     = Mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);

    Mat3::Mat3(const Real m00,
                     const Real m01,
                     const Real m02,
                     const Real m10,
                     const Real m11,
                     const Real m12,
                     const Real m20,
                     const Real m21,
                     const Real m22)
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

    Mat3::Mat3(const Real* v)
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

    Mat3 Mat3::operator*(const Mat3& lhs) const
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

    Vec3 Mat3::operator*(const Vec3& v) const
    {
        Vec3 r{
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z,
        };

        if (isZero(r.x, Epsilon))
            r.x = 0;
        if (isZero(r.y, Epsilon))
            r.y = 0;
        if (isZero(r.z, Epsilon))
            r.z = 0;
        return r;
    }

    bool Mat3::operator==(const Mat3& rhs) const
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (!eq(m[i][j], rhs.m[i][j]))
                    return false;
            }
        }
        return true;
    }

    Mat3 Mat3::transposed() const
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

    Vec3 Mat3::row(const int idx) const
    {
        if (idx < 3 && idx >= 0)
            return {m[0][idx], m[1][idx], m[2][idx]};
        return Vec3::Zero;
    }

    Vec3 Mat3::col(const int idx) const
    {
        if (idx < 3 && idx >= 0)
            return {m[idx][0], m[idx][1], m[idx][2]};
        return Vec3::Zero;
    }

    void Mat3::makeIdentity()
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

    void Mat3::fromAngles(const Real pitch, const Real yaw, const Real roll)
    {
        Real s0, c0, s1, c1, s2, c2;
        angles(pitch, s0, c0);
        angles(yaw, s1, c1);
        angles(roll, s2, c2);

        const Real s2C0 = s2 * c0;
        const Real s2S0 = s2 * s0;

        m[0][0] = c1 * c2;
        m[0][1] = -c1 * s2C0 + s1 * s0;
        m[0][2] = c1 * s2S0 + s1 * c0;
        m[1][0] = s2;
        m[1][1] = c2 * c0;
        m[1][2] = -c2 * s0;
        m[2][0] = -s1 * c2;
        m[2][1] = s1 * s2C0 + c1 * s0;
        m[2][2] = -s1 * s2S0 + c1 * c0;
    }

    void Mat3::fromAngles(const Vec3& dRot)
    {
        fromAngles(dRot.x, dRot.y, dRot.z);
    }

    void Mat3::fromQuaternion(const Quat& q)
    {
        const Real qx2 = q.x * q.x;
        const Real qy2 = q.y * q.y;
        const Real qz2 = q.z * q.z;

        const Real qxy = q.x * q.y;
        const Real qxz = q.x * q.z;
        const Real qyz = q.y * q.z;

        const Real qwx = q.w * q.x;
        const Real qwy = q.w * q.y;
        const Real qwz = q.w * q.z;

        m[0][0] = Real(1.0) - Real(2.0) * (qy2 + qz2);
        m[0][1] = Real(2.0) * (qxy - qwz);
        m[0][2] = Real(2.0) * (qxz + qwy);

        m[1][0] = Real(2.0) * (qxy + qwz);
        m[1][1] = Real(1.0) - Real(2.0) * (qx2 + qz2);
        m[1][2] = Real(2.0) * (qyz - qwx);

        m[2][0] = Real(2.0) * (qxz - qwy);
        m[2][1] = Real(2.0) * (qyz + qwx);
        m[2][2] = Real(1.0) - Real(2.0) * (qx2 + qy2);
    }

    void Mat3::fromMat4(const Mat4& mat4By4)
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

    void Mat3::makeRotZ(const Real theta)
    {
        Real s, c;
        angles(theta, s, c);
        makeIdentity();

        m[1][1] = m[0][0] = c;

        m[0][1] = -s;
        m[1][0] = s;
    }

    void Mat3::makeRotY(const Real theta)
    {
        Real s, c;
        angles(theta, s, c);
        makeIdentity();

        m[2][2] = m[0][0] = c;
        m[0][2]           = -s;
        m[2][0]           = s;
    }

    void Mat3::makeRotX(const Real theta)
    {
        Real s, c;
        angles(theta, s, c);
        makeIdentity();

        m[1][1] = m[2][2] = c;
        m[1][2]           = -s;
        m[2][1]           = s;
    }

    void Mat3::print() const
    {
        Printer::print(*this);
    }
}  // namespace Rt2::Math
