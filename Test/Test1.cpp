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
#include "Math/BoundingBox.h"
#include "Math/Color.h"
#include "Math/Matrix3.h"
#include "Math/Random.h"
#include "Math/Rectangle.h"
#include "gtest/gtest.h"

using namespace Rt2;
using namespace Math;

#ifdef RT_USE_SCALAR_DOUBLE
    #define EXPECT_REAL_EQ EXPECT_DOUBLE_EQ
#else
    #define EXPECT_REAL_EQ EXPECT_FLOAT_EQ
#endif

constexpr int Steps = 32;

GTEST_TEST(Math, RandRange)
{
    initRandom();
    for (int i = 0; i < Steps; ++i)
    {
        const int x = randRange(-3, 3);
        EXPECT_LE(abs(x), 3);
    }
    for (int i = 0; i < Steps; ++i)
    {
        const int x = randRange(-256, Steps);
        if (x < 0)
            EXPECT_GE(x, -256);
        else
            EXPECT_LE(x, Steps);
    }
}

GTEST_TEST(Math, UnitRand)
{
    initRandom();
    for (int i = 0; i < Steps; ++i)
    {
        const Real x = RtAbs(RtCeil(unitRand()));
        EXPECT_LE((int32_t)x, 1);
    }
}

GTEST_TEST(Math, Rect_001)
{
    Math::Rectangle r0{0, 0, 20, 20};
    EXPECT_REAL_EQ(r0.x, 0);
    EXPECT_REAL_EQ(r0.y, 0);
    EXPECT_REAL_EQ(r0.width, 20);
    EXPECT_REAL_EQ(r0.height, 20);

    Math::Rectangle r1;
    EXPECT_REAL_EQ(r1.x, 0);
    EXPECT_REAL_EQ(r1.y, 0);
    EXPECT_REAL_EQ(r1.width, Epsilon);
    EXPECT_REAL_EQ(r1.height, Epsilon);

    Real n[4]{0, 0, 50, 50};

    const Math::Rectangle r3(n);
    EXPECT_REAL_EQ(r3.x, 0);
    EXPECT_REAL_EQ(r3.y, 0);
    EXPECT_REAL_EQ(r3.width, 50);
    EXPECT_REAL_EQ(r3.height, 50);

    r0 = r3;
    EXPECT_REAL_EQ(r3.x, 0);
    EXPECT_REAL_EQ(r3.y, 0);
    EXPECT_REAL_EQ(r3.width, 50);
    EXPECT_REAL_EQ(r3.height, 50);

    r0.setSize(Epsilon, Epsilon);
    (void)r0.center();
    (void)r0.cx();
    (void)r0.cy();
}

GTEST_TEST(Math, Matrix3_001)
{
    {
        Matrix3 r0;
        EXPECT_EQ(r0, Matrix3::Zero);
        r0.makeIdentity();
        EXPECT_EQ(r0, Matrix3::Identity);
    }

    for (int i = 0; i < Steps; ++i)
    {
        // Looking the +Z axis on the XY plane

        Matrix3 r0;
        Vector3 result = Vector3(1, 0, 0);
        EXPECT_EQ(result, Vector3(1, 0, 0));

        r0.makeIdentity();
        r0.makeRotZ(PiH);

        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, 1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(-1, 0, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, -1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(1, 0, 0));
    }

    for (int i = 0; i < Steps; ++i)
    {
        // Looking down the +Y axis on the ZX plane

        Matrix3 r0;
        Vector3 result = Vector3(0, 0, 1);
        EXPECT_EQ(result, Vector3(0, 0, 1));

        r0.makeIdentity();
        r0.makeRotY(PiH);

        result = r0 * result;
        EXPECT_EQ(result, Vector3(-1, 0, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, 0, -1));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(1, 0, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, 0, 1));
    }

    // Looking down the +X axis on the ZY plane
    for (int i = 0; i < Steps; ++i)
    {
        Matrix3 r0;
        Vector3 result = Vector3(0, 0, 1);
        EXPECT_EQ(result, Vector3(0, 0, 1));

        r0.makeIdentity();
        r0.makeRotX(PiH);

        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, -1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, 0, -1));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, 1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vector3(0, 0, 1));
    }

    for (int i = 0; i < Steps; ++i)
    {
        // Start, Looking down the +Y axis on the ZX plane

        Matrix3 r0;
        Vector3 result = Vector3(0, 0, 1);
        EXPECT_EQ(result, Vector3(0, 0, 1));

        r0.makeIdentity();
        r0.makeRotY(-PiH);

        result = r0 * result;
        EXPECT_EQ(result, Vector3(1, 0, 0));

        // Looking down the +Z axis on the YX plane
        Matrix3 r1;
        r1.makeRotZ(PiH);

        result = r1 * result;
        EXPECT_EQ(result, Vector3(0, 1, 0));

        // Looking down the +X axis on the ZY plane

        Matrix3 r2;
        r2.makeRotX(-PiH);

        result = r2 * result;
        EXPECT_EQ(result, Vector3(0, 0, -1));
    }
}

GTEST_TEST(Math, Matrix3_002)
{
    Matrix3 r0{
        (Real)'a',
        (Real)'b',
        (Real)'c',
        (Real)'d',
        (Real)'e',
        (Real)'f',
        (Real)'g',
        (Real)'h',
        (Real)'i',
    };

    r0.transpose();

    // a, d, g, b, e, h, c, f, i
    EXPECT_EQ(r0.m[0][0], (Real)'a');
    EXPECT_EQ(r0.m[0][1], (Real)'d');
    EXPECT_EQ(r0.m[0][2], (Real)'g');
    EXPECT_EQ(r0.m[1][0], (Real)'b');
    EXPECT_EQ(r0.m[1][1], (Real)'e');
    EXPECT_EQ(r0.m[1][2], (Real)'h');
    EXPECT_EQ(r0.m[2][0], (Real)'c');
    EXPECT_EQ(r0.m[2][1], (Real)'f');
    EXPECT_EQ(r0.m[2][2], (Real)'i');

    r0.transpose();

    // a, b, c, d, e, f, g, h, i
    EXPECT_EQ(r0.m[0][0], (Real)'a');
    EXPECT_EQ(r0.m[0][1], (Real)'b');
    EXPECT_EQ(r0.m[0][2], (Real)'c');
    EXPECT_EQ(r0.m[1][0], (Real)'d');
    EXPECT_EQ(r0.m[1][1], (Real)'e');
    EXPECT_EQ(r0.m[1][2], (Real)'f');
    EXPECT_EQ(r0.m[2][0], (Real)'g');
    EXPECT_EQ(r0.m[2][1], (Real)'h');
    EXPECT_EQ(r0.m[2][2], (Real)'i');
}

GTEST_TEST(Math, Color_001)
{
    const Color cv = {0, 0, 0, 1};
    uint8_t     r, g, b, a;
    cv.toBytes(r, g, b, a);

    EXPECT_EQ(0, r);
    EXPECT_EQ(0, g);
    EXPECT_EQ(0, b);
    EXPECT_EQ(255, a);

    uint32_t iv;
    cv.toInt(iv);
    EXPECT_EQ(0x000000FF, iv);
}
