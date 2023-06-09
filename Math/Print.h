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

#include "Math/Scalar.h"
#include "Utils/StackStream.h"
#include "Utils/StreamConverters/Set.h"

namespace Rt2::Math
{
    constexpr uint8_t OpenBracket      = '[';
    constexpr uint8_t CloseBracket     = ']';
    constexpr uint8_t BracketSeparator = ',';

#ifdef Math_USE_DOUBLE
    constexpr size_t RealPrecision = 0;  // Not accurate. This is just to limit default printing.
    constexpr size_t RealWidth     = 2 * DBL_DIG;

    using SetR = TPrintSet<
        double,
        OpenBracket,
        BracketSeparator,
        CloseBracket,
        RealPrecision,
        RealWidth,
        0>;
#else
    constexpr size_t RealPrecision = FLT_DIG;  // Not accurate. This is just to limit default printing.
    constexpr size_t RealWidth     = 2 * RealPrecision;

    using SetR = TPrintSet<
        float,
        OpenBracket,
        BracketSeparator,
        CloseBracket,
        RealPrecision,
        RealWidth,
        1>;
#endif

    class Box2d;
    class Vec2;
    class Vec4;
    class Vec3;
    class Rect;
    class Mat3;
    class Quat;
    class Mat4;

    class Printer
    {
    public:
        static U8 precision;
        static U8 width;

    private:
        static OStream* _output;

    public:
        static void bind(OStream* stream);

        static void setPrecision(U8 p);

        static void print(const Vec2& v);
        static void print(const Vec3& v);
        static void print(const Vec4& v);
        static void print(const Quat& v);
        static void print(const Mat3& v);
        static void print(const Mat4& v);
        static void print(const Box2d& v);
        static void print(const Rect& v);
    };

}  // namespace Rt2::Math
