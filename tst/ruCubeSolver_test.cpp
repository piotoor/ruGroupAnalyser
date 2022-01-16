#include "gtest/gtest.h"
#include "ruCubeSolver.h"
#include "ruCubeFactory.h"
#include <chrono>
#include <vector>
#include <sstream>


TEST(ruCubeSolverTest, multipleScramblesSolutionsAsStringsTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        { R2 },
        { R2, U },
        { R2, U, R},
        { R2, U, R, Ui },
        { R2, U, R, Ui, R2 },
        { R2, Ui, Ri, Ui, R2, U2 },
    };

    std::vector<std::string> expectedSolutionsStrings {
        "R2",
        "U' R2",
        "R' U' R2",
        "U R' U' R2",
        "R2 U R' U' R2",
        "U2 R2 U R U R2"
    };

    std::vector<std::unique_ptr<ruBaseCube>> cubes;
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube));
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruLutCube));

    for (auto &cube: cubes) {
        ruCubeSolver solver;

        for (uint8_t i = 0; i < std::size(scrambles); ++i) {
            std::cout << "Solving scramble of length " << std::setw(2) << size(scrambles[i]) << "... ";
            std::cout.flush();
            cube->reset();
            cube->scramble(scrambles[i]);
            solver.solve(cube.get());
            auto solution = solver.getSolutionsAsVectors();
            auto solutionStr = solver.getSolutionsAsStrings();
            ASSERT_EQ(1, std::size(solution));
            ASSERT_EQ(1, std::size(solutionStr));

            cube->reset();
            cube->scramble(scrambles[i]);
            cube->scramble(solution[0]);
            ASSERT_TRUE(cube->isSolved(ruBaseCube::allCornersMask, ruBaseCube::allEdgesMask));
            ASSERT_EQ(expectedSolutionsStrings[i], solutionStr[0]);
            std::cout << "(sol: " << std::setw(2) << size(solution[0]) << " moves) ";
            std::cout << "DONE" << std::endl;
        }
    }
}

TEST(ruCubeSolverTest, customRuLutCubeEdgesMaskTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        {  },
        { R },
        { R2 },
        { Ri },
        { R2, U },
        { R2, U2 },
        { R2, Ui },
        { R2, U2, R, U, Ri, Ui },
        { R2, U, R, Ui, Ri, Ui },
    };

    std::vector<std::vector<std::string>> expectedSolutionsStrings {
        { "",
          "R'",
          "R2",
          "R",
          "R2",
          "R2",
          "R2",
          "R2",
          "R2"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U2 R2",
          "R'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "R2",
          "R2",
          "R2",
          "R",
          "U2 R"
        },

        { "",
          "R'",
          "R2",
          "R",
          "R2",
          "R2",
          "R2",
          "R2",
          "R2"
        },

        { "",
          "",
          "",
          "",
          "U'",
          "U2",
          "U",
          "U2",
          ""
        },

        { "",
          "",
          "",
          "",
          "U'",
          "U2",
          "U",
          "U'",
          "U"
        },

        { "",
          "",
          "",
          "",
          "U'",
          "U2",
          "U",
          "R U",
          "U"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U R U' R' U2 R2",
          "U R U R' U' R2"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U2 R U2 R",
          "R U2 R' U2 R2"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U2 R U2 R",
          "R U2 R' U2 R2"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U R U' R' U2 R2",
          "U R2 U R2 U'"
        },

    };

    std::vector<uint32_t> edgesMasks {
        0b0000001,
        0b0000010,
        0b0000100,
        0b0001000,
        0b0010000,
        0b0100000,
        0b1000000,

        0b1111111,

        0b0000111,

        0b0001111,
        0b1111000,
    };

    ruLutCube cube;
    ruCubeSolver solver;
    const uint8_t minLength = 0;
    const uint8_t maxLength = 20;
    const uint8_t maxNoOfSols = 1;

    solutionParameters params = { minLength, maxLength, maxNoOfSols };


    for (uint8_t maskInd = 0; maskInd < size(edgesMasks); ++maskInd) {
        solvedMasks masks = {ruLutCube::noCornersMask, edgesMasks[maskInd]};
        solver.configure(params, masks);
        for (uint8_t i = 0; i < size(scrambles); ++i) {
            cube.reset();
            cube.scramble(scrambles[i]);
            solver.solve(&cube);
            auto solution = solver.getSolutionsAsStrings()[0];
            ASSERT_EQ(expectedSolutionsStrings[maskInd][i], solution);
        }

    }
}

