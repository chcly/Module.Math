#pragma once
#include "Math/Rect.h"
#include "Utils/Array.h"

namespace Rt2::Math::BinPack
{
    struct IndexRect
    {
        U32  index{0};
        Rect rect{0, 0, 0, 0};
    };

    using RectList   = SimpleArray<IndexRect>;
    using RectArray  = SimpleArray<Rect>;
    using SortedBins = SimpleArray<RectList>;

}  // namespace Rt2::Math::BinPack
