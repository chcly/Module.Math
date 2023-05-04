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
#include "Math/Bin/TreeStep.h"

namespace Rt2::Math::BinPack
{
    TreeStep::TreeStep(const Real sc, size_t sz)
    {
        _n     = sz;
        _scale = sc;
    }

    void TreeStep::step(Vec2& offs)
    {
        if (_i != 0)
        {
            if (_i==1)
            {
                _step.y += _scale;
                _step.x = (-Real(_n-1) * _scale) * Half;
            }
            _step.x += _scale;
        }

        offs.x = _step.x;
        offs.y = _step.y;

        ++_i;
    }
}  // namespace Rt2::Math::BinPack
