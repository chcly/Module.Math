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
        Scalar x{}, y{};
        Scalar width{RT_EPSILON}, height{RT_EPSILON};

    public:
        Rectangle() = default;

        Rectangle(const Scalar xco,
                  const Scalar yco,
                  const Scalar widthValue,
                  const Scalar heightValue) :
            x(xco),
            y(yco),
            width(Max(widthValue, RT_EPSILON)),
            height(Max(heightValue, RT_EPSILON))
        {
        }

        explicit Rectangle(const Scalar* pointer)
        {
            if (pointer != nullptr)
            {
                x = pointer[0];
                y = pointer[1];

                width  = Max(pointer[2], RT_EPSILON);
                height = Max(pointer[3], RT_EPSILON);
            }
        }

        Rectangle& operator=(const Rectangle& o) = default;

        Vector2 getSize() const
        {
            return Vector2(width, height);
        }

        Vector2 getPosition() const
        {
            return Vector2(x, y);
        }

        Scalar hw() const
        {
            return width * Scalar(.5);
        }

        Scalar hh() const
        {
            return height * Scalar(.5);
        }

        Scalar getWidth() const
        {
            return width;
        }

        Scalar getHeight() const
        {
            return height;
        }

        Scalar getLeft() const
        {
            return x;
        }

        Scalar getRight() const
        {
            return x + width;
        }

        Scalar getTop() const
        {
            return y;
        }

        Scalar getBottom() const
        {
            return y + height;
        }

        void setSize(const Vector2& s)
        {
            width  = s.x;
            height = s.y;
        }

        void setSize(const Scalar sx, const Scalar sy)
        {
            width  = sx;
            height = sy;
        }

        void setPosition(const Vector2& p)
        {
            x = p.x;
            y = p.y;
        }

        void setPosition(Scalar px, Scalar py)
        {
            x = px;
            y = py;
        }

        Vector2 getLeftTop() const
        {
            return Vector2(x, y);
        }

        Vector2 getRightTop() const
        {
            return Vector2(x + width, y);
        }

        Vector2 getLeftBottom() const
        {
            return Vector2(x, y + height);
        }

        Vector2 getRightBottom() const
        {
            return Vector2(x + width, y + height);
        }

        Vector2 getCenter() const
        {
            return Vector2(x + width * Half,
                           y + height * Half);
        }

        void getCenter(Scalar& cx, Scalar& cy) const
        {
            cx = x + width * Half;
            cy = y + height * Half;
        }

        void getCorners(Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb) const
        {
            lt = getLeftTop();
            rt = getRightTop();
            lb = getLeftBottom();
            rb = getRightBottom();
        }

        void offset(const Vector2& v)
        {
            x += v.x;
            y += v.y;
        }

        void offset(Scalar vx, Scalar vy)
        {
            x += vx;
            y += vy;
        }

        void getCorners(Scalar& x1, Scalar& y1, Scalar& x2, Scalar& y2) const
        {
            x1 = x;
            y1 = y;
            x2 = x + width;
            y2 = y + height;
        }

        void setCorners(const Scalar& x1, const Scalar& y1, const Scalar& x2, const Scalar& y2)
        {
            x      = x1;
            y      = y1;
            width  = x2 - x1;
            height = y2 - y1;
        }

        Scalar getAspect() const
        {
            if (RtAbs(height) > RT_EPSILON)
                return width / height;
            return 0;
        }

        Scalar cx() const
        {
            return x + width * Scalar(0.5);
        }

        Scalar cy() const
        {
            return y + height * Scalar(0.5);
        }

        Vector2 center() const
        {
            return Vector2(cx(), cy());
        }

        bool operator==(const Rectangle& rhs) const
        {
            return Eq(x, rhs.x) &&
                   Eq(y, rhs.y) &&
                   Eq(width, rhs.width) &&
                   Eq(height, rhs.height);
        }

        bool operator!=(const Rectangle& rhs) const
        {
            return !(Eq(x, rhs.x) && Eq(y, rhs.y) && Eq(width, rhs.width) && Eq(height, rhs.height));
        }

        void print() const;
    };

}  // namespace Rt2::Math
