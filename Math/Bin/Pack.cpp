#include "Math/Bin/Pack.h"
#include <algorithm>
#include "Math/Bin/Bin.h"

namespace Rt2::Math::BinPack
{

    Pack::Pack() = default;

    Pack::~Pack()
    {
        _input.clear();
        _output.clear();
    }

    void Pack::clear()
    {
        _output.resizeFast(0);
        _input.resizeFast(0);
        _bounds.clear();
    }

    void Pack::push(const Rect& rect)
    {
        _bounds.merge(rect.w, rect.h);
        _input.push_back({_input.size(), rect});
    }

    void Pack::push(const U32 index, const Rect& rect)
    {
        _bounds.merge(rect.w, rect.h);
        _input.push_back({index, rect});
    }

    void Pack::pack(const Vec2& size)
    {
        Bin bin = Bin(_bounds.maximum().maxOf(size), _options);
        for (const auto& inp : _input)
            bin.insert(inp);

        _output.resizeFast(0);
        _bounds.clear();
        _bins.clear();

        do
        {
            _bins.push_back(bin.sorted());
            bin.resort();
        } while (bin.hasMore());

        const size_t pitch = (size_t)sqrt(_bins.size());

        Vec2   step{};
        Real   maxBby = 0;
        size_t i      = 0;

        // shelf the bins

        _bounds.clear();
        for (auto& b : _bins)
        {
            Box2d bb;
            for (auto& r : b)
            {
                bb.merge(r.rect);
                _output.push_back(
                    {
                        r.index,
                        Rect(r.rect.x + step.x, r.rect.y + step.y, r.rect.w, r.rect.h),
                    });
                _bounds.merge(_output.back().rect);
            }

            step.x += bb.x1;
            maxBby = Max(maxBby, bb.y1);

            if (i > pitch)
            {
                i      = 0;
                step.x = 0;
                step.y += maxBby;
                maxBby = 0;
            }
            ++i;
        }

        const Real asp = Min(_bounds.x1, _bounds.y1) / Max(_bounds.x1, _bounds.y1);

        const Real rx = reciprocal(_bounds.x1);
        const Real ry = reciprocal(_bounds.y1);

        _bounds.clear();
        _bounds.x0 = rx;
        _bounds.y0 = ry;
        _bounds.x1 = size.x;
        _bounds.y1 = size.y * asp;

        for (auto& v : _output)
        {
            v.rect.scale(_bounds.x0, _bounds.y0);
            v.rect.scale(_bounds.x1, _bounds.y1);
        }
    }

    Vec2 Pack::dimensions() const
    {
        return _bounds.maximum();
    }

    Real Pack::param(const int op, const Rect& r)
    {
        if (op & SORT_X)
            return r.w;
        if (op & SORT_Y)
            return r.h;
        return r.area();
    }

    void Pack::sort()
    {
        using SortFunction = std::function<bool(const IndexRect& a, const IndexRect& b)>;
        SortFunction func;

        if (_options & SORT_X)
        {
            if (_options & SORT_MIN)
                func = PackUtils::sortAscX;
            else
                func = PackUtils::sortDescX;
        }
        else if (_options & SORT_Y)
        {
            if (_options & SORT_MIN)
                func = PackUtils::sortAscY;
            else
                func = PackUtils::sortDescY;
        }
        else
        {
            if (_options & SORT_MIN)
                func = PackUtils::sortAscA;
            else
                func = PackUtils::sortDescA;
        }
        if (func)
            std::sort(_input.begin(), _input.end(), func);
    }

    void Pack::modSort(Real mod)
    {
        using Accessor = std::function<Real(int, const Rect&)>;

        Accessor method = param;
        int      op     = _options;

        std::sort(_input.begin(),
                  _input.end(),
                  [mod, method, op](const IndexRect& a, const IndexRect& b)
                  {
                      if (op & SORT_MIN)
                          return RtFmod(method(op, a.rect), mod) < RtFmod(method(op, b.rect), mod);
                      return RtFmod(method(op, a.rect), mod) > RtFmod(method(op, b.rect), mod);
                  });
    }

    Rect PackUtils::rand(const I32 min, const I32 max)
    {
        Real r1 = Abs(Real(Rand::range(min, max)));
        Real r2 = Abs(Real(Rand::range(min, max)));
        return {0, 0, r1, r2};
    }

    Rect PackUtils::randSquare(const I32 min, const I32 max)
    {
        Real r1 = Abs(Real(Rand::range(min, max)));
        return {0, 0, r1, r1};
    }

    bool PackUtils::sortAscX(const IndexRect& a, const IndexRect& b)
    {
        return a.rect.w < b.rect.w;
    }

    bool PackUtils::sortDescX(const IndexRect& a, const IndexRect& b)
    {
        return a.rect.w > b.rect.w;
    }

    bool PackUtils::sortAscY(const IndexRect& a, const IndexRect& b)
    {
        return a.rect.h < b.rect.h;
    }

    bool PackUtils::sortDescY(const IndexRect& a, const IndexRect& b)
    {
        return a.rect.h > b.rect.h;
    }

    bool PackUtils::sortAscA(const IndexRect& a, const IndexRect& b)
    {
        return a.rect.area() < b.rect.area();
    }

    bool PackUtils::sortDescA(const IndexRect& a, const IndexRect& b)
    {
        return a.rect.area() > b.rect.area();
    }
}  // namespace Rt2::Math::BinPack
