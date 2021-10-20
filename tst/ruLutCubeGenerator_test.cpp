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
        { 0101114121513, 00234561 },
        { 0101114121513, 00234615 },
        { 0101114121513, 00234156 },
        { 0101114121513, 00231465 },
        { 0101114121513, 00213456 },
        { 0101114121513, 00123465 },
        { 0101114121513, 01023456 },
        { 0101113151214, 00234561 },
        { 0101113151214, 00234615 },
        { 0101113151214, 00234156 },
        { 0101113151214, 00231465 },
        { 0101113151214, 00213456 },
        { 0101113151214, 00123465 },
        { 0101113151214, 01023456 },
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
        { 0151011131214, 01023465 },
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
        { 0101315121411, 00132456 },
        { 0401325121411, 00132456 },
        { 0201345121411, 00132456 },
        { 0101315121411, 00126453 },
        { 0401325121411, 00126453 },
        { 0201345121411, 00126453 },
        { 0101315121411, 00163452 },
        { 0401325121411, 00163452 },
        { 0201345121411, 00163452 },
        { 0101315121411, 00612453 },
        { 0401325121411, 00612453 },
        { 0201345121411, 00612453 },
        { 0101315121411, 06013452 },
        { 0401325121411, 06013452 },
        { 0201345121411, 06013452 },
        { 0101513111412, 00132456 },
        { 0402513111412, 00132456 },
        { 0204513111412, 00132456 },
        { 0101513111412, 00126453 },
        { 0402513111412, 00126453 },
        { 0204513111412, 00126453 },
        { 0101513111412, 00163452 },
        { 0402513111412, 00163452 },
        { 0204513111412, 00163452 },
        { 0101513111412, 00612453 },
        { 0402513111412, 00612453 },
        { 0204513111412, 00612453 },
        { 0101513111412, 06013452 },
        { 0402513111412, 06013452 },
        { 0204513111412, 06013452 },
        { 0151012111413, 00132456 },
        { 0254012111413, 00132456 },
        { 0452012111413, 00132456 },
        { 0151012111413, 00126453 },
        { 0254012111413, 00126453 },
        { 0452012111413, 00126453 },
        { 0151012111413, 00163452 },
        { 0254012111413, 00163452 },
        { 0452012111413, 00163452 },
        { 0151012111413, 00612453 },
        { 0254012111413, 00612453 },
        { 0452012111413, 00612453 },
        { 0151012111413, 06013452 },
        { 0254012111413, 06013452 },
        { 0452012111413, 06013452 },
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

