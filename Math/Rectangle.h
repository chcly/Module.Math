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
#include "Math/Vector2.h"

namespace Rt2::Math
{
    class Rectangle
    {
    public:
        Real x{}, y{};
        Real width{Epsilon}, height{Epsilon};

    public:
        Rectangle() = default;

        Rectangle(const Real xco,
                  const Real yco,
                  const Real widthValue,
                  const Real heightValue) :
            x(xco),
            y(yco),
            width(Max(widthValue, Epsilon)),
            height(Max(heightValue, Epsilon))
        {
        }

        explicit Rectangle(const Real* pointer)
        {
            if (pointer != nullptr)
            {
                x = pointer[0];
                y = pointer[1];

                width  = Max(pointer[2], Epsilon);
                height = Max(pointer[3], Epsilon);
            }
        }

        Rectangle& operator=(const Rectangle& o) = default;

        Vector2 size() const
        {
            return {width, height};
        }

        Vector2 position() const
        {
            return {x, y};
        }

        Real hw() const
        {
            return width * Real(.5);
        }

        Real hh() const
        {
            return height * Real(.5);
        }

        Real w() const
        {
            return width;
        }

        Real h() const
        {
            return height;
        }

        Real left() const
        {
            return x;
        }

        Real right() const
        {
            return x + width;
        }

        Real top() const
        {
            return y;
        }

        Real bottom() const
        {
            return y + height;
        }

        void setSize(const Vector2& s)
        {
            width  = s.x;
            height = s.y;
        }

        void setSize(const Real sx, const Real sy)
        {
            width  = sx;
            height = sy;
        }

        void setPosition(const Vector2& p)
        {
            x = p.x;
            y = p.y;
        }

        void setPosition(const Real px, const Real py)
        {
            x = px;
            y = py;
        }

        Vector2 leftTop() const
        {
            return {x, y};
        }

        Vector2 rightTop() const
        {
            return {x + width, y};
        }

        Vector2 leftBottom() const
        {
            return {x, y + height};
        }

        Vector2 rightBottom() const
        {
            return {x + width, y + height};
        }

        void center(Real& cx, Real& cy) const
        {
            cx = x + width * Half;
            cy = y + height * Half;
        }

        void corners(Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb) const
        {
            lt = leftTop();
            rt = rightTop();
            lb = leftBottom();
            rb = rightBottom();
        }

        void offset(const Vector2& v)
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
            x2 = x + width;
            y2 = y + height;
        }

        void setCorners(const Real& x1, const Real& y1, const Real& x2, const Real& y2)
        {
            x      = x1;
            y      = y1;
            width  = x2 - x1;
            height = y2 - y1;
        }

        Real getAspect() const
        {
            if (RtAbs(height) > Epsilon)
                return width / height;
            return 0;
        }

        Real cx() const
        {
            return x + width * Real(0.5);
        }

        Real cy() const
        {
            return y + height * Real(0.5);
        }

        Vector2 center() const
        {
            return {
                cx(),
                cy(),
            };
        }

        bool operator==(const Rectangle& rhs) const
        {
            return eq(x, rhs.x) &&
                   eq(y, rhs.y) &&
                   eq(width, rhs.width) &&
                   eq(height, rhs.height);
        }

        bool operator!=(const Rectangle& rhs) const
        {
            return !(eq(x, rhs.x) && eq(y, rhs.y) && eq(width, rhs.width) && eq(height, rhs.height));
        }

        void print() const;
    };

}  // namespace Rt2::Math
