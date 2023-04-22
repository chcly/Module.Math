#include "Bin.h"
#include "Pack.h"

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

    void Bin::insert(const Rect& rect)
    {
        if (_sorted.empty())
        {
            push(rect);
            Rect d0, d1;
            split({0, 0, _size.x, _size.y}, rect.size(), d0, d1);

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
                if (rect.w <= value.w &&
                    rect.h <= value.h)
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
                        const Real areaLeft = (value.w - rect.w) * (value.h - rect.h);

                        if (_opts & BEST_FIT_MAX)
                        {
                            if (areaLeft > filter)
                            {
                                filter = areaLeft;
                                bf     = i;
                            }
                        }
                        else  // default: min fit
                        {
                            if (areaLeft < filter)
                            {
                                filter = areaLeft;
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
                const Vec2& sz = rect.size();

                split(cdj, sz, d0, d1);
                push({pt, sz});

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

    void Bin::push(const Rect& rect)
    {
        _sorted.push_back(rect);
        _bounds.merge(rect);
    }

}  // namespace Rt2::Math::BinPack
