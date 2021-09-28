#include "gtest/gtest.h"
#include "ruCubeStateParser.h"
#include "ruException.h"
#include <vector>
#include <string>

// cp, co, ep
using ruCubeStateVect = std::tuple<cornersArray, cornersArray, edgesArray>;

TEST(ruCubeStateParserTest, correctStatesTest) {
    std::vector<std::string> cubeStatesStr {
        "000102030405;0123456",
        "010200030405;0123456",
        "020100030405;0123456",
        "000102030405;0123546",
        "000102030405;0323546",
        "102112032405;0323546",
    };

    std::vector<ruCubeStateVect> expectedVectStates {
        { { 0, 1, 2, 3, 4, 5 }, { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 1, 2, 0, 3, 4, 5 }, { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 2, 1, 0, 3, 4, 5 }, { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 0, 1, 2, 3, 4, 5 }, { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 5, 4, 6 } },
        { { 0, 1, 2, 3, 4, 5 }, { 0, 0, 0, 0, 0, 0 }, { 0, 3, 2, 3, 5, 4, 6 } },
        { { 0, 1, 2, 3, 4, 5 }, { 1, 2, 1, 0, 2, 0 }, { 0, 3, 2, 3, 5, 4, 6 } },
    };

    for (uint8_t i = 0; i < size(expectedVectStates); ++i) {
        auto vectState = ruCubeStateParser::stringStateToVect(cubeStatesStr[i]);
        ASSERT_EQ(expectedVectStates[i], vectState);

    }
}

TEST(ruCubeStateParserTest, negativeTest) {
    std::vector<std::string> cubeStatesStr {
        "0001020304;05;0123456",
        "010200030;405;0123456",
        "020100030407;0123456",
        "0001020304305;0123546",
        "102112032405;0323546423423",
        "102112032405;0323547",
    };

    std::vector<std::string> expectedExceptions {
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition.",
        "ruCubeStateException: Parsing exception. Invalid cube state definition."
    };

    uint8_t i = 0;
    for (; i < size(expectedExceptions); ++i) {
        std::string exceptionMessage;
        try {
            auto vectState = ruCubeStateParser::stringStateToVect(cubeStatesStr[i]);
        } catch (const ruCubeStateException &e) {
            exceptionMessage = e.what();
        }
        ASSERT_EQ(expectedExceptions[i], exceptionMessage);
    }
    ASSERT_EQ(size(expectedExceptions), i);
}
