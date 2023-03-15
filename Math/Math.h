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

#ifdef Math_USE_DOUBLE
    #define RtSqrt (Rt2::Math::Real) sqrt
    #define RtRSqrt (Rt2::Math::Real)1.0 / (Rt2::Math::Real)sqrt
    #define RtFloor (Rt2::Math::Real) floor
    #define RtCeil (Rt2::Math::Real) ceil
    #define RtSin (Rt2::Math::Real) sin
    #define RtCos (Rt2::Math::Real) cos
    #define RtTan (Rt2::Math::Real) tan
    #define RtExp (Rt2::Math::Real) exp
    #define RtLog (Rt2::Math::Real) log
    #define RtPow (Rt2::Math::Real) pow
    #define RtMod (Rt2::Math::Real) fmod
    #define RtASin (Rt2::Math::Real) asin
    #define RtACos (Rt2::Math::Real) acos
    #define RtATan (Rt2::Math::Real) atan
    #define RtATan2 (Rt2::Math::Real) atan2
    #define RtFmod (Rt2::Math::Real) fmod
    #define RtAbs (Rt2::Math::Real) abs
#else
    #define RtSqrt (Rt2::Math::Real) sqrtf
    #define RtRSqrt(x) (Rt2::Math::Real)(powf((x), -0.5f))
    #define RtFloor (Rt2::Math::Real) floorf
    #define RtCeil (Rt2::Math::Real) ceilf
    #define RtSin (Rt2::Math::Real) sinf
    #define RtCos (Rt2::Math::Real) cosf
    #define RtTan (Rt2::Math::Real) tanf
    #define RtExp (Rt2::Math::Real) expf
    #define RtLog (Rt2::Math::Real) logf
    #define RtPow (Rt2::Math::Real) powf
    #define RtMod (Rt2::Math::Real) fmodf
    #define RtASin (Rt2::Math::Real) asinf
    #define RtACos (Rt2::Math::Real) acosf
    #define RtATan (Rt2::Math::Real) atanf
    #define RtATan2 (Rt2::Math::Real) atan2f
    #define RtFmod (Rt2::Math::Real) fmodf
    #define RtAbs (Rt2::Math::Real) fabs
#endif

namespace Rt2::Math
{
    inline Real Max(const Real& a, const Real& b)
    {
        return a > b ? a : b;
    }

    inline Real Min(const Real& a, const Real& b)
    {
        return a < b ? a : b;
    }

    inline Real Max3(const Real& a, const Real& b, const Real& c)
    {
        const Real d = a > b ? a : b;
        return c > d ? c : d;
    }

    inline Real Min3(const Real& a, const Real& b, const Real& c)
    {
        const Real d = a < b ? a : b;
        return c < d ? c : d;
    }

    inline Real Abs(const Real& v)
    {
        return v < Real(0) ? -v : v;
    }

    inline Real Squ(const Real& v)
    {
        return v * v;
    }

    inline Real sign(const Real& value)
    {
        return value > 0 ? Real(1.) : Real(-1.);
    }

    inline Real isInf(const Real v)
    {
        return Abs(v) >= Infinity;
    }

    inline Real isNan(const Real v)
    {
        return std::isnan(v);
    }

    inline Real interpolate(const Real& a,
                            const Real& b,
                            Real        s)
    {
        s = Max(Min(s, Real(1.)), Real(0.));
        return (Real(1) - s) * a + b * s;
    }

    inline Real reciprocal(const Real& value,
                           const Real  def = Epsilon,
                           const Real  tol = Epsilon)
    {
        if (Abs(value) < tol)
            return def;
        return Real(1) / value;
    }

    inline bool equals(const Real& a,
                       const Real& b,
                       const Real  tolerance = Epsilon)
    {
        if (std::isnan(a) && std::isnan(b))
            return true;
        return Abs(a - b) < tolerance;
    }

    inline bool inRange(const Real& a,
                        const Real  tolerance = Epsilon)
    {
        return a >= tolerance && a <= Real(1.) + tolerance;
    }

    inline bool isZero(const Real& a,
                       const Real  tolerance = Epsilon)
    {
        return Abs(a) < tolerance;
    }

    inline bool notZero(const Real& a,
                        const Real  tolerance = Epsilon)
    {
        return Abs(a) > tolerance;
    }

    inline Real makeDivBy(const Real& a, const Real& d)
    {
        return a - Real(RtFmod(a, d));
    }

    inline Real whole(const Real& a)
    {
        return RtFloor(a);
    }

    inline Real largestPow10(const Real& x)
    {
        return RtPow(10, RtFloor(log10(x)));
    }

    inline Real largestDigit(const Real& x)
    {
        const Real lp10 = largestPow10(x);
        return lp10 * RtFloor(x / lp10);
    }

    inline Real decimal(const Real v)
    {
        return v - RtFloor(v);
    }

    inline void split(const Real v, Real& whole, Real& decimal)
    {
        whole   = RtFloor(v);
        decimal = v - whole;
    }

    inline bool eq(const Real x, const Real y)
    {
        return Abs(x - y) < Epsilon;
    }

    inline Real clamp(const Real& v, const Real& vMin, const Real& vMax)
    {
        return v < vMin ? vMin : v > vMax ? vMax
                                          : v;
    }

    inline bool neq(const Real x, const Real y)
    {
        return !eq(x, y);
    }

    inline bool eq(const Real& x, const Real& y, const Real& tol)
    {
        return Abs(x - y) < tol;
    }

    constexpr Real Pi   = Real(3.1415926535897932384626433832795);
    constexpr Real Pi4  = Real(4.0) * Pi;        // 2*Pi
    constexpr Real Pi2  = Real(2.0) * Pi;        // 2*Pi
    constexpr Real PiH  = Real(0.5) * Pi;        // 90 degrees
    constexpr Real PiO3 = Real(Pi) / Real(3.0);  // 60 degrees
    constexpr Real PiO4 = Real(Pi) / Real(4.0);  // 45 degrees
    constexpr Real PiO6 = Real(Pi) / Real(6.0);  // 30 degrees
    constexpr Real Dpr  = Real(180.0) / Pi;      // degrees per radian
    constexpr Real Rpd  = Real(1.0) / Dpr;       // radians per degree
    constexpr Real RPi  = Real(1.0) / Pi;        // reciprocal of Pi
    constexpr Real RPi2 = Real(1.0) / Pi2;       // reciprocal of 2*Pi

    inline Real toDegrees(const Real v)
    {
        return v * Dpr;
    }

    inline Real toRadians(const Real v)
    {
        return v * Rpd;
    }

    inline Real toMillimeters(const Real& deg)
    {
        return Real(18) / RtTan(deg * Pi / Real(360.0));
    }

    inline Real toFieldOfView(const Real& mm)
    {
        // https://www.desmos.com/calculator/aed6jmo0fx
        return Real(360.0) * RtATan(Real(18) / mm) / Pi;
    }

    inline void angles(const Real& theta, Real& y, Real& x)
    {
        y = RtSin(theta);
        x = RtCos(theta);
    }

}  // namespace Rt2::Math
