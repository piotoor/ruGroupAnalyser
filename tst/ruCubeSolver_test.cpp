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
