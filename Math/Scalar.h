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

#ifdef __cplusplus
#include <cfloat>
#include <cmath>
#else
#include <float.h>
#include <math.h>
#endif

/* #define RT_DOUBLE */
#define RT_EPSILON FLT_EPSILON
#define RT_INFINITY FLT_MAX

namespace Rt2::Math
{
    typedef float Scalar;

    constexpr float One = 1;
    constexpr float Half      = One/2;
    constexpr float Forth     = One/4;
    constexpr float Eighth    = One/8;
    constexpr float Twelfth   = One/12;
    constexpr float Sixteenth = One/16;

}  // namespace Rt2::Math
