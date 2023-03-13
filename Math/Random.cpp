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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Math/Scalar.h"
#include "Utils/Definitions.h"

#if _WIN32
#include <Windows.h>
#include <limits>
#else
#include <sys/time.h>
#endif
#undef max

namespace Rt2::Math
{
    void initRandom()
    {
        // If seed is set to 1, the generator is reinitialized to its initial
        // value and produces the same values as before any call to
#if _WIN32
        const uint64_t t64 = (ULONGLONG) GetTickCount64();
        uint32_t seed = t64 % Npos32;
        if (seed == 1)
            seed++;

        srand(seed);
#else
        struct timeval now;
        gettimeofday(&now, nullptr);
        srand((now.tv_sec) / 1000);
#endif
    }

    Real unsignedUnitRand()
    {
        return Real(rand()) / Real(RAND_MAX);
    }

    Real unitRand()
    {
        return Real(2.0) * unsignedUnitRand() - Real(1.0);
    }

    int32_t randRange(const int32_t rmi, const int32_t rma)
    {
        return int32_t((Real(rma) - Real(rmi)) * unsignedUnitRand() + Real(rmi));
    }

}  // namespace Rt2::Math
