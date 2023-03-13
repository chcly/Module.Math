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
#include "Math/Vector3.h"

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

        Real  distance;
        Vector3 point;
        Vector3 normal;
    };


    /**
     * \brief R = tD + o
      */
    class Ray
    {
    public:
        Vector3 origin;
        Vector3 direction;

    public:
        Ray() = default;

        Ray(const Vector3& vOrig, const Vector3& vDir) :
            origin(vOrig),
            direction(vDir)
        {
        }

        Vector3 at(const Real& t) const
        {
            return {
                origin.x + direction.x * t,
                origin.y + direction.y * t,
                origin.z + direction.z * t,
            };
        }

        void at(Vector3& dest, const Real& t) const
        {
            dest.x = origin.x + direction.x * t;
            dest.y = origin.y + direction.y * t;
            dest.z = origin.z + direction.z * t;
        }

        void print() const;
    };
}  // namespace Rt2::Math
