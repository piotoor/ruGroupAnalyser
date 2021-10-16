#include "gtest/gtest.h"
#include "ruCubeSolver.h"
#include "ruCubeFactory.h"
#include <chrono>
#include <vector>
#include <sstream>

TEST(ruCubeSolverTest, simpleDefaultConfigurationSolveTest) {
    std::vector<std::unique_ptr<ruBaseCube>> cubes;
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube));
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruLutCube));

    ASSERT_EQ(2, size(cubes));

    for (auto &cube: cubes) {
        cube->turn(R);
        cube->turn(U);
        cube->turn(R2);
        cube->turn(Ui);

        ruCubeSolver solver;
        solver.solve(cube.get());
        auto solutions = solver.getSolutionsAsVectors();
        std::vector<std::vector<uint8_t>> expectedSolutions = {
            { U, R2, Ui, Ri }
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }



        cube->reset();
        cube->turn(Ri);
        cube->turn(U);
        cube->turn(Ri);
        cube->turn(Ui);

        solver.solve(cube.get());
        solutions = solver.getSolutionsAsVectors();
        expectedSolutions = {
            { U, R, Ui, R }
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }
    }
}

TEST(ruCubeSolverTest, customConfigurationSolveTest) {
    std::vector<std::unique_ptr<ruBaseCube>> cubes;
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube));
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruLutCube));

    for (auto &cube: cubes) {
        cube->scramble({ R2, U2, R2, U2, R2, U2 });

        solutionParameters params = {
            6,
            6,
            2
        };

        ruCubeSolver solver (params);
        solver.solve(cube.get());
        auto solutions = solver.getSolutionsAsVectors();
        std::vector<std::vector<uint8_t>> expectedSolutions = {
            { R2, U2, R2, U2, R2, U2 },
            { U2, R2, U2, R2, U2, R2 },
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }



        cube->reset();
        cube->scramble({ R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U });

        params.minLength = 12;
        params.maxLength = 14;
        params.maxNumOfSolutions = 4;

        solver.configure(params);
        solver.solve(cube.get());
        solutions = solver.getSolutionsAsVectors();
        expectedSolutions = {
            { R2, U2, R2, U2, R2, U, R2, U2, R2, U2, R2, Ui },
            { R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U },
            { U, R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2 },
            { Ui, R2, U2, R2, U2, R2, U, R2, U2, R2, U2, R2 }
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }



        cube->reset();
        cube->scramble({ R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U });

        params.minLength = 6;
        params.maxLength = 10;
        params.maxNumOfSolutions = 4;

        solver.configure(params);
        solver.solve(cube.get());
        solutions = solver.getSolutionsAsVectors();
        expectedSolutions = {
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }



        cube->reset();
        cube->scramble({ R, U, Ri, U, R, U2, Ri });

        params.minLength = 6;
        params.maxLength = 8;
        params.maxNumOfSolutions = 1;

        solver.configure(params);
        solver.solve(cube.get());
        solutions = solver.getSolutionsAsVectors();
        expectedSolutions = {
            { R, U2, Ri, Ui, R, Ui, Ri }
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }



        cube->reset();
        cube->scramble({ R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui });

        params.minLength = 12;
        params.maxLength = 12;
        params.maxNumOfSolutions = 2;

        solver.configure(params);
        solver.solve(cube.get());
        solutions = solver.getSolutionsAsVectors();
        expectedSolutions = {
            { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
            { U, R, Ui, Ri, U, R, Ui, Ri, U, R, Ui, Ri }
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }



        cube->reset();
        cube->scramble({ R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui });

        params.minLength = 12;
        params.maxLength = 12;
        params.maxNumOfSolutions = 200;

        solver.configure(params);
        solver.solve(cube.get());
        solutions = solver.getSolutionsAsVectors();
        expectedSolutions = {
            { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
            { U, R, Ui, Ri, U, R, Ui, Ri, U, R, Ui, Ri }
        };

        ASSERT_EQ(expectedSolutions.size(), solutions.size());
        for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
            ASSERT_EQ(expectedSolutions[i], solutions[i]);
        }
    }
}


