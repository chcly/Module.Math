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
#include "Math/Vec3.h"

namespace Rt2::Math
{
    class Quat
    {
    public:
        static const Quat Identity;
        static const Quat Zero;

        Real w{1}, x{}, y{}, z{};

    public:
        Quat() = default;

        Quat(const Quat& v) = default;

        Quat(const Real nw, const Real nx, const Real ny, const Real nz) :
            w(nw),
            x(nx),
            y(ny),
            z(nz)
        {
        }

        Quat(const Real xRad, const Real yRad, const Real zRad)
        {
            (*this).makeRotXyz(xRad, yRad, zRad);
        }

        explicit Quat(const Vec3& vec)
        {
            (*this).makeRotXyz(vec.x, vec.y, vec.z);
        }

        explicit Quat(const Real* p)
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

        void makeRotXyz(const Real xRad, const Real yRad, const Real zRad)
        {
            Quat q0, q1, q2;
            q0.makeRotX(xRad);
            q1.makeRotY(yRad);
            q2.makeRotZ(zRad);

            *this = q2 * q1 * q0;
            this->normalize();
        }

        void makeRotX(const Real v)
        {
            angles(v * Real(0.5), x, w);
            y = z = 0;
        }

        void makeRotY(const Real v)
        {
            angles(v * Real(0.5), y, w);
            x = z = 0;
        }

        void makeRotZ(const Real v)
        {
            angles(v * Real(0.5), z, w);
            x = y = 0;
        }

        Vec3 toAxis() const
        {
            Real wSq = Real(1.0) - w * w;
            if (wSq < Epsilon)
                return Vec3::UnitZ;

            wSq = Real(1.0) / wSq;
            return {
                x * wSq,
                y * wSq,
                z * wSq,
            };
        }

        Real length() const
        {
            if (const Real len = length2();
                len > Epsilon)
                return RtSqrt(len);
            return Real(0.0);
        }

        void normalize()
        {
            if (Real len = length2();
                len > Epsilon)
            {
                len = RtRSqrt(len);
                w *= len;
                x *= len;
                y *= len;
                z *= len;
            }
        }

        Quat normalized() const
        {
            Quat q(w, x, y, z);
            q.normalize();
            return q;
        }

        Quat inverse() const
        {
            return {w, -x, -y, -z};
        }

        Quat operator-() const
        {
            return {w, -x, -y, -z};
        }

        Quat& invert()
        {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }

        Quat operator*(const Real& v) const
        {
            return {w * v, x * v, y * v, z * v};
        }

        Quat& operator*=(const Real& v)
        {
            w *= v;
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }

        Quat& operator*=(const Quat& v)
        {
            w = w * v.w - x * v.x - y * v.y - z * v.z;
            x = w * v.x + x * v.w + y * v.z - z * v.y;
            y = w * v.y + y * v.w + z * v.x - x * v.z;
            z = w * v.z + z * v.w + x * v.y - y * v.x;
            return *this;
        }

        Quat operator*(const Quat& v) const
        {
            return {
                w * v.w - x * v.x - y * v.y - z * v.z,
                w * v.x + x * v.w + y * v.z - z * v.y,
                w * v.y + y * v.w + z * v.x - x * v.z,
                w * v.z + z * v.w + x * v.y - y * v.x,
            };
        }

        Vec3 operator*(const Vec3& v) const
        {
            const Vec3 c(x, y, z);

            Vec3 a = c.cross(v);
            Vec3 b = c.cross(a);
            a *= Real(2) * w;
            b *= Real(2);
            return v + a + b;
        }

        Quat operator+(const Real& v) const
        {
            return {w + v, x + v, y + v, z + v};
        }

        Quat operator+(const Quat& v) const
        {
            return {w + v.w, x + v.x, y + v.y, z + v.z};
        }

        Quat operator-(const Real& v) const
        {
            return {w - v, x - v, y - v, z - v};
        }

        Quat operator-(const Quat& v) const
        {
            return {w - v.w, x - v.x, y - v.y, z - v.z};
        }

        bool operator==(const Quat& v) const
        {
            return eq(x, v.x) && eq(y, v.y) && eq(z, v.z) && eq(w, v.w);
        }

        bool operator!=(const Quat& v) const
        {
            return neq(x, v.x) && neq(y, v.y) && neq(z, v.z) && neq(w, v.w);
        }

        Real length2() const
        {
            return w * w + x * x + y * y + z * z;
        }

        Real* ptr()
        {
            return &w;
        }

        const Real* ptr() const
        {
            return &w;
        }

        void print() const;
    };
}  // namespace Rt2::Math
