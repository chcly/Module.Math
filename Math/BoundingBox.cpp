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
#include "Math/BoundingBox.h"

namespace Rt2::Math
{
    BoundingBox::BoundingBox(const Real mi[3], const Real ma[3])
    {
        for (int i = 0; i < 3; ++i)
        {
            bMin[i] = mi[i];
            bMax[i] = ma[i];
        }
    }

    BoundingBox::BoundingBox(const Vector3& extent, const Vector3& center)
    {
        const Real* ep = extent.ptr();
        const Real* cp = center.ptr();

        for (int i = 0; i < 3; ++i)
        {
            bMin[i] = cp[i] - ep[i] * Real(0.5);
            bMax[i] = cp[i] + ep[i] * Real(0.5);
        }
    }

    void BoundingBox::clear()
    {
        for (int i = 0; i < 3; ++i)
        {
            bMin[i] = Infinity;
            bMax[i] = -Infinity;
        }
    }

    void BoundingBox::compare(const Vector3& pt)
    {
        const Real* ep = pt.ptr();
        for (int i = 0; i < 3; ++i)
        {
            if (ep[i] < bMin[i])
                bMin[i] = ep[i];
            if (ep[i] > bMax[i])
                bMax[i] = ep[i];
        }
    }

    void BoundingBox::compare(const Real* pt)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (pt[i] < bMin[i])
                bMin[i] = pt[i];
            if (pt[i] > bMax[i])
                bMax[i] = pt[i];
        }
    }

    void BoundingBox::merge(const BoundingBox& bb)
    {
        compare(bb.bMin);
        compare(bb.bMax);
    }

    void BoundingBox::scale(const Real& sc)
    {
        for (int i = 0; i < 3; ++i)
        {
            bMin[i] *= sc;
            bMax[i] *= sc;
        }
    }

    void BoundingBox::translate(const Vector3& pt)
    {
        const Real* ep = pt.ptr();

        for (int i = 0; i < 3; ++i)
        {
            bMin[i] += ep[i];
            bMax[i] += ep[i];
        }
    }

    void BoundingBox::setMin(const Vector3& mi)
    {
        bMin[0] = mi.x;
        bMin[1] = mi.y;
        bMin[2] = mi.z;
    }

    void BoundingBox::setMax(const Vector3& ma)
    {
        bMax[0] = ma.x;
        bMax[1] = ma.y;
        bMax[2] = ma.z;
    }

    Real BoundingBox::signedLength() const
    {
        const Vector3 c = center();

        Real sign = 1;
        if (c.x < 0)
            sign *= -1;
        if (c.y < 0)
            sign *= -1;
        if (c.z < 0)
            sign *= -1;
        return sign * c.length();
    }

    bool BoundingBox::contains(const BoundingBox& bb) const
    {
        const Vector3 tmi = min();
        const Vector3 tma = max();
        const Vector3 bmi = bb.min();
        const Vector3 bma = bb.max();

        bool res = bmi.x >= tmi.x && bmi.y >= tmi.y && bmi.x >= tmi.z;
        if (res)
            res = bma.x <= tma.x && bma.y <= tma.y && bma.x <= tma.z;
        return res;
    }

    void BoundingBox::majorAxis(Vector3& dest, const Vector3& src)
    {
        const Real m = Max3(src.x, src.y, src.z);

        if (eq(m, src.x))
            dest = Vector3::UnitX;
        else if (eq(m, src.y))
            dest = Vector3::UnitY;
        else
            dest = Vector3::UnitZ;
        if (m < 0)
            dest *= -1;
    }

    bool BoundingBox::hit(const Ray& ray, const Vector2& limit) const
    {
        const Real* origP = ray.origin.ptr();
        const Real* dirP  = ray.direction.ptr();

        Real tMin = limit.x;
        Real tMax = limit.y;

        for (int i = 0; i < 3; ++i)
        {
            Real t0 = 0, t1 = 0;
            if (!eq(dirP[i], 0))
            {
                const Real t2 = 1 / dirP[i];

                t0 = (bMin[i] - origP[i]) * t2;
                t1 = (bMax[i] - origP[i]) * t2;

                if (t2 < Real(0.0))
                {
                    const Real t = t0;

                    t0 = t1;
                    t1 = t;
                }
            }

            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;
            if (tMax <= tMin)
                return false;
        }
        return true;
    }

    bool BoundingBox::hit(Real& r0, Real& r1, const Ray& ray, const Vector2& limit) const
    {
        const Real* origP = ray.origin.ptr();
        const Real* dirP  = ray.direction.ptr();

        r0 = limit.x;
        r1 = limit.y;

        for (int i = 0; i < 3; ++i)
        {
            Real t0 = 0, t1 = 0;
            if (!eq(dirP[i], 0))
            {
                const Real t2 = 1 / dirP[i];

                t0 = (bMin[i] - origP[i]) * t2;
                t1 = (bMax[i] - origP[i]) * t2;

                if (t2 < Real(0.0))
                {
                    const Real t = t0;

                    t0 = t1;
                    t1 = t;
                }
            }

            r0 = t0 > r0 ? t0 : r0;
            r1 = t1 < r1 ? t1 : r1;
            if (r1 < r0)
                return false;
        }
        return true;
    }

    bool BoundingBox::hit(RayHitTest& dest, const Ray& ray, const Vector2& limit) const
    {
        const Real* origP = ray.origin.ptr();
        const Real* dirP  = ray.direction.ptr();

        Real tMin = limit.x;
        Real tMax = limit.y;

        for (int i = 0; i < 3; ++i)
        {
            Real t0 = 0, t1 = 0;

            if (!eq(dirP[i], 0))
            {
                const Real t2 = 1 / dirP[i];

                t0 = (bMin[i] - origP[i]) * t2;
                t1 = (bMax[i] - origP[i]) * t2;

                if (t2 < Real(0.0))
                {
                    const Real t = t0;

                    t0 = t1;
                    t1 = t;
                }
            }

            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;
            if (tMax <= tMin)
                return false;
        }

        dest.distance = tMin;
        dest.point    = ray.at(tMin);

        const Vector3 p1 = dest.point - center();
        const Vector3 p2 = extent() * Real(0.5);
        const Vector3 p3 = p1 / p2;
        const Vector3 p4 = p3.abs();
        const Real  m3 = p4.max3();
        dest.normal        = {0, 0, 0};
        if (eq(m3, p4.x))
            dest.normal.x = sign(p3.x);
        else if (eq(m3, p4.y))
            dest.normal.y = sign(p3.y);
        else
            dest.normal.z = sign(p3.z);
        return true;
    }

}  // namespace Rt2::Math
