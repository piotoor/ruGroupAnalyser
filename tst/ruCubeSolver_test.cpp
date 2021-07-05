#include "gtest/gtest.h"
#include "ruCubeSolver.h"
#include "ruCubeFactory.h"
#include <chrono>

TEST(ruCubeSolverTest, simpleDefaultConfigurationSolveTest) {

    auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
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

TEST(ruCubeSolverTest, customConfigurationSolveTest) {

    auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
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

        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        cube->scramble(scrambles[i]);
        solver.solve(cube.get());
        auto solutions = solver.getSolutionsAsVectors();

        ASSERT_EQ(expectedSolutions[i], solutions[0]);
    }
}


TEST(ruCubeSolverTest, DISABLED_multipleScramblesTest) {
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


    auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
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

class ruCubeSolverPerformanceTests : public ::testing::Test
{
    protected:
        virtual void SetUp() {

        }

        virtual void TearDown() {

        }

        void setupSolver() {
            minLength = 1;
            maxLength = 20;
            numOfSolves = 10;
            scramble = { R2, U, R, Ui, R2, U, R, U, R, Ui, R2, U2, R, U2, Ri, U2, R, U, Ri, U };
            solver.configure(minLength, maxLength, numOfSolves);
        }

        void solveSingleThread() {
            std::cout << "solveSingleThread... ";
            cube->reset();
            cube->scramble(scramble);

            const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

            solver.solve(cube.get());
            solutions = solver.getSolutionsAsVectors();

            const auto stop = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = stop - start;
            singleThreadTime = diff;
            verifySolutions();
            std::cout << std::setw(19) << "DONE" << std::endl;
        }

        void solveMultiThread(uint8_t multiThreadingThreshold) {
            std::cout << "solveMultiThread of threshold " << std::setw(2) << static_cast<int>(multiThreadingThreshold) << "... ";
            cube->scramble(scramble);

            const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

            solver.solve(cube.get(), true, multiThreadingThreshold);
            solutions = solver.getSolutionsAsVectors();

            const auto stop = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = stop - start;
            multiThreadingThresholdsTimes[multiThreadingThreshold] = diff;

            verifySolutions();
            std::cout << "DONE" << std::endl;
        }

        void verifySolutions() {
            for (const auto &sol: solutions) {
    //            std::copy(begin(sol), end(sol), std::ostream_iterator<int>(std::cout, " "));
    //            std::cout << std::endl;
                cube->reset();
                cube->scramble(scramble);
                cube->scramble(sol);
                ASSERT_TRUE(cube->isSolved(ruBaseCube::allEdgesMask, ruBaseCube::allCornersMask));
            }
        }

        void printReport() {
            using namespace std::literals;
            std::streamsize ss = std::cout.precision();
            std::cout << std::endl;
            std::cout << "+---------+-- Report -+-----------+-------+" << std::endl;
            std::cout << "| threads | threshold |" << std::setw(11) << " time [ms] " << "| ratio |" << std::endl;
            std::cout << "+---------+-----------+-----------+-------+" << std::endl;
            std::cout << "| " << std::setw(7) << 1 << " | " << std::setw(9) << "N/A" << " | " << std::setw(9) << singleThreadTime / 1ms << " | " << std::setw(5) << 1 << " |" << std::endl;
            std::cout << "+---------+-----------+-----------+-------+" << std::endl;
            for (const auto &[k, v]: multiThreadingThresholdsTimes) {
                double ms = v / 1ms;
                double ratio_ = ms / (singleThreadTime / 1ms);
                std::cout << "| " << std::setw(7) << 6 << " | " << std::setw(9) << static_cast<int>(k) << " | " << std::setprecision(ss) <<  std::setw(9) << ms << " | " << std::setw(5) << std::setprecision(3) << ratio_ << " |" << std::endl;
            }

            std::cout << "+---------+-----------+-----------+-------+" << std::endl;
            std::cout << std::endl;
        }


        ruCubeSolver solver;

        std::unique_ptr<ruBaseCube>  cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        std::map<uint8_t, std::chrono::duration<double>> multiThreadingThresholdsTimes;
        std::chrono::duration<double> singleThreadTime;

        std::vector<std::vector<uint8_t>> solutions;
        std::vector<uint8_t> scramble;

        uint8_t minLength;
        uint8_t maxLength;
        uint8_t numOfSolves;

};

TEST_F(ruCubeSolverPerformanceTests, DISABLED_MultithreadingTest) {
    setupSolver();
    solveSingleThread();

    for (uint8_t threshold = minLength; threshold < maxLength; ++threshold) {
        solveMultiThread(threshold);
    }

    printReport();
}

