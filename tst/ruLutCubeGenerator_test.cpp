#include "gtest/gtest.h"
#include "ruLutCubeGenerator.h"
#include "ruCubeStateConverter.h"

TEST(ruLutCubeGeneratorTest, generateCubesWithLockedPiecesTest) {
    ruLutCubeGenerator generator;
    std::vector<int8_t> lockedCornersPerm { 0, 2, 4, 5 };
    std::vector<int8_t> ignoredCornersPerm {};
    std::vector<int8_t> lockedEdges { 0, 1, 2, 4, 6 };
    std::vector<int8_t> ignoredEdges {};
    std::vector<int8_t> lockedCornersOrient { 0, 0, 0, 0, -1, -1 };
    std::vector<int8_t> ignoredCornersOrient {};

    auto ruLutCubes = generator.generateCubes(  lockedEdges, ignoredEdges,
                                                lockedCornersPerm, ignoredCornersPerm,
                                                lockedCornersOrient, ignoredCornersOrient);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes {
        { 0101112131415, 00123456 },
        { 0101112132445, 00123456 },
        { 0101112134425, 00123456 }
    };

    ASSERT_EQ(size(ruLutCubes), size(expectedCubes));

    ruCubeStateConverter converter;

    for (uint8_t i = 0; i < size(expectedCubes); ++i ) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCubes[i].getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCubes[i].getCornersPerm(), ruLutCubes[i].getCornersOrient()));
    }

    lockedCornersPerm = { 0, 1, 2, 3 };    // 012345 012354
    ignoredCornersPerm = {};
    // 356
    lockedEdges = { 0, 1, 2, 4 };    // 00123456 00123465 00125436 00125463 00126435 00126453
    ignoredEdges = {};
    lockedCornersOrient = { -1, 0, 0, 0, -1, -1 };  // 000000 000012 000021 100002 100011 100020 200001 200010 200022
    ignoredCornersOrient = {};

    ruLutCubes = generator.generateCubes(   lockedEdges, ignoredEdges,
                                            lockedCornersPerm, ignoredCornersPerm,
                                            lockedCornersOrient, ignoredCornersOrient);

    expectedCubes = {
        { 0101112131415, 00123456 },
        { 0101112132445, 00123456 },
        { 0101112134425, 00123456 },

        { 0201112131445, 00123456 },
        { 0201112132425, 00123456 },
        { 0201112134415, 00123456 },

        { 0401112131425, 00123456 },
        { 0401112132415, 00123456 },
        { 0401112134445, 00123456 },
//--------------------------------------------
        { 0101112131415, 00125463 },
        { 0101112132445, 00125463 },
        { 0101112134425, 00125463 },

        { 0201112131445, 00125463 },
        { 0201112132425, 00125463 },
        { 0201112134415, 00125463 },

        { 0401112131425, 00125463 },
        { 0401112132415, 00125463 },
        { 0401112134445, 00125463 },
//--------------------------------------------
        { 0101112131415, 00126435 },
        { 0101112132445, 00126435 },
        { 0101112134425, 00126435 },

        { 0201112131445, 00126435 },
        { 0201112132425, 00126435 },
        { 0201112134415, 00126435 },

        { 0401112131425, 00126435 },
        { 0401112132415, 00126435 },
        { 0401112134445, 00126435 },
//--------------------------------------------
    };

    ASSERT_EQ(size(ruLutCubes), size(expectedCubes));

    for (uint8_t i = 0; i < size(expectedCubes); ++i ) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCubes[i].getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCubes[i].getCornersPerm(), ruLutCubes[i].getCornersOrient()));
    }
}

TEST(ruLutCubeGeneratorTest, generateCubesWithIgnoredPiecesTest) {
    ruLutCubeGenerator generator;
    std::vector<int8_t> lockedCornersPerm {  };
    std::vector<int8_t> ignoredCornersPerm { };
    std::vector<int8_t> lockedEdges { };
    std::vector<int8_t> ignoredEdges { };
    std::vector<int8_t> lockedCornersOrient { };
    std::vector<int8_t> ignoredCornersOrient { };

    auto ruLutCubes = generator.generateCubes(  lockedEdges, ignoredEdges,
                                                lockedCornersPerm, ignoredCornersPerm,
                                                lockedCornersOrient, ignoredCornersOrient);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes {
        { 0101112131415, 00123456 },
        { 0101112132445, 00123456 },
        { 0101112134425, 00123456 }
    };

    ASSERT_EQ(size(ruLutCubes), size(expectedCubes));

    ruCubeStateConverter converter;

    for (uint8_t i = 0; i < size(expectedCubes); ++i ) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCubes[i].getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCubes[i].getCornersPerm(), ruLutCubes[i].getCornersOrient()));
    }
}

TEST(ruLutCubeGeneratorTest, generateCubesWithLockedAndIgnoredPiecesTest) {
    ruLutCubeGenerator generator;

    ASSERT_TRUE(false);
}
