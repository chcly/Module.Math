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
#include "Math/Ray.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
namespace Rt2::Math
{
    class Plane
    {
    public:
        Vec3 p0;
        Vec3 n;

    public:
        Plane()                 = default;
        Plane(const Plane& n) = default;

        explicit Plane(const Vec3& point, const Vec3& normal) :
            p0(point),
            n(normal)
        {
        }


        bool hit(Real& t, const Ray& ray, const Vec2& limit) const
        {
            Real kn = n.x * (ray.origin.x - p0.x);
            Real kd = ray.direction.x * n.x;

            kn += n.y * (ray.origin.y - p0.y);
            kd += ray.direction.y * n.y;
            kn += -n.z * (ray.origin.z - p0.z);
            kd += ray.direction.z * -n.z;

            // > 0 in < 0 out == 0 on

            if (!isZero(kd))
            {
                t = (-kn + p0.length()) / kd;
                if (t >= limit.x && t <= limit.y)
                    return true;
            }
            return false;
        }

        bool hit(RayHitTest& ht, const Ray& ray, const Vec2& limit) const
        {
            if (hit(ht.distance, ray, limit))
            {
                ht.normal = n;
                ht.point  = ray.at(ht.distance);
                return true;
            }
            return false;
        }

        void print() const;
    };

}  // namespace Rt2::Math
