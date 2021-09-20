#include "gtest/gtest.h"
#include "orientationGenerator.h"
#include <vector>
#include <iostream>
using namespace std;


TEST(orientationGeneratorTest, generateOrientationtTest) {
    orientationGenerator gen;

    const std::vector<cornersArray> expectedOrients = {
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 2 },
        { 0, 0, 0, 0, 2, 1 },
        { 0, 0, 0, 1, 0, 2 },
        { 0, 0, 0, 1, 1, 1 },
        { 0, 0, 0, 1, 2, 0 },
        { 0, 0, 0, 2, 0, 1 },
        { 0, 0, 0, 2, 1, 0 },
        { 0, 0, 0, 2, 2, 2 },
        { 0, 0, 1, 0, 0, 2 },
        { 0, 0, 1, 0, 1, 1 },
        { 0, 0, 1, 0, 2, 0 },
        { 0, 0, 1, 1, 0, 1 },
        { 0, 0, 1, 1, 1, 0 },
        { 0, 0, 1, 1, 2, 2 },
        { 0, 0, 1, 2, 0, 0 },
        { 0, 0, 1, 2, 1, 2 },
        { 0, 0, 1, 2, 2, 1 },
        { 0, 0, 2, 0, 0, 1 },
        { 0, 0, 2, 0, 1, 0 },
        { 0, 0, 2, 0, 2, 2 },
        { 0, 0, 2, 1, 0, 0 },
        { 0, 0, 2, 1, 1, 2 },
        { 0, 0, 2, 1, 2, 1 },
        { 0, 0, 2, 2, 0, 2 },
        { 0, 0, 2, 2, 1, 1 },
        { 0, 0, 2, 2, 2, 0 },
        { 0, 1, 0, 0, 0, 2 },
        { 0, 1, 0, 0, 1, 1 },
        { 0, 1, 0, 0, 2, 0 },
        { 0, 1, 0, 1, 0, 1 },
        { 0, 1, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 2, 2 },
        { 0, 1, 0, 2, 0, 0 },
        { 0, 1, 0, 2, 1, 2 },
        { 0, 1, 0, 2, 2, 1 },
        { 0, 1, 1, 0, 0, 1 },
        { 0, 1, 1, 0, 1, 0 },
        { 0, 1, 1, 0, 2, 2 },
        { 0, 1, 1, 1, 0, 0 },
        { 0, 1, 1, 1, 1, 2 },
        { 0, 1, 1, 1, 2, 1 },
        { 0, 1, 1, 2, 0, 2 },
        { 0, 1, 1, 2, 1, 1 },
        { 0, 1, 1, 2, 2, 0 },
        { 0, 1, 2, 0, 0, 0 },
        { 0, 1, 2, 0, 1, 2 },
        { 0, 1, 2, 0, 2, 1 },
        { 0, 1, 2, 1, 0, 2 },
        { 0, 1, 2, 1, 1, 1 },
        { 0, 1, 2, 1, 2, 0 },
        { 0, 1, 2, 2, 0, 1 },
        { 0, 1, 2, 2, 1, 0 },
        { 0, 1, 2, 2, 2, 2 },
        { 0, 2, 0, 0, 0, 1 },
        { 0, 2, 0, 0, 1, 0 },
        { 0, 2, 0, 0, 2, 2 },
        { 0, 2, 0, 1, 0, 0 },
        { 0, 2, 0, 1, 1, 2 },
        { 0, 2, 0, 1, 2, 1 },
        { 0, 2, 0, 2, 0, 2 },
        { 0, 2, 0, 2, 1, 1 },
        { 0, 2, 0, 2, 2, 0 },
        { 0, 2, 1, 0, 0, 0 },
        { 0, 2, 1, 0, 1, 2 },
        { 0, 2, 1, 0, 2, 1 },
        { 0, 2, 1, 1, 0, 2 },
        { 0, 2, 1, 1, 1, 1 },
        { 0, 2, 1, 1, 2, 0 },
        { 0, 2, 1, 2, 0, 1 },
        { 0, 2, 1, 2, 1, 0 },
        { 0, 2, 1, 2, 2, 2 },
        { 0, 2, 2, 0, 0, 2 },
        { 0, 2, 2, 0, 1, 1 },
        { 0, 2, 2, 0, 2, 0 },
        { 0, 2, 2, 1, 0, 1 },
        { 0, 2, 2, 1, 1, 0 },
        { 0, 2, 2, 1, 2, 2 },
        { 0, 2, 2, 2, 0, 0 },
        { 0, 2, 2, 2, 1, 2 },
        { 0, 2, 2, 2, 2, 1 }
    };

    auto orients = gen.generateOrientations();
    ASSERT_TRUE(size(orients) >= size(expectedOrients));
    for (uint8_t i = 0; i < size(expectedOrients); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}

