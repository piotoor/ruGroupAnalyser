#include "gtest/gtest.h"
#include "ruCubeScrambleParser.h"
#include "ruException.h"
#include "testCustomDefinitions.h"

#include <string>
#include <algorithm>

namespace {
    class ruCubeScrambleParserVectorScrambleToStringScrambleTestFixtureBase: public testing::TestWithParam<std::tuple<std::vector<uint8_t>, std::string>>{
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[scramble, expected] = testData.param;
                    bool compressSolution = true;
                    bool alnumMoves = true;
                    return ruCubeScrambleParser::vectorScrambleToStringScramble(scramble, compressSolution, alnumMoves);

                }
            };
    };

    class ruCubeScrambleParserTestFixture: public ruCubeScrambleParserVectorScrambleToStringScrambleTestFixtureBase {};
    class ruCubeScrambleParserCompressSolutionTestFixture: public ruCubeScrambleParserVectorScrambleToStringScrambleTestFixtureBase {};

    INSTANTIATE_TEST_SUITE_P (
        vectorScrambleToStringScrambleTests,
        ruCubeScrambleParserTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::vector<uint8_t>, std::string> (
            {
                { R, R2, Ri, U, U2, Ui },
                { R },
                { R2 },
                { Ri },
                { U },
                { U2 },
                { Ui },
                { R, U },
                { R, U, R, U, R, U, Ri, Ui, R2, U2, R2, U2, R, Ui, R2, U2, R2, U2, R2, Ui }
            },
            {
                "R R2 R' U U2 U'",
                "R",
                "R2",
                "R'",
                "U",
                "U2",
                "U'",
                "R U",
                "R U R U R U R' U' R2 U2 R2 U2 R U' R2 U2 R2 U2 R2 U'"
            }
        )),
        ruCubeScrambleParserTestFixture::toString()
    );

    INSTANTIATE_TEST_SUITE_P (
        vectorScrambleToStringScrambleNegativeTests,
        ruCubeScrambleParserTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::vector<uint8_t>, std::string> (
            {
                { R, R2, Ri, 12, U, U2, Ui, 11, 8 },
                { R, 15 },
                { R2, 7, 99, 121 },
                { Ri, 7 },
                { U, 7 },
                { 7, 7, 7, 7, 7, 7, U2, 8 },
                { Ui, 14 },
                { R, 12, U },
                { R, U, R, 9, U, R, U, 9, Ri, Ui, R2, U2, R2, U2, R, 9, Ui, R2, U2, R2, U2, R2, Ui }
            },
            {
                "R R2 R' U U2 U'",
                "R",
                "R2",
                "R'",
                "U",
                "U2",
                "U'",
                "R U",
                "R U R U R U R' U' R2 U2 R2 U2 R U' R2 U2 R2 U2 R2 U'"
            }
        )),
        ruCubeScrambleParserTestFixture::toString()
    );

    TEST_P(ruCubeScrambleParserTestFixture, vectorScrambleToStringScrambleTest) {
        const auto &[scramble, expected] = GetParam();
        ASSERT_EQ(expected, ruCubeScrambleParser::vectorScrambleToStringScramble(scramble));
    }

    INSTANTIATE_TEST_SUITE_P (
        vectorScrambleToStringScrambleCompressedSolutionTests,
        ruCubeScrambleParserCompressSolutionTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::vector<uint8_t>, std::string> (
            {
                { R, R2, Ri, U, U2, Ui },
                { R },
                { R2 },
                { Ri },
                { U },
                { U2 },
                { Ui },
                { R, U },
                { R, U, R, U, R, U, Ri, Ui, R2, U2, R2, U2, R, Ui, R2, U2, R2, U2, R2, Ui }
            },
            {
                "RR2R'UU2U'",
                "R",
                "R2",
                "R'",
                "U",
                "U2",
                "U'",
                "RU",
                "RURURUR'U'R2U2R2U2RU'R2U2R2U2R2U'"
            }
        )),
        ruCubeScrambleParserCompressSolutionTestFixture::toString()
    );

    TEST_P(ruCubeScrambleParserCompressSolutionTestFixture, vectorScrambleToStringScrambleCompressSolutionTest) {
        const auto &[scramble, expected] = GetParam();
        const bool compressSolution = true;
        ASSERT_EQ(expected, ruCubeScrambleParser::vectorScrambleToStringScramble(scramble, compressSolution));
    }
}

namespace {
    class ruCubeScrambleParserStringScrambleToVectorScrambleTestFixture: public testing::TestWithParam<std::tuple<std::string, std::vector<uint8_t>>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[scramble, expected] = testData.param;
                    std::string compressedScramble = scramble;
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
    };

    INSTANTIATE_TEST_SUITE_P (
        stringScrambleToVectorScrambleTests,
        ruCubeScrambleParserStringScrambleToVectorScrambleTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::string, std::vector<uint8_t>> (
            {
                "R R2 R' U U2 U'",
                "R",
                "R2",
                "R'",
                "U",
                "U2",
                "U'",
                "R U",
                "R U R U R U R' U' R2 U2 R2 U2 R U' R2 U2 R2 U2 R2 U'"
            },
            {
                { R, R2, Ri, U, U2, Ui },
                { R },
                { R2 },
                { Ri },
                { U },
                { U2 },
                { Ui },
                { R, U },
                { R, U, R, U, R, U, Ri, Ui, R2, U2, R2, U2, R, Ui, R2, U2, R2, U2, R2, Ui }
            }
        )),
        ruCubeScrambleParserStringScrambleToVectorScrambleTestFixture::toString()
    );

    TEST_P(ruCubeScrambleParserStringScrambleToVectorScrambleTestFixture, stringScrambleToVectorScrambleTest) {
        const auto &[scramble, expected] = GetParam();
        ASSERT_EQ(expected, ruCubeScrambleParser::stringScrambleToVectorScramble(scramble));
    }
}

namespace {
    class ruCubeScrambleParserStringScrambleToVectorScrambleNegativeTestFixture: public testing::TestWithParam<std::tuple<std::string>> {};

    INSTANTIATE_TEST_SUITE_P (
        stringScrambleToVectorScrambleNegativeTests,
        ruCubeScrambleParserStringScrambleToVectorScrambleNegativeTestFixture,
        ::testing::Values(
            "RR2 R'rU U2 U'",
            "RXCV",
            "R2XVCXVCCXVCXV",
            "'''' 12341234213412342134 QWEQWEQWEwqeqweqweR'",
            "U3",
            "U2    2",
            "U''",
            "R';';';;;;;::[]{}[]]][]}}}!@#$%^&*()-=+______0,.<>/???`~ U",
            "R U R U R U R'YUI H      U' R2vbnnbvnbvnbvnvb%^^%%^5645665^%%$#$#234#24 U2 R2 U2 R U' R22 U2 R3 U1 R2 U'"
        )
    );

    TEST_P(ruCubeScrambleParserStringScrambleToVectorScrambleNegativeTestFixture, stringScrambleToVectorScrambleNegativeTest) {
        const auto &[scramble] = GetParam();
        std::string expectedException = "ruCubeScrambleException: Parsing exception. Invalid scramble.";
        ASSERT_THROW (
            try {
                auto vectScramble = ruCubeScrambleParser::stringScrambleToVectorScramble(scramble);
            } catch (const ruCubeScrambleException &e) {
                std::cout << std::string(e.what()) << std::endl;
                ASSERT_EQ(expectedException, std::string(e.what()));
                throw;
            },
            ruCubeScrambleException
        );
    }
}
