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

    class Vector3
    {
    public:
        Real x{}, y{}, z{};

        static const Vector3 Unit;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;
        static const Vector3 Zero;

    public:
        Vector3() = default;

        explicit Vector3(const Color& col);

        Vector3(const Real nx, const Real ny, const Real nz) :
            x(nx),
            y(ny),
            z(nz)
        {
        }

        explicit Vector3(const float* pointer)
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

        explicit Vector3(const double* p)
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

        Vector3(const Vector3& v) = default;

        Real* ptr()
        {
            return &x;
        }

        const Real* ptr() const
        {
            return &x;
        }

        bool operator==(const Vector3& v) const
        {
            return eq(x, v.x) && eq(y, v.y) && eq(z, v.z);
        }

        bool operator!=(const Vector3& v) const
        {
            return !eq(x, v.x) && !eq(y, v.y) && !eq(z, v.z);
        }

        Vector3 operator+(const Real v) const
        {
            return {x + v, y + v, z + v};
        }

        Vector3 operator+(const Vector3& v) const
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        Vector3& operator+=(const Real v)
        {
            x += v;
            y += v;
            z += v;
            return *this;
        }

        Vector3& operator+=(const Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3 majorAxis() const
        {
            Vector3 result;
            majorAxis(result, *this);
            return result;
        }

        Vector3 abs() const
        {
            return {
                Abs(x),
                Abs(y),
                Abs(z),
            };
        }

        Vector3 operator-(const Real v) const
        {
            return {x - v, y - v, z - v};
        }

        Vector3 operator-(const Vector3& v) const
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        Vector3& operator-=(const Real v)
        {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }

        Vector3& operator-=(const Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vector3 operator-() const
        {
            return {-x, -y, -z};
        }

        Vector3 operator*(const Real v) const
        {
            return {x * v, y * v, z * v};
        }

        Vector3 operator*(const Vector3& v) const
        {
            return {x * v.x, y * v.y, z * v.z};
        }

        Vector3& operator*=(const Real v)
        {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }

        Vector3& operator*=(const Vector3& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        Vector3 operator/(const Real v) const
        {
            const Real n = reciprocal(v);
            return {x * n, y * n, z * n};
        }

        Vector3 operator/(const Vector3& v) const
        {
            return {
                x * reciprocal(v.x),
                y * reciprocal(v.y),
                z * reciprocal(v.z),
            };
        }

        Vector3& operator/=(const Real v)
        {
            const Real n = reciprocal(v);
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }

        Vector3& operator/=(const Vector3& v)
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

        Real dot(const Vector3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        Real distance(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z).length();
        }

        Real distance2(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z).length2();
        }

        Vector3 cross(const Vector3& v) const
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

        Vector3 normalized() const
        {
            if (const Real sl = length2();
                sl > Epsilon)
            {
                const Real rs = RtRSqrt(sl);
                return {x * rs, y * rs, z * rs};
            }

            return Zero;
        }

        static void majorAxis(Vector3& dest, const Vector3& src)
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

    inline Vector3 operator-(const Real r, const Vector3& l)
    {
        return {l.x - r, l.y - r, l.z - r};
    }

    inline Vector3 operator+(const Real r, const Vector3& l)
    {
        return {l.x + r, l.y + r, l.z + r};
    }

    inline Vector3 operator/(const Real r, const Vector3& l)
    {
        return {l.x / r, l.y / r, l.z / r};
    }

    inline Vector3 operator*(const Real r, const Vector3& l)
    {
        return {l.x * r, l.y * r, l.z * r};
    }
}  // namespace Rt2::Math