TEST(orientationGeneratorTest, generateOrientationtWithLockedPiecesTest) {
    orientationGenerator gen;

    const std::vector<std::vector<cornersArray>> expectedOrients = {
        {{ 1, 0, 2, 0, 0, 0 },
         { 1, 0, 2, 0, 1, 2 },
         { 1, 0, 2, 0, 2, 1 },
         { 1, 0, 2, 1, 0, 2 },
         { 1, 0, 2, 1, 1, 1 },
         { 1, 0, 2, 1, 2, 0 },
         { 1, 0, 2, 2, 0, 1 },
         { 1, 0, 2, 2, 1, 0 },
         { 1, 0, 2, 2, 2, 2 }},

        {{ 0, 1, 0, 2, 0, 0 },
         { 0, 1, 0, 2, 1, 2 },
         { 0, 1, 0, 2, 2, 1 },
         { 1, 1, 0, 2, 0, 2 },
         { 1, 1, 0, 2, 1, 1 },
         { 1, 1, 0, 2, 2, 0 },
         { 2, 1, 0, 2, 0, 1 },
         { 2, 1, 0, 2, 1, 0 },
         { 2, 1, 0, 2, 2, 2 }},

        {{ 0, 0, 0, 0, 0, 0 },
         { 0, 0, 0, 0, 1, 2 },
         { 0, 0, 0, 0, 2, 1 },
         { 0, 0, 0, 1, 0, 2 },
         { 0, 0, 0, 1, 1, 1 },
         { 0, 0, 0, 1, 2, 0 },
         { 0, 0, 0, 2, 0, 1 },
         { 0, 0, 0, 2, 1, 0 },
         { 0, 0, 0, 2, 2, 2 },
         { 0, 0, 1, 0, 0, 2 },
         { 0, 0, 1, 0, 1, 1 },
         { 0, 0, 1, 0, 2, 0 },
         { 0, 0, 1, 1, 0, 1 },
         { 0, 0, 1, 1, 1, 0 },
         { 0, 0, 1, 1, 2, 2 },
         { 0, 0, 1, 2, 0, 0 },
         { 0, 0, 1, 2, 1, 2 },
         { 0, 0, 1, 2, 2, 1 },
         { 0, 0, 2, 0, 0, 1 },
         { 0, 0, 2, 0, 1, 0 },
         { 0, 0, 2, 0, 2, 2 },
         { 0, 0, 2, 1, 0, 0 },
         { 0, 0, 2, 1, 1, 2 },
         { 0, 0, 2, 1, 2, 1 },
         { 0, 0, 2, 2, 0, 2 },
         { 0, 0, 2, 2, 1, 1 },
         { 0, 0, 2, 2, 2, 0 },
         { 0, 1, 0, 0, 0, 2 },
         { 0, 1, 0, 0, 1, 1 },
         { 0, 1, 0, 0, 2, 0 },
         { 0, 1, 0, 1, 0, 1 },
         { 0, 1, 0, 1, 1, 0 },
         { 0, 1, 0, 1, 2, 2 },
         { 0, 1, 0, 2, 0, 0 },
         { 0, 1, 0, 2, 1, 2 },
         { 0, 1, 0, 2, 2, 1 },
         { 0, 1, 1, 0, 0, 1 },
         { 0, 1, 1, 0, 1, 0 },
         { 0, 1, 1, 0, 2, 2 },
         { 0, 1, 1, 1, 0, 0 },
         { 0, 1, 1, 1, 1, 2 },
         { 0, 1, 1, 1, 2, 1 },
         { 0, 1, 1, 2, 0, 2 },
         { 0, 1, 1, 2, 1, 1 },
         { 0, 1, 1, 2, 2, 0 },
         { 0, 1, 2, 0, 0, 0 },
         { 0, 1, 2, 0, 1, 2 },
         { 0, 1, 2, 0, 2, 1 },
         { 0, 1, 2, 1, 0, 2 },
         { 0, 1, 2, 1, 1, 1 },
         { 0, 1, 2, 1, 2, 0 },
         { 0, 1, 2, 2, 0, 1 },
         { 0, 1, 2, 2, 1, 0 },
         { 0, 1, 2, 2, 2, 2 },
         { 0, 2, 0, 0, 0, 1 },
         { 0, 2, 0, 0, 1, 0 },
         { 0, 2, 0, 0, 2, 2 },
         { 0, 2, 0, 1, 0, 0 },
         { 0, 2, 0, 1, 1, 2 },
         { 0, 2, 0, 1, 2, 1 },
         { 0, 2, 0, 2, 0, 2 },
         { 0, 2, 0, 2, 1, 1 },
         { 0, 2, 0, 2, 2, 0 },
         { 0, 2, 1, 0, 0, 0 },
         { 0, 2, 1, 0, 1, 2 },
         { 0, 2, 1, 0, 2, 1 },
         { 0, 2, 1, 1, 0, 2 },
         { 0, 2, 1, 1, 1, 1 },
         { 0, 2, 1, 1, 2, 0 },
         { 0, 2, 1, 2, 0, 1 },
         { 0, 2, 1, 2, 1, 0 },
         { 0, 2, 1, 2, 2, 2 },
         { 0, 2, 2, 0, 0, 2 },
         { 0, 2, 2, 0, 1, 1 },
         { 0, 2, 2, 0, 2, 0 },
         { 0, 2, 2, 1, 0, 1 },
         { 0, 2, 2, 1, 1, 0 },
         { 0, 2, 2, 1, 2, 2 },
         { 0, 2, 2, 2, 0, 0 },
         { 0, 2, 2, 2, 1, 2 },
         { 0, 2, 2, 2, 2, 1 }},
    };

    const std::vector<cornersArray> lockedPieces = {
        {  1,  0,  2, -1, -1, -1 },
        { -1,  1,  0,  2, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
    };

    for (uint8_t j = 0; j < size(lockedPieces); ++j) {
        auto orients = gen.generateOrientations(lockedPieces[j]);
        ASSERT_TRUE(size(orients) >= size(expectedOrients[j]));
        for (uint8_t i = 0; i < size(expectedOrients[j]); ++i) {
            ASSERT_EQ(expectedOrients[j][i], orients[i]);
        }
    }
}

TEST(orientationGeneratorTest, generateOrientationtWithIgnoredPiecesTest) {
    orientationGenerator gen;

    const std::vector<std::vector<cornersArray>> expectedOrients = {
        {{ -1, -1, -1, -1, -1, -1 }},

        {{ 0, 0, 0, 0, 0, 0 },
         { 0, 0, 0, 0, 1, 2 },
         { 0, 0, 0, 0, 2, 1 },
         { 0, 0, 0, 1, 0, 2 },
         { 0, 0, 0, 1, 1, 1 },
         { 0, 0, 0, 1, 2, 0 },
         { 0, 0, 0, 2, 0, 1 },
         { 0, 0, 0, 2, 1, 0 },
         { 0, 0, 0, 2, 2, 2 },
         { 0, 0, 1, 0, 0, 2 },
         { 0, 0, 1, 0, 1, 1 },
         { 0, 0, 1, 0, 2, 0 },
         { 0, 0, 1, 1, 0, 1 },
         { 0, 0, 1, 1, 1, 0 },
         { 0, 0, 1, 1, 2, 2 },
         { 0, 0, 1, 2, 0, 0 },
         { 0, 0, 1, 2, 1, 2 },
         { 0, 0, 1, 2, 2, 1 },
         { 0, 0, 2, 0, 0, 1 },
         { 0, 0, 2, 0, 1, 0 },
         { 0, 0, 2, 0, 2, 2 },
         { 0, 0, 2, 1, 0, 0 },
         { 0, 0, 2, 1, 1, 2 },
         { 0, 0, 2, 1, 2, 1 },
         { 0, 0, 2, 2, 0, 2 },
         { 0, 0, 2, 2, 1, 1 },
         { 0, 0, 2, 2, 2, 0 },
         { 0, 1, 0, 0, 0, 2 },
         { 0, 1, 0, 0, 1, 1 },
         { 0, 1, 0, 0, 2, 0 },
         { 0, 1, 0, 1, 0, 1 },
         { 0, 1, 0, 1, 1, 0 },
         { 0, 1, 0, 1, 2, 2 },
         { 0, 1, 0, 2, 0, 0 },
         { 0, 1, 0, 2, 1, 2 },
         { 0, 1, 0, 2, 2, 1 },
         { 0, 1, 1, 0, 0, 1 },
         { 0, 1, 1, 0, 1, 0 },
         { 0, 1, 1, 0, 2, 2 },
         { 0, 1, 1, 1, 0, 0 },
         { 0, 1, 1, 1, 1, 2 },
         { 0, 1, 1, 1, 2, 1 },
         { 0, 1, 1, 2, 0, 2 },
         { 0, 1, 1, 2, 1, 1 },
         { 0, 1, 1, 2, 2, 0 },
         { 0, 1, 2, 0, 0, 0 },
         { 0, 1, 2, 0, 1, 2 },
         { 0, 1, 2, 0, 2, 1 },
         { 0, 1, 2, 1, 0, 2 },
         { 0, 1, 2, 1, 1, 1 },
         { 0, 1, 2, 1, 2, 0 },
         { 0, 1, 2, 2, 0, 1 },
         { 0, 1, 2, 2, 1, 0 },
         { 0, 1, 2, 2, 2, 2 },
         { 0, 2, 0, 0, 0, 1 },
         { 0, 2, 0, 0, 1, 0 },
         { 0, 2, 0, 0, 2, 2 },
         { 0, 2, 0, 1, 0, 0 },
         { 0, 2, 0, 1, 1, 2 },
         { 0, 2, 0, 1, 2, 1 },
         { 0, 2, 0, 2, 0, 2 },
         { 0, 2, 0, 2, 1, 1 },
         { 0, 2, 0, 2, 2, 0 },
         { 0, 2, 1, 0, 0, 0 },
         { 0, 2, 1, 0, 1, 2 },
         { 0, 2, 1, 0, 2, 1 },
         { 0, 2, 1, 1, 0, 2 },
         { 0, 2, 1, 1, 1, 1 },
         { 0, 2, 1, 1, 2, 0 },
         { 0, 2, 1, 2, 0, 1 },
         { 0, 2, 1, 2, 1, 0 },
         { 0, 2, 1, 2, 2, 2 },
         { 0, 2, 2, 0, 0, 2 },
         { 0, 2, 2, 0, 1, 1 },
         { 0, 2, 2, 0, 2, 0 },
         { 0, 2, 2, 1, 0, 1 },
         { 0, 2, 2, 1, 1, 0 },
         { 0, 2, 2, 1, 2, 2 },
         { 0, 2, 2, 2, 0, 0 },
         { 0, 2, 2, 2, 1, 2 },
         { 0, 2, 2, 2, 2, 1 }},

        {{ -1, -1,  0,  0, -1, -1 },
         { -1, -1,  0,  1, -1, -1 },
         { -1, -1,  0,  2, -1, -1 },
         { -1, -1,  1,  0, -1, -1 },
         { -1, -1,  1,  1, -1, -1 },
         { -1, -1,  1,  2, -1, -1 },
         { -1, -1,  2,  0, -1, -1 },
         { -1, -1,  2,  1, -1, -1 },
         { -1, -1,  2,  2, -1, -1 }},
    };

    const std::vector<cornersArray> lockedPieces = {
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1 },
    };

    const std::vector<cornersArray> ignoredPieces = {
        { 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 1, 1 },
    };

    for (uint8_t j = 0; j < size(lockedPieces); ++j) {
        auto orients = gen.generateOrientations(lockedPieces[j], ignoredPieces[j]);
        for (uint8_t i = 0; i < size(expectedOrients[j]); ++i) {
            ASSERT_EQ(expectedOrients[j][i], orients[i]);
        }
    }
}


TEST(orientationGeneratorTest, generateOrientationtWithIgnoredAndLockedPiecesTest) {
    orientationGenerator gen;

    const std::vector<std::vector<cornersArray>> expectedOrients = {
        {{  1,  1,  1, -1, -1, -1 }},

        {{  1,  2,  1,  2, -1,  0 }},

        {{ -1,  2,  1,  2,  2,  1 }},
    };

    const std::vector<cornersArray> lockedPieces = {
        {  1,  1,  1, -1, -1, -1 },
        {  1,  2,  1,  2, -1, -1 },
        { -1,  2,  1,  2,  2,  1 },
    };

    const std::vector<cornersArray> ignoredPieces = {
        { 0, 0, 0, 1, 1, 1 },
        { 0, 0, 0, 0, 1, 0 },
        { 1, 0, 0, 0, 0, 0 },
    };

    for (uint8_t j = 0; j < size(lockedPieces); ++j) {
        auto orients = gen.generateOrientations(lockedPieces[j], ignoredPieces[j]);
        for (uint8_t i = 0; i < size(expectedOrients[j]); ++i) {
            ASSERT_EQ(expectedOrients[j][i], orients[i]);
        }
    }
}

