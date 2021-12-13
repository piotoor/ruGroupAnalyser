#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"
#include "testCustomDefinitions.h"
#include "ruCubeScrambleParser.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>

TEST(ruCubeTests, initialStateTest) {
    ruCube cube;

    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, ruCube::solvedEdges, cube.getEdges());
    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, ruCube::solvedCorners, cube.getCorners());
    ASSERT_TRUE (cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
    ASSERT_TRUE (cube.isInDomino());
}

namespace {
    class ruCubeIsSolvedTestFixture: public templateFixtureClasses::ruCubeIsSolvedBaseParameterizedTestFixture<ruCube> {
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeTests,
        ruCubeIsSolvedTestFixture,
        ::testing::ValuesIn(testDataGenerators::combineTwoVectorsCartesianCombineThirdLinear<std::vector<uint8_t>, std::tuple<uint64_t, uint32_t>, bool> (
            {
                { R2, U2, R2, U2, R2, U2 },
                { R,  U,  Ri, U,  R,  U2, Ri, U2 },
                { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
                { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
                { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
                { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
            },
            {
                { 0000000000077, 00000070 },
                { 0000000000007, 00000070 },
                { 0000000000070, 00000070 },

                { 0000000007700, 00000070 },
                { 0000000000700, 00000070 },
                { 0000000007000, 00000070 },

                { 0000000770000, 00000070 },
                { 0000000070000, 00000070 },
                { 0000000700000, 00000070 },

                { 0000000000077, 07000070 },
                { 0000000000007, 07000070 },
                { 0000000000070, 07000070 },

                { 0000000007700, 07000070 },
                { 0000000000700, 07000070 },
                { 0000000007000, 07000070 },

                { 0000000770000, 07000070 },
                { 0000000070000, 07000070 },
                { 0000000700000, 07000070 }
            },
            {
                true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    false, false, false,
                true,  true,  true,       true,  true,  true,     false, true,  false,    false, false, false,    false, false, false,    false, false, false,
                true,  true,  true,       true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,
                true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    false, false, false,
                false, false, true,       true,  true,  true,     false, false, false,    false, false, true,     true,  true,  true,     false, false, false,
                true,  true,  true,       true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true
            }
        )),
        ruCubeIsSolvedTestFixture::toString()
    );

    TEST_P(ruCubeIsSolvedTestFixture, customIsSolvedFiltersTest) {
        const auto& [scramble, masks, expected] = GetParam();
        const auto& [cornersMask, edgesMask] = masks;

        cube.scramble(scramble);
        ASSERT_EQ(expected, cube.isSolved(cornersMask, edgesMask));
    }
}

namespace {
    class ruCubePartialEdgesTestFixture: public templateFixtureClasses::ruCubePartialStateBaseParameterizedTestFixture<uint32_t, 7> {
    };

    class ruCubePartialCornersPermTestFixture: public templateFixtureClasses::ruCubePartialStateBaseParameterizedTestFixture<uint64_t, 12> {
    };

    class ruCubePartialCornersOrientTestFixture: public templateFixtureClasses::ruCubePartialStateBaseParameterizedTestFixture<uint64_t, 12> {
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeTests,
        ruCubePartialEdgesTestFixture,
        ::testing::ValuesIn(testDataGenerators::combineTwoVectorsCartesianCombineThirdLinear<uint32_t, uint32_t, uint32_t> (
            {
                00123456,
                06543210,
            },
            {
                0b0000001,
                0b0000010,
                0b0000100,
                0b0001000,
                0b0010000,
                0b0100000,
                0b1000000,

                0b1111111,
                0b0000111,
                0b0001111,
                0b1111000,
                0b0000000,
            },
            {
                07777776,
                07777757,
                07777477,
                07773777,
                07727777,
                07177777,
                00777777,

                00123456,
                07777456,
                07773456,
                00123777,
                07777777,

                06777777,
                07577777,
                07747777,
                07773777,
                07777277,
                07777717,
                07777770,

                06543210,
                06547777,
                06543777,
                07773210,
                07777777
            }
        )),
        ruCubePartialEdgesTestFixture::toString()
    );

    TEST_P(ruCubePartialEdgesTestFixture, getPartialEdgesTest) {
        const auto& [intEdges, edgesMask, expectedPartialEdges] = GetParam();

        cube.setEdges(intEdges);
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, expectedPartialEdges, cube.getPartialEdges(edgesMask));
    }

    INSTANTIATE_TEST_SUITE_P (
        ruCubeTests,
        ruCubePartialCornersPermTestFixture,
        ::testing::ValuesIn(testDataGenerators::combineTwoVectorsCartesianCombineThirdLinear<uint64_t, uint32_t, uint32_t> (
            {
                0000102030405,
                0050403020100,
                0442142251013,
            },
            {
                0b000001,
                0b000010,
                0b000100,
                0b001000,
                0b010000,
                0b100000,

                0b111111,
                0b000111,
                0b001111,
                0b111000,
                0b000000,
                0b110010
            },
            {
                0777775,
                0777747,
                0777377,
                0772777,
                0717777,
                0077777,

                0012345,
                0777345,
                0772345,
                0012777,
                0777777,
                0017747,

                0577777,
                0747777,
                0773777,
                0777277,
                0777717,
                0777770,

                0543210,
                0543777,
                0543277,
                0777210,
                0777777,
                0747710,

                0777577,
                0477777,
                0777773,
                0772777,
                0717777,
                0777707,

                0412503,
                0477573,
                0472573,
                0712707,
                0777777,
                0417707
            }
        )),
        ruCubePartialCornersPermTestFixture::toString()
    );

    TEST_P(ruCubePartialCornersPermTestFixture, getPartialCornersPermTest) {
        const auto& [intCorners, cornersPermMask, expectedPartialCornersPerm] = GetParam();

        cube.setCorners(intCorners);
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, expectedPartialCornersPerm, cube.getPartialCornersPerm(cornersPermMask));
    }

    INSTANTIATE_TEST_SUITE_P (
        ruCubeTests,
        ruCubePartialCornersOrientTestFixture,
        ::testing::ValuesIn(testDataGenerators::combineTwoVectorsCartesianCombineThirdLinear<uint64_t, uint32_t, uint32_t> (
            {
                0000102030405,
                0151413121110,
                0442142251013
            },
            {
                0b000001,
                0b000010,
                0b000100,
                0b001000,
                0b010000,
                0b100000,

                0b111111,
                0b000111,
                0b001111,
                0b111000,
                0b000000,
                0b110010
            },
            {
                0777770,
                0777707,
                0777077,
                0770777,
                0707777,
                0077777,

                0000000,
                0777000,
                0770000,
                0000777,
                0777777,
                0007707,

                0177777,
                0717777,
                0771777,
                0777177,
                0777717,
                0777771,

                0111111,
                0111777,
                0111177,
                0777111,
                0777777,
                0717711,

                0777277,
                0477777,
                0777771,
                0774777,
                0727777,
                0777717,

                0424211,
                0477271,
                0474271,
                0724717,
                0777777,
                0427717
            }
        )),
        ruCubePartialCornersOrientTestFixture::toString()
    );

    TEST_P(ruCubePartialCornersOrientTestFixture, getPartialCornersOrientTest) {
        const auto& [intCorners, cornersOrientMask, expectedPartialCornersOrient] = GetParam();

        cube.setCorners(intCorners);
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, expectedPartialCornersOrient, cube.getPartialCornersOrient(cornersOrientMask));
    }
}
