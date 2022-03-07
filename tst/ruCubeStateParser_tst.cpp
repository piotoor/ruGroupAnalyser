#include "gtest/gtest.h"
#include "ruCubeStateParser.h"
#include "ruException.h"
#include "testCustomDefinitions.h"
#include <vector>
#include <string>

// cp, co, ep
using ruCubeStateVect = std::tuple<cornersArray, cornersArray, edgesArray>;

namespace {
    class ruCubeStateParserCorrectStatesTest: public testing::TestWithParam<std::tuple<std::string, ruCubeStateVect>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    ruCubeStateConverter conv;
                    const auto &[cubeStateStr, vectCubeState] = testData.param;
                    const auto &[cp, co, ep] = vectCubeState;

                    std::string parsedCubeStateStr = cubeStateStr;
                    std::replace_if(begin(parsedCubeStateStr),
                                    end(parsedCubeStateStr),
                                    ::ispunct,
                                    '_');

                    return parsedCubeStateStr + "_" + conv.containerToString(co) + "_" + conv.containerToString(cp);
                }
            };
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeStateParserTests,
        ruCubeStateParserCorrectStatesTest,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::string, ruCubeStateVect> (
            {
                "000102030405;0123456",
                "010200030405;0123456",
                "020100030405;0123456",
                "000102030405;0123546",
                "000102030405;0323546",
                "102112032405;0323546",
            },
            {
                { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 0, 0, 0, 0, 0, 0 }, { 1, 2, 0, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 0, 0, 0, 0, 0, 0 }, { 2, 1, 0, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 5, 4, 6 } },
                { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 3, 2, 3, 5, 4, 6 } },
                { { 1, 2, 1, 0, 2, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 3, 2, 3, 5, 4, 6 } },
            }
        )),
        ruCubeStateParserCorrectStatesTest::toString()
    );

    TEST_P(ruCubeStateParserCorrectStatesTest, correctStatesTest) {
        const auto &[cubeStateStr, expected] = GetParam();
        ruCubeStateVect vectState;
        ASSERT_NO_THROW(vectState = ruCubeStateParser::stringStateToVect(cubeStateStr));
        ASSERT_EQ(expected, vectState);
    }

    TEST_P(ruCubeStateParserCorrectStatesTest, negativeTest) {
        const auto &[cubeStateStr, expected] = GetParam();
        std::string expectedException = "ruCubeStateException: Parsing exception. Invalid cube state definition.";

        std::string exceptionMessage;
        try {
            ruCubeStateParser::stringStateToVect(cubeStateStr);
        } catch (const ruCubeStateException &e) {
            exceptionMessage = std::string(e.what());
        }
        ASSERT_EQ(expectedException, exceptionMessage);
    }
}
