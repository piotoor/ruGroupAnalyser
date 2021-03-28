#include "gtest/gtest.h"
#include "ruCubeStateConverter.h"

#include <vector>
#include <iostream>


TEST(ruCubeStateConverterTest, convertVectCornersToInt) {
    ruCubeStateConverter conv;
    std::vector<uint8_t> cornersOrient = {
        0, 0, 0, 0, 0, 0
    };
    std::vector<uint8_t> cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    uint64_t expectedCorners = 0101112131415;
    auto corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        1, 1, 1, 1, 1, 1
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0202122232425;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        0, 1, 0, 1, 0, 1
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0102112231425;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 2, 2, 2, 2, 2
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0404142434445;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 0, 2, 0, 2, 0
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0401142134415;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 1, 2, 1, 2, 1
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0402142234425;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 1, 2, 1, 2, 1
    };
    cornersPerm = {
        5, 4, 3, 2, 1, 0
    };
    expectedCorners = 0452443224120;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 0, 2, 0, 2, 0
    };
    cornersPerm = {
        5, 4, 3, 2, 1, 0
    };
    expectedCorners = 0451443124110;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 1, 2, 1, 0, 0
    };
    cornersPerm = {
        5, 4, 3, 2, 1, 0
    };
    expectedCorners = 0452443221110;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 1, 2, 1, 0, 0
    };
    cornersPerm = {
        2, 4, 3, 1, 5, 0
    };
    expectedCorners = 0422443211510;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 1, 1, 0, 1, 1
    };
    cornersPerm = {
        0, 4, 3, 1, 2, 5
    };
    expectedCorners = 0402423112225;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);
}
