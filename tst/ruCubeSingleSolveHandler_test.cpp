#include "gtest/gtest.h"
#include "ruCubeSingleSolveHandler.h"
#include "ruCubeSingleSolveInputParser.h"
#include <vector>
#include <iostream>
#include <string>

TEST(ruCubeSingleSolveHandlerTest, getReportDefaultTest) {
    ruCubeSingleSolveHandler handler;
    ruCubeSingleSolveInputParser parser;

    std::vector<std::string> scrambles {
        "R",
        "R U",
        "R U R",
        "R U R' U R U2 R'"
    };

    std::vector<std::string> expectedReports {
        "R'\n",
        "U' R'\n",
        "R' U' R'\n",
        "R U2 R' U' R U' R'\n"
    };

    for (uint8_t i = 0; i < size(scrambles); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
}

TEST(ruCubeSingleSolveHandlerTest, getReportMaxNumOfSolutionsMinLengthMaxLengthTest) {
    solutionParameters params = {
        5, 15, 2
    };
    ruCubeSingleSolveHandler handler(params);
    ruCubeSingleSolveInputParser parser;

    std::vector<std::string> scrambles {
        "R",
        "R U R' U R U2 R'",
        "R U2 R' U' R U' R2 U2 R U R' U R"
    };

    std::vector<std::string> expectedReports {
        "R U2 R2 U2 R2 U2 R2 U2 R2 U2 R2 U2\n"
        "U2 R2 U2 R2 U2 R2 U2 R2 U2 R2 U2 R\n",

        "R U2 R' U' R U' R'\n"
        "R2 U2 R' U2 R' U R U2 R U2 R' U R'\n",

        "R' U' R U' R' U2 R2 U R' U R U2 R'\n"
        "R U2 R' U2 R2 U R' U R U2 R2 U' R U R'\n"
    };

    for (uint8_t i = 0; i < size(scrambles); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
// -----------------------------------------------------------------

    params.minLength = 1;
    params.maxLength = 13;
    params.maxNumOfSolutions = 3;

    handler.configure(params);

    scrambles = {
        "R2 U2 R2 U2 R2 U2",
        "R' U R' U' R' U' R' U R U R2",
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'"
    };

    expectedReports = {
        "R2 U2 R2 U2 R2 U2\n"
        "U2 R2 U2 R2 U2 R2\n"
        "R U2 R2 U R2 U2 R2 U2 R2 U' R2 U2 R\n",

        "R2 U' R' U' R U R U R U' R\n"
        "R U2 R U R U R U' R' U' R' U R'\n"
        "U R U2 R U R U R2 U' R' U' R2 U'\n",

        "R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
        "R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'\n"
    };

    for (uint8_t i = 0; i < size(scrambles); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
// -----------------------------------------------------------------
}

