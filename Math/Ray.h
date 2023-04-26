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
#include "Math/Vec3.h"

namespace Rt2::Math
{
    class Ray;

    struct RayHitTest
    {
        RayHitTest() :
            distance(0)
        {
        }

        RayHitTest(const RayHitTest& rhs) = default;

        Real distance;
        Vec3 point;
        Vec3 normal;
    };

    class Ray
    {
    public:
        Vec3 origin;
        Vec3 direction;

    public:
        Ray() = default;

        Ray(const Vec3& vOrig, const Vec3& vDir) :
            origin(vOrig),
            direction(vDir)
        {
        }

        Vec3 at(const Real& t) const
        {
            return {
                origin.x + direction.x * t,
                origin.y + direction.y * t,
                origin.z + direction.z * t,
            };
        }

        void at(Vec3& dest, const Real& t) const
        {
            dest.x = origin.x + direction.x * t;
            dest.y = origin.y + direction.y * t;
            dest.z = origin.z + direction.z * t;
        }

        void print() const;
    };
}  // namespace Rt2::Math
