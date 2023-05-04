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
#include "Math/Math.h"
#include "Math/Vec2.h"
#include "Utils/Definitions.h"

namespace Rt2::Math::BinPack
{
    class TreeStep
    {
    private:
        Real _scale{1.1};
        size_t _n{0}, _i{0}, _r{4}, _c{1};
        Vec2 _step{0,0};

    public:
        explicit TreeStep(Real sc, size_t sz);

        void step(Vec2& offs);
    };

}  // namespace Rt2::Math::BinPack
