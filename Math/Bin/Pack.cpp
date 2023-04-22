#include "Math/Bin/Pack.h"
#include <algorithm>
#include "Math/Bin/Bin.h"

namespace Rt2::Math::BinPack
{

    Pack::Pack() = default;

    void Pack::clear()
    {
        _output.resizeFast(0);
        _input.resizeFast(0);
        _bounds.clear();
    }

    void Pack::push(const Rect& rect)
    {
        _bounds.merge(rect.w, rect.h);
        _input.push_back(rect);
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
                bb.merge(r);
                _output.push_back({r.x + step.x, r.y + step.y, r.w, r.h});
                _bounds.merge(_output.back());
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
            v.scale(_bounds.x0, _bounds.y0);
            v.scale(_bounds.x1, _bounds.y1);
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
        using SortFunction = std::function<bool(const Rect& a, const Rect& b)>;
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
                  [mod, method, op](const Rect& a, const Rect& b)
                  {
                      if (op & SORT_MIN)
                          return RtFmod(method(op, a), mod) < RtFmod(method(op, b), mod);
                      return RtFmod(method(op, a), mod) > RtFmod(method(op, b), mod);
                  });
    }

    Rect PackUtils::rand(I32 min, I32 max)
    {
        Real r1 = Abs(Real(Rand::range(min, max)));
        Real r2 = Abs(Real(Rand::range(min, max)));
        return {0, 0, r1, r2};
    }

    Rect PackUtils::randSquare(I32 min, I32 max)
    {
        Real r1 = Abs(Real(Rand::range(min, max)));
        return {0, 0, r1, r1};
    }

    bool PackUtils::sortAscX(const Rect& a, const Rect& b)
    {
        return a.w < b.w;
    }

    bool PackUtils::sortDescX(const Rect& a, const Rect& b)
    {
        return a.w > b.w;
    }

    bool PackUtils::sortAscY(const Rect& a, const Rect& b)
    {
        return a.h < b.h;
    }

    bool PackUtils::sortDescY(const Rect& a, const Rect& b)
    {
        return a.h > b.h;
    }

    bool PackUtils::sortAscA(const Rect& a, const Rect& b)
    {
        return a.area() < b.area();
    }

    bool PackUtils::sortDescA(const Rect& a, const Rect& b)
    {
        return a.area() > b.area();
    }
}  // namespace Rt2::Math::BinPack
