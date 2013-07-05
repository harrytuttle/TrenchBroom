/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include "Mat.h"
#include "Quat.h"
#include "Vec.h"
#include "TrenchBroom.h"
#include "TestUtils.h"

TEST(MatTest, nullMatrix) {
    const Mat4x4d& m = Mat4x4d::Null;
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(0.0, m[c][r]);
        }
    }
}

TEST(MatTest, identityMatrix) {
    const Mat4x4d& m = Mat4x4d::Identity;
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            if (c == r)
                ASSERT_DOUBLE_EQ(1.0, m[c][r]);
            else
                ASSERT_DOUBLE_EQ(0.0, m[c][r]);
        }
    }
}

TEST(MatTest, rot90XCWMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot90XCW;
    const Vec4d& v = Vec4d::PosY;
    ASSERT_VEC_EQ(Vec4d::NegZ, m * v);
}

TEST(MatTest, rot90YCWMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot90YCW;
    const Vec4d& v = Vec4d::PosX;
    ASSERT_VEC_EQ(Vec4d::PosZ, m * v);
}

TEST(MatTest, rot90ZCWMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot90ZCW;
    const Vec4d& v = Vec4d::PosY;
    ASSERT_VEC_EQ(Vec4d::PosX, m * v);
}

TEST(MatTest, rot90XCCWMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot90XCCW;
    const Vec4d& v = Vec4d::PosY;
    ASSERT_VEC_EQ(Vec4d::PosZ, m * v);
}

TEST(MatTest, rot90YCCWMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot90YCCW;
    const Vec4d& v = Vec4d::PosX;
    ASSERT_VEC_EQ(Vec4d::NegZ, m * v);
}

TEST(MatTest, rot90ZCCWMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot90ZCCW;
    const Vec4d& v = Vec4d::PosX;
    ASSERT_VEC_EQ(Vec4d::PosY, m * v);
}

TEST(MatTest, rot180XMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot180X;
    const Vec4d& v = Vec4d::PosY;
    ASSERT_VEC_EQ(Vec4d::NegY, m * v);
}

TEST(MatTest, rot180YMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot180Y;
    const Vec4d& v = Vec4d::PosX;
    ASSERT_VEC_EQ(Vec4d::NegX, m * v);
}

TEST(MatTest, rot180ZMatrix) {
    const Mat4x4d& m = Mat4x4d::Rot180Z;
    const Vec4d& v = Vec4d::PosY;
    ASSERT_VEC_EQ(Vec4d::NegY, m * v);
}

TEST(MatTest, mirXMatrix) {
    const Mat4x4d& m = Mat4x4d::MirX;
    const Vec4d v(1.0, 1.0, 1.0, 0.0);
    ASSERT_VEC_EQ(Vec4d(-1.0, 1.0, 1.0, 0.0), m * v);
}

TEST(MatTest, mirYMatrix) {
    const Mat4x4d& m = Mat4x4d::MirY;
    const Vec4d v(1.0, 1.0, 1.0, 0.0);
    ASSERT_VEC_EQ(Vec4d(1.0, -1.0, 1.0, 0.0), m * v);
}

TEST(MatTest, mirZMatrix) {
    const Mat4x4d& m = Mat4x4d::MirZ;
    const Vec4d v(1.0, 1.0, 1.0, 0.0);
    ASSERT_VEC_EQ(Vec4d(1.0, 1.0, -1.0, 0.0), m * v);
}

TEST(MatTest, defaultConstructor) {
    const Mat4x4d m;
    ASSERT_MAT_EQ(Mat4x4d::Identity, m);
}

TEST(MatTest, 3x3Constructor) {
    const Mat3x3d m(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);
    ASSERT_DOUBLE_EQ(1.0, m[0][0]);
    ASSERT_DOUBLE_EQ(2.0, m[1][0]);
    ASSERT_DOUBLE_EQ(3.0, m[2][0]);
    ASSERT_DOUBLE_EQ(4.0, m[0][1]);
    ASSERT_DOUBLE_EQ(5.0, m[1][1]);
    ASSERT_DOUBLE_EQ(6.0, m[2][1]);
    ASSERT_DOUBLE_EQ(7.0, m[0][2]);
    ASSERT_DOUBLE_EQ(8.0, m[1][2]);
    ASSERT_DOUBLE_EQ(9.0, m[2][2]);
}

