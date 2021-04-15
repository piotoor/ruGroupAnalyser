#include "gtest/gtest.h"
#include "ruCubeSolver.h"



TEST(ruCubeSolverTest, simpleDefaultConfigurationSolveTest) {
    ruCube cube;
    cube.turn(0);
    cube.turn(3);

    ruCubeSolver solver;
    solver.solve(&cube);
    auto solutions = solver.getSolutionsAsVectors();
    #include <iostream>
    using namespace std;

    for (const auto &x: solutions) {
        copy(begin(x), end(x), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    ASSERT_TRUE(false);
}
