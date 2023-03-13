#include <cstdio>
#include "ThisDir.h"
#include "gtest/gtest.h"
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

GTEST_TEST(Math, RandRange)
{
    RandInit();
    for (int i = 0; i < 64; ++i)
    {
        const int x = RandRange(-3, 3);
        EXPECT_LE(abs(x), 3);
    }
    for (int i = 0; i < 64; ++i)
    {
        const int x = RandRange(-256, 64);
        if (x < 0)
            EXPECT_GE(x, -256);
        else
            EXPECT_LE(x, 64);
    }
}

GTEST_TEST(Math, UnitRand)
{
    RandInit();
    for (int i = 0; i < 64; ++i)
    {
        const Scalar x = RtAbs(RtCeil(UnitRand()));
        EXPECT_LE((int32_t)x, 1);
    }
}

GTEST_TEST(Math, Rect_001)
{
    Math::Rectangle r0{0, 0, 20, 20};
    EXPECT_FLOAT_EQ(r0.x, 0);
    EXPECT_FLOAT_EQ(r0.y, 0);
    EXPECT_FLOAT_EQ(r0.width, 20);
    EXPECT_FLOAT_EQ(r0.height, 20);

    Math::Rectangle r1;
    EXPECT_FLOAT_EQ(r1.x, 0);
    EXPECT_FLOAT_EQ(r1.y, 0);
    EXPECT_FLOAT_EQ(r1.width, RT_EPSILON);
    EXPECT_FLOAT_EQ(r1.height, RT_EPSILON);

    float n[4]{0, 0, 50, 50};

    const Math::Rectangle r3(n);
    EXPECT_FLOAT_EQ(r3.x, 0);
    EXPECT_FLOAT_EQ(r3.y, 0);
    EXPECT_FLOAT_EQ(r3.width, 50);
    EXPECT_FLOAT_EQ(r3.height, 50);

    r0 = r3;
    EXPECT_FLOAT_EQ(r3.x, 0);
    EXPECT_FLOAT_EQ(r3.y, 0);
    EXPECT_FLOAT_EQ(r3.width, 50);
    EXPECT_FLOAT_EQ(r3.height, 50);

    r0.setSize(RT_EPSILON, RT_EPSILON);
    (void)r0.center();
    (void)r0.cx();
    (void)r0.cy();
}

GTEST_TEST(Math, Matrix3_001)
{
    Matrix3 r0;
    EXPECT_EQ(r0, Matrix3::Zero);
    r0.makeIdentity();
    EXPECT_EQ(r0, Matrix3::Identity);

    for (int i = 0; i < 100; ++i)
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

    for (int i = 0; i < 64; ++i)
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
    for (int i = 0; i < 64; ++i)
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

    for (int i = 0; i < 64; ++i)
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
        (float)'a',
        (float)'b',
        (float)'c',
        (float)'d',
        (float)'e',
        (float)'f',
        (float)'g',
        (float)'h',
        (float)'i',
    };

    r0.transpose();

    // a, d, g, b, e, h, c, f, i
    EXPECT_EQ(r0.m[0][0], (float)'a');
    EXPECT_EQ(r0.m[0][1], (float)'d');
    EXPECT_EQ(r0.m[0][2], (float)'g');
    EXPECT_EQ(r0.m[1][0], (float)'b');
    EXPECT_EQ(r0.m[1][1], (float)'e');
    EXPECT_EQ(r0.m[1][2], (float)'h');
    EXPECT_EQ(r0.m[2][0], (float)'c');
    EXPECT_EQ(r0.m[2][1], (float)'f');
    EXPECT_EQ(r0.m[2][2], (float)'i');

    r0.transpose();

    // a, b, c, d, e, f, g, h, i
    EXPECT_EQ(r0.m[0][0], (float)'a');
    EXPECT_EQ(r0.m[0][1], (float)'b');
    EXPECT_EQ(r0.m[0][2], (float)'c');
    EXPECT_EQ(r0.m[1][0], (float)'d');
    EXPECT_EQ(r0.m[1][1], (float)'e');
    EXPECT_EQ(r0.m[1][2], (float)'f');
    EXPECT_EQ(r0.m[2][0], (float)'g');
    EXPECT_EQ(r0.m[2][1], (float)'h');
    EXPECT_EQ(r0.m[2][2], (float)'i');
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
