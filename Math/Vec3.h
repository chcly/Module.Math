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

namespace Rt2::Math
{
    class Color;

    class Vec3
    {
    public:
        Real x{}, y{}, z{};

        static const Vec3 Unit;
        static const Vec3 UnitX;
        static const Vec3 UnitY;
        static const Vec3 UnitZ;
        static const Vec3 Zero;

    public:
        Vec3() = default;

        explicit Vec3(const Color& col);

        Vec3(const Real nx, const Real ny, const Real nz) :
            x(nx),
            y(ny),
            z(nz)
        {
        }

        explicit Vec3(const float* pointer)
        {
            if (pointer)
            {
                x = (Real)pointer[0];
                y = (Real)pointer[1];
                z = (Real)pointer[2];
            }
            else
                x = y = z = 0;
        }

        explicit Vec3(const double* p)
        {
            if (p)
            {
                x = (Real)p[0];
                y = (Real)p[1];
                z = (Real)p[2];
            }
            else
                x = y = z = 0;
        }

        Vec3(const Vec3& v) = default;

        Real* ptr()
        {
            return &x;
        }

        const Real* ptr() const
        {
            return &x;
        }

        bool operator==(const Vec3& v) const
        {
            return eq(x, v.x) && eq(y, v.y) && eq(z, v.z);
        }

        bool operator!=(const Vec3& v) const
        {
            return !eq(x, v.x) && !eq(y, v.y) && !eq(z, v.z);
        }

        Vec3 operator+(const Real v) const
        {
            return {x + v, y + v, z + v};
        }

        Vec3 operator+(const Vec3& v) const
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        Vec3& operator+=(const Real v)
        {
            x += v;
            y += v;
            z += v;
            return *this;
        }

        Vec3& operator+=(const Vec3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vec3 majorAxis() const
        {
            Vec3 result;
            majorAxis(result, *this);
            return result;
        }

        Vec3 abs() const
        {
            return {
                Abs(x),
                Abs(y),
                Abs(z),
            };
        }

        Vec3 operator-(const Real v) const
        {
            return {x - v, y - v, z - v};
        }

        Vec3 operator-(const Vec3& v) const
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        Vec3& operator-=(const Real v)
        {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }

        Vec3& operator-=(const Vec3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vec3 operator-() const
        {
            return {-x, -y, -z};
        }

        Vec3 operator*(const Real v) const
        {
            return {x * v, y * v, z * v};
        }

        Vec3 operator*(const Vec3& v) const
        {
            return {x * v.x, y * v.y, z * v.z};
        }

        Vec3& operator*=(const Real v)
        {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }

        Vec3& operator*=(const Vec3& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        Vec3 operator/(const Real v) const
        {
            const Real n = reciprocal(v);
            return {x * n, y * n, z * n};
        }

        Vec3 operator/(const Vec3& v) const
        {
            return {
                x * reciprocal(v.x),
                y * reciprocal(v.y),
                z * reciprocal(v.z),
            };
        }

        Vec3& operator/=(const Real v)
        {
            const Real n = reciprocal(v);
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }

        Vec3& operator/=(const Vec3& v)
        {
            x *= reciprocal(v.x);
            y *= reciprocal(v.y);
            z *= reciprocal(v.z);
            return *this;
        }

        Real length() const
        {
            return RtSqrt(length2());
        }

        Real length2() const
        {
            return x * x + y * y + z * z;
        }

        Real dot(const Vec3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        Real distance(const Vec3& v) const
        {
            return Vec3(x - v.x, y - v.y, z - v.z).length();
        }

        Real distance2(const Vec3& v) const
        {
            return Vec3(x - v.x, y - v.y, z - v.z).length2();
        }

        Vec3 cross(const Vec3& v) const
        {
            return {
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x,
            };
        }

        Real max3() const
        {
            return Max3(x, y, z);
        }

        void normalize()
        {
            if (const Real sl = length2(); sl > Epsilon)
            {
                const Real rs = RtRSqrt(sl);
                x *= rs;
                y *= rs;
                z *= rs;
            }
        }

        Vec3 normalized() const
        {
            if (const Real sl = length2();
                sl > Epsilon)
            {
                const Real rs = RtRSqrt(sl);
                return {x * rs, y * rs, z * rs};
            }

            return Zero;
        }

        static void majorAxis(Vec3& dest, const Vec3& src)
        {
            if (const Real m = Max3(src.x, src.y, src.z);
                eq(m, src.x))
                dest = UnitX;
            else if (eq(m, src.y))
                dest = UnitY;
            else
                dest = UnitZ;
        }

        void print() const;
    };

    inline Vec3 operator-(const Real r, const Vec3& l)
    {
        return {l.x - r, l.y - r, l.z - r};
    }

    inline Vec3 operator+(const Real r, const Vec3& l)
    {
        return {l.x + r, l.y + r, l.z + r};
    }

    inline Vec3 operator/(const Real r, const Vec3& l)
    {
        return {l.x / r, l.y / r, l.z / r};
    }

    inline Vec3 operator*(const Real r, const Vec3& l)
    {
        return {l.x * r, l.y * r, l.z * r};
    }
}  // namespace Rt2::Math
