#include "gtest/gtest.h"
#include "ruLutCubeGenerator.h"
#include "ruCubeStateConverter.h"

using cornersArray = std::array<int8_t, 6>;

TEST(ruLutCubeGeneratorTest, generateCubesTotalNumberOfCubesTest) {
    ruLutCubeGenerator generator;
    std::vector<int8_t> lockedCornersPerm { };
    std::vector<int8_t> ignoredCornersPerm { };
    std::vector<int8_t> lockedEdges { };
    std::vector<int8_t> ignoredEdges { };
    cornersArray lockedCornersOrient { -1, -1, -1, -1, -1, -1 };
    cornersArray ignoredCornersOrient { 0, 0, 0, 0, 0, 0 };

    const int expectedNumberOfCubes = 73'483'200;

    generator.init (lockedEdges, ignoredEdges,
                    lockedCornersPerm, ignoredCornersPerm,
                    lockedCornersOrient, ignoredCornersOrient);

    int i = 0;
    for (; i < expectedNumberOfCubes; ++i ) {

        ASSERT_TRUE(generator.hasNext());
        auto ruLutCube = generator.next();
    }
    std::cout << "Total number of cubes: " << (int) i << std::endl;
    ASSERT_FALSE(generator.hasNext());
}

TEST(ruLutCubeGeneratorTest, generateCubesWithLockedPiecesTest) {
    ruLutCubeGenerator generator;
    std::vector<int8_t> lockedCornersPerm { 0, 2, 4, 5 };
    std::vector<int8_t> ignoredCornersPerm {};
    std::vector<int8_t> lockedEdges { 0, 1, 2, 4, 6 };
    std::vector<int8_t> ignoredEdges {};
    cornersArray lockedCornersOrient { 0, 0, 0, 0, -1, -1 };
    cornersArray ignoredCornersOrient { 0, 0, 0, 0, 0, 0 };

    generator.init (lockedEdges, ignoredEdges,
                    lockedCornersPerm, ignoredCornersPerm,
                    lockedCornersOrient, ignoredCornersOrient);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes {
        { 0101112131415, 00123456 },
        { 0101112132445, 00123456 },
        { 0101112134425, 00123456 }
    };

    ruCubeStateConverter converter;

    for (uint32_t i = 0; i < size(expectedCubes); ++i ) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_TRUE(generator.hasNext());
        auto ruLutCube = generator.next();
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCube.getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCube.getCornersPerm(), ruLutCube.getCornersOrient()));
    }
    ASSERT_FALSE(generator.hasNext());

    lockedCornersPerm = { 0, 1, 2, 3 };    // 012345 012354
    ignoredCornersPerm = {};

    lockedEdges = { 0, 1, 2, 4 };    // 00123456 00123465 00125436 00125463 00126435 00126453
    ignoredEdges = {};
    lockedCornersOrient = { -1, 0, 0, 0, -1, -1 };  // 000000 000012 000021 100002 100011 100020 200001 200010 200022
    ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    generator.init (lockedEdges, ignoredEdges,
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

    for (uint32_t i = 0; i < size(expectedCubes); ++i ) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_TRUE(generator.hasNext());
        auto ruLutCube = generator.next();
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCube.getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCube.getCornersPerm(), ruLutCube.getCornersOrient()));
    }
    ASSERT_FALSE(generator.hasNext());
}

