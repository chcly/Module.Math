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

#include <cstdint>
#include "Math/Math.h"
#include "Utils/Definitions.h"

namespace Rt2::Math
{
    class Vec3;

    class ColorHsv;
    class Color;

    union ColorU
    {
        ColorU() :
            b{0, 0, 0, 0}
        {
        }

        U8  b[4];
        U32 i;
    };

    union ColorUf
    {
        ColorUf() :
            b{0, 0, 0, 0}
        {
        }

        U8    b[4];
        float f;
    };

    class ColorUtils
    {
    public:
        static const Real i100;
        static const Real i255;
        static const Real i360;

        static void convert(U32& dst, const Color& src);
        static void convert(Color& dst, const U32& src);
        static void convert(U32& dst, const U8* src);
        static void convert(Color& dst, const ColorHsv& src);
        static void convert(ColorHsv& dst, const Color& src);
        static void convert(U8*& dst, const Color& src);
        static void convert(Color& dst, const U8* src);
        static void convert(U8*& dst, const Real& src);
        static void convert(U8*& dst, const U32& src);
        static void convert(Color& dst, const Real& src);
    };

    class ColorHsv
    {
    public:
        // h is 0, 360;
        // s, v, a [0,1]
        Real h{}, s{}, v{}, a{};

    public:
        ColorHsv() = default;

        ColorHsv(const U32& hv,
                 const U32& sv,
                 const U32& vv,
                 const U32& av = 100) :
            h(Real(hv) * ColorUtils::i360),
            s(Real(sv) * ColorUtils::i100),
            v(Real(vv) * ColorUtils::i100),
            a(Real(av) * ColorUtils::i100)
        {
        }

        explicit ColorHsv(const Color& rgb)
        {
            ColorUtils::convert(*this, rgb);
        }

        void setHue(const U32& hue)
        {
            h = Real(hue);
        }

        void setSaturation(const U32& sat)
        {
            s = Real(sat) * ColorUtils::i100;
        }

        void setValue(const U32& val)
        {
            v = Real(val) * ColorUtils::i100;
        }

        void saturate(const Real offset)
        {
            s = clamp(s + offset, Real(0.0), Real(1.0));
        }

        void lighten(const Real offset)
        {
            v = clamp(v + offset, Real(0.0), Real(1.0));
        }

        void toInt(U32& dH, U32& dS, U32& dV, U32& dA) const
        {
            dH = U32(h);
            dS = U32(s * 100);
            dV = U32(v * 100);
            dA = U32(a * 100);
        }
    };

    class Color
    {
    public:
        Real r{}, g{}, b{}, a{};

        static const Color White;
        static const Color Black;

    public:
        Color()               = default;
        Color(const Color& o) = default;
        explicit Color(const Vec3& v);

        Color(const Real rv,
              const Real gv,
              const Real bv,
              const Real av = Real(1.0)) :
            r(rv),
            g(gv),
            b(bv),
            a(av)
        {
        }

        explicit Color(const U32& color)
        {
            ColorUtils::convert(*this, color);
        }

        explicit operator U32() const
        {
            U32 i;
            ColorUtils::convert(i, *this);
            return i;
        }

        void set(const Real rv,
                 const Real gv,
                 const Real bv,
                 const Real av = Real(1.0))
        {
            r = rv;
            g = gv;
            b = bv;
            a = av;
        }

        void setMonochrome(const Real value,
                           const Real alpha = Real(1.0))
        {
            r = value;
            g = value;
            b = value;
            a = alpha;
        }

        void setUb(const U8 rByte,
                   const U8 gByte,
                   const U8 bByte,
                   const U8 aByte = 255)
        {
            r = Real(rByte) * ColorUtils::i255;
            g = Real(gByte) * ColorUtils::i255;
            b = Real(bByte) * ColorUtils::i255;
            a = Real(aByte) * ColorUtils::i255;
        }

        explicit Color(const ColorHsv& hsv)
        {
            ColorUtils::convert(*this, hsv);
        }

        void setHue(const U32& h)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.h = Real(h);
            ColorUtils::convert(*this, hsv);
        }

