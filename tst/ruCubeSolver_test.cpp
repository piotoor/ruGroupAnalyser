#include "gtest/gtest.h"
#include "ruCubeSolver.h"
#include <chrono>

TEST(ruCubeSolverTest, simpleDefaultConfigurationSolveTest) {
    ruCube cube;
    cube.turn(R);
    cube.turn(U);
    cube.turn(R2);
    cube.turn(Ui);

    ruCubeSolver solver;
    solver.solve(&cube);
    auto solutions = solver.getSolutionsAsVectors();
    std::vector<std::vector<uint8_t>> expectedSolutions = {
        { U, R2, Ui, Ri }
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }



    cube.reset();
    cube.turn(Ri);
    cube.turn(U);
    cube.turn(Ri);
    cube.turn(Ui);

    solver.solve(&cube);
    solutions = solver.getSolutionsAsVectors();
    expectedSolutions = {
        { U, R, Ui, R }
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }
}

TEST(ruCubeSolverTest, customConfigurationSolveTest) {
    ruCube cube;
    cube.scramble({ R2, U2, R2, U2, R2, U2 });

    ruCubeSolver solver (6, 6, 2);
    solver.solve(&cube);
    auto solutions = solver.getSolutionsAsVectors();
    std::vector<std::vector<uint8_t>> expectedSolutions = {
        { R2, U2, R2, U2, R2, U2 },
        { U2, R2, U2, R2, U2, R2 },
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }



    cube.reset();
    cube.scramble({ R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U });

    solver.configure(12, 14, 4);
    solver.solve(&cube);
    solutions = solver.getSolutionsAsVectors();
    expectedSolutions = {
        { R2, U2, R2, U2, R2, U, R2, U2, R2, U2, R2, Ui },
        { R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U },
        { U, R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2 },
        { Ui, R2, U2, R2, U2, R2, U, R2, U2, R2, U2, R2 }
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }



    cube.reset();
    cube.scramble({ R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U });

    solver.configure(6, 10, 4);
    solver.solve(&cube);
    solutions = solver.getSolutionsAsVectors();
    expectedSolutions = {
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }



    cube.reset();
    cube.scramble({ R, U, Ri, U, R, U2, Ri });

    solver.configure(6, 8, 1);
    solver.solve(&cube);
    solutions = solver.getSolutionsAsVectors();
    expectedSolutions = {
        { R, U2, Ri, Ui, R, Ui, Ri }
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }



    cube.reset();
    cube.scramble({ R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui });

    solver.configure(12, 12, 2);
    solver.solve(&cube);
    solutions = solver.getSolutionsAsVectors();
    expectedSolutions = {
        { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
        { U, R, Ui, Ri, U, R, Ui, Ri, U, R, Ui, Ri }
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
    }



    cube.reset();
    cube.scramble({ R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui });

    solver.configure(12, 12, 200);
    solver.solve(&cube);
    solutions = solver.getSolutionsAsVectors();
    expectedSolutions = {
        { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
        { U, R, Ui, Ri, U, R, Ui, Ri, U, R, Ui, Ri }
    };

    ASSERT_EQ(expectedSolutions.size(), solutions.size());
    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ASSERT_EQ(expectedSolutions[i], solutions[i]);
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

    for (int i = 0; i < expectedSolutions.size(); ++i) {
        ruCubeSolver solver;
        ruCube cube;
        cube.scramble(scrambles[i]);
        solver.solve(&cube);
        auto solutions = solver.getSolutionsAsVectors();

        ASSERT_EQ(expectedSolutions[i], solutions[0]);
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

    ruCube cube;
    ruCubeSolver solver;

    for (const auto &scr: scrambles) {
        std::cout << "Solving scramble of length " << std::setw(2) << size(scr) << "... ";
        std::cout.flush();
        cube.reset();
        cube.scramble(scr);
        solver.solve(&cube);
        auto solution = solver.getSolutionsAsVectors()[0];
        cube.reset();
        cube.scramble(scr);
        cube.scramble(solution);
        ASSERT_TRUE(cube.isSolved());
        std::cout << "(sol: " << std::setw(2) << size(solution) << " moves) ";
        std::cout << "DONE" << std::endl;
    }

}

TEST (ruCubeSolverTest, benchmarkTest) {
    ruCube cube;
    std::vector<uint8_t> scr { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R, U, Ri, U };
    cube.scramble(scr);

    const uint8_t minLength = 1;
    const uint8_t maxLength = 20;
    const uint8_t numOfSolves = 10;

    ruCubeSolver solver(minLength, maxLength, numOfSolves);
    solver.solve(&cube);

    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    auto solutions = solver.getSolutionsAsVectors();
    for (const auto &sol: solutions) {
        cube.reset();
        cube.scramble(scr);
        cube.scramble(sol);
        ASSERT_TRUE(cube.isSolved());
    }

    using namespace std::literals;
    const auto stop = std::chrono::steady_clock::now();
    //(stop - start) / 1ms << "ms";
}
