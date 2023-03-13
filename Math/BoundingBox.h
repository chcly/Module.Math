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
#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace Rt2::Math
{
    class BoundingBox
    {
    public:
        Real bMin[3]{};
        Real bMax[3]{};

    public:
        BoundingBox();

        BoundingBox(const Real mi[3], const Real ma[3]);

        BoundingBox(const Vector3& extent, const Vector3& center);

        void clear();

        void compare(const Vector3& pt);

        void compare(const Real* pt);

        void merge(const BoundingBox& bb);

        void scale(const Real& sc);

        void translate(const Vector3& pt);

        void setMin(const Vector3& mi);

        void setMax(const Vector3& ma);

        Real signedLength() const;

        bool contains(const BoundingBox& bb) const;

        static void majorAxis(Vector3& dest, const Vector3& src);

        bool hit(const Ray& ray, const Vector2& limit) const;

        bool hit(Real& r0, Real& r1, const Ray& ray, const Vector2& limit) const;

        bool hit(RayHitTest& dest, const Ray& ray, const Vector2& limit) const;

        Vector3 min() const;

        Vector3 max() const;

        Vector3 extent() const;

        Real halfLength2() const;

        Real halfLength() const;

        Real max3() const;

        Real min3() const;

        Vector3 center() const;

        Real length() const;

        Real length2() const;

        bool less(const BoundingBox& bb) const;
    };

    inline BoundingBox::BoundingBox()
    {
        clear();
    }

    inline Vector3 BoundingBox::min() const
    {
        return Vector3(bMin[0], bMin[1], bMin[2]);
    }

    inline Vector3 BoundingBox::max() const
    {
        return Vector3(bMax[0], bMax[1], bMax[2]);
    }

    inline Vector3 BoundingBox::extent() const
    {
        return Vector3(bMax[0] - bMin[0], bMax[1] - bMin[1], bMax[2] - bMin[2]);
    }

    inline Real BoundingBox::halfLength2() const
    {
        return extent().length2() * Real(0.5);
    }

    inline Real BoundingBox::halfLength() const
    {
        return extent().length() * Real(0.5);
    }

    inline Real BoundingBox::max3() const
    {
        return std::max(bMax[0], std::max(bMax[1], bMax[2]));
    }

    inline Real BoundingBox::min3() const
    {
        return std::min(bMin[0], std::min(bMin[1], bMin[2]));
    }

    inline Vector3 BoundingBox::center() const
    {
        return Vector3(
            Real(0.5) * (bMax[0] + bMin[0]),
            Real(0.5) * (bMax[1] + bMin[1]),
            Real(0.5) * (bMax[2] + bMin[2]));
    }

    inline Real BoundingBox::length() const
    {
        return extent().length();
    }

    inline Real BoundingBox::length2() const
    {
        return extent().length();
    }

    inline bool BoundingBox::less(const BoundingBox& bb) const
    {
        return signedLength() < bb.signedLength();
    }

}  // namespace Rt2::Math
