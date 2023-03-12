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
    class Vector4
    {
    public:
        Scalar x{}, y{}, z{}, w{};

        static const Vector4 Unit;
        static const Vector4 Zero;

    public:
        Vector4()                 = default;
        Vector4(const Vector4& v) = default;

        Vector4(const Scalar& nx,
                const Scalar& ny,
                const Scalar& nz,
                const Scalar& nw) :
            x(nx),
            y(ny),
            z(nz),
            w(nw)
        {
        }

        explicit Vector4(const Scalar* p)
        {
            if (p != nullptr)
            {
                x = p[0];
                y = p[1];
                z = p[2];
                w = p[3];
            }
        }

        Scalar* ptr()
        {
            return &x;
        }

        const Scalar* ptr() const
        {
            return &x;
        }

        inline bool operator==(const Vector4& v) const;

        inline bool operator!=(const Vector4& v) const;

        void print() const;
    };

    inline bool Vector4::operator==(const Vector4& v) const
    {
        return Eq(x, v.x) && Eq(y, v.y) && Eq(z, v.z) && Eq(w, v.w);
    }

    inline bool Vector4::operator!=(const Vector4& v) const
    {
        return !Eq(x, v.x) && !Eq(y, v.y) && !Eq(z, v.z) && !Eq(w, v.w);
    }

}  // namespace Rt2::Math
