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

#include <cfloat>
#include <cmath>
#include "Math/Config.h"

namespace Rt2::Math
{
#ifdef Math_USE_DOUBLE
    using Real              = double;
    constexpr Real Epsilon  = DBL_EPSILON;
    constexpr Real Infinity = DBL_MAX;
#else
    using Real              = float;
    constexpr Real Epsilon  = FLT_EPSILON;
    constexpr Real Infinity = FLT_MAX;
#endif
    constexpr Real Zero      = Real(0.0);
    constexpr Real One       = Real(1.0);
    constexpr Real Half      = One / Real(2.0);
    constexpr Real Forth     = One / Real(4.0);
    constexpr Real Eighth    = One / Real(8.0);
    constexpr Real Twelfth   = One / Real(12.0);
    constexpr Real Sixteenth = One / Real(16.0);
    constexpr Real One15     = One / Real(15.0);
    constexpr Real One24     = One / Real(24.0);
    constexpr Real One25     = One / Real(25.0);
    constexpr Real One60     = One / Real(60.0);
    constexpr Real One255    = One / Real(255.0);
    constexpr Real One256    = One / Real(256.0);

}  // namespace Rt2::Math