TEST(ruCubeSolverTest, singleMoveSolutionsTest) {
    std::vector<std::vector<uint8_t>> expectedSolutions = {
        { Ui },
        { U2 },
        { U },
        { Ri },
        { R2 },
        { R }
    };

    std::vector<std::vector<uint8_t>> scrambles = {
        { U },
        { U2 },
        { Ui },
        { R },
        { R2 },
        { Ri }
    };

    for (uint8_t i = 0; i < expectedSolutions.size(); ++i) {
        ruCubeSolver solver;

        std::vector<std::unique_ptr<ruBaseCube>> cubes;
        cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube));
        cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruLutCube));

        for (auto &cube: cubes) {
            cube->scramble(scrambles[i]);
            solver.solve(cube.get());
            auto solutions = solver.getSolutionsAsVectors();

            ASSERT_EQ(expectedSolutions[i], solutions[0]);
        }
    }
}




TEST(ruCubeSolverTest, multipleScramblesTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        { R2 },
        { R2, U },
        { R2, U, R},
        { R2, U, R, Ui },
        { R2, U, R, Ui, R2 },
        { R2, U, R, Ui, R2, U },
        { R2, U, R, Ui, R2, Ui, Ri },
        { R2, U, R, Ui, R2, U, R, U },
        { R2, U, R, Ui, R2, U, R, U, R },
        { R2, U, R, Ui, R2, U, R, U, R, U2 },
        { R2, U, R, Ui, R2, U, R, U, R, U, Ri },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2 },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, Ri, U },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2 },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R2 },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, Ri, U },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R, Ui, R },
        { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R, U, Ri, U },
    };


    std::vector<std::unique_ptr<ruBaseCube>> cubes;
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube));
    cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruLutCube));

    for (auto &cube: cubes) {
        ruCubeSolver solver;

        for (const auto &scr: scrambles) {
            std::cout << "Solving scramble of length " << std::setw(2) << size(scr) << "... ";
            std::cout.flush();
            cube->reset();
            cube->scramble(scr);
            solver.solve(cube.get());
            auto solution = solver.getSolutionsAsVectors()[0];
            cube->reset();
            cube->scramble(scr);
            cube->scramble(solution);
            ASSERT_TRUE(cube->isSolved(ruBaseCube::allEdgesMask, ruBaseCube::allCornersMask));
            std::cout << "(sol: " << std::setw(2) << size(solution) << " moves) ";
            std::cout << "DONE" << std::endl;
        }
    }
}


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
            ASSERT_TRUE(cube->isSolved(ruBaseCube::allEdgesMask, ruBaseCube::allCornersMask));
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
        solvedMasks masks = {edgesMasks[maskInd], ruLutCube::noCornersMask};
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
        solvedMasks masks = { ruLutCube::noEdgesMask, cornersMasks[maskInd] };
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

    std::vector<std::pair<uint32_t, uint64_t>> masks {
        { 0b1000000, 0x0000003F'00000000 },
        { 0b0000001, 0x00000000'0000003F },
        { 0b1000001, 0x0000003F'0000003F },
        { 0b0000001, 0x00000003'00000003 },
        { 0b0000001, 0x00000020'00000020 },
        { 0b1000000, 0x00000010'00000010 },
    };

    ruLutCube cube;
    ruCubeSolver solver;
    const uint8_t minLength = 0;
    const uint8_t maxLength = 20;
    const uint8_t maxNoOfSols = 1;

    solutionParameters params = { minLength, maxLength, maxNoOfSols };

    for (uint8_t maskInd = 0; maskInd < size(masks); ++maskInd) {
        auto &[edgesMask, cornersMask] = masks[maskInd];
        solvedMasks masks = {edgesMask, cornersMask};
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

class ruCubeSolverPerformanceTest : public ::testing::Test {
    protected:
        void ruCubeSolverVsRuLutCubeSolver(uint32_t edgesMask = ruCube::allEdgesMask, uint32_t ruEdgesMask = ruCube::allEdgesMask) {
            std::vector<std::vector<uint8_t>> scrambles {
                { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R, U, Ri, U },
                { R, U, R, U, R2, U, R, U, R, Ui, R, U2, R2, U2, Ri, U2, R, U, Ri, U },
                { R, U, R, U, R2, U, R, Ui, Ri, U, Ri, Ui, Ri, Ui, Ri, U2, R, U, Ri, Ui },
                { Ri, Ui, Ri, Ui, R2, U, R, Ui, Ri, U, Ri, Ui, Ri, Ui, Ri, U2, R, U, Ri, U2 },
                { R2, U2, R2, U2, R2, Ui, R, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, Ri, U2 },

                { R2, U2, R2, U2, R, U, R2, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, Ri, U2 },
                { R2, U2, R2, U, R2, Ui, R, U, Ri, U, Ri, U, Ri, Ui, Ri, U, R, U, Ri, U },
                { R2, U2, R, U2, R2, Ui, R, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, R2, U2 },
                { R2, U2, R2, U2, Ri, Ui, R, Ui, Ri, U, R2, U2, Ri, Ui, Ri, U2, R, U, Ri, U2 },
                { R2, U2, R2, Ui, R2, U2, R, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, Ri, U2 },

                { U2, R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R, U, Ri, U },
                { Ui, R, U, R, U, R2, U, R, U, R, Ui, R, U2, R2, U2, Ri, U2, R, U, Ri, U },
                { R, Ui, R, U, R2, U, R, Ui, Ri, U, Ri, Ui, Ri, Ui, Ri, U2, R, U, Ri, Ui },
                { Ri, Ui, Ri, Ui, R2, U, R, Ui, Ri, Ui, Ri, Ui, Ri, Ui, Ri, U2, R, U, Ri, U2 },
                { U, R2, U2, R, U2, R2, Ui, R, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, Ri, U2 },

                { R2, U2, R2, U2, R, U, R2, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, Ri, U2, R },
                { R2, U2, R2, U, R2, Ui, R, U, Ri, U, Ri, U, Ri, Ui, Ri, U, R, U, Ri, U, Ri },
                { R2, U2, R, U2, R2, Ui, R, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, R2, U2, R2 },
                { R2, U2, R2, U2, Ri, Ui, R, Ui, Ri, U, R2, U2, Ri, Ui, Ri, U2, R, U, Ri, Ui, R },
                { R2, U2, R2, Ui, R2, U2, R, Ui, Ri, U, Ri, U2, Ri, Ui, Ri, U2, R, U, Ri, U, Ri }
            };

            std::vector<std::unique_ptr<ruBaseCube>> cubes;
            cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube));
            cubes.push_back(ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruLutCube));

            std::stringstream ss;

            ss << std::endl;
            ss << "+-----------+-----------+" << std::endl;
            ss << "| cube type | time [ms] |" << std::endl;
            ss << "+-----------+-----------+";

            int i = 0;
            std::vector<std::string> cubesNames {"ruCube", "ruLutCube"};
            std::vector<uint32_t> edgesMasks {edgesMask, ruEdgesMask};

            for (auto &cube: cubes) {
                solutionParameters params = {
                    0, 20, 1
                };

                solvedMasks masks = {
                    edgesMasks[i],
                    ruBaseCube::allCornersMask
                };

                ruCubeSolver solver(params, masks);
                std::vector<std::vector<uint8_t>> solutions;


                const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

                int scrIndex = 0;
                for (const auto &scr: scrambles) {
                    std::cout << std::setw(10) <<  cubesNames[i] << " solving scramble " << std::setw(2) << scrIndex << "..." << std::flush;
                    cube->reset();
                    cube->scramble(scr);
                    solver.solve(cube.get());
                    solutions.push_back(solver.getSolutionsAsVectors()[0]);
                    ++scrIndex;
                    std::cout << "DONE" << std::endl << std::flush;
                }

                const auto stop = std::chrono::steady_clock::now();
                std::chrono::duration<double> diff = stop - start;
                using namespace std::literals;
                double dur = diff / 1ms;
                ss << std::endl << "| " << std::setw(9) << cubesNames[i] << " |";
                ss << std::setw(11) << dur << "|";

                for (uint8_t j = 0; j < size(scrambles); ++j) {
                    cube->reset();
                    cube->scramble(scrambles[j]);
                    cube->scramble(solutions[j]);
                    ASSERT_TRUE(cube->isSolved(edgesMasks[i], ruBaseCube::allCornersMask));
                }
                ++i;
            }
            ss << std::endl;
            ss << "+-----------+-----------+" << std::endl;
            std::cout << ss.str();
        }
};

TEST_F(ruCubeSolverPerformanceTest, ruCubeSolverVsRuLutCubeSolver) {
    ruCubeSolverVsRuLutCubeSolver();
}

TEST_F(ruCubeSolverPerformanceTest, ruCubeSolverVsRuLutCubeSolverCustomEdgesMask) {
    ruCubeSolverVsRuLutCubeSolver(00070707, 0b0010101);
}

