#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"
#include "testCustomDefinitions.h"


TEST(ruLutCubeTests, initialStateTest) {
    ruLutCube cube;

    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, ruLutCube::solvedLexIndexCornersOrient, cube.getEdges());
    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, ruLutCube::solvedLexIndexCornersPerm, cube.getCornersPerm());
    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, ruLutCube::solvedLexIndexCornersOrient, cube.getCornersOrient());

    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
    ASSERT_TRUE (cube.isInDomino());
}

TEST(ruLutCubeTests, settersGettersTest) {
    ruLutCube cube;

    cube.reset();
    cube.setCornersPerm(2234);
    cube.setCornersOrient(34);
    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, 2234, cube.getCornersPerm());
    EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, 34, cube.getCornersOrient());
}

namespace {
    class ruLutCubeIsSolvedTestFixture: public templateFixtureClasses::ruCubeIsSolvedBaseParameterizedTestFixture<ruLutCube> {
    };

    INSTANTIATE_TEST_SUITE_P (
        ruLutCubeTests,
        ruLutCubeIsSolvedTestFixture,
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
                { 0b0001011111100000000000000000000000000111111, 0b111000000101010 },
                { 0b0001011111100000000000000000000000000111011, 0b111000000101010 },
                { 0b0001001000000000000000000000000000000111111, 0b010000000100010 },
                { 0b0001011111100000000000000000000000000011111, 0b111000000101010 },
                { 0b0000001000000000000000000000000000000000001, 0b000000000100000 },
                { 0b0000000001000000000000000000000000000001000, 0b000000000001010 },
                { 0b0000010000000000000000000000000000000000001, 0b000000000100000 },
                { 0b0000010011100000000000000000000000001000000, 0b000000000100010 },
                { 0b0100101010100000000000000000000000000000001, 0b000000000001000 },
                { 0b0001011111100000000000000000000000000111111, 0b000000010001000 },
                { 0b0000001000000000000000000000000000000000001, 0b000000000000001 },
                { 0b0000000001000000000000000000000000000001000, 0b000000000000100 },
                { 0b0000000001000000000000000000000000000001000, 0b000000010101000 },
                { 0b0000000001000000000000000000000000000001000, 0b000000011101000 },
                { 0b0000000001000000000000000000000000000001000, 0b000000010001000 },
                { 0b0000000000000000000000000000000000000000000, 0b111000000101010 },
                { 0b0000100000000000000000000000000000001000000, 0b000000000101010 },
                { 0b1111111111100000000000000000000011111111111, 0b100000010101010 },
            },
            {
                true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    true , true , false,
                false, false, true,       false, true,  false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false,
                false, false, false,      false, false, false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false,
                false, false, false,      false, false, false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false,
                false, false, false,      false, false, false,    false, false, false,    false, false, false,    false, false, false,    true , false, false,
                false, false, false,      false, false, true,     true,  true,  false,    false, false, true,     true,  true,  true,     true , false, false,
            }
        )),
        ruLutCubeIsSolvedTestFixture::toString()
    );

    TEST_P(ruLutCubeIsSolvedTestFixture, customIsSolvedFiltersTest) {
        const auto& [scramble, masks, expected] = GetParam();
        const auto& [cornersMask, edgesMask] = masks;

        cube.scramble(scramble);
        ASSERT_EQ(expected, cube.isSolved(cornersMask, edgesMask));
    }
}

namespace {
    class ruLutCubeToStringPamrameterizedTestFixture: public testing::TestWithParam<std::tuple<uint64_t, uint32_t, std::string>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto& [corners, edges, expected] = testData.param;