TEST(ruCubeSolverTest, customRuLutCubeCornersMaskTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        {  },
        { R },
        { R2 },
        { Ri },
        { R2, U },
        { R2, U2 },
        { R2, Ui },
        { R2, U2, R, U, Ri, Ui },
        { R2, U, R, Ui, Ri, Ui },
    };

    std::vector<std::vector<std::string>> expectedSolutionsStrings {
        { "",
          "R",
          "",
          "R",
          "",
          "",
          "",
          "U R U' R",
          "U R U R"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "R2 U' R'",
          "U' R' U"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U R U' R' U2 R2",
          "R' U' R U R'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U R U R2",
          "R' U' R U R'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "R2",
          "R2",
          "R2",
          "R2",
          "R2"
        },

        { "",
          "",
          "",
          "",
          "U'",
          "U2",
          "U",
          "U'",
          "U"
        },

        { "",
          "",
          "",
          "",
          "U'",
          "U2",
          "U",
          "R U' R' U2",
          ""
        },

        { "",
          "R'",
          "R2",
          "R",
          "R2",
          "R2",
          "R2",
          "R",
          "R' U'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "R' U' R",
          "R'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U2 R2",
          "U2 R' U' R2"
        },
    };

    std::vector<uint64_t> cornersMasks {
        0x0000003F'00000000,    // CO only
        0x00000000'0000003F,    // CP only
        0x0000003F'0000003F,    // CO + CP
        0x00000003'00000003,    // F2L corners
        0x00000020'00000020,    // URF
        0x00000010'00000010,    // UFL
        0x00000008'00000008,    // ULB
        0x00000004'00000004,    // UBR
        0x00000002'00000002,    // DRB
        0x00000001'00000001,    // DFR
    };

    ruLutCube cube;
    ruCubeSolver solver;
    const uint8_t minLength = 0;
    const uint8_t maxLength = 20;
    const uint8_t maxNoOfSols = 1;

    solutionParameters params = { minLength, maxLength, maxNoOfSols };

    for (uint8_t maskInd = 0; maskInd < size(cornersMasks); ++maskInd) {
        solvedMasks masks = { cornersMasks[maskInd], ruLutCube::noEdgesMask };
        solver.configure(params, masks);

        for (uint8_t i = 0; i < size(scrambles); ++i) {
            cube.reset();
            cube.scramble(scrambles[i]);
            solver.solve(&cube);
            auto solution = solver.getSolutionsAsStrings()[0];
            ASSERT_EQ(expectedSolutionsStrings[maskInd][i], solution);
        }

    };
}

TEST(ruCubeSolverTest, customRuLutCubeEdgesAndCornersMaskTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        {  },
        { R },
        { R2 },
        { Ri },
        { R2, U },
        { R2, U2 },
        { R2, Ui },
        { R2, U2, R, U, Ri, Ui },
        { R2, U, R, Ui, Ri, Ui },
    };

    std::vector<std::vector<std::string>> expectedSolutionsStrings {
        { "",
          "R",
          "",
          "R",
          "U'",
          "U2",
          "U",
          "U R U' R U2",
          "R' U R U R"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U2 R U2 R",
          "U2 R U' R"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U R U' R' U2 R2",
          "R' U' R U R'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "U' R2",
          "U2 R2",
          "U R2",
          "U R U' R' U2 R2",
          "R' U' R U R'"
        },

        { "",
          "R'",
          "R2",
          "R",
          "R2",
          "R2",
          "R2",
          "R2",
          "R2"
        },

        { "",
          "",
          "",
          "",
          "U'",
          "U2",
          "U",
          "U R U' R' U2",
          "U"
        },
    };

    std::vector<std::pair<uint64_t, uint32_t>> masks {
        { 0x0000003F'00000000, 0b1000000 },
        { 0x00000000'0000003F, 0b0000001 },
        { 0x0000003F'0000003F, 0b1000001 },
        { 0x00000003'00000003, 0b0000001 },
        { 0x00000020'00000020, 0b0000001 },
        { 0x00000010'00000010, 0b1000000 },
    };

    ruLutCube cube;
    ruCubeSolver solver;
    const uint8_t minLength = 0;
    const uint8_t maxLength = 20;
    const uint8_t maxNoOfSols = 1;

    solutionParameters params = { minLength, maxLength, maxNoOfSols };

    for (uint8_t maskInd = 0; maskInd < size(masks); ++maskInd) {

        auto &[cornersMask, edgesMask] = masks[maskInd];
        solvedMasks masks = {cornersMask, edgesMask};
        solver.configure(params, masks);

        for (uint8_t i = 0; i < size(scrambles); ++i) {
            cube.reset();
            cube.scramble(scrambles[i]);
            solver.solve(&cube);
            auto solution = solver.getSolutionsAsStrings()[0];
            ASSERT_EQ(expectedSolutionsStrings[maskInd][i], solution);
        }

    };
}

