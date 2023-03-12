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
#include "Utils/Allocator.h"

namespace Rt2::Math
{
    class Vector2
    {
    public:
        Scalar x{}, y{};

        static const Vector2 Unit;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 Zero;

    public:
        Vector2()                 = default;
        Vector2(const Vector2& v) = default;

        Vector2(const Scalar nx, const Scalar ny) :
            x(nx),
            y(ny)
        {
        }

        explicit Vector2(const Scalar* pointer)
        {
            RT_ASSERT(pointer)
            x = pointer[0];
            y = pointer[1];
        }

        Scalar* ptr()
        {
            return &x;
        }

        const Scalar* ptr() const
        {
            return &x;
        }

        Vector2& operator=(const Vector2& v) = default;

        bool operator==(const Vector2& v) const
        {
            return Eq(x, v.x) && Eq(y, v.y);
        }

        bool operator!=(const Vector2& v) const
        {
            return !Eq(x, v.x) && !Eq(y, v.y);
        }

        bool operator<(const Vector2& v) const
        {
            return x < v.x && y < v.y;
        }

        bool operator>(const Vector2& v) const
        {
            return x > v.x && y > v.y;
        }

        bool operator<=(const Vector2& v) const
        {
            return x <= v.x && y <= v.y;
        }

        bool operator>=(const Vector2& v) const
        {
            return x >= v.x && y >= v.y;
        }

        Vector2 operator+(Scalar v) const
        {
            return Vector2(x + v, y + v);
        }

        Vector2 operator+(const Vector2& v) const
        {
            return Vector2(x + v.x, y + v.y);
        }

        Vector2& operator+=(Scalar v)
        {
            x += v;
            y += v;
            return *this;
        }

        Vector2& operator+=(const Vector2& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        friend Vector2 operator+(const Scalar r, const Vector2& l)
        {
            return Vector2(l.x + r, l.y + r);
        }

        Vector2 operator-(const Scalar v) const
        {
            return Vector2(x - v, y - v);
        }

        Vector2 operator-(const Vector2& v) const
        {
            return Vector2(x - v.x, y - v.y);
        }

        Vector2& operator-=(const Scalar v)
        {
            x -= v;
            y -= v;
            return *this;
        }

        Vector2& operator-=(const Vector2& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2 operator-() const
        {
            return Vector2(-x, -y);
        }

        friend Vector2 operator-(const Scalar r, const Vector2& l)
        {
            return Vector2(l.x - r, l.y - r);
        }

        Vector2 operator*(const Scalar v) const
        {
            return Vector2(x * v, y * v);
        }

        Vector2 operator*(const Vector2& v) const
        {
            return Vector2(x * v.x, y * v.y);
        }

        Vector2& operator*=(Scalar v)
        {
            x *= v;
            y *= v;
            return *this;
        }

        Vector2& operator*=(const Vector2& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        friend Vector2 operator*(const Scalar r, const Vector2& l)
        {
            return Vector2(l.x * r, l.y * r);
        }

        Vector2 operator/(const Scalar v) const
        {
            const Scalar n = SafeReciprocal(v);
            return Vector2(x * n, y * n);
        }

        Vector2 operator/(const Vector2& v) const
        {
            return Vector2(x * SafeReciprocal(v.x), y * SafeReciprocal(v.y));
        }

        Vector2& operator/=(const Scalar v)
        {
            const Scalar n = SafeReciprocal(v);
            x *= n;
            y *= n;
            return *this;
        }

        Vector2& operator/=(const Vector2& v)
        {
            x *= SafeReciprocal(v.x);
            y *= SafeReciprocal(v.y);
            return *this;
        }

        Scalar length() const
        {
            return RtSqrt(length2());
        }

        Scalar length2() const
        {
            return dot(*this);
        }

        Scalar dot(const Vector2& v) const
        {
            return x * v.x + y * v.y;
        }

        Vector2 abs() const
        {
            return Vector2(Abs(x), Abs(y));
        }

        Scalar distance(const Vector2& v) const
        {
            return Vector2(x - v.x, y - v.y).length();
        }

        Scalar distance2(const Vector2& v) const
        {
            return Vector2(x - v.x, y - v.y).length2();
        }

        Vector2 perpendicular() const
        {
            return Vector2(-y, x);
        }

        bool isZero() const
        {
            return IsZero(x) && IsZero(y);
        }

        void normalize()
        {
            Scalar len = x * x + y * y;
            if (len > RT_EPSILON)
            {
                len = RtRSqrt(len);
                x *= len;
                y *= len;
            }
        }

        Vector2 normalized() const
        {
            Vector2 v(x, y);
            v.normalize();
            return v;
        }

        Scalar hx() const
        {
            return x * Half;
        }

        Scalar hy() const
        {
            return y * Half;
        }

        void print() const;
    };
}  // namespace Rt2::Math
