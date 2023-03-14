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
#include "Math/Color.h"
#include <cstdint>
#include <cstdio>
#include "Math/Vec3.h"
#include "Utils/Definitions.h"

namespace Rt2::Math
{
#if RT_ENDIAN == RT_ENDIAN_BIG
    constexpr uint8_t Ir = 0;
    constexpr uint8_t Ig = 1;
    constexpr uint8_t Ib = 2;
    constexpr uint8_t Ia = 3;
#else
    constexpr uint8_t Ir = 3;
    constexpr uint8_t Ig = 2;
    constexpr uint8_t Ib = 1;
    constexpr uint8_t Ia = 0;
#endif

    const Color Color::White = Color(1, 1, 1, 1);
    const Color Color::Black = Color(0, 0, 0, 1);

    const Real ColorUtils::i100 = Real(1.0 / 100.0);
    const Real ColorUtils::i255 = Real(1.0 / 255.0);
    const Real ColorUtils::i360 = Real(1.0 / 360.0);

    // constants for rotating
    constexpr Real Ri1 = PiO3;
    constexpr Real Ri2 = 2 * PiO3;
    constexpr Real Ri3 = 3 * PiO3;
    constexpr Real Ri4 = 4 * PiO3;
    constexpr Real Ri5 = 5 * PiO3;

    Color::Color(const Vec3& v) :
        r(v.x),
        g(v.y),
        b(v.z),
        a(1)
    {
    }

    void Color::print() const
    {
        uint8_t vr, vg, vb, va;
        toBytes(vr, vg, vb, va);
        printf("#%02X%02X%02X%02X\n", vr, vg, vb, va);
    }

    void Color::toBytes(uint8_t& vr, uint8_t& vg, uint8_t& vb, uint8_t& va) const
    {
        vr = uint8_t(r * Real(255));
        vg = uint8_t(g * Real(255));
        vb = uint8_t(b * Real(255));
        va = uint8_t(a * Real(255));
    }

    void Color::toBytes(uint8_t& vr, uint8_t& vg, uint8_t& vb) const
    {
        vr = uint8_t(r * Real(255));
        vg = uint8_t(g * Real(255));
        vb = uint8_t(b * Real(255));
    }

    void ColorUtils::convert(uint32_t& dst, const Color& src)
    {
        ColorU color;
        color.b[3] = (unsigned char)(src.r * 255);
        color.b[2] = (unsigned char)(src.g * 255);
        color.b[1] = (unsigned char)(src.b * 255);
        color.b[0] = (unsigned char)(src.a * 255);
        dst        = color.i;
    }

    void ColorUtils::convert(Color& dst, const uint32_t& src)
    {
        ColorU color;
        color.i = src;
        dst.r   = (Real)color.b[Ir] * i255;
        dst.g   = (Real)color.b[Ig] * i255;
        dst.b   = (Real)color.b[Ib] * i255;
        dst.a   = (Real)color.b[Ia] * i255;
    }

    void ColorUtils::convert(uint32_t& dst, const uint8_t* src)
    {
        ColorU color{};
        color.b[Ir] = src[Ir];
        color.b[Ig] = src[Ig];
        color.b[Ib] = src[Ib];
        color.b[Ia] = src[Ia];
        dst         = color.i;
    }

    void ColorUtils::convert(Color& dst, const ColorHsv& src)
    {
        // https://en.wikipedia.org/w/index.php?title=HSL_and_HSV&oldid=941280606

        const Real H = src.h / Real(60.0);
        Real       c = src.v * src.s;
        if (c > Real(1.0))
            c = Real(1.0);

        const Real x = c * Abs(RtFmod(H, Real(2.0)));

        Real m = src.v - c;
        if (m > Real(1.0))
            m = Real(1.0);
        if (m < Real(0.0))
            m = Real(0.0);

        if (H >= Real(0.0) && H <= Ri1)
        {
            dst.r = c;
            dst.g = x;
            dst.b = 0;
        }
        else if (H >= Ri1 && H <= Ri2)
        {
            dst.r = x;
            dst.g = c;
            dst.b = 0;
        }
        else if (H >= Ri2 && H <= Ri3)
        {
            dst.r = 0;
            dst.g = c;
            dst.b = x;
        }
        else if (H >= Ri3 && H <= Ri4)
        {
            dst.r = 0;
            dst.g = x;
            dst.b = c;
        }
        else if (H >= Ri4 && H <= Ri5)
        {
            dst.r = x;
            dst.g = 0;
            dst.b = c;
        }
        else
        {
            dst.r = c;
            dst.g = 0;
            dst.b = x;
        }

        dst.r += m;
        dst.g += m;
        dst.b += m;

        dst.limit();
        dst.a = src.a;
    }

    void ColorUtils::convert(uint8_t*& dst, const Color& src)
    {
        dst[Ir] = (unsigned char)(src.r * 255.99f);
        dst[Ig] = (unsigned char)(src.g * 255.99f);
        dst[Ib] = (unsigned char)(src.b * 255.99f);
        dst[Ia] = (unsigned char)(src.a * 255.99f);
    }

    void ColorUtils::convert(Color& dst, const uint8_t* src)
    {
        dst.r = (Real)src[Ir] * i255;
        dst.g = (Real)src[Ig] * i255;
        dst.b = (Real)src[Ib] * i255;
        dst.a = (Real)src[Ia] * i255;
    }

    void ColorUtils::convert(uint8_t*& dst, const Real& src)
    {
        ColorUf uf;
        uf.f    = src;
        dst[Ir] = uf.b[Ir];
        dst[Ig] = uf.b[Ig];
        dst[Ib] = uf.b[Ib];
        dst[Ia] = uf.b[Ia];
    }

    void ColorUtils::convert(uint8_t*& dst, const uint32_t& src)
    {
        ColorU uf;
        uf.i    = src;
        dst[Ir] = uf.b[Ir];
        dst[Ig] = uf.b[Ig];
        dst[Ib] = uf.b[Ib];
        dst[Ia] = uf.b[Ia];
    }

    void ColorUtils::convert(Color& dst, const Real& src)
    {
        ColorUf uf;
        uf.f = src;
        dst.r = (Real)uf.b[Ir] * i255;
        dst.g = (Real)uf.b[Ig] * i255;
        dst.b = (Real)uf.b[Ib] * i255;
        dst.a = (Real)uf.b[Ia] * i255;
    }

    void ColorUtils::convert(ColorHsv& dst, const Color& src)
    {
        dst.v = Max3(src.r, src.g, src.b);
        dst.a = dst.v - Min3(src.r, src.g, src.b);

        if (dst.a <= Real(0.0))
            dst.h = Real(0.0);
        else if (eq(src.r, dst.v))
            dst.h = PiO3 * ((src.g - src.b) / dst.a);
        else if (eq(src.g, dst.v))
            dst.h = PiO3 * (Real(2) + (src.b - src.r) / dst.a);
        else
            dst.h = PiO3 * (Real(4) + (src.r - src.g) / dst.a);

        dst.h *= Dpr;
        dst.h = RtCeil(dst.h);
        dst.s = dst.v;
        if (dst.v > 0)
            dst.s = dst.a / dst.v;
        dst.a = src.a;
    }

}  // namespace Rt2::Math