TEST(MatTest, 4x4Constructor) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    ASSERT_DOUBLE_EQ( 1.0, m[0][0]);
    ASSERT_DOUBLE_EQ( 2.0, m[1][0]);
    ASSERT_DOUBLE_EQ( 3.0, m[2][0]);
    ASSERT_DOUBLE_EQ( 4.0, m[3][0]);
    ASSERT_DOUBLE_EQ( 5.0, m[0][1]);
    ASSERT_DOUBLE_EQ( 6.0, m[1][1]);
    ASSERT_DOUBLE_EQ( 7.0, m[2][1]);
    ASSERT_DOUBLE_EQ( 8.0, m[3][1]);
    ASSERT_DOUBLE_EQ( 9.0, m[0][2]);
    ASSERT_DOUBLE_EQ(10.0, m[1][2]);
    ASSERT_DOUBLE_EQ(11.0, m[2][2]);
    ASSERT_DOUBLE_EQ(12.0, m[3][2]);
    ASSERT_DOUBLE_EQ(13.0, m[0][3]);
    ASSERT_DOUBLE_EQ(14.0, m[1][3]);
    ASSERT_DOUBLE_EQ(15.0, m[2][3]);
    ASSERT_DOUBLE_EQ(16.0, m[3][3]);
}

TEST(MatTest, copyConstructor) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n(m);
    ASSERT_MAT_EQ(m, n);
}

TEST(MatTest, assign) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n = m;
    ASSERT_MAT_EQ(m, n);
}

TEST(MatTest, negate) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n = -m;

    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(-m[c][r], n[c][r]);
        }
    }
}

TEST(MatTest, equal) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d o( 2.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    ASSERT_TRUE(m == n);
    ASSERT_FALSE(m == o);
}

TEST(MatTest, addMatrix) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d o = m + n;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] + n[c][r], o[c][r]);
        }
    }
}

TEST(MatTest, addMatrixAndAssign) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    Mat4x4d o = m;
    o += n;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] + n[c][r], o[c][r]);
        }
    }
}

TEST(MatTest, subtractMatrix) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d o = m - n;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] - n[c][r], o[c][r]);
        }
    }
}

TEST(MatTest, subtractMatrixAndAssign) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    Mat4x4d o = m;
    o -= n;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] - n[c][r], o[c][r]);
        }
    }
}

TEST(MatTest, multiplyWithMatrix) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d r( 91.0, 107.0, 110.0, 120.0,
                    207.0, 247.0, 254.0, 280.0,
                    323.0, 387.0, 398.0, 440.0,
                    439.0, 527.0, 542.0, 600.0);
    const Mat4x4d o = m * n;
    ASSERT_MAT_EQ(r, o);
}

TEST(MatTest, multiplyWithMatrixAndAssign) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d r( 91.0, 107.0, 110.0, 120.0,
                    207.0, 247.0, 254.0, 280.0,
                    323.0, 387.0, 398.0, 440.0,
                    439.0, 527.0, 542.0, 600.0);
    Mat4x4d o = m;
    o *= n;
    ASSERT_MAT_EQ(r, o);
}

TEST(MatTest, rightMultiplyWithScalar) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d o = m * 3.0;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] * 3.0, o[c][r]);
        }
    }
}

TEST(MatTest, leftMultiplyWithScalar) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d o = 3.0 * m;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] * 3.0, o[c][r]);
        }
    }
}

TEST(MatTest, rightMultiplyWithScalarAndAssign) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    Mat4x4d o = m;
    o *= 3.0;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] * 3.0, o[c][r]);
        }
    }
}

TEST(MatTest, divideByScalar) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d o = m / 3.0;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] / 3.0, o[c][r]);
        }
    }
}

TEST(MatTest, divideByScalarAndAssign) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    Mat4x4d o = m;
    o /= 3.0;
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r] / 3.0, o[c][r]);
        }
    }
}

TEST(MatTest, rightMultiplyIdentityMatrixWithVector) {
    const Vec4d v(1.0, 2.0, 3.0, 1.0);
    ASSERT_VEC_EQ(v, Mat4x4d::Identity * v);
}

TEST(MatTest, rightMultiplyWithVector) {
    const Vec4d v(1.0, 2.0, 3.0, 1.0);
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Vec4d r(18.0, 46.0, 74.0, 102.0);
    ASSERT_VEC_EQ(r, m * v);
}

TEST(MatTest, leftMultiplyIdentityMatrixWithVector) {
    const Vec4d v(1.0, 2.0, 3.0, 1.0);
    ASSERT_VEC_EQ(v, v * Mat4x4d::Identity);
}

TEST(MatTest, leftMultiplyWithVector) {
    const Vec4d v(1.0, 2.0, 3.0, 1.0);
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Vec4d r(51.0, 58.0, 65.0, 72.0);
    ASSERT_VEC_EQ(r, v * m);
}

TEST(MatTest, leftMultiplyWithVectorAndAssign) {
    ASSERT_TRUE(false);
}

TEST(MatTest, rightMultiplyWithVectorOneLessDimension) {
    ASSERT_TRUE(false);
}

TEST(MatTest, leftMultiplyWithVectorOneLessDimension) {
    ASSERT_TRUE(false);
}

