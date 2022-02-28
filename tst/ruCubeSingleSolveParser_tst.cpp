#include "gtest/gtest.h"
#include "ruCubeSingleSolveInputParser.h"
#include "ruCube.h"
#include "ruCubeStateConverter.h"
#include "ruException.h"
#include "testCustomDefinitions.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>


namespace {
    class ruCubeSingleSolveInputParserGetCubeFromScrambleTestFixture: public testing::TestWithParam<std::tuple<std::string, ruLutCube>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto& [scramble, expected] = testData.param;
                    std::string compressedScramble = std::string("_") + scramble;
                    auto eraseFrom = std::remove(begin(compressedScramble),
                                                 end(compressedScramble),
                                                 ' ');

                    std::replace(begin(compressedScramble),
                                 end(compressedScramble),
                                 '\'',
                                 'i');

                    compressedScramble.erase(eraseFrom, end(compressedScramble));
                    return compressedScramble;
                }
            };

        protected:
            ruCubeSingleSolveInputParser parser;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSingleSolveInputParserTests,
        ruCubeSingleSolveInputParserGetCubeFromScrambleTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::string, ruLutCube> (
            {
                "",
                "R",
                "R'",
                "R2",
                "U",
                "U'",
                "U2",
                "R2 U2 R2 U2 R2 U2",
                "R U R' U' R U R' U' R U2 R U2 R U2 R'",
                "R U R' U R U2 R' U2"
            },
            {
                ruLutCube(),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0251112402344),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0251112402344),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00126345)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0231112442540),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0231112442540),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00124563)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0141112151013),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0141112151013),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00125634)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0131011121415),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0131011121415),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(03012456)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0111213101415),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0111213101415),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(01230456)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0121310111415),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0121310111415),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(02301456)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0101112131415),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0101112131415),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(02103654)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0224543202144),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0224543202144),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(06403125)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0401142431415),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0401142431415),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(03102456)),
            }
        )),
        ruCubeSingleSolveInputParserGetCubeFromScrambleTestFixture::toString()
    );

    TEST_P(ruCubeSingleSolveInputParserGetCubeFromScrambleTestFixture, getCubeFromScrambleTest) {
        const auto &[scramble, expected] = GetParam();
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scramble));
        ASSERT_EQ(expected, cube);
    }
}

namespace {
    class ruCubeSingleSolveInputParserGetCubeFromScrambleNegativeTestFixture: public testing::TestWithParam<std::string> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    std::string scramble = testData.param;

                    std::replace(begin(scramble),
                                 end(scramble),
                                 '\'',
                                 'i');

                    auto eraseFrom = std::remove_if(begin(scramble),
                                                    end(scramble),
                                                    [] (const auto &c) {
                                                        return not isalnum(c);
                                                    });

                    scramble.erase(eraseFrom, end(scramble));
                    return std::string("_") + scramble;
                }
            };

        protected:
            ruCubeSingleSolveInputParser parser;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSingleSolveInputParserTests,
        ruCubeSingleSolveInputParserGetCubeFromScrambleNegativeTestFixture,
        ::testing::Values(
            "                          ",
            "  2234123412341234                        ",
            "dupa",
            "R3",
            "3R'",
            "R  2",
            "Ulrich Von Jungingen",
            "U''",
            "U2 Concert",
            "R21 U2 R2222 U23 R2' 'U2",
            "R U R'2 U' R U R' U' R U2 R U2 R U2 R'",
            "R U-( R' U R U2 R') U2"
        ),
        ruCubeSingleSolveInputParserGetCubeFromScrambleNegativeTestFixture::toString()
    );

    TEST_P(ruCubeSingleSolveInputParserGetCubeFromScrambleNegativeTestFixture, getCubeFromScrambleNegativeTest) {
        std::string scramble = GetParam();
        const std::string expectedException = "ruCubeScrambleException: Parsing exception. Invalid scramble.";
        ASSERT_THROW (
            try {
                auto cube = parser.getCubeFromScramble(scramble);
            } catch (const ruCubeScrambleException &e) {
                std::cout << std::string(e.what()) << std::endl;
                ASSERT_EQ(expectedException, std::string(e.what()));
                throw;
            },
            ruCubeScrambleException
        );

    }
}


namespace {
    class ruCubeSingleSolveInputParserGetCubeFromStateTestFixture: public testing::TestWithParam<std::tuple<std::string, ruLutCube>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    auto [state, expected] = testData.param;

                    std::replace(begin(state),
                                 end(state),
                                 ';',
                                 '_');

                    return state;
                }
            };

        protected:
            ruCubeSingleSolveInputParser parser;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSingleSolveInputParserTests,
        ruCubeSingleSolveInputParserGetCubeFromStateTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::string, ruLutCube> (
            {
                "000102030405;0123456",
                "101112030405;0123456",
                "101112031425;0123456",
                "121310011425;0123456",
                "121310011425;0123645",
                "121310011425;2013645",
            },
            {
                ruLutCube(),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0202122131415),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0202122131415),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00123456)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0202122132445),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0202122132445),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00123456)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0222320112445),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0222320112445),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00123456)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0222320112445),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0222320112445),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(00123645)),
                ruLutCube(ruCubeStateConverter().intCornersToLexIndexCornersOrient(0222320112445),
                          ruCubeStateConverter().intCornersToLexIndexCornersPerm(0222320112445),
                          ruCubeStateConverter().intEdgesToLexIndexEdges(02013645)),
            }
        )),
        ruCubeSingleSolveInputParserGetCubeFromStateTestFixture::toString()
    );

    TEST_P(ruCubeSingleSolveInputParserGetCubeFromStateTestFixture, GetCubeFromStateTest) {
        const auto &[state, expected] = GetParam();
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromState(state));
        ASSERT_EQ(expected, cube);
    }
}

TEST(ruCubeSingleSolveInputParserTest, getCubeFromStateNegativeTest) {
    std::vector<std::string> states = {
        "0001020304;05;0123456",
        "010200030;405;0123456",
        "020100030407;0123456",
        "0001020304305;0123546",
        "102112032405;0323546423423",
        "102112032405;0323547",
        "",

        "000102030404;0123456",
        "000102030304;0123456",
        "101112031405;0123456",
        "001112031405;0123456",
        "101112031425;0123455",
        "101112031425;0123450",

        "000102030504;0123456",
        "000103020504;0123456",
        "000102040503;0123456",
        "000102040503;0123546",
    };

    ruCubeStateConverter c;
    std::vector<std::string> exceptions = {
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",

        "ruCubeStateException: Validation exception. Invalid corners permutation.",
        "ruCubeStateException: Validation exception. Invalid corners permutation.",
        "ruCubeStateException: Validation exception. Invalid corners orientation.",
        "ruCubeStateException: Validation exception. Invalid corners orientation.",
        "ruCubeStateException: Validation exception. Invalid edges permutation.",
        "ruCubeStateException: Validation exception. Invalid edges permutation.",

        "ruCubeStateException: Validation exception. Unsolvable state.",
        "ruCubeStateException: Validation exception. Unsolvable state.",
        "ruCubeStateException: Validation exception. Unsolvable state.",
        "ruCubeStateException: Validation exception. Unsolvable state.",
    };

    ruCubeSingleSolveInputParser parser;
    size_t i = 0;
    for (; i < size(states); ++i) {
        try {
            auto cube = parser.getCubeFromState(states[i]);
        } catch (const ruCubeStateException &e) {
            ASSERT_EQ(exceptions[i], std::string(e.what()));
        }
    }
    ASSERT_EQ(size(states), i);
}