                    std::stringstream ss;
                    bool compressSolution = true;
                    bool alnumMoves = true;
                    ss  << std::oct << std::setw(12) << std::setfill('0') << corners << "_"
                        << std::oct << std::setw(7)  << std::setfill('0') << edges;
                    return ss.str();
                }
            };

        protected:
            ruLutCube cube;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruLutCubeTests,
        ruLutCubeToStringPamrameterizedTestFixture,
        ::testing::ValuesIn( std::vector<std::tuple<uint64_t, uint32_t, std::string>> {
                { 0101112131415, 00234651, "000102030405;0234651" },
                { 0101112131415, 00234516, "000102030405;0234516" },
                { 0101112131415, 00234165, "000102030405;0234165" },
                { 0101112131415, 00231456, "000102030405;0231456" },

                { 0101112131415, 00213465, "000102030405;0213465" },
                { 0101112131415, 00123456, "000102030405;0123456" },
                { 0101112131415, 01023465, "000102030405;1023465" },
                { 0101114121513, 00234561, "000104020503;0234561" },

                { 0101114121513, 00234615, "000104020503;0234615" },
                { 0101114121513, 00234156, "000104020503;0234156" },
                { 0101114121513, 00231465, "000104020503;0231465" },
                { 0101114121513, 00213456, "000104020503;0213456" },

                { 0101114121513, 00123465, "000104020503;0123465" },
                { 0101114121513, 01023456, "000104020503;1023456" },
                { 0101113151214, 00234561, "000103050204;0234561" },
                { 0101113151214, 00234615, "000103050204;0234615" }
            }
        ),
        ruLutCubeToStringPamrameterizedTestFixture::toString()
    );

    TEST_P(ruLutCubeToStringPamrameterizedTestFixture, customIsSolvedFiltersTest) {
        ruCubeStateConverter conv;
        const auto &[corners, edges, expected] = GetParam();

        ruLutCube cube(conv.intCornersToLexIndexCornersOrient(corners), conv.intCornersToLexIndexCornersPerm(corners), conv.intEdgesToLexIndexEdges(edges));
        ASSERT_EQ(expected, cube.toString());
    }
}

TEST(ruLutCubeTests, toStringWithIgnoredTest) {
    std::vector<std::tuple<uint64_t, uint32_t, std::bitset<ruBaseCube::noOfCorners>, std::bitset<ruBaseCube::noOfCorners>, std::bitset<ruBaseCube::noOfEdges>>> cubes {
        { 0101112131415, 00234651, 0b000000, 0b000000, 0b0000000 },
        { 0101112131415, 00234516, 0b000000, 0b000000, 0b0000000 },
        { 0101112131415, 00234165, 0b000000, 0b000000, 0b0000000 },
        { 0101112131415, 00231456, 0b000000, 0b000000, 0b0000000 },

        { 0101112131415, 00213465, 0b000000, 0b111111, 0b0000000 },
        { 0101112131415, 00123456, 0b111111, 0b000000, 0b0000000 },
        { 0101112131415, 01023465, 0b000000, 0b000000, 0b1111111 },
        { 0101114121513, 00234561, 0b111111, 0b111111, 0b1111111 },

        { 0101114121513, 00234615, 0b100000, 0b100000, 0b1000000 },
        { 0101114121513, 00234156, 0b010000, 0b010000, 0b0100000 },
        { 0101114121513, 00231465, 0b001000, 0b001000, 0b0010000 },
        { 0101114121513, 00213456, 0b000100, 0b000100, 0b0001000 },

        { 0101114121513, 00123465, 0b000010, 0b000010, 0b0000100 },
        { 0101114121513, 01023456, 0b000001, 0b000001, 0b0000010 },
        { 0101113151214, 00234561, 0b111100, 0b111100, 0b0000001 },
        { 0101113151214, 00234615, 0b111100, 0b111100, 0b0000011 },
    };

    std::vector<std::string> expectedStrCubes {
        "000102030405;0234651",
        "000102030405;0234516",
        "000102030405;0234165",
        "000102030405;0231456",

        "0-0-0-0-0-0-;0213465",
        "-0-1-2-3-4-5;0123456",
        "000102030405;-------",
        "------------;-------",

        "00010402--03;0234-15",
        "0001--020503;02341-6",
        "0001040205--;0231-65",
        "000104--0503;021-456",

        "00--04020503;01-3465",
        "--0104020503;-023456",
        "0001--------;-234561",
        "0001--------;-2346-5",
    };

    ruCubeStateConverter conv;

    for (size_t i = 0; i < size(expectedStrCubes); ++i) {
        const auto &[corners, edges, coi, cpi, epi] = cubes[i];
        ruLutCubeIgnoredPieces ignoredPieces { coi, cpi, epi };
        ruLutCube cube( conv.intCornersToLexIndexCornersOrient(corners),
                        conv.intCornersToLexIndexCornersPerm(corners),
                        conv.intEdgesToLexIndexEdges(edges),
                        ignoredPieces);
        ASSERT_EQ(expectedStrCubes[i], cube.toString());
    }
}