TEST(ruLutCubeGeneratorTest, generateCubesRUCornersPermOnlyTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;
    params.lockedCornersPerm = { };
    params.ignoredCornersPerm = { };
    params.lockedEdges = { };
    params.ignoredEdges = { 0, 1, 2, 3, 4, 5, 6 };
    params.lockedCornersOrient = { -1, -1, -1, -1, -1, -1 };
    params.ignoredCornersOrient = { 1, 1, 1, 1, 1, 1 };

    generator.init(params);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes = {
        { 0101112131415, 0123456 },
        { 0101113151214, 0123465 },
        { 0101114121513, 0123465 },
        { 0101115141312, 0123456 },
        { 0101211151413, 0123456 },
        { 0101213141511, 0123456 },
        { 0101214111315, 0123465 },
        { 0101215131114, 0123465 },
        { 0101311141215, 0123465 },
        { 0101312111514, 0123456 },
        { 0101314151112, 0123456 },
        { 0101315121411, 0123465 },
        { 0101411131512, 0123465 },
        { 0101412151311, 0123465 },
        { 0101413121115, 0123456 },
        { 0101415111213, 0123456 },
        { 0101511121314, 0123456 },
        { 0101512141113, 0123465 },
        { 0101513111412, 0123465 },
        { 0101514131211, 0123456 },
        { 0111012141315, 0123456 },
        { 0111013121514, 0123465 },
        { 0111014151213, 0123465 },
        { 0111015131412, 0123456 },
        { 0111210151314, 0123456 },
        { 0111213101415, 0123465 },
        { 0111214131510, 0123456 },
        { 0111215141013, 0123465 },
        { 0111310141512, 0123465 },
        { 0111312151410, 0123465 },
        { 0111314121015, 0123456 },
        { 0111315101214, 0123456 },
        { 0111410131215, 0123465 },
        { 0111412101513, 0123456 },
        { 0111413151012, 0123456 },
        { 0111415121310, 0123465 },
        { 0111510121413, 0123456 },
        { 0111512131014, 0123465 },
        { 0111513141210, 0123456 },
        { 0111514101312, 0123465 },
        { 0121011141513, 0123456 },
        { 0121013151411, 0123456 },
        { 0121014131115, 0123465 },
        { 0121015111314, 0123465 },
        { 0121110131514, 0123456 },
        { 0121113141015, 0123465 },
        { 0121114151310, 0123456 },
        { 0121115101413, 0123465 },
        { 0121310111415, 0123456 },
        { 0121311151014, 0123465 },
        { 0121314101511, 0123465 },
        { 0121315141110, 0123456 },
        { 0121410151113, 0123465 },
        { 0121411101315, 0123456 },
        { 0121413111510, 0123465 },
        { 0121415131011, 0123456 },
        { 0121510141311, 0123465 },
        { 0121511131410, 0123465 },
        { 0121513101114, 0123456 },
        { 0121514111013, 0123456 },
        { 0131011121415, 0123465 },
        { 0131012151114, 0123456 },
        { 0131014111512, 0123456 },
        { 0131015141211, 0123465 },
        { 0131110151412, 0123465 },
        { 0131112141510, 0123465 },
        { 0131114101215, 0123456 },
        { 0131115121014, 0123456 },
        { 0131210141115, 0123456 },
        { 0131211101514, 0123465 },
        { 0131214151011, 0123465 },
        { 0131215111410, 0123456 },
        { 0131410121511, 0123456 },
        { 0131411151210, 0123456 },
        { 0131412111015, 0123465 },
        { 0131415101112, 0123465 },
        { 0131510111214, 0123465 },
        { 0131511141012, 0123456 },
        { 0131512101411, 0123456 },
        { 0131514121110, 0123465 },
        { 0141011151312, 0123465 },
        { 0141012131511, 0123465 },
        { 0141013111215, 0123456 },
        { 0141015121113, 0123456 },
        { 0141110121315, 0123465 },
        { 0141112151013, 0123456 },
        { 0141113101512, 0123456 },
        { 0141115131210, 0123465 },
        { 0141210111513, 0123465 },
        { 0141211131015, 0123456 },
        { 0141213151110, 0123465 },
        { 0141215101311, 0123456 },
        { 0141310151211, 0123456 },
        { 0141311121510, 0123456 },
        { 0141312101115, 0123465 },
        { 0141315111012, 0123465 },
        { 0141510131112, 0123456 },
        { 0141511101213, 0123465 },
        { 0141512111310, 0123456 },
        { 0141513121011, 0123465 },
        { 0151011131214, 0123456 },
        { 0151012111413, 0123465 },
        { 0151013141112, 0123465 },
        { 0151014121311, 0123456 },
        { 0151110141213, 0123456 },
        { 0151112101314, 0123465 },
        { 0151113121410, 0123456 },
        { 0151114131012, 0123465 },
        { 0151210131411, 0123465 },
        { 0151211141310, 0123465 },
        { 0151213111014, 0123456 },
        { 0151214101113, 0123456 },
        { 0151310121114, 0123465 },
        { 0151311101412, 0123456 },
        { 0151312141011, 0123456 },
        { 0151314111210, 0123465 },
        { 0151410111312, 0123456 },
        { 0151411121013, 0123465 },
        { 0151412131110, 0123456 },
        { 0151413101211, 0123465 }
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


TEST(ruLutCubeGeneratorTest, generateCubesNumberOfCubesAfterLockingAndIgnoringCornersTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;
    params.lockedCornersPerm = { };
    params.ignoredCornersPerm = { };
    params.lockedEdges = { };
    params.ignoredEdges = { 0, 1, 2, 3, 4, 5, 6 };
    params.lockedCornersOrient = { -1, -1, -1, -1, -1, -1 };
    params.ignoredCornersOrient = { 1, 1, 1, 1, 1, 1 };

    const std::vector<std::vector<uint8_t>> expectedNumberOfCornerPerms {
        { 120, 20, 4, 1, 1, 1, 1 },
        { 120, 20, 4, 1, 1, 1 },
        { 120, 20, 4, 1, 1 },
        { 120, 20, 4, 1 },
        {  30,  5, 1 },
        {   6,  1 },
        {   1 }
    };

    for (int8_t numOfIgnored = -1; numOfIgnored < ruCube::noOfCorners; ++numOfIgnored) {
        if (numOfIgnored >= 0) {
            params.ignoredCornersPerm.insert(numOfIgnored);
        }

        params.lockedCornersPerm.clear();
        generator.init(params);

        uint16_t numOfGeneratedCubes = 0;
        while (generator.hasNext()) {
            auto lutCube = generator.next();
            ++numOfGeneratedCubes;
        }

        ASSERT_EQ(expectedNumberOfCornerPerms[size(params.ignoredCornersPerm)][size(params.lockedCornersPerm)], numOfGeneratedCubes);

        for (int8_t numOfLocked = numOfIgnored + 1; numOfLocked < ruCube::noOfCorners ; ++numOfLocked) {
            params.lockedCornersPerm.insert(numOfLocked);
            generator.init(params);

            uint16_t numOfGeneratedCubes = 0;
            while (generator.hasNext()) {
                auto lutCube = generator.next();
                ++numOfGeneratedCubes;
            }
            ASSERT_EQ(expectedNumberOfCornerPerms[size(params.ignoredCornersPerm)][size(params.lockedCornersPerm)], numOfGeneratedCubes);

        }
    }

}

TEST(ruLutCubeGeneratorTest, generateCubesLLCornersPermutationTest) {
    ruLutCubeGenerator generator;

    generatorParameters params;
    params.lockedCornersPerm = { 4, 5 };
    params.ignoredCornersPerm = { };
    params.lockedEdges = { 4, 5, 6 };
    params.ignoredEdges = { 0, 1, 2, 3, 4, 5, 6 };
    params.lockedCornersOrient = { 0, 0, 0, 0, 0, 0 };
    params.ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    generator.init(params);

    std::vector<std::tuple<uint64_t, uint32_t>> expectedCubes = {
        { 0101112131415, 0123456 },
        { 0111213101415, 0132456 },
        { 0121310111415, 0123456 },
        { 0131011121415, 0132456 },
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
