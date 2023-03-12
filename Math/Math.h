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

#ifdef RT_DOUBLE
#define RtSqrt (Rt2::Math::Scalar) sqrt
#define RtInvSqrt (Rt2::Math::Scalar)1.0 / (Rt2::Math::Scalar)sqrt
#define RtFloor (Rt2::Math::Scalar) floor
#define RtCeil (Rt2::Math::Scalar) ceil
#define RtSin (Rt2::Math::Scalar) sin
#define RtCos (Rt2::Math::Scalar) cos
#define RtTan (Rt2::Math::Scalar) tan
#define RtExp (Rt2::Math::Scalar) exp
#define RtLog (Rt2::Math::Scalar) log
#define RtPow (Rt2::Math::Scalar) pow
#define RtMod (Rt2::Math::Scalar) fmod
#define RtASin (Rt2::Math::Scalar) asin
#define RtACos (Rt2::Math::Scalar) acos
#define RtATan (Rt2::Math::Scalar) atan
#define RtATan2 (Rt2::Math::Scalar) atan2
#define RtFmod (Rt2::Math::Scalar) fmod
#define RtAbs (Rt2::Math::Scalar) abs
#else
#define RtSqrt (Rt2::Math::Scalar) sqrtf
#define RtRSqrt(x) (Rt2::Math::Scalar)(powf((x), -0.5f))
#define RtFloor (Rt2::Math::Scalar) floorf
#define RtCeil (Rt2::Math::Scalar) ceilf
#define RtSin (Rt2::Math::Scalar) sinf
#define RtCos (Rt2::Math::Scalar) cosf
#define RtTan (Rt2::Math::Scalar) tanf
#define RtExp (Rt2::Math::Scalar) expf
#define RtLog (Rt2::Math::Scalar) logf
#define RtPow (Rt2::Math::Scalar) powf
#define RtMod (Rt2::Math::Scalar) fmodf
#define RtASin (Rt2::Math::Scalar) asinf
#define RtACos (Rt2::Math::Scalar) acosf
#define RtATan (Rt2::Math::Scalar) atanf
#define RtATan2 (Rt2::Math::Scalar) atan2f
#define RtFmod (Rt2::Math::Scalar) fmodf
#define RtAbs (Rt2::Math::Scalar) fabs
#endif

namespace Rt2::Math
{
    inline Scalar Max(const Scalar& a, const Scalar& b)
    {
        return a > b ? a : b;
    }

    inline Scalar Min(const Scalar& a, const Scalar& b)
    {
        return a < b ? a : b;
    }

    inline Scalar Max3(const Scalar& a, const Scalar& b, const Scalar& c)
    {
        const Scalar d = a > b ? a : b;
        return c > d ? c : d;
    }

    inline Scalar Min3(const Scalar& a, const Scalar& b, const Scalar& c)
    {
        const Scalar d = a < b ? a : b;
        return c < d ? c : d;
    }

    inline Scalar Abs(const Scalar& v)
    {
        return v < 0 ? -v : v;
    }

    inline Scalar Squ(const Scalar& v)
    {
        return v * v;
    }

    inline Scalar Sign(const Scalar& v)
    {
        return v > 0 ? Scalar(1.) : Scalar(-1.);
    }

    inline Scalar IsInf(const Scalar v)
    {
        return Abs(v) >= RT_INFINITY;
    }

    inline Scalar IsNan(const Scalar v)
    {
        return std::isnan(v);
    }

    inline Scalar DecimalPart(const Scalar v)
    {
        return v - RtFloor(v);
    }

    inline void SplitScalar(const Scalar v, Scalar& whole, Scalar& decimal)
    {
        whole   = RtFloor(v);
        decimal = v - whole;
    }

    inline bool IsZero(const Scalar v)
    {
        return Abs(v) < RT_EPSILON;
    }

    inline bool IsZero(Scalar v, Scalar tol)
    {
        return Abs(v) < tol;
    }

    inline Scalar SafeReciprocal(const Scalar& v)
    {
        if (Abs(v) > RT_EPSILON)
            return 1.f / v;
        return 1.f / RT_EPSILON;
    }

    inline bool Eq(Scalar x, Scalar y)
    {
        return Abs(x - y) < RT_EPSILON;
    }

    inline Scalar Clamp(const Scalar& v, const Scalar& vMin, const Scalar& vMax)
    {
        return v < vMin ? vMin : v > vMax ? vMax
                                          : v;
    }

    inline bool NEq(Scalar x, Scalar y)
    {
        return !Eq(x, y);
    }

    inline bool EqTol(const Scalar& x, const Scalar& y, const Scalar& tol)
    {
        return Abs(x - y) < tol;
    }

    constexpr Scalar Pi               = 3.1415926535897932384626433832795f;
    constexpr Scalar Pi4              = Scalar(4.0) * Pi;
    constexpr Scalar Pi2              = Scalar(2.0) * Pi;
    constexpr Scalar PiH              = Scalar(0.5) * Pi;          // 90
    constexpr Scalar PiO3             = Scalar(Pi) / Scalar(3.0);  // 60
    constexpr Scalar PiO4             = Scalar(Pi) / Scalar(4.0);  // 45
    constexpr Scalar PiO6             = Scalar(Pi) / Scalar(6.0);  // 30
    constexpr Scalar DegreesPerRadian = Scalar(180.0) / Pi;
    constexpr Scalar RadianPerDegree  = Scalar(1.0) / DegreesPerRadian;
    constexpr Scalar RPi              = Scalar(1.0) / Pi;
    constexpr Scalar RPi2             = Scalar(1.0) / Pi2;

    inline Scalar toDegrees(Scalar v)
    {
        return v * DegreesPerRadian;
    }

    inline Scalar toRadians(Scalar v)
    {
        return v * RadianPerDegree;
    }

    inline Scalar toMillimeters(const Scalar& deg)
    {
        return Scalar(18) / RtTan(deg * Pi / Scalar(360.0));
    }

    inline Scalar toFieldOfView(const Scalar& mm)
    {
        // https://www.desmos.com/calculator/aed6jmo0fx
        return Scalar(360.0) * RtATan(Scalar(18) / mm) / Pi;
    }

    inline void SinCos(const Scalar& theta, Scalar& y, Scalar& x)
    {
        y = RtSin(theta);
        x = RtCos(theta);
    }

}  // namespace Rt2::Math
