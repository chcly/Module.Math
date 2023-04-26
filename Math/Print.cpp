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
#include "Math/Box2d.h"
#include "Math/Mat3.h"
#include "Math/Mat4.h"
#include "Math/Quat.h"
#include "Math/Rect.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"

namespace Rt2::Math
{

    class BracePrint : public TPrintSet<Real, '[', ' ', ']', 3, 6, true>
    {
    public:
        using Base = TPrintSet<Real, '[', ' ', ']', 3, 6, true>;

    public:
        explicit BracePrint(const Rect& v) :
            Base({v.x, v.y, v.w, v.h},
                 Printer::width,
                 Printer::precision)
        {
        }

        explicit BracePrint(const Box2d& v) :
            Base({v.x0, v.y0, v.x1, v.y1},
                 Printer::width,
                 Printer::precision)
        {
        }

        explicit BracePrint(const Vec2& v) :
            Base({v.x, v.y},
                 Printer::width,
                 Printer::precision)
        {
        }

        explicit BracePrint(const Vec3& v) :
            Base({v.x, v.y, v.z},
                 Printer::width,
                 Printer::precision)
        {
        }

        explicit BracePrint(const Quat& v) :
            Base({v.w, v.x, v.y, v.z},
                 Printer::width,
                 Printer::precision)
        {
        }

        explicit BracePrint(const Vec4& v) :
            Base({v.x, v.y, v.z, v.w},
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

    void Printer::setPrecision(const U8 p)
    {
        precision = p;
        width     = precision * 2;
    }

    void Printer::print(const Vec2& v)
    {
        if (_output)
            Ts::println(*_output, BracePrint(v));
    }

    void Printer::print(const Vec3& v)
    {
        if (_output)
            Ts::println(*_output, BracePrint(v));
    }

    void Printer::print(const Mat3& v)
    {
        if (_output)
        {
            Ts::println(*_output, BracePrint(v.row(0)));
            Ts::println(*_output, BracePrint(v.row(1)));
            Ts::println(*_output, BracePrint(v.row(2)));
        }
    }

    void Printer::print(const Mat4& v)
    {
        if (_output)
        {
            Ts::println(*_output, BracePrint(v.row(0)));
            Ts::println(*_output, BracePrint(v.row(1)));
            Ts::println(*_output, BracePrint(v.row(2)));
            Ts::println(*_output, BracePrint(v.row(3)));
        }
    }

    void Printer::print(const Vec4& v)
    {
        if (_output)
            Ts::println(*_output, BracePrint(v));
    }

    void Printer::print(const Quat& v)
    {
        if (_output)
            Ts::println(*_output, BracePrint(v));
    }

    void Printer::print(const Box2d& v)
    {
        if (_output)
            Ts::println(*_output, BracePrint(v));
    }

    void Printer::print(const Rect& v)
    {
        if (_output)
            Ts::println(*_output, BracePrint(v));
    }

}  // namespace Rt2::Math
