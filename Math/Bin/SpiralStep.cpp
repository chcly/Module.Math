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
#include "Math/Bin/SpiralStep.h"

namespace Rt2::Math::BinPack
{
    SpiralStep::SpiralStep(const Real sc)
    {
        _scale = sc;
        _s     = -1;
        _t     = _s + 2;
    }

    void SpiralStep::step(Vec2& offs)
    {
        ++_i;
        switch (_st)
        {
        case Start:
            _i = 0;
            offs.x = 0;
            offs.y = 0;
            _st    = Next;
            break;
        case Next:
            _i = 0;
            offs.x -= _scale;
            offs.y += _scale;
            _st = East;
            _s += 2;
            _t += 2;
            break;
        case East:
            if (_i < _t)
                offs.x += _scale;
            else
            {
                offs.y -= _scale;
                _i  = 0;
                _st = South;
            }
            break;
        case South:

            if (_i < _s)
                offs.y -= _scale;
            else
            {
                offs.y -= _scale;
                _i  = 0;
                _st = West;
            }
            break;
        case West:
            if (_i < _t)
                offs.x -= _scale;
            else
            {
                offs.y += _scale;
                _i  = 0;
                _st = North;
            }
            break;
        case North:
            if (_i < _s)
                offs.y += _scale;
            else
            {
                offs.y += 2 * _scale;
                offs.x -= _scale;
                _t += 2;
                _s += 2;
                _i  = 0;
                _st = East;
            }
            break;
        default:
            break;
        }
    }
}  // namespace Rt2::Math::BinPack
