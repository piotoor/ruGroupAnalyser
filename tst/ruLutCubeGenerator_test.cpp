#include "gtest/gtest.h"
#include "ruLutCubeGenerator.h"
#include "ruCubeStateConverter.h"

using cornersArray = std::array<int8_t, 6>;

TEST(ruLutCubeGeneratorTest, generateCubesTotalNumberOfCubesTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;

    const int expectedNumberOfCubes = 73'483'200;

    generator.init (params);

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

    generatorParameters params;
    params.lockedCornersPerm = { 0, 2, 4, 5 };
    params.ignoredCornersPerm = {};
    params.lockedEdges = { 0, 1, 2, 4, 6 };
    params.ignoredEdges = {};
    params.lockedCornersOrient = { 0, 0, 0, 0, -1, -1 };
    params.ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    generator.init (params);

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

    params.lockedCornersPerm = { 0, 1, 2, 3 };    // 012345 012354
    params.ignoredCornersPerm = {};

    params.lockedEdges = { 0, 1, 2, 4 };    // 00123456 00123465 00125436 00125463 00126435 00126453
    params.ignoredEdges = {};
    params.lockedCornersOrient = { -1, 0, 0, 0, -1, -1 };  // 000000 000012 000021 100002 100011 100020 200001 200010 200022
    params.ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    generator.init (params);

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

    generatorParameters params;
    params.lockedCornersPerm = { };
    params.ignoredCornersPerm = { 0, 1, 2, 3, 4 };
    params.lockedEdges = { };
    params.ignoredEdges = { 0, 2, 3, 4, 5, 6 };
    params.lockedCornersOrient = { -1, -1, -1, -1, -1, -1 };
    params.ignoredCornersOrient = { 1, 1, 1, 1, 1, 1 };

    generator.init(params);

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

    generatorParameters params;
    params.lockedCornersPerm = { 0, 3, 4 };
    params.ignoredCornersPerm = { 1, 2, 5,};
    params.lockedEdges = { 0 };
    params.ignoredEdges = { 1, 2, 3, 4, 5, 6 };
    params.lockedCornersOrient = { -1, -1, -1, -1, -1, -1 };
    params.ignoredCornersOrient = { 1, 1, 1, 1, 0, 0 };

    generator.init(params);

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
        const auto &[corners, edges] = expectedCubes[i];
        ASSERT_TRUE(generator.hasNext());
        auto ruLutCube = generator.next();
        ASSERT_EQ(edges, converter.lexIndexEdgesToIntEdges(ruLutCube.getEdges()));
        ASSERT_EQ(corners, converter.lexIndexCornersToIntCorners(ruLutCube.getCornersPerm(), ruLutCube.getCornersOrient()));
    }
    ASSERT_FALSE(generator.hasNext());
}

