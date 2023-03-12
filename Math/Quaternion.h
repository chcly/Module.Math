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

#include "Math/Math.h"
#include "Math/Vector3.h"

namespace Rt2::Math
{
    class Quaternion
    {
    public:
        static const Quaternion Identity;
        static const Quaternion Zero;

        Scalar w{1}, x{}, y{}, z{};

    public:
        Quaternion() = default;

        Quaternion(const Quaternion& v) = default;

        Quaternion(const Scalar nw, const Scalar nx, const Scalar ny, const Scalar nz) :
            w(nw),
            x(nx),
            y(ny),
            z(nz)
        {
        }

        Quaternion(const Scalar xRad, const Scalar yRad, const Scalar zRad)
        {
            (*this).makeRotXYZ(xRad, yRad, zRad);
        }

        Quaternion(const Vector3& vec)
        {
            (*this).makeRotXYZ(vec.x, vec.y, vec.z);
        }

        explicit Quaternion(const Scalar* p)
        {
            if (p != nullptr)
            {
                w = p[0];
                x = p[1];
                y = p[2];
                z = p[3];
            }
        }

        void makeIdentity()
        {
            w = 1;
            x = y = z = 0;
        }

        void makeRotXYZ(const Scalar xRad, const Scalar yRad, const Scalar zRad)
        {
            Quaternion q0, q1, q2;
            q0.makeRotX(xRad);
            q1.makeRotY(yRad);
            q2.makeRotZ(zRad);

            *this = q2 * q1 * q0;
            this->normalize();
        }

        void makeRotX(const Scalar v)
        {
            SinCos(v * Scalar(0.5), x, w);
            y = z = 0;
        }

        void makeRotY(const Scalar v)
        {
            SinCos(v * Scalar(0.5), y, w);
            x = z = 0;
        }

        void makeRotZ(const Scalar v)
        {
            SinCos(v * Scalar(0.5), z, w);
            x = y = 0;
        }

        Vector3 toAxis() const
        {
            Scalar wSq = Scalar(1.0) - w * w;
            if (wSq < RT_EPSILON)
                return Vector3::UnitZ;

            wSq = Scalar(1.0) / wSq;
            return Vector3(x * wSq, y * wSq, z * wSq);
        }

        Scalar length() const
        {
            const Scalar len = length2();
            if (len > RT_EPSILON)
                return RtSqrt(len);
            return Scalar(0.0);
        }

        void normalize()
        {
            Scalar len = length2();
            if (len > RT_EPSILON)
            {
                len = RtRSqrt(len);
                w *= len;
                x *= len;
                y *= len;
                z *= len;
            }
        }

        Quaternion normalized() const
        {
            Quaternion q(w, x, y, z);
            q.normalize();
            return q;
        }

        Quaternion inverse() const
        {
            return Quaternion(w, -x, -y, -z);
        }

        Quaternion operator-() const
        {
            return Quaternion(w, -x, -y, -z);
        }

        Quaternion& invert()
        {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }

        Quaternion operator*(const Scalar& v) const
        {
            return Quaternion(w * v, x * v, y * v, z * v);
        }

        Quaternion& operator*=(const Scalar& v)
        {
            w *= v;
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }

        Quaternion& operator*=(const Quaternion& v)
        {
            w = w * v.w - x * v.x - y * v.y - z * v.z;
            x = w * v.x + x * v.w + y * v.z - z * v.y;
            y = w * v.y + y * v.w + z * v.x - x * v.z;
            z = w * v.z + z * v.w + x * v.y - y * v.x;
            return *this;
        }

        Quaternion operator*(const Quaternion& v) const
        {
            return Quaternion(
                w * v.w - x * v.x - y * v.y - z * v.z,
                w * v.x + x * v.w + y * v.z - z * v.y,
                w * v.y + y * v.w + z * v.x - x * v.z,
                w * v.z + z * v.w + x * v.y - y * v.x);
        }

        Vector3 operator*(const Vector3& v) const
        {
            const Vector3 c(x, y, z);

            Vector3 a = c.cross(v);
            Vector3 b = c.cross(a);
            a *= Scalar(2) * w;
            b *= Scalar(2);
            return v + a + b;
        }

        Quaternion operator+(const Scalar& v) const
        {
            return Quaternion(w + v, x + v, y + v, z + v);
        }

        Quaternion operator+(const Quaternion& v) const
        {
            return Quaternion(w + v.w, x + v.x, y + v.y, z + v.z);
        }

        Quaternion operator-(const Scalar& v) const
        {
            return Quaternion(w - v, x - v, y - v, z - v);
        }

        Quaternion operator-(const Quaternion& v) const
        {
            return Quaternion(w - v.w, x - v.x, y - v.y, z - v.z);
        }

        bool operator==(const Quaternion& v) const
        {
            return Eq(x, v.x) && Eq(y, v.y) && Eq(z, v.z) && Eq(w, v.w);
        }

        bool operator!=(const Quaternion& v) const
        {
            return NEq(x, v.x) && NEq(y, v.y) && NEq(z, v.z) && NEq(w, v.w);
        }

        Scalar length2() const
        {
            return w * w + x * x + y * y + z * z;
        }

        Scalar* ptr()
        {
            return &w;
        }

        const Scalar* ptr() const
        {
            return &w;
        }

        void print() const;
    };
}  // namespace Rt2::Math