TEST(MatTest, leftMultiplyWithVectorOneLessDimensionAndAssign) {
    ASSERT_TRUE(false);
}

TEST(MatTest, rightMultiplyWithListOfVectors) {
    ASSERT_TRUE(false);
}

TEST(MatTest, leftMultiplyWithListOfVectors) {
    ASSERT_TRUE(false);
}

TEST(MatTest, leftMultiplyWithListOfVectorsAndAssign) {
    ASSERT_TRUE(false);
}

TEST(MatTest, rightMultiplyWithListOfVectorsOneLessDimension) {
    ASSERT_TRUE(false);
}

TEST(MatTest, leftMultiplyWithListOfVectorsOneLessDimension) {
    ASSERT_TRUE(false);
}

TEST(MatTest, leftMultiplyWithListOfVectorsOneLessDimensionAndAssign) {
    ASSERT_TRUE(false);
}

TEST(MatTest, indexedAccess) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m.v[c][r], m[c][r]);
        }
    }
}

TEST(MatTest, equals) {
    const Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
                     5.0,  6.0,  7.0,  8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    const Mat4x4d n = m;
    const Mat4x4d o( 2.0,  2.0,  3.0,  4.0,
                     5.0,  8.0,  7.0,  8.0,
                     9.0, 11.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
    
    ASSERT_TRUE(m.equals(n));
    ASSERT_FALSE(m.equals(o));
}

TEST(MatTest, null) {
    ASSERT_TRUE(Mat4x4d::Null.null());
    ASSERT_FALSE(Mat4x4d::Identity.null());
}

TEST(MatTest, setIdentity) {
    Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
               5.0,  6.0,  7.0,  8.0,
               9.0, 10.0, 11.0, 12.0,
              13.0, 14.0, 15.0, 16.0);
    m.setIdentity();
    ASSERT_MAT_EQ(Mat4x4d::Identity, m);
}

TEST(MatTest, setNull) {
    Mat4x4d m( 1.0,  2.0,  3.0,  4.0,
               5.0,  6.0,  7.0,  8.0,
               9.0, 10.0, 11.0, 12.0,
              13.0, 14.0, 15.0, 16.0);
    m.setNull();
    ASSERT_MAT_EQ(Mat4x4d::Null, m);
}

TEST(MatTest, transposeMatrix) {
    Mat<double, 4, 4> m;
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            m[c][r] = static_cast<double>(c * 4 + r);
        }
    }
    
    Mat<double, 4, 4> t = m;
    transposeMatrix(t);
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            ASSERT_DOUBLE_EQ(m[c][r], t[r][c]);
        }
    }
}

TEST(MatTest, transposed) {
    Mat<double, 3, 4> m;
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 3; r++) {
            m[c][r] = static_cast<double>(c * 3 + r);
        }
    }
    
    const Mat<double, 4, 3> t = m.transposed();
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 3; r++) {
            ASSERT_DOUBLE_EQ(m[c][r], t[r][c]);
        }
    }
}

TEST(MatTest, buffer) {
    ASSERT_TRUE(false);
}

TEST(MatTest, minorMatrix) {
    ASSERT_TRUE(false);
}

TEST(MatTest, matrixDeterminant) {
    ASSERT_TRUE(false);
}

TEST(MatTest, adjoinMatrix) {
    ASSERT_TRUE(false);
}

TEST(MatTest, adjointMatrix) {
    ASSERT_TRUE(false);
}

TEST(MatTest, invertMatrix) {
    ASSERT_TRUE(false);
}

TEST(MatTest, invertedMatrix) {
    ASSERT_TRUE(false);
}

TEST(MatTest, rotationMatrixWithAngleAndAxis) {
    ASSERT_TRUE(false);
}

TEST(MatTest, rotationMatrixWithQuaternion) {
    ASSERT_TRUE(false);
}

TEST(MatTest, translationMatrix) {
    const Vec3d v(2.0, 3.0, 4.0);
    const Mat4x4d t = translationMatrix(v);
    
    ASSERT_VEC_EQ(t[0], Vec4d::PosX);
    ASSERT_VEC_EQ(t[1], Vec4d::PosY);
    ASSERT_VEC_EQ(t[2], Vec4d::PosZ);
    ASSERT_VEC_EQ(t[3], Vec4d(v, 1.0));
}

TEST(MatTest, scalingMatrix) {
    const Vec3d v(2.0, 3.0, 4.0);
    const Mat4x4d t = scalingMatrix(v);
    
    for (size_t c = 0; c < 4; c++) {
        for (size_t r = 0; r < 4; r++) {
            if (c == r) {
                if (c < 3)
                    ASSERT_DOUBLE_EQ(v[c], t[c][r]);
                else
                    ASSERT_DOUBLE_EQ(1.0, t[c][r]);
            } else {
                ASSERT_DOUBLE_EQ(0.0, t[c][r]);
            }
        }
    }
}