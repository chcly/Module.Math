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

#include "Math/Vector3.h"
#include <cstdio>
#include "Math/Color.h"

namespace Rt2::Math
{
    const Vector3 Vector3::Unit  = Vector3(1, 1, 1);
    const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
    const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
    const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);
    const Vector3 Vector3::Zero  = Vector3(0, 0, 0);

    void Vector3::print() const
    {
        printf("[%3.3f, %3.3f, %3.3f]\n", (double)x, (double)y, (double)z);
    }

    Vector3::Vector3(const Color& col) :
        x(col.r),
        y(col.g),
        z(col.b)
    {
    }
}  // namespace Rt2::Math
