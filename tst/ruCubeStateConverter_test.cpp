#include "gtest/gtest.h"
#include "ruCubeStateConverter.h"

#include <vector>
#include <iostream>


TEST(ruCubeStateConverterTest, convertVectCornersToIntTest) {
    ruCubeStateConverter conv;
    std::vector<std::vector<int8_t>> cornersOrient = {
        { 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1 },
        { 0, 1, 0, 1, 0, 1 },
        { 2, 2, 2, 2, 2, 2 },
        { 2, 0, 2, 0, 2, 0 },
        { 2, 1, 2, 1, 2, 1 },
        { 2, 1, 2, 1, 2, 1 },
        { 2, 0, 2, 0, 2, 0 },
        { 2, 1, 2, 1, 0, 0 },
        { 2, 1, 2, 1, 0, 0 },
        { 2, 1, 1, 0, 1, 1 },
    };

    std::vector<std::vector<int8_t>> cornersPerm = {
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
        { 5, 4, 3, 2, 1, 0 },
        { 5, 4, 3, 2, 1, 0 },
        { 5, 4, 3, 2, 1, 0 },
        { 2, 4, 3, 1, 5, 0 },
        { 0, 4, 3, 1, 2, 5 },
    };

    std::vector<uint64_t> expectedCorners = {
        0101112131415,
        0202122232425,
        0102112231425,
        0404142434445,
        0401142134415,
        0402142234425,
        0452443224120,
        0451443124110,
        0452443221110,
        0422443211510,
        0402423112225,
    };

    for (uint8_t i = 0; i < std::size(cornersOrient); ++i) {
        auto corners = conv.vectCornersToInt(cornersPerm[i], cornersOrient[i]);
        ASSERT_EQ(expectedCorners[i], corners);
    }
}

TEST(ruCubeStateConverterTest, convertVectEdgesToIntTest) {
    ruCubeStateConverter conv;

    std::vector<std::vector<int8_t>> edgesPerm = {
        { 0, 1, 2, 3, 4, 5, 6 },
        { 6, 5, 4, 3, 2, 1, 0 },
        { 1, 3, 0, 2, 4, 5, 6 },
        { 6, 5, 1, 3, 4, 2, 0 },
        { 2, 0, 1, 3, 6, 4, 5 },
    };

    std::vector<uint64_t> expectedEdges = {
        00123456,
        06543210,
        01302456,
        06513420,
        02013645,
    };

    for (uint8_t i = 0; i < std::size(edgesPerm); ++i) {
        auto edges = conv.vectEdgesToInt(edgesPerm[i]);
        ASSERT_EQ(expectedEdges[i], edges);
    }
}

TEST(ruCubeStateConverterTest, convertVectCornersWithIgnoredPiecesToIntTest) {
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

TEST(ruCubeStateConverterTest, convertVectEdgesWithIgnoredPiecesToIntTest) {
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

TEST(ruCubeStateConverterTest, convertIntEdgesToEdgesLexIndexTest) {
    ruCubeStateConverter conv;

    std::vector<uint32_t> edgesInts = {
        0012345,
        0012354
    };


    std::vector<uint16_t> expectedEdgesLexIndices = {
        0,
        1
    };

    for (int i = 0; i < std::size(edgesInts); ++i) {
        uint16_t edgesLexIndex = conv.intEdgesToEdgesLexIndex(edgesInts[1]);
        ASSERT_EQ(expectedEdgesLexIndices[i], edgesLexIndex);
    }



}