TEST(ruLutCubeGeneratorTest, generateCubesLastF2LPairTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;
    params.lockedCornersPerm = { 4 };
    params.ignoredCornersPerm = { 0, 1, 2, 3 };
    params.lockedEdges = { 4, 5 };
    params.ignoredEdges = { 0, 1, 2, 3 };
    params.lockedCornersOrient = { -1, -1, -1, -1, 0, -1 };
    params.ignoredCornersOrient = { 1, 1, 1, 1, 0, 0 };

    generator.init(params);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes = {
        { 0101112131415, 00123456 },
        { 0401112131425, 00123456 },
        { 0201112131445, 00123456 },
        { 0101112131415, 00136452 },
        { 0401112131425, 00136452 },
        { 0201112131445, 00136452 },
        { 0101112131415, 00162453 },
        { 0401112131425, 00162453 },
        { 0201112131445, 00162453 },
        { 0101112131415, 00613452 },
        { 0401112131425, 00613452 },
        { 0201112131445, 00613452 },
        { 0101112131415, 06012453 },
        { 0401112131425, 06012453 },
        { 0201112131445, 06012453 },
        { 0101211151413, 00123456 },
        { 0401211251413, 00123456 },
        { 0201211451413, 00123456 },
        { 0101211151413, 00136452 },
        { 0401211251413, 00136452 },
        { 0201211451413, 00136452 },
        { 0101211151413, 00162453 },
        { 0401211251413, 00162453 },
        { 0201211451413, 00162453 },
        { 0101211151413, 00613452 },
        { 0401211251413, 00613452 },
        { 0201211451413, 00613452 },
        { 0101211151413, 06012453 },
        { 0401211251413, 06012453 },
        { 0201211451413, 06012453 },
        { 0111015131412, 00123456 },
        { 0114025131412, 00123456 },
        { 0112045131412, 00123456 },
        { 0111015131412, 00136452 },
        { 0114025131412, 00136452 },
        { 0112045131412, 00136452 },
        { 0111015131412, 00162453 },
        { 0114025131412, 00162453 },
        { 0112045131412, 00162453 },
        { 0111015131412, 00613452 },
        { 0114025131412, 00613452 },
        { 0112045131412, 00613452 },
        { 0111015131412, 06012453 },
        { 0114025131412, 06012453 },
        { 0112045131412, 06012453 },
        { 0111510121413, 00123456 },
        { 0112540121413, 00123456 },
        { 0114520121413, 00123456 },
        { 0111510121413, 00136452 },
        { 0112540121413, 00136452 },
        { 0114520121413, 00136452 },
        { 0111510121413, 00162453 },
        { 0112540121413, 00162453 },
        { 0114520121413, 00162453 },
        { 0111510121413, 00613452 },
        { 0112540121413, 00613452 },
        { 0114520121413, 00613452 },
        { 0111510121413, 06012453 },
        { 0112540121413, 06012453 },
        { 0114520121413, 06012453 },
        { 0151113121410, 00123456 },
        { 0251113121440, 00123456 },
        { 0451113121420, 00123456 },
        { 0151113121410, 00136452 },
        { 0251113121440, 00136452 },
        { 0451113121420, 00136452 },
        { 0151113121410, 00162453 },
        { 0251113121440, 00162453 },
        { 0451113121420, 00162453 },
        { 0151113121410, 00613452 },
        { 0251113121440, 00613452 },
        { 0451113121420, 00613452 },
        { 0151113121410, 06012453 },
        { 0251113121440, 06012453 },
        { 0451113121420, 06012453 }
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

TEST(ruLutCubeGeneratorTest, generateCubesLLEdgesTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;
    params.lockedCornersPerm = { 0, 1, 2, 3, 4, 5 };
    params.ignoredCornersPerm = { };
    params.lockedEdges = { 4, 5, 6 };
    params.ignoredEdges = { };
    params.lockedCornersOrient = { 0, 0, 0, 0, 0, 0 };
    params.ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    generator.init(params);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes = {
        { 0101112131415, 00123456 },
        { 0101112131415, 00231456 },
        { 0101112131415, 00312456 },

        { 0101112131415, 01032456 },
        { 0101112131415, 01203456 },
        { 0101112131415, 01320456 },

        { 0101112131415, 02013456 },
        { 0101112131415, 02130456 },
        { 0101112131415, 02301456 },

        { 0101112131415, 03021456 },
        { 0101112131415, 03102456 },
        { 0101112131415, 03210456 },
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

TEST(ruLutCubeGeneratorTest, generateCubesLLCornersOrientationTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;
    params.lockedCornersPerm = { 0, 1, 2, 3, 4, 5 };
    params.ignoredCornersPerm = { };
    params.lockedEdges = { 0, 1, 2, 3, 4, 5, 6 };
    params.ignoredEdges = { };
    params.lockedCornersOrient = { -1, -1, -1, -1, 0, 0 };
    params.ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    generator.init(params);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes = {
        { 0101112131415, 0123456 },
        { 0101122431415, 0123456 },
        { 0101142231415, 0123456 },
        { 0102112431415, 0123456 },
        { 0102122231415, 0123456 },
        { 0102142131415, 0123456 },
        { 0104112231415, 0123456 },
        { 0104122131415, 0123456 },
        { 0104142431415, 0123456 },
        { 0201112431415, 0123456 },
        { 0201122231415, 0123456 },
        { 0201142131415, 0123456 },
        { 0202112231415, 0123456 },
        { 0202122131415, 0123456 },
        { 0202142431415, 0123456 },
        { 0204112131415, 0123456 },
        { 0204122431415, 0123456 },
        { 0204142231415, 0123456 },
        { 0401112231415, 0123456 },
        { 0401122131415, 0123456 },
        { 0401142431415, 0123456 },
        { 0402112131415, 0123456 },
        { 0402122431415, 0123456 },
        { 0402142231415, 0123456 },
        { 0404112431415, 0123456 },
        { 0404122231415, 0123456 },
        { 0404142131415, 0123456 },
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