        void setSaturation(const U32& s)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.s = Real(s) * ColorUtils::i100;
            ColorUtils::convert(*this, hsv);
        }

        void setValue(const U32& v)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.v = Real(v) * ColorUtils::i100;
            ColorUtils::convert(*this, hsv);
        }

        void saturate(const Real fac)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.saturate(fac);
            ColorUtils::convert(*this, hsv);
        }

        void lighten(const Real fac)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.lighten(fac);
            ColorUtils::convert(*this, hsv);
        }

        U32 toInt() const
        {
            U32 i;
            ColorUtils::convert(i, *this);
            return i;
        }

        void toInt(U32& dest) const
        {
            ColorUtils::convert(dest, *this);
        }

        void limit()
        {
            r = clamp(r, 0, 1);
            g = clamp(g, 0, 1);
            b = clamp(b, 0, 1);
            a = clamp(a, 0, 1);
        }

        void limit(Color& dest) const
        {
            const Real* s = ptr();
            Real*       d = dest.ptr();

            for (int i = 0; i < 4; ++i)
            {
                if (s[i] < Real(0))
                    d[i] = 0;
                else if (s[i] > Real(1))
                    d[i] = 1;
                else
                    d[i] = s[i];
            }
        }

        void invertRgb()
        {
            r = 1 - r;
            g = 1 - g;
            b = 1 - b;
        }

        Color limit() const
        {
            return {
                clamp(r, 0, 1),
                clamp(g, 0, 1),
                clamp(b, 0, 1),
                clamp(a, 0, 1),
            };
        }

        Color operator+(const Real offset) const
        {
            return {r + offset, g + offset, b + offset, a};
        }

        Color operator+(const Color& col) const
        {
            return {r + col.r, g + col.g, b + col.b, a};
        }

        Color& operator+=(const Real val)
        {
            r += val;
            g += val;
            b += val;
            limit();
            return *this;
        }

        Color& operator+=(const Color& v)
        {
            r += v.r;
            g += v.g;
            b += v.b;
            limit();
            return *this;
        }

        friend Color operator+(const Real rc, const Color& l)
        {
            return l + rc;
        }

        Color operator-(const Real value) const
        {
            return {
                r - value,
                g - value,
                b - value,
                a,
            };
        }

        Color operator-(const Color& col) const
        {
            return {
                r - col.r,
                g - col.g,
                b - col.b,
                a,
            };
        }

        Color& operator-=(const Real value)
        {
            r -= value;
            g -= value;
            b -= value;
            limit();
            return *this;
        }

        Color& operator-=(const Color& col)
        {
            r -= col.r;
            g -= col.g;
            b -= col.b;
            limit();
            return *this;
        }

        friend Color operator-(const Real rc, const Color& l)
        {
            return l - rc;
        }

        Color operator*(const Real factor) const
        {
            return {
                r * factor,
                g * factor,
                b * factor,
                a,
            };
        }

        Color operator*(const Color& v) const
        {
            return {
                r * v.r,
                g * v.g,
                b * v.b,
                a,
            };
        }

        Color& operator*=(const Real factor)
        {
            r *= factor;
            g *= factor;
            b *= factor;
            limit();
            return *this;
        }

        Color& operator*=(const Color& col)
        {
            r *= col.r;
            g *= col.g;
            b *= col.b;
            limit();
            return *this;
        }

        friend Color operator*(const Real rc, const Color& l)
        {
            return l * rc;
        }

        Color operator/(Real v) const
        {
            if (isZero(v))
                v = Epsilon;
            return {r / v, g / v, b / v, a};
        }

        Color operator/(const Color& v) const
        {
            return {r / v.r, g / v.g, b / v.b, a};
        }

        Color& operator/=(const Real v)
        {
            return operator*=(reciprocal(v));
        }

        Color& operator/=(const Color& v)
        {
            r /= v.r;
            g /= v.g;
            b /= v.b;
            return *this;
        }

        friend Color operator/(const Real rc, const Color& l)
        {
            return l / rc;
        }

        Color& operator=(const Color& o) = default;

        Real* ptr();

        const Real* ptr() const;

        void toBytes(U8& vr, U8& vg, U8& vb, U8& va) const;

        void toBytes(U8& vr, U8& vg, U8& vb) const;

        void print() const;

        Color& mix(const Color& rhs, const Real t)
        {
            const Real iT = One - t;

            r = iT * r + t * rhs.r;
            g = iT * g + t * rhs.g;
            b = iT * b + t * rhs.b;
            return *this;
        }
    };

    inline Real* Color::ptr()
    {
        return &r;
    }

    inline const Real* Color::ptr() const
    {
        return &r;
    }

}  // namespace Rt2::Math
