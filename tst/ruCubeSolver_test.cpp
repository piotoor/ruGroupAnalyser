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

        ruCubeSolver solver (6, 6, 2);
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

        solver.configure(12, 14, 4);
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

        solver.configure(6, 10, 4);
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

        solver.configure(6, 8, 1);
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

        solver.configure(12, 12, 2);
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

        solver.configure(12, 12, 200);
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

TEST(ruCubeSolverTest, ruCubeSolverVsRuLutCubeSolver) {
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

    for (auto &cube: cubes) {
        ruCubeSolver solver;
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
        ss << std::endl << "| " << std::setw(9) << cubesNames[i++] << " |";
        ss << std::setw(11) << dur << "|";

        for (int i = 0; i < size(scrambles); ++i) {
            cube->reset();
            cube->scramble(scrambles[i]);
            cube->scramble(solutions[i]);
            ASSERT_TRUE(cube->isSolved(ruBaseCube::allEdgesMask, ruBaseCube::allCornersMask));
        }
    }
    ss << std::endl;
    ss << "+-----------+-----------+" << std::endl;
    std::cout << ss.str();
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

        for (int i = 0; i < std::size(scrambles); ++i) {
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
