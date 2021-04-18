#include "gtest/gtest.h"
#include "ruCubeSolver.h"


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
