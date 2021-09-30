#include "gtest/gtest.h"
#include "ruCubeSingleSolveInputParser.h"
#include <vector>
#include <iostream>
#include <string>
#include "ruCube.h"
#include "ruCubeStateConverter.h"
#include "ruException.h"

TEST(ruCubeSingleSolveInputParserTest, getCubeFromScrambleTest) {
    std::vector<std::string> scrambles = {
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
    };

    ruCubeStateConverter c;
    std::vector<ruLutCube> expectedCubes = {
        ruLutCube(),
        ruLutCube(c.intEdgesToLexIndexEdges(00126345),
                  c.intCornersToLexIndexCornersPerm(0251112402344),
                  c.intCornersToLexIndexCornersOrient(0251112402344)),
        ruLutCube(c.intEdgesToLexIndexEdges(00124563),
                  c.intCornersToLexIndexCornersPerm(0231112442540),
                  c.intCornersToLexIndexCornersOrient(0231112442540)),
        ruLutCube(c.intEdgesToLexIndexEdges(00125634),
                  c.intCornersToLexIndexCornersPerm(0141112151013),
                  c.intCornersToLexIndexCornersOrient(0141112151013)),
        ruLutCube(c.intEdgesToLexIndexEdges(03012456),
                  c.intCornersToLexIndexCornersPerm(0131011121415),
                  c.intCornersToLexIndexCornersOrient(0131011121415)),
        ruLutCube(c.intEdgesToLexIndexEdges(01230456),
                  c.intCornersToLexIndexCornersPerm(0111213101415),
                  c.intCornersToLexIndexCornersOrient(0111213101415)),
        ruLutCube(c.intEdgesToLexIndexEdges(02301456),
                  c.intCornersToLexIndexCornersPerm(0121310111415),
                  c.intCornersToLexIndexCornersOrient(0121310111415)),
        ruLutCube(c.intEdgesToLexIndexEdges(02103654),
                  c.intCornersToLexIndexCornersPerm(0101112131415),
                  c.intCornersToLexIndexCornersOrient(0101112131415)),
        ruLutCube(c.intEdgesToLexIndexEdges(06403125),
                  c.intCornersToLexIndexCornersPerm(0224543202144),
                  c.intCornersToLexIndexCornersOrient(0224543202144)),
        ruLutCube(c.intEdgesToLexIndexEdges(03102456),
                  c.intCornersToLexIndexCornersPerm(0401142431415),
                  c.intCornersToLexIndexCornersOrient(0401142431415)),
    };

    ruCubeSingleSolveInputParser parser;
    for (uint8_t i = 0; i < size(scrambles); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        ASSERT_EQ(expectedCubes[i], cube);
    }
}

TEST(ruCubeSingleSolveInputParserTest, getCubeFromScrambleNegativeTest) {
    std::vector<std::string> scrambles = {
        "                          ",
        "  2234123412341234                        ",
        "dupa",
        "R3",
        "3R'",
        "R  2",
        "Ulrich Von Jungingen",
        "U'",
        "U2 Concert",
        "R21 U2 R2222 U23 R2' 'U2",
        "R U R'2 U' R U R' U' R U2 R U2 R U2 R'",
        "R U-( R' U R U2 R') U2"
    };

    ruCubeStateConverter c;
    std::vector<ruLutCube> expectedCubes = {
        ruLutCube(),
        ruLutCube(),
        ruLutCube(),
        ruLutCube(c.intEdgesToLexIndexEdges(00126345),
                  c.intCornersToLexIndexCornersPerm(0251112402344),
                  c.intCornersToLexIndexCornersOrient(0251112402344)),
        ruLutCube(c.intEdgesToLexIndexEdges(00124563),
                  c.intCornersToLexIndexCornersPerm(0231112442540),
                  c.intCornersToLexIndexCornersOrient(0231112442540)),
        ruLutCube(c.intEdgesToLexIndexEdges(00125634),
                  c.intCornersToLexIndexCornersPerm(0141112151013),
                  c.intCornersToLexIndexCornersOrient(0141112151013)),
        ruLutCube(c.intEdgesToLexIndexEdges(03012456),
                  c.intCornersToLexIndexCornersPerm(0131011121415),
                  c.intCornersToLexIndexCornersOrient(0131011121415)),
        ruLutCube(c.intEdgesToLexIndexEdges(01230456),
                  c.intCornersToLexIndexCornersPerm(0111213101415),
                  c.intCornersToLexIndexCornersOrient(0111213101415)),
        ruLutCube(c.intEdgesToLexIndexEdges(02301456),
                  c.intCornersToLexIndexCornersPerm(0121310111415),
                  c.intCornersToLexIndexCornersOrient(0121310111415)),
        ruLutCube(c.intEdgesToLexIndexEdges(02103654),
                  c.intCornersToLexIndexCornersPerm(0101112131415),
                  c.intCornersToLexIndexCornersOrient(0101112131415)),
        ruLutCube(c.intEdgesToLexIndexEdges(06403125),
                  c.intCornersToLexIndexCornersPerm(0224543202144),
                  c.intCornersToLexIndexCornersOrient(0224543202144)),
        ruLutCube(c.intEdgesToLexIndexEdges(03102456),
                  c.intCornersToLexIndexCornersPerm(0401142431415),
                  c.intCornersToLexIndexCornersOrient(0401142431415)),
    };

    ruCubeSingleSolveInputParser parser;
    for (uint8_t i = 0; i < size(scrambles); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        ASSERT_EQ(expectedCubes[i], cube);
    }
}

TEST(ruCubeSingleSolveInputParserTest, getCubeFromStateTest) {
    std::vector<std::string> states = {
        "000102030405;0123456",
        "101112030405;0123456",
        "101112031425;0123456",
        "121310011425;0123456",
        "121310011425;0123645",
        "121310011425;2013645",
    };

    ruCubeStateConverter c;
    std::vector<ruLutCube> expectedCubes = {
        ruLutCube(),
        ruLutCube(c.intEdgesToLexIndexEdges(00123456),
                  c.intCornersToLexIndexCornersPerm(0202122131415),
                  c.intCornersToLexIndexCornersOrient(0202122131415)),
        ruLutCube(c.intEdgesToLexIndexEdges(00123456),
                  c.intCornersToLexIndexCornersPerm(0202122132445),
                  c.intCornersToLexIndexCornersOrient(0202122132445)),
        ruLutCube(c.intEdgesToLexIndexEdges(00123456),
                  c.intCornersToLexIndexCornersPerm(0222320112445),
                  c.intCornersToLexIndexCornersOrient(0222320112445)),
        ruLutCube(c.intEdgesToLexIndexEdges(00123645),
                  c.intCornersToLexIndexCornersPerm(0222320112445),
                  c.intCornersToLexIndexCornersOrient(0222320112445)),
        ruLutCube(c.intEdgesToLexIndexEdges(02013645),
                  c.intCornersToLexIndexCornersPerm(0222320112445),
                  c.intCornersToLexIndexCornersOrient(0222320112445)),
    };

    ruCubeSingleSolveInputParser parser;
    for (uint8_t i = 0; i < size(states); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromState(states[i]));
        ASSERT_EQ(expectedCubes[i], cube);
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
    uint8_t i = 0;
    for (; i < size(states); ++i) {
        try {
            auto cube = parser.getCubeFromState(states[i]);
        } catch (const ruCubeStateException &e) {
            ASSERT_EQ(exceptions[i], e.what());
        }
    }
    ASSERT_EQ(size(states), i);
}



