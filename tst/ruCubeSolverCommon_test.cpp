#include "gtest/gtest.h"
#include "ruCubeSolver.h"
#include "ruCubeFactory.h"
#include "ruCubeSolver.h"
#include "ruCubeScrambleParser.h"
#include <chrono>
#include <vector>
#include <sstream>


namespace {
    template <class T>
    class ruCubeAndLutCubeSolverIsSolvedTests: public testing::Test {
        protected:
            ruCubeAndLutCubeSolverIsSolvedTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeSolverIsSolvedTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::vector<uint8_t>> testData {
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
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeSolverIsSolvedTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeSolverIsSolvedTests, isSolvedTest) {
        for (const auto &data: this->testData) {
            auto scr = data;
            SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));

            std::cout << "Solving scramble of length " << std::setw(2) << size(scr) << "... ";
            std::cout.flush();
            this->cube->reset();
            this->cube->scramble(scr);
            ruCubeSolver solver;
            solver.solve(this->cube.get());
            auto solution = solver.getSolutionsAsVectors()[0];
            this->cube->reset();
            this->cube->scramble(scr);
            this->cube->scramble(solution);
            ASSERT_TRUE(this->cube->isSolved(ruBaseCube::allCornersMask, ruBaseCube::allEdgesMask));
            std::cout << "(sol: " << std::setw(2) << size(solution) << " moves) ";
            std::cout << "DONE" << std::endl;
        }
    }
}
