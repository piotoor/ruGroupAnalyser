#include "gtest/gtest.h"
#include "ruCubeStateConverter.h"

#include <vector>
#include <iostream>


TEST(ruCubeStateConverterTest, convertVectCornersToIntTest) {
    ruCubeStateConverter conv;
    const std::vector<std::vector<int8_t>> cornersOrient = {
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

    const std::vector<std::vector<int8_t>> cornersPerm = {
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

    const std::vector<uint64_t> expectedCorners = {
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

    const std::vector<std::vector<int8_t>> edgesPerm = {
        { 0, 1, 2, 3, 4, 5, 6 },
        { 6, 5, 4, 3, 2, 1, 0 },
        { 1, 3, 0, 2, 4, 5, 6 },
        { 6, 5, 1, 3, 4, 2, 0 },
        { 2, 0, 1, 3, 6, 4, 5 },
    };

    const std::vector<uint64_t> expectedEdges = {
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

    const std::vector<std::vector<int8_t>> cornersOrient = {
        {  0,  0,  0,  0,  0,  0 },
        { -1,  1,  1,  1,  1, -1 },
        { -1,  1,  1,  1,  1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        {  0,  0,  0,  0,  0,  0 },
        { -1, -1, -1, -1, -1, -1 },
        {  2,  2,  2,  2,  2, -1 },
        {  2,  2,  2,  1,  1, -1 },
        {  2,  2,  2,  1,  1,  1 },
    };
    const std::vector<std::vector<int8_t>> cornersPerm = {
        {  0,  1,  2,  3, -1, -1 },
        {  0,  1,  2,  3,  4,  5 },
        {  0, -1, -1,  3,  4,  5 },
        {  0,  1,  2,  3,  4,  5 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        {  5,  4,  3, -1, -1,  1 },
    };

    const std::vector<uint64_t> expectedCorners = {
        0101112131415,
        0402122232415,
        0402122232415,
        0101112131415,
        0101112131415,
        0101112131415,
        0404142434445,
        0404142232425,
        0454443202221,
    };

    for (uint8_t i = 0; i < std::size(cornersPerm); ++i) {
        auto corners = conv.vectCornersToInt(cornersPerm[i], cornersOrient[i]);
        ASSERT_EQ(expectedCorners[i], corners);
    }

}

TEST(ruCubeStateConverterTest, convertVectEdgesWithIgnoredPiecesToIntTest) {
    ruCubeStateConverter conv;

    const std::vector<std::vector<int8_t>> edgesPerm = {
        {  0,  1,  2,  3,  4,  5, -1 },
        {  6,  5, -1,  3,  2,  1,  0 },
        {  6,  5, -1, -1, -1, -1,  0 },
        { -1, -1, -1, -1, -1, -1,  1 },
        {  3, -1,  0, -1, -1, -1,  1 },
    };

    const std::vector<uint64_t> expectedEdges = {
        00123456,
        06543210,
        06512340,
        00234561,
        03204561,
    };

    for (uint8_t i = 0; i < std::size(edgesPerm); ++i) {
        auto edges = conv.vectEdgesToInt(edgesPerm[i]);
        ASSERT_EQ(expectedEdges[i], edges);
    }
}

TEST(ruCubeStateConverterTest, convertIntEdgesToEdgesLexIndexTest) {
    ruCubeStateConverter conv;

    const std::vector<uint32_t> edgesInts = {
        0012345,
        0012354
    };


    const std::vector<uint16_t> expectedEdgesLexIndices = {
        0,
        1
    };

    for (int i = 0; i < std::size(edgesInts); ++i) {
        uint16_t edgesLexIndex = conv.intEdgesToEdgesLexIndex(edgesInts[1]);
        ASSERT_EQ(expectedEdgesLexIndices[i], edgesLexIndex);
    }
}
