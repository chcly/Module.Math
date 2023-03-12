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

namespace Rt2::Math
{
    class Vector3;

    class ColorHsv;
    class Color;

    union ColorU
    {
        ColorU() :
            b{0, 0, 0, 0}
        {
        }

        uint8_t  b[4];
        uint32_t i;
    };

    union ColorUf
    {
        ColorUf() :
            b{0, 0, 0, 0}
        {
        }

        uint8_t b[4];
        float   f;
    };

    class ColorUtils
    {
    public:
        static const Scalar i100;
        static const Scalar i255;
        static const Scalar i360;

        static void convert(uint32_t& dst, const Color& src);
        static void convert(Color& dst, const uint32_t& src);
        static void convert(uint32_t& dst, const uint8_t* src);
        static void convert(Color& dst, const ColorHsv& src);
        static void convert(ColorHsv& dst, const Color& src);
        static void convert(uint8_t*& dst, const Color& src);
        static void convert(Color& dst, const uint8_t* src);
        static void convert(uint8_t*& dst, const Scalar& src);
        static void convert(uint8_t*& dst, const uint32_t& src);
        static void convert(Color& dst, const Scalar& src);
    };

    class ColorHsv
    {
    public:
        // h is 0, 360;
        // s, v, a [0,1]
        Scalar h{}, s{}, v{}, a{};

    public:
        ColorHsv() = default;

        ColorHsv(const uint32_t& hv,
                 const uint32_t& sv,
                 const uint32_t& vv,
                 const uint32_t& av = 100) :
            h(Scalar(hv) * ColorUtils::i360),
            s(Scalar(sv) * ColorUtils::i100),
            v(Scalar(vv) * ColorUtils::i100),
            a(Scalar(av) * ColorUtils::i100)
        {
        }

        explicit ColorHsv(const Color& rgb)
        {
            ColorUtils::convert(*this, rgb);
        }

        void setHue(const uint32_t& hue)
        {
            h = Scalar(hue);
        }

        void setSaturation(const uint32_t& sat)
        {
            s = Scalar(sat) * ColorUtils::i100;
        }

        void setValue(const uint32_t& val)
        {
            v = Scalar(val) * ColorUtils::i100;
        }

        void saturate(const Scalar offset)
        {
            s = Clamp(s + offset, Scalar(0.0), Scalar(1.0));
        }

        void lighten(const Scalar offset)
        {
            v = Clamp(v + offset, Scalar(0.0), Scalar(1.0));
        }

        void toInt(uint32_t& dH, uint32_t& dS, uint32_t& dV, uint32_t& dA) const
        {
            dH = uint32_t(h);
            dS = uint32_t(s * 100);
            dV = uint32_t(v * 100);
            dA = uint32_t(a * 100);
        }
    };

    class Color
    {
    public:
        Scalar r{}, g{}, b{}, a{};

        static const Color White;
        static const Color Black;

    public:
        Color()               = default;
        Color(const Color& o) = default;
        explicit Color(const Vector3& v);

        Color(const Scalar rv, const Scalar gv, const Scalar bv, const Scalar av = Scalar(1.0)) :
            r(rv),
            g(gv),
            b(bv),
            a(av)
        {
        }

        explicit Color(const uint32_t& color)
        {
            ColorUtils::convert(*this, color);
        }

        explicit operator uint32_t() const
        {
            uint32_t i;
            ColorUtils::convert(i, *this);
            return i;
        }

        void set(const Scalar rv, const Scalar gv, const Scalar bv, const Scalar av = Scalar(1.0))
        {
            r = rv;
            g = gv;
            b = bv;
            a = av;
        }

        void setMonochrome(const Scalar value, const Scalar alpha = Scalar(1.0))
        {
            r = value;
            g = value;
            b = value;
            a = alpha;
        }

        void setUb(const uint8_t rByte, const uint8_t gByte, const uint8_t bByte, const uint8_t aByte = 255)
        {
            r = Scalar(rByte) * ColorUtils::i255;
            g = Scalar(gByte) * ColorUtils::i255;
            b = Scalar(bByte) * ColorUtils::i255;
            a = Scalar(aByte) * ColorUtils::i255;
        }

        explicit Color(const ColorHsv& hsv)
        {
            ColorUtils::convert(*this, hsv);
        }

