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
#include "Math/Bin/Bin.h"
#include "Math/Bin/Pack.h"

namespace Rt2::Math::BinPack
{
    Bin::Bin(const Vec2& size, const int opts) :
        _size(size),
        _opts(opts)
    {
        _bounds.clear();
    }

    bool Bin::hasMore() const
    {
        return !_sorted.empty() || !_rejected.empty();
    }

    void Bin::insert(const IndexRect& rect)
    {
        if (_sorted.empty())
        {
            push(rect);
            Rect d0, d1;
            split({0, 0, _size.x, _size.y},
                  rect.rect.size(),
                  d0,
                  d1);

            _disjoint.push_back(d0);
            _disjoint.push_back(d1);
        }
        else
        {
            int bf = -1;

            Real filter = _opts & BEST_FIT_MAX ? 0 : Infinity;

            int i = 0;
            for (const auto& value : _disjoint)
            {
                if (rect.rect.w <= value.w &&
                    rect.rect.h <= value.h)
                {
                    if (_opts & BEST_FIT_FIRST)
                    {
                        bf = i;
                        break;
                    }
                    if (_opts & BEST_FIT_LAST)
                        bf = i;
                    else
                    {
                        const Real remaining = (value.w - rect.rect.w) * (value.h - rect.rect.h);
                        if (_opts & BEST_FIT_MAX)
                        {
                            if (remaining > filter)
                            {
                                filter = remaining;
                                bf     = i;
                            }
                        }
                        else  // default: min fit
                        {
                            if (remaining < filter)
                            {
                                filter = remaining;
                                bf     = i;
                            }
                        }
                    }
                }
                ++i;
            }

            if (bf == -1)
                _rejected.push_back(rect);
            else
            {
                const Rect& cdj = _disjoint.at(bf);

                Rect        d0, d1;
                const Vec2& pt = cdj.lt();
                const Vec2& sz = rect.rect.size();

                split(cdj, sz, d0, d1);
                push({
                    rect.index, rect.sortParam, {pt, sz}
                });
                _disjoint.remove(bf);

                _disjoint.push_back(d0);
                _disjoint.push_back(d1);
            }
        }
    }

    void Bin::resort()
    {
        RectList r = _rejected;
        _size.x += 1;
        _size.y += 1;
        _rejected.resizeFast(0);
        _sorted.resizeFast(0);
        _disjoint.resizeFast(0);
        _bounds.clear();

        for (const auto& v : r)
            insert(v);
    }

    Real Bin::FreeRects::minimum() const
    {
        const Real a = d0.w * d0.h;
        const Real b = d1.w * d1.h;
        return Min(a, b);
    }

    Real Bin::FreeRects::maximum() const
    {
        const Real a = d0.w * d0.h;
        const Real b = d1.w * d1.h;
        return Max(a, b);
    }

    void Bin::split(const Rect& pt, const Vec2& in, Rect& d0, Rect& d1) const
    {
        FreeRects a, b;

        // vertical
        a.d0 = {pt.x + in.x, pt.y, pt.w - in.x, pt.h};
        a.d1 = {pt.x, pt.y + in.y, in.x, pt.h - in.y};

        // horizontal
        b.d0 = {pt.x + in.x, pt.y, pt.w - in.x, in.y};
        b.d1 = {pt.x, pt.y + in.y, pt.w, pt.h - in.y};

        bool chooseA;
        if (_opts & MIN_AREA_MIN)
            chooseA = a.minimum() < b.minimum();
        else if (_opts & MIN_AREA_MAX)
            chooseA = a.minimum() > b.minimum();
        else if (_opts & MAX_AREA_MIN)
            chooseA = a.maximum() < b.maximum();
        else
            chooseA = a.maximum() > b.maximum();

        if (chooseA)
        {
            d0 = a.d0;
            d1 = a.d1;
        }
        else
        {
            d0 = b.d0;
            d1 = b.d1;
        }
    }

    void Bin::push(const IndexRect& rect)
    {
        _sorted.push_back(rect);
        _bounds.merge(rect.rect);
    }

}  // namespace Rt2::Math::BinPack
