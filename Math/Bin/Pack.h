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
#include "Math/Rand.h"
#include "Math/Rect.h"
#include "Math/Vec2.h"
#include "Utils/Array.h"

namespace Rt2::Math::BinPack
{
    enum Options
    {
        SORT_MIN       = 0x001,
        USE_PARAM      = 0x002,
        MIN_AREA_MIN   = 0x004,
        MIN_AREA_MAX   = 0x008,
        MAX_AREA_MIN   = 0x010,
        MAX_AREA_MAX   = 0x020,
        BEST_FIT_MAX   = 0x040,
        BEST_FIT_FIRST = 0x080,
        BEST_FIT_LAST  = 0x100,
    };

    class Pack
    {
    public:
        using Size = RectList::SizeType;

    private:
        RectList   _input;
        RectList   _output;
        Box2d      _bounds;
        SortedBins _bins;
        int        _options{0};

        static Real param(int op, const IndexRect& r);

    public:
        Pack();
        ~Pack();

        void clear();

        void push(const Rect& rect);

        void push(U32 index, size_t param, const Rect& rect);

        void setOptions(int op);

        void sort();

        void modSort(Real mod);

        const RectList& input();

        const RectList& output();

        Size size() const;

        const Box2d& bounds() const;

        void pack(const Vec2& size);

        Vec2 dimensions() const;
    };

    inline const RectList& Pack::input()
    {
        return _input;
    }

    inline const RectList& Pack::output()
    {
        return _output;
    }

    inline Pack::Size Pack::size() const
    {
        return _input.size();
    }

    inline const Box2d& Pack::bounds() const
    {
        return _bounds;
    }

    inline void Pack::setOptions(const int op)
    {
        _options = op;
    }

    class PackUtils
    {
    public:
        static Rect rand(I32 min, I32 max);

        static Rect randSquare(I32 min, I32 max);

        static bool sortAscP(const IndexRect& a, const IndexRect& b);

        static bool sortDescP(const IndexRect& a, const IndexRect& b);

        static bool sortAscA(const IndexRect& a, const IndexRect& b);

        static bool sortDescA(const IndexRect& a, const IndexRect& b);
    };
}  // namespace Rt2::Math::BinPack
