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
        Scalar x{}, y{}, z{};

        static const Vector3 Unit;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;
        static const Vector3 Zero;

    public:
        Vector3() = default;

        explicit Vector3(const Color& col);

        Vector3(Scalar nx, Scalar ny, Scalar nz) :
            x(nx),
            y(ny),
            z(nz)
        {
        }

        explicit Vector3(const float* pointer)
        {
            if (pointer)
            {
                x = (Scalar)pointer[0];
                y = (Scalar)pointer[1];
                z = (Scalar)pointer[2];
            }
            else
                x = y = z = 0;
        }

        explicit Vector3(const double* p)
        {
            if (p)
            {
                x = (Scalar)p[0];
                y = (Scalar)p[1];
                z = (Scalar)p[2];
            }
            else
                x = y = z = 0;
        }

        Vector3(const Vector3& v) = default;

        Scalar* ptr()
        {
            return &x;
        }

        const Scalar* ptr() const
        {
            return &x;
        }

        bool operator==(const Vector3& v) const
        {
            return Eq(x, v.x) && Eq(y, v.y) && Eq(z, v.z);
        }

        bool operator!=(const Vector3& v) const
        {
            return !Eq(x, v.x) && !Eq(y, v.y) && !Eq(z, v.z);
        }

        Vector3 operator+(Scalar v) const
        {
            return Vector3(x + v, y + v, z + v);
        }

        Vector3 operator+(const Vector3& v) const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3& operator+=(Scalar v)
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

        static void majorAxis(Vector3& dest, const Vector3& src)
        {
            const Scalar m = Max3(src.x, src.y, src.z);

            if (Eq(m, src.x))
                dest = UnitX;
            else if (Eq(m, src.y))
                dest = UnitY;
            else
                dest = UnitZ;
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

        Vector3 operator-(Scalar v) const
        {
            return Vector3(x - v, y - v, z - v);
        }

        Vector3 operator-(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3& operator-=(Scalar v)
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
            return Vector3(-x, -y, -z);
        }

        Vector3 operator*(Scalar v) const
        {
            return Vector3(x * v, y * v, z * v);
        }

        Vector3 operator*(const Vector3& v) const
        {
            return Vector3(x * v.x, y * v.y, z * v.z);
        }

        Vector3& operator*=(Scalar v)
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

        Vector3 operator/(Scalar v) const
        {
            const Scalar n = SafeReciprocal(v);
            return Vector3(x * n, y * n, z * n);
        }

        Vector3 operator/(const Vector3& v) const
        {
            return Vector3(x * SafeReciprocal(v.x),
                           y * SafeReciprocal(v.y),
                           z * SafeReciprocal(v.z));
        }

        Vector3& operator/=(Scalar v)
        {
            const Scalar n = SafeReciprocal(v);
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }

        Vector3& operator/=(const Vector3& v)
        {
            x *= SafeReciprocal(v.x);
            y *= SafeReciprocal(v.y);
            z *= SafeReciprocal(v.z);
            return *this;
        }

        Scalar length() const
        {
            return RtSqrt(length2());
        }

        Scalar length2() const
        {
            return x * x + y * y + z * z;
        }

        Scalar dot(const Vector3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        Scalar distance(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z).length();
        }

        Scalar distance2(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z).length2();
        }

        Vector3 cross(const Vector3& v) const
        {
            return Vector3(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x);
        }

        Scalar max3() const
        {
            return Max3(x, y, z);
        }

        void normalize()
        {
            const Scalar sl = length2();

            if (sl > RT_EPSILON)
            {
                const Scalar rs = RtRSqrt(sl);
                x *= rs;
                y *= rs;
                z *= rs;
            }
        }

        Vector3 normalized() const
        {
            const Scalar sl = length2();
            if (sl > RT_EPSILON)
            {
                const Scalar rs = RtRSqrt(sl);
                return {x * rs, y * rs, z * rs};
            }

            return Zero;
        }

        void print() const;
    };

    inline Vector3 operator-(Scalar r, const Vector3& l)
    {
        return Vector3(l.x - r, l.y - r, l.z - r);
    }

    inline Vector3 operator+(Scalar r, const Vector3& l)
    {
        return Vector3(l.x + r, l.y + r, l.z + r);
    }

    inline Vector3 operator/(Scalar r, const Vector3& l)
    {
        return Vector3(l.x / r, l.y / r, l.z / r);
    }

    inline Vector3 operator*(Scalar r, const Vector3& l)
    {
        return Vector3(l.x * r, l.y * r, l.z * r);
    }
}  // namespace Rt2::Math
