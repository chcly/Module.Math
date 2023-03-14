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
#include "Math/Box3d.h"
#include "Math/Color.h"
#include "Math/Mat3.h"
#include "Math/Rand.h"
#include "Math/Rect.h"
#include "Utils/Console.h"
#include "Utils/StreamMethods.h"
#include "gtest/gtest.h"

using namespace Rt2;
using namespace Math;

#ifdef RT_USE_SCALAR_DOUBLE
    #define EXPECT_REAL_EQ EXPECT_DOUBLE_EQ
#else
    #define EXPECT_REAL_EQ EXPECT_FLOAT_EQ
#endif

constexpr int Steps = 32;
constexpr int Lps   = Steps / 4;

GTEST_TEST(Math, Random_range)
{
    Rand::init();

    for (int i = 0; i < Steps; ++i)
    {
        const int r = Steps * (i + 1);

        const Real v = Rand::range(-r, r);
        EXPECT_GE(v, -r);
        EXPECT_LE(v, r);

        Console::print(Hex(v), ' ');
        if (i % Lps == Lps - 1)
            Console::nl();
    }
}

GTEST_TEST(Math, Random_unit)
{
    Rand::init();
    for (int i = 0; i < Steps; ++i)
    {
        const Real x = Rand::real();
        EXPECT_LE(x, 1);
        EXPECT_GE(x, 0);
    }
}

GTEST_TEST(Math, Random_u8)
{
    Rand::init();
    for (int i = 0; i < Steps; ++i)
    {
        const U8 x = Rand::u8();
        EXPECT_LE(x, 255);
        EXPECT_GE(x, 0);

        Console::print(Hex(x), ' ');
        if (i % Lps == Lps - 1)
            Console::nl();
    }
}

GTEST_TEST(Math, Rect_001)
{
    Rect r0{0, 0, 20, 20};
    EXPECT_REAL_EQ(r0.x, 0);
    EXPECT_REAL_EQ(r0.y, 0);
    EXPECT_REAL_EQ(r0.width, 20);
    EXPECT_REAL_EQ(r0.height, 20);
    r0.print();

    Rect r1;
    EXPECT_REAL_EQ(r1.x, 0);
    EXPECT_REAL_EQ(r1.y, 0);
    EXPECT_REAL_EQ(r1.width, Epsilon);
    EXPECT_REAL_EQ(r1.height, Epsilon);
    r1.print();

    Real n[4]{0, 0, 50, 50};

    const Rect r3(n);
    EXPECT_REAL_EQ(r3.x, 0);
    EXPECT_REAL_EQ(r3.y, 0);
    EXPECT_REAL_EQ(r3.width, 50);
    EXPECT_REAL_EQ(r3.height, 50);
    r3.print();

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

GTEST_TEST(Math, Matrix3_identity)
{
    Mat3 r0;
    EXPECT_EQ(r0, Mat3::Zero);
    r0.makeIdentity();
    EXPECT_EQ(r0, Mat3::Identity);
}

GTEST_TEST(Math, Matrix3_rotate90)
{
    for (int i = 0; i < Steps; ++i)
    {
        // Looking the +Z axis on the XY plane

        Mat3 r0;
        Vec3 result = Vec3(1, 0, 0);
        EXPECT_EQ(result, Vec3(1, 0, 0));

        r0.makeIdentity();
        r0.makeRotZ(PiH);
        r0.print();

        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, 1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(-1, 0, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, -1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(1, 0, 0));
    }

    for (int i = 0; i < Steps; ++i)
    {
        // Looking down the +Y axis on the ZX plane

        Mat3 r0;
        Vec3 result = Vec3(0, 0, 1);
        EXPECT_EQ(result, Vec3(0, 0, 1));

        r0.makeIdentity();
        r0.makeRotY(PiH);
        r0.print();

        result = r0 * result;
        EXPECT_EQ(result, Vec3(-1, 0, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, 0, -1));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(1, 0, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, 0, 1));
    }

    // Looking down the +X axis on the ZY plane
    for (int i = 0; i < Steps; ++i)
    {
        Mat3 r0;
        Vec3 result = Vec3(0, 0, 1);
        EXPECT_EQ(result, Vec3(0, 0, 1));

        r0.makeIdentity();
        r0.makeRotX(PiH);
        r0.print();

        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, -1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, 0, -1));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, 1, 0));
        result = r0 * result;
        EXPECT_EQ(result, Vec3(0, 0, 1));
    }

    for (int i = 0; i < Steps; ++i)
    {
        // Start, Looking down the +Y axis on the ZX plane

        Mat3 r0;
        Vec3 result = Vec3(0, 0, 1);
        EXPECT_EQ(result, Vec3(0, 0, 1));

        r0.makeIdentity();
        r0.makeRotY(-PiH);
        r0.print();

        result = r0 * result;
        EXPECT_EQ(result, Vec3(1, 0, 0));

        // Looking down the +Z axis on the YX plane
        Mat3 r1;
        r1.makeRotZ(PiH);

        result = r1 * result;
        EXPECT_EQ(result, Vec3(0, 1, 0));

        // Looking down the +X axis on the ZY plane

        Mat3 r2;
        r2.makeRotX(-PiH);

        result = r2 * result;
        EXPECT_EQ(result, Vec3(0, 0, -1));
    }
}

GTEST_TEST(Math, Matrix3_transpose)
{
    Mat3 r0{
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
    r0.print();

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
    r0.print();

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


GTEST_TEST(Math, Vector2_001)
{
    Math::Vec2 v2;
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
