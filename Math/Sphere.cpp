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
#include "Math/Sphere.h"

namespace Rt2::Math
{
    Sphere::Sphere(const Vec3& newCenter, const Real& newRadius) :
        center(newCenter),
        radius(newRadius)
    {
    }

    bool Sphere::hit(RayHitTest& dest, const Ray& ray, const Vec2& limit) const
    {
        const Real vec[3] = {
            ray.origin.x - center.x,
            ray.origin.y - center.y,
            ray.origin.z - center.z,
        };

        const Real a =
            ray.direction.x * ray.direction.x +
            ray.direction.y * ray.direction.y +
            ray.direction.z * ray.direction.z;

        const Real b =
            vec[0] * ray.direction.x +
            vec[1] * ray.direction.y +
            vec[2] * ray.direction.z;

        const Real r = radius * radius;
        const Real c =
            vec[0] * vec[0] - r +
            vec[1] * vec[1] - r +
            vec[2] * vec[2] - r;

        Real d = b * b - a * c;
        if (d > 0)
        {
            d = RtSqrt(d);

            Real x = (-b - d) / a;
            if (x >= limit.x && x <= limit.y)
            {
                dest.distance = x;
                dest.point    = ray.at(x);
                dest.normal   = dest.point - center;
                dest.normal.normalize();
                return true;
            }

            x = (-b + d) / a;
            if (x >= limit.x && x < limit.y)
            {
                dest.distance = x;
                dest.point    = ray.at(x);
                dest.normal   = dest.point - center;
                dest.normal.normalize();
                return true;
            }
        }
        return false;
    }

    bool Sphere::hit(const Ray& ray, const Vec2& limit) const
    {
        const Real vec[3] = {
            ray.origin.x - center.x,
            ray.origin.y - center.y,
            ray.origin.z - center.z,
        };
        const Real a =
            ray.direction.x * ray.direction.x +
            ray.direction.y * ray.direction.y +
            ray.direction.z * ray.direction.z;

        const Real b =
            vec[0] * ray.direction.x +
            vec[1] * ray.direction.y +
            vec[2] * ray.direction.z;
        const Real r = radius * radius;

        const Real c =
            vec[0] * vec[0] - r +
            vec[1] * vec[1] - r +
            vec[2] * vec[2] - r;

        Real d = b * b - a * c;
        if (d > 0)
        {
            d = RtSqrt(d);

            Real x = (-b - d) / a;
            if (x >= limit.x && x <= limit.y)
                return true;

            x = (-b + d) / a;
            if (x >= limit.x && x < limit.y)
                return true;
        }
        return false;
    }
}  // namespace Rt2::Math
