#include "gtest/gtest.h"
#include "ruCubeStateConverter.h"

#include <vector>
#include <iostream>


TEST(ruCubeStateConverterTest, convertVectCornersToInt) {
    ruCubeStateConverter conv;
    std::vector<int8_t> cornersOrient = {
        0, 0, 0, 0, 0, 0
    };
    std::vector<int8_t> cornersPerm = {
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

TEST(ruCubeStateConverterTest, convertVectEdgesToInt) {
    ruCubeStateConverter conv;

    std::vector<int8_t> edgesPerm = {
        0, 1, 2, 3, 4, 5, 6
    };
    uint32_t expectedEdges = 00123456;
    auto edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        6, 5, 4, 3, 2, 1, 0
    };
    expectedEdges = 06543210;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        1, 3, 0, 2, 4, 5, 6
    };
    expectedEdges = 01302456;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        6, 5, 1, 3, 4, 2, 0
    };
    expectedEdges = 06513420;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        2, 0, 1, 3, 6, 4, 5
    };
    expectedEdges = 02013645;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);
}

TEST(ruCubeStateConverterTest, convertVectCornersWithIgnoredPiecesToInt) {
    ruCubeStateConverter conv;
    std::vector<int8_t> cornersOrient = {
        0, 0, 0, 0, 0, 0
    };
    std::vector<int8_t> cornersPerm = {
        0, 1, 2, 3, -1, -1
    };
    uint64_t expectedCorners = 0101112131415;
    auto corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        -1, 1, 1, 1, 1, -1
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0402122232415;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
//    std::cout << "actual = " << std::oct << corners << std::endl;
//    std::cout << "expected = " << std::oct << expectedCorners << std::endl;
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        -1, 1, 1, 1, 1, -1
    };
    cornersPerm = {
        0, -1, -1, 3, 4, 5
    };
    expectedCorners = 0402122232415;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        -1, -1, -1, -1, -1, -1
    };
    cornersPerm = {
        0, 1, 2, 3, 4, 5
    };
    expectedCorners = 0101112131415;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        0, 0, 0, 0, 0, 0
    };
    cornersPerm = {
        -1, -1, -1, -1, -1, -1
    };
    expectedCorners = 0101112131415;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        -1, -1, -1, -1, -1, -1
    };
    cornersPerm = {
        -1, -1, -1, -1, -1, -1
    };
    expectedCorners = 0101112131415;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 2, 2, 2, 2, -1
    };
    cornersPerm = {
        -1, -1, -1, -1, -1, -1
    };
    expectedCorners = 0404142434445;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 2, 2, 1, 1, -1
    };
    cornersPerm = {
        -1, -1, -1, -1, -1, -1
    };
    expectedCorners = 0404142232425;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);



    cornersOrient = {
        2, 2, 2, 1, 1, 1
    };
    cornersPerm = {
        5, 4, 3, -1, -1, 1
    };
    expectedCorners = 0454443202221;
    corners = conv.vectCornersToInt(cornersPerm, cornersOrient);
    ASSERT_EQ(expectedCorners, corners);
}

TEST(ruCubeStateConverterTest, convertVectEdgesWithIgnoredPiecesToInt) {
    ruCubeStateConverter conv;

    std::vector<int8_t> edgesPerm = {
        0, 1, 2, 3, 4, 5, -1
    };
    uint32_t expectedEdges = 00123456;
    auto edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        6, 5, -1, 3, 2, 1, 0
    };
    expectedEdges = 06543210;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        6, 5, -1, -1, -1, -1, 0
    };
    expectedEdges = 06512340;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        -1, -1, -1, -1, -1, -1, 1
    };
    expectedEdges = 00234561;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);



    edgesPerm = {
        3, -1, 0, -1, -1, -1, 1
    };
    expectedEdges = 03204561;
    edges = conv.vectEdgesToInt(edgesPerm);
    ASSERT_EQ(expectedEdges, edges);
}
