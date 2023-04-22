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
#include "Math/Rect.h"
#include "Math/Vec2.h"

namespace Rt2::Math
{
    class Box2d
    {
    public:
        Real x0{Infinity}, y0{Infinity};
        Real x1{Zero}, y1{Zero};

    public:
        Box2d() = default;
        Box2d(const Real& nx0, const Real& ny0, const Real& nx1, const Real& ny1) :
            x0(nx0),
            y0(ny0),
            x1(nx1),
            y1(ny1)
        {
        }

        void clear()
        {
            x0 = y0 = Infinity;
            x1 = y1 = Zero;
        }

        Vec2 minimum() const
        {
            return {x0, y0};
        }

        Vec2 maximum() const
        {
            return {x1, y1};
        }

        void merge(const Box2d& bb)
        {
            if (bb.x0 < x0)
                x0 = bb.x0;
            if (bb.y0 < y0)
                y0 = bb.y0;
            if (bb.x1 > x1)
                x1 = bb.x1;
            if (bb.y1 > y1)
                y1 = bb.y1;
        }

        void merge(const Real& a, const Real& b)
        {
            if (a < x0) x0 = a;
            if (a > x1) x1 = a;
            if (b < y0) y0 = b;
            if (b > y1) y1 = b;
        }

        void merge(const Rect& v)
        {
            Real l, t, r, b;
            v.corners(l, t, r, b);
            merge(Box2d{l, t, r, b});
        }

        void print() const;

        void zero()
        {
            x0 = x1 = Zero;
            y0 = y1 = Zero;
        }

        Real area() const
        {
            return (x1 - x0) * (y1 - y0);
        }

        Box2d operator*(const Vec2& v) const
        {
            return {
                x0 * v.x,
                y0 * v.y,
                x1 * v.x,
                y1 * v.y,
            };
        }
        Rect toRect() const
        {
            return {
                x0,
                y0,
                x1 - x0,
                y1 - y0,
            };
        }
    };

}  // namespace Rt2::Math
