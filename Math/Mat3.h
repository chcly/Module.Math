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
#include "Math/Vec3.h"

namespace Rt2::Math
{
    class Quat;
    class Mat4;

    /**
     *     [1, 0, 0]
     * I = [0, 1, 0]
     *     [0, 0, 1]
     *
     *      [1,  0,    0 ]
     * Rx = [0, cos, -sin]
     *      [0, sin,  cos]
     *
     *      [cos,  0, sin]
     * Ry = [0,    1, 0  ]
     *      [-sin, 0, cos]
     *
     *      [cos, -sin, 0]
     * Rz = [sin,  cos, 0]
     *      [0,     0,  1]
     */
    class Mat3
    {
    public:
        static const Mat3 Identity;
        static const Mat3 Zero;

        Real m[3][3]{};

    public:
        Mat3() = default;
        Mat3(const Mat3&) = default;

        explicit Mat3(const Real* v);

        explicit Mat3(const Mat4& m4)
        {
            this->fromMat4(m4);
        }

        Mat3(Real m00,
                Real m01,
                Real m02,
                Real m10,
                Real m11,
                Real m12,
                Real m20,
                Real m21,
                Real m22);

        Mat3 operator*(const Mat3& lhs) const;
        Vec3 operator*(const Vec3& v) const;

        bool operator==(const Mat3& rhs) const;


        void transpose()
        {
            *this = transposed();
        }

        Mat3 transposed() const;

        Vec3 row(int idx) const;

        Vec3 col(int idx) const;

        void makeIdentity();

        void fromAngles(Real pitch, Real yaw, Real roll);

        void fromAngles(const Vec3& dRot);

        void fromQuaternion(const Quat& q);

        void fromMat4(const Mat4& mat4By4);

        void makeRotX(Real theta);

        void makeRotY(Real theta);

        void makeRotZ(Real theta);

        void print() const;
    };

}  // namespace Rt2::Math
