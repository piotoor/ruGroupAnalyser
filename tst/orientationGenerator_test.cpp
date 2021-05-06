#include "gtest/gtest.h"
#include "orientationGenerator.h"

#include <vector>
#include <iostream>
using namespace std;


TEST(orientationGeneratorTest, generateOrientationtTest) {
    orientationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedOrients = {
        {{ }},

        {{ 0 }},

        {{ 0, 0 },
         { 1, 2 },
         { 2, 1 }},

        {{ 0, 0, 0 },
         { 0, 1, 2 },
         { 0, 2, 1 },
         { 1, 0, 2 },
         { 1, 1, 1 },
         { 1, 2, 0 },
         { 2, 0, 1 },
         { 2, 1, 0 },
         { 2, 2, 2 }},

        {{ 0, 0, 0, 0 },
         { 0, 0, 1, 2 },
         { 0, 0, 2, 1 },
         { 0, 1, 0, 2 },
         { 0, 1, 1, 1 },
         { 0, 1, 2, 0 },
         { 0, 2, 0, 1 },
         { 0, 2, 1, 0 },
         { 0, 2, 2, 2 },
         { 1, 0, 0, 2 },
         { 1, 0, 1, 1 },
         { 1, 0, 2, 0 },
         { 1, 1, 0, 1 },
         { 1, 1, 1, 0 },
         { 1, 1, 2, 2 },
         { 1, 2, 0, 0 },
         { 1, 2, 1, 2 },
         { 1, 2, 2, 1 },
         { 2, 0, 0, 1 },
         { 2, 0, 1, 0 },
         { 2, 0, 2, 2 },
         { 2, 1, 0, 0 },
         { 2, 1, 1, 2 },
         { 2, 1, 2, 1 },
         { 2, 2, 0, 2 },
         { 2, 2, 1, 1 },
         { 2, 2, 2, 0 }},

        {{ 0, 0, 0, 0, 0 },
         { 0, 0, 0, 1, 2 },
         { 0, 0, 0, 2, 1 },
         { 0, 0, 1, 0, 2 },
         { 0, 0, 1, 1, 1 },
         { 0, 0, 1, 2, 0 },
         { 0, 0, 2, 0, 1 },
         { 0, 0, 2, 1, 0 },
         { 0, 0, 2, 2, 2 },
         { 0, 1, 0, 0, 2 },
         { 0, 1, 0, 1, 1 },
         { 0, 1, 0, 2, 0 },
         { 0, 1, 1, 0, 1 },
         { 0, 1, 1, 1, 0 },
         { 0, 1, 1, 2, 2 },
         { 0, 1, 2, 0, 0 },
         { 0, 1, 2, 1, 2 },
         { 0, 1, 2, 2, 1 },
         { 0, 2, 0, 0, 1 },
         { 0, 2, 0, 1, 0 },
         { 0, 2, 0, 2, 2 },
         { 0, 2, 1, 0, 0 },
         { 0, 2, 1, 1, 2 },
         { 0, 2, 1, 2, 1 },
         { 0, 2, 2, 0, 2 },
         { 0, 2, 2, 1, 1 },
         { 0, 2, 2, 2, 0 },
         { 1, 0, 0, 0, 2 },
         { 1, 0, 0, 1, 1 },
         { 1, 0, 0, 2, 0 },
         { 1, 0, 1, 0, 1 },
         { 1, 0, 1, 1, 0 },
         { 1, 0, 1, 2, 2 },
         { 1, 0, 2, 0, 0 },
         { 1, 0, 2, 1, 2 },
         { 1, 0, 2, 2, 1 },
         { 1, 1, 0, 0, 1 },
         { 1, 1, 0, 1, 0 },
         { 1, 1, 0, 2, 2 },
         { 1, 1, 1, 0, 0 },
         { 1, 1, 1, 1, 2 },
         { 1, 1, 1, 2, 1 },
         { 1, 1, 2, 0, 2 },
         { 1, 1, 2, 1, 1 },
         { 1, 1, 2, 2, 0 },
         { 1, 2, 0, 0, 0 },
         { 1, 2, 0, 1, 2 },
         { 1, 2, 0, 2, 1 },
         { 1, 2, 1, 0, 2 },
         { 1, 2, 1, 1, 1 },
         { 1, 2, 1, 2, 0 },
         { 1, 2, 2, 0, 1 },
         { 1, 2, 2, 1, 0 },
         { 1, 2, 2, 2, 2 },
         { 2, 0, 0, 0, 1 },
         { 2, 0, 0, 1, 0 },
         { 2, 0, 0, 2, 2 },
         { 2, 0, 1, 0, 0 },
         { 2, 0, 1, 1, 2 },
         { 2, 0, 1, 2, 1 },
         { 2, 0, 2, 0, 2 },
         { 2, 0, 2, 1, 1 },
         { 2, 0, 2, 2, 0 },
         { 2, 1, 0, 0, 0 },
         { 2, 1, 0, 1, 2 },
         { 2, 1, 0, 2, 1 },
         { 2, 1, 1, 0, 2 },
         { 2, 1, 1, 1, 1 },
         { 2, 1, 1, 2, 0 },
         { 2, 1, 2, 0, 1 },
         { 2, 1, 2, 1, 0 },
         { 2, 1, 2, 2, 2 },
         { 2, 2, 0, 0, 2 },
         { 2, 2, 0, 1, 1 },
         { 2, 2, 0, 2, 0 },
         { 2, 2, 1, 0, 1 },
         { 2, 2, 1, 1, 0 },
         { 2, 2, 1, 2, 2 },
         { 2, 2, 2, 0, 0 },
         { 2, 2, 2, 1, 2 },
         { 2, 2, 2, 2, 1 }}
    };

    const std::vector<uint8_t> orientLengths { 0, 1, 2, 3, 4, 5 };

    for (uint8_t test = 0; test < size(expectedOrients); ++test) {
        auto perms = gen.generateOrientations(orientLengths[test]);
        ASSERT_EQ(expectedOrients[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedOrients[test].size(); ++i) {
            ASSERT_EQ(expectedOrients[test][i], perms[i]);
        }
    }
}

TEST(orientationGeneratorTest, generateOrientationtWithLockedPiecesTest) {
    orientationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedOrients = {
        {{ }},

        {{ 0 }},

        {{ 0, 0 },
         { 1, 2 },
         { 2, 1 }},

        {{ 1, 2 }},

        {{ 0, 0 },
         { 1, 2 },
         { 2, 1 }},

        {{ 0, 0, 0 },
         { 0, 1, 2 },
         { 0, 2, 1 },
         { 1, 0, 2 },
         { 1, 1, 1 },
         { 1, 2, 0 },
         { 2, 0, 1 },
         { 2, 1, 0 },
         { 2, 2, 2 }},

        {{ 0, 1, 2 },
         { 1, 0, 2 },
         { 2, 2, 2 }},

        {{ 0, 1, 2 }},

        {{ 1, 0, 2 }},

        {{ 1, 0, 2, 0, 0, 0 },
         { 1, 0, 2, 0, 1, 2 },
         { 1, 0, 2, 0, 2, 1 },
         { 1, 0, 2, 1, 0, 2 },
         { 1, 0, 2, 1, 1, 1 },
         { 1, 0, 2, 1, 2, 0 },
         { 1, 0, 2, 2, 0, 1 },
         { 1, 0, 2, 2, 1, 0 },
         { 1, 0, 2, 2, 2, 2 }},
    };

    const std::vector<std::vector<int8_t>> lockedPieces = {
        {  },
        {  },
        {  },
        { -1,  2 },
        { -1, -1 },
        { -1, -1, -1 },
        { -1, -1,  2 },
        {  0, -1,  2 },
        {  1,  0,  2 },
        {  1,  0,  2, -1, -1, -1 }
    };

    const std::vector<uint8_t> orientLengths { 0, 1, 2, 2, 2, 3, 3, 3, 3, 6 };

    for (uint8_t test = 0; test < size(expectedOrients); ++test) {
        auto perms = gen.generateOrientations(orientLengths[test], lockedPieces[test]);
        ASSERT_EQ(expectedOrients[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedOrients[test].size(); ++i) {
            ASSERT_EQ(expectedOrients[test][i], perms[i]);
        }
    }
}

TEST(orientationGeneratorTest, generateOrientationtWithIgnoredPiecesTest) {
    orientationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedOrients = {
        {{ }},

        {{ 0, 0, 0, 0, 0 },
         { 0, 0, 0, 1, 2 },
         { 0, 0, 0, 2, 1 },
         { 0, 0, 1, 0, 2 },
         { 0, 0, 1, 1, 1 },
         { 0, 0, 1, 2, 0 },
         { 0, 0, 2, 0, 1 },
         { 0, 0, 2, 1, 0 },
         { 0, 0, 2, 2, 2 },
         { 0, 1, 0, 0, 2 },
         { 0, 1, 0, 1, 1 },
         { 0, 1, 0, 2, 0 },
         { 0, 1, 1, 0, 1 },
         { 0, 1, 1, 1, 0 },
         { 0, 1, 1, 2, 2 },
         { 0, 1, 2, 0, 0 },
         { 0, 1, 2, 1, 2 },
         { 0, 1, 2, 2, 1 },
         { 0, 2, 0, 0, 1 },
         { 0, 2, 0, 1, 0 },
         { 0, 2, 0, 2, 2 },
         { 0, 2, 1, 0, 0 },
         { 0, 2, 1, 1, 2 },
         { 0, 2, 1, 2, 1 },
         { 0, 2, 2, 0, 2 },
         { 0, 2, 2, 1, 1 },
         { 0, 2, 2, 2, 0 },
         { 1, 0, 0, 0, 2 },
         { 1, 0, 0, 1, 1 },
         { 1, 0, 0, 2, 0 },
         { 1, 0, 1, 0, 1 },
         { 1, 0, 1, 1, 0 },
         { 1, 0, 1, 2, 2 },
         { 1, 0, 2, 0, 0 },
         { 1, 0, 2, 1, 2 },
         { 1, 0, 2, 2, 1 },
         { 1, 1, 0, 0, 1 },
         { 1, 1, 0, 1, 0 },
         { 1, 1, 0, 2, 2 },
         { 1, 1, 1, 0, 0 },
         { 1, 1, 1, 1, 2 },
         { 1, 1, 1, 2, 1 },
         { 1, 1, 2, 0, 2 },
         { 1, 1, 2, 1, 1 },
         { 1, 1, 2, 2, 0 },
         { 1, 2, 0, 0, 0 },
         { 1, 2, 0, 1, 2 },
         { 1, 2, 0, 2, 1 },
         { 1, 2, 1, 0, 2 },
         { 1, 2, 1, 1, 1 },
         { 1, 2, 1, 2, 0 },
         { 1, 2, 2, 0, 1 },
         { 1, 2, 2, 1, 0 },
         { 1, 2, 2, 2, 2 },
         { 2, 0, 0, 0, 1 },
         { 2, 0, 0, 1, 0 },
         { 2, 0, 0, 2, 2 },
         { 2, 0, 1, 0, 0 },
         { 2, 0, 1, 1, 2 },
         { 2, 0, 1, 2, 1 },
         { 2, 0, 2, 0, 2 },
         { 2, 0, 2, 1, 1 },
         { 2, 0, 2, 2, 0 },
         { 2, 1, 0, 0, 0 },
         { 2, 1, 0, 1, 2 },
         { 2, 1, 0, 2, 1 },
         { 2, 1, 1, 0, 2 },
         { 2, 1, 1, 1, 1 },
         { 2, 1, 1, 2, 0 },
         { 2, 1, 2, 0, 1 },
         { 2, 1, 2, 1, 0 },
         { 2, 1, 2, 2, 2 },
         { 2, 2, 0, 0, 2 },
         { 2, 2, 0, 1, 1 },
         { 2, 2, 0, 2, 0 },
         { 2, 2, 1, 0, 1 },
         { 2, 2, 1, 1, 0 },
         { 2, 2, 1, 2, 2 },
         { 2, 2, 2, 0, 0 },
         { 2, 2, 2, 1, 2 },
         { 2, 2, 2, 2, 1 }},

        {{ -1, -1, 0 },
         { -1, -1, 1 },
         { -1, -1, 2 }},

        {{ -1, -1, -1 }},

        {{ -1, 0, 0 },
         { -1, 0, 1 },
         { -1, 0, 2 },
         { -1, 1, 0 },
         { -1, 1, 1 },
         { -1, 1, 2 },
         { -1, 2, 0 },
         { -1, 2, 1 },
         { -1, 2, 2 }},

        {{ 0, -1, -1 },
         { 1, -1, -1 },
         { 2, -1, -1 }},

        {{ 0, -1, -1, 0 },
         { 0, -1, -1, 1 },
         { 0, -1, -1, 2 },
         { 1, -1, -1, 0 },
         { 1, -1, -1, 1 },
         { 1, -1, -1, 2 },
         { 2, -1, -1, 0 },
         { 2, -1, -1, 1 },
         { 2, -1, -1, 2 }}
    };

    const std::vector<std::vector<int8_t>> lockedPieces = {
        { },
        { },
        { },
        { },
        { },
        { },
        { }
    };

    const std::vector<std::vector<int8_t>> ignoredPieces = {
        { },
        { },
        { 1, 1, 0 },
        { 1, 1, 1 },
        { 1, 0, 0 },
        { 0, 1, 1 },
        { 0, 1, 1, 0 }
    };

    const std::vector<uint8_t> orientLengths { 0, 5, 3, 3, 3, 3, 4 };

    for (uint8_t test = 0; test < size(expectedOrients); ++test) {
        auto perms = gen.generateOrientations(orientLengths[test], lockedPieces[test], ignoredPieces[test]);
        ASSERT_EQ(expectedOrients[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedOrients[test].size(); ++i) {
            ASSERT_EQ(expectedOrients[test][i], perms[i]);
        }
    }
}

TEST(orientationGeneratorTest, generateOrientationtWithIgnoredAndLockedPiecesTest) {
    orientationGenerator gen;
    std::vector<int8_t> lockedPieces = {-1, -1, 2, 1};
    std::vector<int8_t> ignoredPieces = {1, 1, 0, 0};
    auto orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    std::vector<std::vector<int8_t>>  expectedOrients = {
        { -1, -1, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, 2, 1};
    ignoredPieces = {1, 0, 0, 0};
    orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, 1 },
        { -1, 1, 2, 1 },
        { -1, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, 2, -1};
    ignoredPieces = {1, 0, 0, 0};
    orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, 0 },
        { -1, 0, 2, 1 },
        { -1, 0, 2, 2 },
        { -1, 1, 2, 0 },
        { -1, 1, 2, 1 },
        { -1, 1, 2, 2 },
        { -1, 2, 2, 0 },
        { -1, 2, 2, 1 },
        { -1, 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, 2, -1, 1};
    ignoredPieces = {1, 0, 0, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, -1, 1},
        { -1, 1, 2, -1, 1},
        { -1, 2, 2, -1, 1}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }




    lockedPieces = {-1, -1, 2, -1, 1};
    ignoredPieces = {1, 0, 0, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, -1, 1},
        { -1, 1, 2, -1, 1},
        { -1, 2, 2, -1, 1}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, -1, -1, 0};
    ignoredPieces = {1, 0, 0, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 0, -1, 0},
        { -1, 0, 1, -1, 0},
        { -1, 0, 2, -1, 0},
        { -1, 1, 0, -1, 0},
        { -1, 1, 1, -1, 0},
        { -1, 1, 2, -1, 0},
        { -1, 2, 0, -1, 0},
        { -1, 2, 1, -1, 0},
        { -1, 2, 2, -1, 0}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, -1, -1, -1};
    ignoredPieces = {0, 0, 0, 0, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2 },
        { 0, 0, 0, 2, 1 },
        { 0, 0, 1, 0, 2 },
        { 0, 0, 1, 1, 1 },
        { 0, 0, 1, 2, 0 },
        { 0, 0, 2, 0, 1 },
        { 0, 0, 2, 1, 0 },
        { 0, 0, 2, 2, 2 },
        { 0, 1, 0, 0, 2 },
        { 0, 1, 0, 1, 1 },
        { 0, 1, 0, 2, 0 },
        { 0, 1, 1, 0, 1 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 1, 2, 2 },
        { 0, 1, 2, 0, 0 },
        { 0, 1, 2, 1, 2 },
        { 0, 1, 2, 2, 1 },
        { 0, 2, 0, 0, 1 },
        { 0, 2, 0, 1, 0 },
        { 0, 2, 0, 2, 2 },
        { 0, 2, 1, 0, 0 },
        { 0, 2, 1, 1, 2 },
        { 0, 2, 1, 2, 1 },
        { 0, 2, 2, 0, 2 },
        { 0, 2, 2, 1, 1 },
        { 0, 2, 2, 2, 0 },
        { 1, 0, 0, 0, 2 },
        { 1, 0, 0, 1, 1 },
        { 1, 0, 0, 2, 0 },
        { 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 0 },
        { 1, 0, 1, 2, 2 },
        { 1, 0, 2, 0, 0 },
        { 1, 0, 2, 1, 2 },
        { 1, 0, 2, 2, 1 },
        { 1, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 0 },
        { 1, 1, 0, 2, 2 },
        { 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 2 },
        { 1, 1, 1, 2, 1 },
        { 1, 1, 2, 0, 2 },
        { 1, 1, 2, 1, 1 },
        { 1, 1, 2, 2, 0 },
        { 1, 2, 0, 0, 0 },
        { 1, 2, 0, 1, 2 },
        { 1, 2, 0, 2, 1 },
        { 1, 2, 1, 0, 2 },
        { 1, 2, 1, 1, 1 },
        { 1, 2, 1, 2, 0 },
        { 1, 2, 2, 0, 1 },
        { 1, 2, 2, 1, 0 },
        { 1, 2, 2, 2, 2 },
        { 2, 0, 0, 0, 1 },
        { 2, 0, 0, 1, 0 },
        { 2, 0, 0, 2, 2 },
        { 2, 0, 1, 0, 0 },
        { 2, 0, 1, 1, 2 },
        { 2, 0, 1, 2, 1 },
        { 2, 0, 2, 0, 2 },
        { 2, 0, 2, 1, 1 },
        { 2, 0, 2, 2, 0 },
        { 2, 1, 0, 0, 0 },
        { 2, 1, 0, 1, 2 },
        { 2, 1, 0, 2, 1 },
        { 2, 1, 1, 0, 2 },
        { 2, 1, 1, 1, 1 },
        { 2, 1, 1, 2, 0 },
        { 2, 1, 2, 0, 1 },
        { 2, 1, 2, 1, 0 },
        { 2, 1, 2, 2, 2 },
        { 2, 2, 0, 0, 2 },
        { 2, 2, 0, 1, 1 },
        { 2, 2, 0, 2, 0 },
        { 2, 2, 1, 0, 1 },
        { 2, 2, 1, 1, 0 },
        { 2, 2, 1, 2, 2 },
        { 2, 2, 2, 0, 0 },
        { 2, 2, 2, 1, 2 },
        { 2, 2, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, -1, -1, 0};
    ignoredPieces = {1, 1, 1, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, -1, -1, -1, 0}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}
