#include "gtest/gtest.h"
#include "ruCubeSingleSolveHandler.h"
#include "ruCubeSingleSolveInputParser.h"
#include <vector>
#include <iostream>
#include <string>
#include <regex>

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

TEST(ruCubeSingleSolveHandlerTest, getReportCustomSolutionParametersTest) {
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

TEST(ruCubeSingleSolveHandlerTest, getReportCustomSolveReportFlagsHeadersTest) {
    solutionParameters params;
    ruCubeSingleSolveHandler handler;
    ruCubeSingleSolveInputParser parser;

    params.minLength = 1;
    params.maxLength = 13;
    params.maxNumOfSolutions = 3;

    solveReportFlags flags;
    flags.headers = true;

    handler.configure(params, solvedMasks(), flags);


    std::vector<std::string> scrambles {
        "R2 U2 R2 U2 R2 U2",
        "R' U R' U' R' U' R' U R U R2",
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'"
    };

    std::vector<std::string> expectedReports {
        "Solutions of length  6...\n"
        "R2 U2 R2 U2 R2 U2\n"
        "U2 R2 U2 R2 U2 R2\n"
        "\n"
        "Solutions of length 13...\n"
        "R U2 R2 U R2 U2 R2 U2 R2 U' R2 U2 R\n",

        "Solutions of length 11...\n"
        "R2 U' R' U' R U R U R U' R\n"
        "\n"
        "Solutions of length 13...\n"
        "R U2 R U R U R U' R' U' R' U R'\n"
        "U R U2 R U R U R2 U' R' U' R2 U'\n",

        "Solutions of length 11...\n"
        "R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
        "R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
        "\n"
        "Solutions of length 12...\n"
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'\n"
    };

    for (uint8_t i = 0; i < size(expectedReports); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
}

TEST(ruCubeSingleSolveHandlerTest, getReportCustomSolveReportFlagsHeadersLineNumbersTest) {
    solutionParameters params;
    ruCubeSingleSolveHandler handler;
    ruCubeSingleSolveInputParser parser;

    params.minLength = 1;
    params.maxLength = 13;
    params.maxNumOfSolutions = 3;

    solveReportFlags flags;
    flags.headers = true;
    flags.lineNumbers = true;

    handler.configure(params, solvedMasks(), flags);


    std::vector<std::string> scrambles {
        "R2 U2 R2 U2 R2 U2",
        "R' U R' U' R' U' R' U R U R2",
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'"
    };

    std::vector<std::string> expectedReports {
        "Solutions of length  6...\n"
        "1. R2 U2 R2 U2 R2 U2\n"
        "2. U2 R2 U2 R2 U2 R2\n"
        "\n"
        "Solutions of length 13...\n"
        "3. R U2 R2 U R2 U2 R2 U2 R2 U' R2 U2 R\n",

        "Solutions of length 11...\n"
        "1. R2 U' R' U' R U R U R U' R\n"
        "\n"
        "Solutions of length 13...\n"
        "2. R U2 R U R U R U' R' U' R' U R'\n"
        "3. U R U2 R U R U R2 U' R' U' R2 U'\n",

        "Solutions of length 11...\n"
        "1. R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
        "2. R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
        "\n"
        "Solutions of length 12...\n"
        "3. R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'\n"
    };

    for (uint8_t i = 0; i < size(expectedReports); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
}

TEST(ruCubeSingleSolveHandlerTest, getReportCustomSolveReportFlagsHeadersLineNumbersFixedWidthMovesTest) {
    solutionParameters params;
    ruCubeSingleSolveHandler handler;
    ruCubeSingleSolveInputParser parser;

    params.minLength = 1;
    params.maxLength = 13;
    params.maxNumOfSolutions = 3;

    solveReportFlags flags;
    flags.headers = true;
    flags.lineNumbers = true;
    flags.fixedWidthMoves = true;

    handler.configure(params, solvedMasks(), flags);


    std::vector<std::string> scrambles {
        "R2 U2 R2 U2 R2 U2",
        "R' U R' U' R' U' R' U R U R2",
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'"
    };

    std::vector<std::string> expectedReports {
        "Solutions of length  6...\n"
        "1. R2 U2 R2 U2 R2 U2\n"
        "2. U2 R2 U2 R2 U2 R2\n"
        "\n"
        "Solutions of length 13...\n"
        "3. R  U2 R2 U  R2 U2 R2 U2 R2 U' R2 U2 R\n",

        "Solutions of length 11...\n"
        "1. R2 U' R' U' R  U  R  U  R  U' R\n"
        "\n"
        "Solutions of length 13...\n"
        "2. R  U2 R  U  R  U  R  U' R' U' R' U  R'\n"
        "3. U  R  U2 R  U  R  U  R2 U' R' U' R2 U'\n",

        "Solutions of length 11...\n"
        "1. R2 U2 R  U2 R2 U2 R2 U2 R  U2 R2\n"
        "2. R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
        "\n"
        "Solutions of length 12...\n"
        "3. R2 U2 R2 U2 R2 U  R2 U2 R2 U2 R2 U'\n"
    };

    for (uint8_t i = 0; i < size(expectedReports); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
}

TEST(ruCubeSingleSolveHandlerTest, getReportCustomSolveReportFlagsHeadersLineNumbersFixedWidthMovesCompressSolutionsTest) {
    solutionParameters params;
    ruCubeSingleSolveHandler handler;
    ruCubeSingleSolveInputParser parser;

    params.minLength = 1;
    params.maxLength = 13;
    params.maxNumOfSolutions = 3;

    solveReportFlags flags;
    flags.headers = true;
    flags.lineNumbers = true;
    flags.fixedWidthMoves = true;
    flags.compressSolutions = true;

    handler.configure(params, solvedMasks(), flags);


    std::vector<std::string> scrambles {
        "R2 U2 R2 U2 R2 U2",
        "R' U R' U' R' U' R' U R U R2",
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'"
    };

    std::vector<std::string> expectedReports {
        "Solutions of length  6...\n"
        "1. R2U2R2U2R2U2\n"
        "2. U2R2U2R2U2R2\n"
        "\n"
        "Solutions of length 13...\n"
        "3. RU2R2UR2U2R2U2R2U'R2U2R\n",

        "Solutions of length 11...\n"
        "1. R2U'R'U'RURURU'R\n"
        "\n"
        "Solutions of length 13...\n"
        "2. RU2RURURU'R'U'R'UR'\n"
        "3. URU2RURUR2U'R'U'R2U'\n",

        "Solutions of length 11...\n"
        "1. R2U2RU2R2U2R2U2RU2R2\n"
        "2. R2U2R'U2R2U2R2U2R'U2R2\n"
        "\n"
        "Solutions of length 12...\n"
        "3. R2U2R2U2R2UR2U2R2U2R2U'\n"
    };

    for (uint8_t i = 0; i < size(expectedReports); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        ASSERT_EQ(expectedReports[i], handler.getReport());
    }
}

TEST(ruCubeSingleSolveHandlerTest, getReportCustomSolveReportFlagsHeadersLineNumbersFixedWidthMovesCompressSolutionsSummaryTest) {
    solutionParameters params;
    ruCubeSingleSolveHandler handler;
    ruCubeSingleSolveInputParser parser;

    params.minLength = 1;
    params.maxLength = 13;
    params.maxNumOfSolutions = 3;

    solveReportFlags flags;
    flags.headers = true;
    flags.lineNumbers = true;
    flags.fixedWidthMoves = true;
    flags.compressSolutions = true;
    flags.summary = true;
    handler.configure(params, solvedMasks(), flags);


    std::vector<std::string> scrambles {
        "R2 U2 R2 U2 R2 U2",
        "R' U R' U' R' U' R' U R U R2",
        "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'"
    };

    std::vector<std::string> expectedReports {
        "Solutions of length  6...\n"
        "1. R2U2R2U2R2U2\n"
        "2. U2R2U2R2U2R2\n"
        "\n"
        "Solutions of length 13...\n"
        "3. RU2R2UR2U2R2U2R2U'R2U2R\n"

        "\nSolutions found: 3\n",

        "Solutions of length 11...\n"
        "1. R2U'R'U'RURURU'R\n"
        "\n"
        "Solutions of length 13...\n"
        "2. RU2RURURU'R'U'R'UR'\n"
        "3. URU2RURUR2U'R'U'R2U'\n"

        "\nSolutions found: 3\n",

        "Solutions of length 11...\n"
        "1. R2U2RU2R2U2R2U2RU2R2\n"
        "2. R2U2R'U2R2U2R2U2R'U2R2\n"
        "\n"
        "Solutions of length 12...\n"
        "3. R2U2R2U2R2UR2U2R2U2R2U'\n"

        "\nSolutions found: 3\n"
    };

    for (uint8_t i = 0; i < size(expectedReports); ++i) {
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scrambles[i]));
        handler.solve(cube);
        std::string report = handler.getReport();
        auto lastLineStart = report.find("Solving time");
        std::string lastLine = report.substr(lastLineStart);
        report = report.substr(0, lastLineStart);
        ASSERT_EQ(expectedReports[i], report);

        std::regex lastLineValidator("^Solving time:[[:space:]]+[[:digit:]]+ms\n$");
        ASSERT_TRUE(std::regex_match(lastLine, lastLineValidator));
    }
}