        void setHue(const uint32_t& h)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.h = Scalar(h);
            ColorUtils::convert(*this, hsv);
        }

        void setSaturation(const uint32_t& s)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.s = Scalar(s) * ColorUtils::i100;
            ColorUtils::convert(*this, hsv);
        }

        void setValue(const uint32_t& v)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.v = Scalar(v) * ColorUtils::i100;
            ColorUtils::convert(*this, hsv);
        }

        void saturate(Scalar fac)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.saturate(fac);
            ColorUtils::convert(*this, hsv);
        }

        void lighten(Scalar fac)
        {
            ColorHsv hsv;
            ColorUtils::convert(hsv, *this);
            hsv.lighten(fac);
            ColorUtils::convert(*this, hsv);
        }

        uint32_t toInt() const
        {
            uint32_t i;
            ColorUtils::convert(i, *this);
            return i;
        }

        void toInt(uint32_t& dest) const
        {
            ColorUtils::convert(dest, *this);
        }

        void limit()
        {
            r = Clamp(r, 0, 1);
            g = Clamp(g, 0, 1);
            b = Clamp(b, 0, 1);
            a = Clamp(a, 0, 1);
        }

        void limit(Color& d) const
        {
            const Scalar* srcPtr = ptr();
            Scalar*       dstPtr = d.ptr();

            for (int i = 0; i < 4; ++i)
            {
                if (srcPtr[i] < Scalar(0))
                    dstPtr[i] = 0;
                else if (srcPtr[i] > Scalar(1))
                    dstPtr[i] = 1;
                else
                    dstPtr[i] = srcPtr[i];
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
            return Color(
                Clamp(r, 0, 1),
                Clamp(g, 0, 1),
                Clamp(b, 0, 1),
                Clamp(a, 0, 1));
        }

        Color operator+(const Scalar offset) const
        {
            return Color(r + offset, g + offset, b + offset, a);
        }

        Color operator+(const Color& col) const
        {
            return Color(r + col.r, g + col.g, b + col.b, a);
        }

        Color& operator+=(Scalar val)
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

        friend Color operator+(const Scalar rc, const Color& l)
        {
            return l + rc;
        }

        Color operator-(const Scalar value) const
        {
            return Color(r - value, g - value, b - value, a);
        }

        Color operator-(const Color& col) const
        {
            return Color(r - col.r, g - col.g, b - col.b, a);
        }

        Color& operator-=(const Scalar value)
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

        friend Color operator-(const Scalar rc, const Color& l)
        {
            return l - rc;
        }

        Color operator*(const Scalar factor) const
        {
            return Color(r * factor, g * factor, b * factor, a);
        }

        Color operator*(const Color& v) const
        {
            return Color(r * v.r, g * v.g, b * v.b, a);
        }

        Color& operator*=(const Scalar factor)
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

        friend Color operator*(Scalar rc, const Color& l)
        {
            return l * rc;
        }

        Color operator/(Scalar v) const
        {
            if (IsZero(v))
                v = 1;

            return Color(r / v, g / v, b / v, a);
        }

        Color operator/(const Color& v) const
        {
            return Color(r / v.r, g / v.g, b / v.b, a);
        }

        Color& operator/=(Scalar v)
        {
            r /= v;
            g /= v;
            b /= v;
            return *this;
        }

        Color& operator/=(const Color& v)
        {
            r /= v.r;
            g /= v.g;
            b /= v.b;
            return *this;
        }

        friend Color operator/(Scalar rc, const Color& l)
        {
            return l / rc;
        }

        Color& operator=(const Color& o) = default;

        Scalar* ptr()
        {
            return &r;
        }

        const Scalar* ptr() const
        {
            return &r;
        }

        void toBytes(uint8_t& vr, uint8_t& vg, uint8_t& vb, uint8_t& va) const;

        void toBytes(uint8_t& vr, uint8_t& vg, uint8_t& vb) const;

        void print() const;

        Color& mix(const Color& rhs, const Scalar t)
        {
            const Scalar iT = 1 - t;

            r = iT * r + t * rhs.r;
            g = iT * g + t * rhs.g;
            b = iT * b + t * rhs.b;

            return *this;
        }
    };

}  // namespace Rt2::Math
