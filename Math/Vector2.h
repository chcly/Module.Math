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
    class Vector2
    {
    public:
        Real x{}, y{};

        static const Vector2 Unit;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 Zero;

    public:
        Vector2()                 = default;
        Vector2(const Vector2& v) = default;

        Vector2(const Real nx, const Real ny) :
            x(nx),
            y(ny)
        {
        }

        explicit Vector2(const Real* pointer)
        {
            x = pointer[0];
            y = pointer[1];
        }

        Real* ptr()
        {
            return &x;
        }

        const Real* ptr() const
        {
            return &x;
        }

        Vector2& operator=(const Vector2& v) = default;

        bool operator==(const Vector2& v) const
        {
            return eq(x, v.x) && eq(y, v.y);
        }

        bool operator!=(const Vector2& v) const
        {
            return !eq(x, v.x) && !eq(y, v.y);
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

        Vector2 operator+(const Real v) const
        {
            return {x + v, y + v};
        }

        Vector2 operator+(const Vector2& v) const
        {
            return {x + v.x, y + v.y};
        }

        Vector2& operator+=(const Real v)
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

        friend Vector2 operator+(const Real r, const Vector2& l)
        {
            return {l.x + r, l.y + r};
        }

        Vector2 operator-(const Real v) const
        {
            return {x - v, y - v};
        }

        Vector2 operator-(const Vector2& v) const
        {
            return {x - v.x, y - v.y};
        }

        Vector2& operator-=(const Real v)
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
            return {-x, -y};
        }

        friend Vector2 operator-(const Real r, const Vector2& l)
        {
            return {l.x - r, l.y - r};
        }

        Vector2 operator*(const Real v) const
        {
            return {x * v, y * v};
        }

        Vector2 operator*(const Vector2& v) const
        {
            return {x * v.x, y * v.y};
        }

        Vector2& operator*=(Real v)
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

        friend Vector2 operator*(const Real r, const Vector2& l)
        {
            return {l.x * r, l.y * r};
        }

        Vector2 operator/(const Real v) const
        {
            const Real n = reciprocal(v);
            return {x * n, y * n};
        }

        Vector2 operator/(const Vector2& v) const
        {
            return {x * reciprocal(v.x), y * reciprocal(v.y)};
        }

        Vector2& operator/=(const Real v)
        {
            const Real n = reciprocal(v);
            x *= n;
            y *= n;
            return *this;
        }

        Vector2& operator/=(const Vector2& v)
        {
            x *= reciprocal(v.x);
            y *= reciprocal(v.y);
            return *this;
        }

        Real length() const
        {
            return RtSqrt(length2());
        }

        Real length2() const
        {
            return dot(*this);
        }

        Real dot(const Vector2& v) const
        {
            return x * v.x + y * v.y;
        }

        Vector2 abs() const
        {
            return {Abs(x), Abs(y)};
        }

        Real distance(const Vector2& v) const
        {
            return Vector2(x - v.x, y - v.y).length();
        }

        Real distance2(const Vector2& v) const
        {
            return Vector2(x - v.x, y - v.y).length2();
        }

        Vector2 perpendicular() const
        {
            return {-y, x};
        }

        void normalize()
        {
            if (Real len = x * x + y * y;
                len > Epsilon)
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

        Real hx() const
        {
            return x * Half;
        }

        Real hy() const
        {
            return y * Half;
        }

        void print() const;
    };
}  // namespace Rt2::Math
