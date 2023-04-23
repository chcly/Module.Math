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
#include "Math/Bin/Rect.h"
#include "Math/Box2d.h"
#include "Math/Math.h"
#include "Math/Vec2.h"
#include "Utils/Array.h"

namespace Rt2::Math::BinPack
{
    class Bin
    {
    public:
        using Size = RectList::SizeType;

        struct FreeRects
        {
            Rect d0;
            Rect d1;

            Real minimum() const;

            Real maximum() const;
        };

    private:
        Vec2      _size;
        RectList  _sorted;
        RectArray _disjoint;
        RectList  _rejected;
        Box2d     _bounds;
        int       _opts{0};

    public:
        explicit Bin(const Vec2& size, int opts);

        bool hasMore() const;

        void resort();

        void insert(const PackedRect& rect);

        const RectList& sorted() const;

        const Box2d& bounds() const;

    private:
        void split(const Rect& pt, const Vec2& in, Rect& d0, Rect& d1) const;

        void push(const PackedRect& rect);
    };

    inline const RectList& Bin::sorted() const
    {
        return _sorted;
    }

    inline const Box2d& Bin::bounds() const
    {
        return _bounds;
    }

}  // namespace Rt2::Math::BinPack
