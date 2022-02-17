#include "gtest/gtest.h"
#include "ruCubeSingleSolveHandler.h"
#include "ruCubeSingleSolveInputParser.h"
#include <vector>
#include <iostream>
#include <string>
#include <regex>


namespace {
    class ruCubeSingleSolveHandlerTestFixture: public testing::TestWithParam<std::tuple<std::string, solutionParameters, solveReportFlags, std::string>> {
        protected:
            ruCubeSingleSolveHandler handler;
            ruCubeSingleSolveInputParser parser;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSingleSolveHandlerTests,
        ruCubeSingleSolveHandlerTestFixture,
        ::testing::Values(
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R",
                solutionParameters(),
                solveReportFlags(),
                "+------------+-------+\n"
                "|150102201324;0126345|\n"
                "+------------+-------+\n"
                "R'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R U",
                solutionParameters(),
                solveReportFlags(),
                "+------------+-------+\n"
                "|201501021324;6012345|\n"
                "+------------+-------+\n"
                "U' R'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R U R",
                solutionParameters(),
                solveReportFlags(),
                "+------------+-------+\n"
                "|041501101203;6015234|\n"
                "+------------+-------+\n"
                "R' U' R'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R U R' U R U2 R'",
                solutionParameters(),
                solveReportFlags(),
                "+------------+-------+\n"
                "|222320010405;0231456|\n"
                "+------------+-------+\n"
                "R U2 R' U' R U' R'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R",
                { 5, 15, 2 },
                solveReportFlags(),
                "+------------+-------+\n"
                "|150102201324;0126345|\n"
                "+------------+-------+\n"
                "R U2 R2 U2 R2 U2 R2 U2 R2 U2 R2 U2\n"
                "U2 R2 U2 R2 U2 R2 U2 R2 U2 R2 U2 R\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R U R' U R U2 R'",
                { 5, 15, 2 },
                solveReportFlags(),
                "+------------+-------+\n"
                "|222320010405;0231456|\n"
                "+------------+-------+\n"
                "R U2 R' U' R U' R'\n"
                "R2 U2 R' U2 R' U R U2 R U2 R' U R'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R U2 R' U' R U' R2 U2 R U R' U R",
                { 5, 15, 2 },
                solveReportFlags(),
                "+------------+-------+\n"
                "|000112230405;3210456|\n"
                "+------------+-------+\n"
                "R' U' R U' R' U2 R2 U R' U R U2 R'\n"
                "R U2 R' U2 R2 U R' U R U2 R2 U' R U R'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                solveReportFlags(),
                "+------------+-------+\n"
                "|000102030405;2103654|\n"
                "+------------+-------+\n"
                "R2 U2 R2 U2 R2 U2\n"
                "U2 R2 U2 R2 U2 R2\n"
                "R U2 R2 U R2 U2 R2 U2 R2 U' R2 U2 R\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                solveReportFlags(),
                "+------------+-------+\n"
                "|000102030405;0312456|\n"
                "+------------+-------+\n"
                "R2 U' R' U' R U R U R U' R\n"
                "R U2 R U R U R U' R' U' R' U R'\n"
                "U R U2 R U R U R2 U' R' U' R2 U'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                solveReportFlags(),
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
                "R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                {
                    true, false, false, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2103654|\n"
                "+------------+-------+\n"
                "Solutions of length  6...\n"
                "R2 U2 R2 U2 R2 U2\n"
                "U2 R2 U2 R2 U2 R2\n"
                "\n"
                "Solutions of length 13...\n"
                "R U2 R2 U R2 U2 R2 U2 R2 U' R2 U2 R\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                {
                    true, false, false, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;0312456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "R2 U' R' U' R U R U R U' R\n"
                "\n"
                "Solutions of length 13...\n"
                "R U2 R U R U R U' R' U' R' U R'\n"
                "U R U2 R U R U R2 U' R' U' R2 U'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, false, false, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
                "R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
                "\n"
                "Solutions of length 12...\n"
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                {
                    true, true, false, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2103654|\n"
                "+------------+-------+\n"
                "Solutions of length  6...\n"
                "1. R2 U2 R2 U2 R2 U2\n"
                "2. U2 R2 U2 R2 U2 R2\n"
                "\n"
                "Solutions of length 13...\n"
                "3. R U2 R2 U R2 U2 R2 U2 R2 U' R2 U2 R\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                {
                    true, true, false, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;0312456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2 U' R' U' R U R U R U' R\n"
                "\n"
                "Solutions of length 13...\n"
                "2. R U2 R U R U R U' R' U' R' U R'\n"
                "3. U R U2 R U R U R2 U' R' U' R2 U'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, true, false, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
                "2. R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
                "\n"
                "Solutions of length 12...\n"
                "3. R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                {
                    true, true, true, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2103654|\n"
                "+------------+-------+\n"
                "Solutions of length  6...\n"
                "1. R2 U2 R2 U2 R2 U2\n"
                "2. U2 R2 U2 R2 U2 R2\n"
                "\n"
                "Solutions of length 13...\n"
                "3. R  U2 R2 U  R2 U2 R2 U2 R2 U' R2 U2 R\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                {
                    true, true, true, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;0312456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2 U' R' U' R  U  R  U  R  U' R\n"
                "\n"
                "Solutions of length 13...\n"
                "2. R  U2 R  U  R  U  R  U' R' U' R' U  R'\n"
                "3. U  R  U2 R  U  R  U  R2 U' R' U' R2 U'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, true, true, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2 U2 R  U2 R2 U2 R2 U2 R  U2 R2\n"
                "2. R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
                "\n"
                "Solutions of length 12...\n"
                "3. R2 U2 R2 U2 R2 U  R2 U2 R2 U2 R2 U'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                {
                    true, true, true, true, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2103654|\n"
                "+------------+-------+\n"
                "Solutions of length  6...\n"
                "1. R2U2R2U2R2U2\n"
                "2. U2R2U2R2U2R2\n"
                "\n"
                "Solutions of length 13...\n"
                "3. RU2R2UR2U2R2U2R2U'R2U2R\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                {
                    true, true, true, true, false, false
                },
                "+------------+-------+\n"
                "|000102030405;0312456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2U'R'U'RURURU'R\n"
                "\n"
                "Solutions of length 13...\n"
                "2. RU2RURURU'R'U'R'UR'\n"
                "3. URU2RURUR2U'R'U'R2U'\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, true, true, true, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2U2RU2R2U2R2U2RU2R2\n"
                "2. R2U2R'U2R2U2R2U2R'U2R2\n"
                "\n"
                "Solutions of length 12...\n"
                "3. R2U2R2U2R2UR2U2R2U2R2U'\n"
            },
                        std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, true, true, false, false, false
                },
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2 U2 R  U2 R2 U2 R2 U2 R  U2 R2\n"
                "2. R2 U2 R' U2 R2 U2 R2 U2 R' U2 R2\n"
                "\n"
                "Solutions of length 12...\n"
                "3. R2 U2 R2 U2 R2 U  R2 U2 R2 U2 R2 U'\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                {
                    true, true, true, true, false, true
                },
                "+------------+-------+\n"
                "|000102030405;2103654|\n"
                "+------------+-------+\n"
                "Solutions of length  6...\n"
                "1. R2U2R2U2R2U2\n"
                "2. U2R2U2R2U2R2\n"
                "\n"
                "Solutions of length 13...\n"
                "3. RU2R2UR2U2R2U2R2U'R2U2R\n"

                "\nSolutions found: 3\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                {
                    true, true, true, true, false, true
                },
                "+------------+-------+\n"
                "|000102030405;0312456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2U'R'U'RURURU'R\n"
                "\n"
                "Solutions of length 13...\n"
                "2. RU2RURURU'R'U'R'UR'\n"
                "3. URU2RURUR2U'R'U'R2U'\n"

                "\nSolutions found: 3\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, true, true, true, false, true
                },
                "+------------+-------+\n"
                "|000102030405;2301456|\n"
                "+------------+-------+\n"
                "Solutions of length 11...\n"
                "1. R2U2RU2R2U2R2U2RU2R2\n"
                "2. R2U2R'U2R2U2R2U2R'U2R2\n"
                "\n"
                "Solutions of length 12...\n"
                "3. R2U2R2U2R2UR2U2R2U2R2U'\n"

                "\nSolutions found: 3\n"
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U2",
                { 1, 13, 3 },
                {
                    true, true, true, true, true, true
                },
                "000102030405;2103654\n"
                "Solutions of length  6...\n"
                "1. R2U2R2U2R2U2\n"
                "2. U2R2U2R2U2R2\n"
                "\n"
                "Solutions of length 13...\n"
                "3. RU2R2UR2U2R2U2R2U'R2U2R\n"

                "\nSolutions found: 3\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R' U R' U' R' U' R' U R U R2",
                { 1, 13, 3 },
                {
                    true, true, true, true, true, true
                },
                "000102030405;0312456\n"
                "Solutions of length 11...\n"
                "1. R2U'R'U'RURURU'R\n"
                "\n"
                "Solutions of length 13...\n"
                "2. RU2RURURU'R'U'R'UR'\n"
                "3. URU2RURUR2U'R'U'R2U'\n"

                "\nSolutions found: 3\n",
            },
            std::tuple <std::string, solutionParameters, solveReportFlags, std::string> {
                "R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U'",
                { 1, 13, 3 },
                {
                    true, true, true, true, true, true
                },
                "000102030405;2301456\n"
                "Solutions of length 11...\n"
                "1. R2U2RU2R2U2R2U2RU2R2\n"
                "2. R2U2R'U2R2U2R2U2R'U2R2\n"
                "\n"
                "Solutions of length 12...\n"
                "3. R2U2R2U2R2UR2U2R2U2R2U'\n"

                "\nSolutions found: 3\n"
            }
        )
    );

    TEST_P(ruCubeSingleSolveHandlerTestFixture, getReportTest) {
        const auto& [scramble, solParams, reportFlags, expected] = GetParam();
        ruLutCube cube;
        ASSERT_NO_THROW(cube = parser.getCubeFromScramble(scramble));
        handler.configure(solParams, solvedMasks(), reportFlags);
        handler.solve(cube);

        std::string report = handler.getReport();
        auto lastLineStart = report.find("Solving time");
        if (lastLineStart != std::string::npos) {
            std::string lastLine = report.substr(lastLineStart);
            report = report.substr(0, lastLineStart);
            std::regex lastLineValidator("^Solving time:[[:space:]]+[[:digit:]]+ms\n$");
            ASSERT_TRUE(std::regex_match(lastLine, lastLineValidator));
        }

        ASSERT_EQ(expected, report);
    }
}