TEST(ruLutCubeGeneratorTest, generateCubesWithIgnoredPiecesTest) {
    ruLutCubeGenerator generator;
    std::vector<int8_t> lockedCornersPerm { };
    std::vector<int8_t> ignoredCornersPerm { 0, 1, 2, 3, 4 };
    std::vector<int8_t> lockedEdges { };
    std::vector<int8_t> ignoredEdges { 0, 2, 3, 4, 5, 6 };
    cornersArray lockedCornersOrient { -1, -1, -1, -1, -1, -1 };
    cornersArray ignoredCornersOrient { 1, 1, 1, 1, 1, 1 };

    generator.init( lockedEdges, ignoredEdges,
                    lockedCornersPerm, ignoredCornersPerm,
                    lockedCornersOrient, ignoredCornersOrient);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes {
        { 0101112131415, 00234651 },
        { 0101112131415, 00234516 },
        { 0101112131415, 00234165 },
        { 0101112131415, 00231456 },
        { 0101112131415, 00213465 },
        { 0101112131415, 00123456 },
        { 0101112131415, 01023465 },
        { 0101213141511, 00234651 },
        { 0101213141511, 00234516 },
        { 0101213141511, 00234165 },
        { 0101213141511, 00231456 },
        { 0101213141511, 00213465 },
        { 0101213141511, 00123456 },
        { 0101213141511, 01023465 },
        { 0101211151413, 00234651 },
        { 0101211151413, 00234516 },
        { 0101211151413, 00234165 },
        { 0101211151413, 00231456 },
        { 0101211151413, 00213465 },
        { 0101211151413, 00123456 },
        { 0101211151413, 01023465 },
        { 0101115141312, 00234651 },
        { 0101115141312, 00234516 },
        { 0101115141312, 00234165 },
        { 0101115141312, 00231456 },
        { 0101115141312, 00213465 },
        { 0101115141312, 00123456 },
        { 0101115141312, 01023465 },
        { 0101511121314, 00234651 },
        { 0101511121314, 00234516 },
        { 0101511121314, 00234165 },
        { 0101511121314, 00231456 },
        { 0101511121314, 00213465 },
        { 0101511121314, 00123456 },
        { 0101511121314, 01023465 },
        { 0151011131214, 00234651 },
        { 0151011131214, 00234516 },
        { 0151011131214, 00234165 },
        { 0151011131214, 00231456 },
        { 0151011131214, 00213465 },
        { 0151011131214, 00123456 },
        { 0151011131214, 01023465 }
    };

    ruCubeStateConverter converter;

    for (uint32_t i = 0; i < size(expectedCubes); ++i ) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_TRUE(generator.hasNext());
        auto ruLutCube = generator.next();
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCube.getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCube.getCornersPerm(), ruLutCube.getCornersOrient()));
    }

    ASSERT_FALSE(generator.hasNext());
}

TEST(ruLutCubeGeneratorTest, generateCubesWithLockedAndIgnoredPiecesTest) {
    ruLutCubeGenerator generator;
    std::vector<int8_t> lockedCornersPerm { 0, 3, 4 };
    std::vector<int8_t> ignoredCornersPerm { 1, 2, 5,};
    std::vector<int8_t> lockedEdges { 0 };
    std::vector<int8_t> ignoredEdges { 1, 2, 3, 4, 5, 6 };
    cornersArray lockedCornersOrient { -1, -1, -1, -1, -1, -1 };
    cornersArray ignoredCornersOrient { 1, 1, 1, 1, 0, 0 };

    generator.init( lockedEdges, ignoredEdges,
                    lockedCornersPerm, ignoredCornersPerm,
                    lockedCornersOrient, ignoredCornersOrient);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes {
        { 0101112131415, 00123456 },
        { 0401112131425, 00123456 },
        { 0201112131445, 00123456 },
        { 0401112132415, 00123456 },

        { 0201112132425, 00123456 },
        { 0101112132445, 00123456 },
        { 0201112134415, 00123456 },
        { 0101112134425, 00123456 },

        { 0401112134445, 00123456 },
    };

    ruCubeStateConverter converter;

    for (uint32_t i = 0; i < size(expectedCubes); ++i ) {
    //while (generator.hasNext()) {
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_TRUE(generator.hasNext());
        auto ruLutCube = generator.next();
//        std::cout << std::oct << converter.lexIndexCornersToIntCorners(ruLutCube.getCornersPerm(), ruLutCube.getCornersOrient()) << " "
//                    << converter.lexIndexEdgesToIntEdges(ruLutCube.getEdges()) << std::endl;
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCube.getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCube.getCornersPerm(), ruLutCube.getCornersOrient()));
    }

    ASSERT_FALSE(generator.hasNext());
}
