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
#include "Math/Print.h"
#include "Box2d.h"
#include "Rect.h"

namespace Rt2::Math
{

    class Box2dPrint : public TPrintSet<Real, '{', ' ', '}', 3, 6, true>
    {
    public:
        using Base = TPrintSet<Real, '{', ' ', '}', 3, 6, true>;
    public:
        explicit Box2dPrint(const Box2d& v) :
            Base({v.x0, v.y0, v.x1, v.y1},
                 Printer::width,
                 Printer::precision)
        {
        }
    };

    
    class RectPrint : public TPrintSet<Real, '[', ' ', ']', 3, 6, true>
    {
    public:
        using Base = TPrintSet<Real, '[', ' ', ']', 3, 6, true>;
    public:
        explicit RectPrint(const Rect& v) :
            Base({v.x, v.y, v.w, v.h},
                 Printer::width,
                 Printer::precision)
        {
        }
    };


    OStream* Printer::_output   = nullptr;
    uint8_t  Printer::precision = 3;
    uint8_t  Printer::width     = 6;

    void Printer::bind(OStream* stream)
    {
        _output = stream;
    }

    void Printer::setPrecision(U8 p)
    {
        precision = p;
        width     = precision * 2;
    }

    void Printer::print(const Box2d& v)
    {
        if (_output)
            Ts::println(*_output, Box2dPrint(v));
    }

    void Printer::print(const Rect& v)
    {
        if (_output)
            Ts::println(*_output, RectPrint(v));
    }

}  // namespace Rt2::Math
