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
    class Vec2
    {
    public:
        Real x{}, y{};

    public:
        Vec2() = default;

        Vec2(const Vec2& v) = default;

        constexpr Vec2(const Real nx, const Real ny) :
            x(nx),
            y(ny)
        {
        }

        explicit Vec2(const Real* pointer)
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

        Vec2& operator=(const Vec2& v) = default;

        bool operator==(const Vec2& v) const
        {
            return eq(x, v.x) && eq(y, v.y);
        }

        bool operator!=(const Vec2& v) const
        {
            return !eq(x, v.x) && !eq(y, v.y);
        }

        bool operator<(const Vec2& v) const
        {
            return x < v.x && y < v.y;
        }

        bool operator>(const Vec2& v) const
        {
            return x > v.x && y > v.y;
        }

        bool operator<=(const Vec2& v) const
        {
            return x <= v.x && y <= v.y;
        }

        bool operator>=(const Vec2& v) const
        {
            return x >= v.x && y >= v.y;
        }

        Vec2 operator+(const Real v) const
        {
            return {x + v, y + v};
        }

        Vec2 operator+(const Vec2& v) const
        {
            return {x + v.x, y + v.y};
        }

        Vec2& operator+=(const Real v)
        {
            x += v;
            y += v;
            return *this;
        }

        Vec2& operator+=(const Vec2& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        friend Vec2 operator+(const Real r, const Vec2& l)
        {
            return {l.x + r, l.y + r};
        }

        Vec2 operator-(const Real v) const
        {
            return {x - v, y - v};
        }

        Vec2 operator-(const Vec2& v) const
        {
            return {x - v.x, y - v.y};
        }

        Vec2& operator-=(const Real v)
        {
            x -= v;
            y -= v;
            return *this;
        }

        Vec2& operator-=(const Vec2& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vec2 operator-() const
        {
            return {-x, -y};
        }

        friend Vec2 operator-(const Real r, const Vec2& l)
        {
            return {l.x - r, l.y - r};
        }

        Vec2 operator*(const Real v) const
        {
            return {x * v, y * v};
        }

        Vec2 operator*(const Vec2& v) const
        {
            return {x * v.x, y * v.y};
        }

        Vec2& operator*=(const Real v)
        {
            x *= v;
            y *= v;
            return *this;
        }

        Vec2& operator*=(const Vec2& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        friend Vec2 operator*(const Real r, const Vec2& l)
        {
            return {l.x * r, l.y * r};
        }

        Vec2 operator/(const Real v) const
        {
            const Real n = reciprocal(v);
            return {x * n, y * n};
        }

        Vec2 operator/(const Vec2& v) const
        {
            return {x * reciprocal(v.x), y * reciprocal(v.y)};
        }

        Vec2& operator/=(const Real v)
        {
            const Real n = reciprocal(v);
            x *= n;
            y *= n;
            return *this;
        }

        Vec2& operator/=(const Vec2& v)
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

        Real dot(const Vec2& v) const
        {
            return x * v.x + y * v.y;
        }

        Vec2 abs() const
        {
            return {Abs(x), Abs(y)};
        }

        Real distance(const Vec2& v) const
        {
            return Vec2(x - v.x, y - v.y).length();
        }

        Real distance2(const Vec2& v) const
        {
            return Vec2(x - v.x, y - v.y).length2();
        }

        Vec2 perpendicular() const
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

        Vec2 normalized() const
        {
            Vec2 v(x, y);
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

        Vec2 maxOf(const Vec2& v) const
        {
            return {Max(x, v.x), Max(y, v.y)};
        }

        Vec2 minOf(const Vec2& v) const
        {
            return {Min(x, v.x), Min(y, v.y)};
        }

        void print() const;
    };
}  // namespace Rt2::Math
