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

#include <algorithm>
#include "Math/Math.h"
#include "Math/Ray.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"

namespace Rt2::Math
{
    class Box3d
    {
    public:
        Real bMin[3]{};
        Real bMax[3]{};

    public:
        Box3d();

        Box3d(const Real mi[3], const Real ma[3]);

        Box3d(const Vec3& extent, const Vec3& center);

        void clear();

        void compare(const Vec3& pt);

        void compare(const Real* pt);

        void merge(const Box3d& bb);

        void scale(const Real& sc);

        void translate(const Vec3& pt);

        void setMin(const Vec3& mi);

        void setMax(const Vec3& ma);

        Real signedLength() const;

        bool contains(const Box3d& bb) const;

        static void majorAxis(Vec3& dest, const Vec3& src);

        bool hit(const Ray& ray, const Vec2& limit) const;

        bool hit(Real& r0, Real& r1, const Ray& ray, const Vec2& limit) const;

        bool hit(RayHitTest& dest, const Ray& ray, const Vec2& limit) const;

        Vec3 min() const;

        Vec3 max() const;

        Vec3 extent() const;

        Real halfLength2() const;

        Real halfLength() const;

        Real max3() const;

        Real min3() const;

        Vec3 center() const;

        Real length() const;

        Real length2() const;

        bool less(const Box3d& bb) const;
    };

    inline Box3d::Box3d()
    {
        clear();
    }

    inline Vec3 Box3d::min() const
    {
        return {bMin[0], bMin[1], bMin[2]};
    }

    inline Vec3 Box3d::max() const
    {
        return {bMax[0], bMax[1], bMax[2]};
    }

    inline Vec3 Box3d::extent() const
    {
        return {bMax[0] - bMin[0], bMax[1] - bMin[1], bMax[2] - bMin[2]};
    }

    inline Real Box3d::halfLength2() const
    {
        return extent().length2() * Real(0.5);
    }

    inline Real Box3d::halfLength() const
    {
        return extent().length() * Real(0.5);
    }

    inline Real Box3d::max3() const
    {
        return std::max(bMax[0], std::max(bMax[1], bMax[2]));
    }

    inline Real Box3d::min3() const
    {
        return std::min(bMin[0], std::min(bMin[1], bMin[2]));
    }

    inline Vec3 Box3d::center() const
    {
        return {
            Real(0.5) * (bMax[0] + bMin[0]),
            Real(0.5) * (bMax[1] + bMin[1]),
            Real(0.5) * (bMax[2] + bMin[2])};
    }

    inline Real Box3d::length() const
    {
        return extent().length();
    }

    inline Real Box3d::length2() const
    {
        return extent().length();
    }

    inline bool Box3d::less(const Box3d& bb) const
    {
        return signedLength() < bb.signedLength();
    }

}  // namespace Rt2::Math
