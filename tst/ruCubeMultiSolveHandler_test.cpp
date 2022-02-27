#include "gtest/gtest.h"
#include "ruCubeMultiSolveHandler.h"
#include "ruLutCubeGenerator.h"

#include <filesystem>
#include <fstream>

namespace {
    class ruCubeMultiSolveHandlerCalculationsTestFixture: public testing::TestWithParam<std::tuple<generatorParameters, int>>{
        protected:
            ruCubeMultiSolveHandler handler;
    };

    INSTANTIATE_TEST_SUITE_P (
        numberOfCubesToGenerateTests,
        ruCubeMultiSolveHandlerCalculationsTestFixture,
        ::testing::Values(
            std::tuple<generatorParameters, int> {
                generatorParameters(),
                73'483'200
            },
            std::tuple<generatorParameters, int> {
                {   // LL
                    { 4, 5, 6 },                // lockedEdges
                    { },                        // ignoredEdges
                    { 4, 5 },                   // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { -1, -1, -1, -1, 0, 0 },   // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                1296
            },
            std::tuple<generatorParameters, int> {
                {   // PLL
                    { 4, 5, 6 },                // lockedEdges
                    { },                        // ignoredEdges
                    { 4, 5 },                   // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { 0, 0, 0, 0, 0, 0 },       // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                48
            },
            std::tuple<generatorParameters, int> {
                {   // H no AUF
                    { 4, 5, 6 },                // lockedEdges
                    { },                        // ignoredEdges
                    { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { 1, 2, 1, 2, 0, 0 },       // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                12
            },
            std::tuple<generatorParameters, int> {
                {   // Sune no AUF
                    { 4, 5, 6 },                // lockedEdges
                    { },                        // ignoredEdges
                    { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { 1, 0, 1, 1, 0, 0 },       // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                12
            },
            std::tuple<generatorParameters, int> {
                {   // corners flip
                    { 0, 1, 2, 3, 4, 5, 6 },    // lockedEdges
                    { },                        // ignoredEdges
                    { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                243
            },
            std::tuple<generatorParameters, int> {
                {   // permutation only
                    { },                        // lockedEdges
                    { },                        // ignoredEdges
                    { },                        // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 1, 1, 1, 1, 1, 1 },       // ignoredCornersOrient
                },
                302'400
            },
            std::tuple<generatorParameters, int> {
                {   // permutation only, 2 edges ignored
                    { },                        // lockedEdges
                    { 3, 5 },                   // ignoredEdges
                    { },                        // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 1, 1, 1, 1, 1, 1 },       // ignoredCornersOrient
                },
                302'400
            },
            std::tuple<generatorParameters, int> {
                {   // last F2L slot
                    { 4, 5 },                   // lockedEdges
                    { 0, 1, 2, 3 },             // ignoredEdges
                    { 4 },                      // lockedCornersPerm
                    { 0, 1, 2, 3 },             // ignoredCornersPerm
                    { -1, -1, -1, -1, 0, -1 },  // lockedCornersOrient
                    { 1, 1, 1, 1, 0, 0 },       // ignoredCornersOrient
                },
                75
            },
            std::tuple<generatorParameters, int> {
                {   // last two F2L slots
                    { 5 },                      // lockedEdges
                    { 0, 1, 2, 3 },             // ignoredEdges
                    { },                        // lockedCornersPerm
                    { 0, 1, 2, 3 },             // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 1, 1, 1, 1, 0, 0 },       // ignoredCornersOrient
                },
                8100
            },
            std::tuple<generatorParameters, int> {
                {   // all pieces but two edges and two corners are locked. The rest is ignored.
                    { 0, 1, 3, 4, 6 },          // lockedEdges
                    { 2, 5 },                   // ignoredEdges
                    { 0, 1, 3, 4 },             // lockedCornersPerm
                    { 2, 5 },                   // ignoredCornersPerm
                    { 0, 0, -1, 0, -1, 0 },     // lockedCornersOrient
                    { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
                },
                1
            },
            std::tuple<generatorParameters, int> {
                {   // all pieces but three edges and two corners are locked. The rest is ignored.
                    { 0, 1, 3, 6 },             // lockedEdges
                    { 2, 4, 5 },                // ignoredEdges
                    { 0, 1, 3, 4 },             // lockedCornersPerm
                    { 2, 5 },                   // ignoredCornersPerm
                    { 0, 0, -1, 0, -1, 0 },     // lockedCornersOrient
                    { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
                },
                1
            },
            std::tuple<generatorParameters, int> {
                {   // two edges and two corners ignored
                    { },                        // lockedEdges
                    { 2, 4 },                   // ignoredEdges
                    {  },                       // lockedCornersPerm
                    { 2, 4 },                   // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
                },
                24'494'400
            },
            std::tuple<generatorParameters, int> {
                {   // one edge and two corners ignored
                    { },                        // lockedEdges
                    { 2 },                      // ignoredEdges
                    {  },                       // lockedCornersPerm
                    { 2, 4 },                   // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
                },
                24'494'400
            },
            std::tuple<generatorParameters, int> {
                {   // one edge and one corner ignored
                    { },                        // lockedEdges
                    { 2 },                      // ignoredEdges
                    {  },                       // lockedCornersPerm
                    { 4 },                      // ignoredCornersPerm
                    { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                    { 0, 0, 1, 0, 0, 0 },       // ignoredCornersOrient
                },
                73'483'200
            }
        )
    );

    TEST_P(ruCubeMultiSolveHandlerCalculationsTestFixture, calculateTotalNumberOfCubesToGenerateTest) {
        const auto &[genParams, expected] = GetParam();
        handler.configure(genParams);
        ASSERT_EQ(handler.calculateTotalNumberOfCubesToGenerate(), expected);
    }
}

namespace {
    class ruCubeMultiSolveHandlerGenerateTestFixture: public testing::TestWithParam<std::tuple<generatorParameters, std::set<std::string>>>{
        protected:
            ruCubeMultiSolveHandler handler;
    };

    INSTANTIATE_TEST_SUITE_P (
        numberOfCubesToGenerateTests,
        ruCubeMultiSolveHandlerGenerateTestFixture,
        ::testing::Values(
            std::tuple<generatorParameters, std::set<std::string>> {
                {   // all pieces but two edges and two corners are locked. The rest is ignored.
                    { 0, 1, 3, 4, 6 },          // lockedEdges
                    { 2, 5 },                   // ignoredEdges
                    { 0, 1, 3, 4 },             // lockedCornersPerm
                    { 2, 5 },                   // ignoredCornersPerm
                    { 0, 0, -1, 0, -1, 0 },     // lockedCornersOrient
                    { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
                },
                std::set<std::string> {
                    "+------------+-------+\n"
                    "|0001--03-40-;01-34-6|\n"
                    "+------------+-------+\n"
                    "\n"
                    "\n"
                }
            },
            std::tuple<generatorParameters, std::set<std::string>> {
                {   // UL - UB - UR edges
                    { 0, 4, 5, 6 },             // lockedEdges
                    { },                        // ignoredEdges
                    { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { 0, 0, 0, 0, 0, 0 },       // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                std::set<std::string> {
                    "+------------+-------+\n"
                    "|000102030405;0123456|\n"
                    "+------------+-------+\n"
                    "\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;0231456|\n"
                    "+------------+-------+\n"
                    "R' U R' U' R' U' R' U R U R2\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;0312456|\n"
                    "+------------+-------+\n"
                    "R2 U' R' U' R U R U R U' R\n"
                    "\n"
                }
            },
            std::tuple<generatorParameters, std::set<std::string>> {
                {   // LL edges
                    { 4, 5, 6 },                // lockedEdges
                    { },                        // ignoredEdges
                    { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
                    { },                        // ignoredCornersPerm
                    { 0, 0, 0, 0, 0, 0 },       // lockedCornersOrient
                    { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
                },
                std::set<std::string> {
                    "+------------+-------+\n"
                    "|000102030405;0123456|\n"
                    "+------------+-------+\n"
                    "\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;0231456|\n"
                    "+------------+-------+\n"
                    "R' U R' U' R' U' R' U R U R2\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;0312456|\n"
                    "+------------+-------+\n"
                    "R2 U' R' U' R U R U R U' R\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;1032456|\n"
                    "+------------+-------+\n"
                    "R2 U' R2 U' R U2 R2 U2 R2 U2 R U R2 U R2\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;1203456|\n"
                    "+------------+-------+\n"
                    "U R' U R' U' R' U' R' U R U R2 U'\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;1320456|\n"
                    "+------------+-------+\n"
                    "R2 U R U R' U' R' U' R' U R'\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;2013456|\n"
                    "+------------+-------+\n"
                    "U R2 U' R' U' R U R U R U' R U'\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;2130456|\n"
                    "+------------+-------+\n"
                    "R2 U R U R2 U' R' U' R' U2 R'\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;2301456|\n"
                    "+------------+-------+\n"
                    "R2 U2 R U2 R2 U2 R2 U2 R U2 R2\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;3021456|\n"
                    "+------------+-------+\n"
                    "R U' R U R U R U' R' U' R2\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;3102456|\n"
                    "+------------+-------+\n"
                    "R U2 R U R U R2 U' R' U' R2\n"
                    "\n",
                    "+------------+-------+\n"
                    "|000102030405;3210456|\n"
                    "+------------+-------+\n"
                    "R2 U R2 U R U2 R2 U2 R2 U2 R U' R2 U' R2\n"
                    "\n"
                }
            }
        )
    );

    TEST_P(ruCubeMultiSolveHandlerGenerateTestFixture, generateAndSolveTest) {
        const auto &[genParams, expected] = GetParam();
        handler.configure(genParams);
        const std::string testFileName = "testSolutions.txt";
        handler.generateAndSolve(testFileName);

        std::ifstream solutionsFile(testFileName);
        if (solutionsFile.is_open()) {
            std::set<std::string> actual;
            std::string line;
            std::string cube;

            int n = 0;
            while (getline(solutionsFile, line)) {
                cube += line + "\n";
                if (n % 5 == 4) {
                    actual.insert(cube);
                    cube.clear();
                }
                ++n;
            }

            solutionsFile.close();
            ASSERT_EQ(actual, expected);
        } else {
            std::cout << "Error opening " << testFileName << std::endl;
        }

        try {
            std::filesystem::remove(testFileName);
        } catch (const std::filesystem::filesystem_error& err) {
            std::cout << "Filesystem error: " << err.what() << std::endl;
        }
    }
}
