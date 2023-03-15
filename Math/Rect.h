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
#include "Math/Vec2.h"

namespace Rt2::Math
{
    class Rect
    {
    public:
        Real x{}, y{};
        Real w{Epsilon}, h{Epsilon};

    public:
        Rect() = default;

        Rect(const Real xco,
             const Real yco,
             const Real widthValue,
             const Real heightValue) :
            x(xco),
            y(yco),
            w(Max(widthValue, Epsilon)),
            h(Max(heightValue, Epsilon))
        {
        }

        explicit Rect(const Real* pointer)
        {
            if (pointer != nullptr)
            {
                x = pointer[0];
                y = pointer[1];

                w = Max(pointer[2], Epsilon);
                h = Max(pointer[3], Epsilon);
            }
        }

        Rect& operator=(const Rect& o) = default;

        Vec2 size() const
        {
            return {w, h};
        }

        Vec2 position() const
        {
            return {x, y};
        }

        Real hw() const
        {
            return w * Real(.5);
        }

        Real hh() const
        {
            return h * Real(.5);
        }

        Real width() const
        {
            return this->w;
        }

        Real height() const
        {
            return h;
        }

        Real left() const
        {
            return x;
        }

        Real right() const
        {
            return x + w;
        }

        Real top() const
        {
            return y;
        }

        Real bottom() const
        {
            return y + h;
        }

        void setSize(const Vec2& s)
        {
            w = s.x;
            h = s.y;
        }

        void setSize(const Real sx, const Real sy)
        {
            w = sx;
            h = sy;
        }

        void setPosition(const Vec2& p)
        {
            x = p.x;
            y = p.y;
        }

        void setPosition(const Real px, const Real py)
        {
            x = px;
            y = py;
        }

        Vec2 leftTop() const
        {
            return {x, y};
        }

        Vec2 rightTop() const
        {
            return {x + w, y};
        }

        Vec2 leftBottom() const
        {
            return {x, y + h};
        }

        Vec2 rightBottom() const
        {
            return {x + w, y + h};
        }

        void center(Real& cx, Real& cy) const
        {
            cx = x + w * Half;
            cy = y + h * Half;
        }

        void corners(Vec2& lt, Vec2& rt, Vec2& lb, Vec2& rb) const
        {
            lt = leftTop();
            rt = rightTop();
            lb = leftBottom();
            rb = rightBottom();
        }

        void offset(const Vec2& v)
        {
            x += v.x;
            y += v.y;
        }

        void offset(const Real vx, const Real vy)
        {
            x += vx;
            y += vy;
        }

        void corners(Real& x1, Real& y1, Real& x2, Real& y2) const
        {
            x1 = x;
            y1 = y;
            x2 = x + w;
            y2 = y + h;
        }

        void setCorners(const Real& x1, const Real& y1, const Real& x2, const Real& y2)
        {
            x = x1;
            y = y1;
            w = x2 - x1;
            h = y2 - y1;
        }

        Real getAspect() const
        {
            if (RtAbs(h) > Epsilon)
                return w / h;
            return 0;
        }

        Real cx() const
        {
            return x + w * Real(0.5);
        }

        Real cy() const
        {
            return y + h * Real(0.5);
        }

        Vec2 center() const
        {
            return {
                cx(),
                cy(),
            };
        }

        bool operator==(const Rect& rhs) const
        {
            return eq(x, rhs.x) &&
                   eq(y, rhs.y) &&
                   eq(w, rhs.w) &&
                   eq(h, rhs.h);
        }

        bool operator!=(const Rect& rhs) const
        {
            return !(eq(x, rhs.x) && eq(y, rhs.y) && eq(w, rhs.w) && eq(h, rhs.h));
        }

        void print() const;
    };

}  // namespace Rt2::Math
