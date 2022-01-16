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
                    ruBaseCube::allCornersMask,
                    edgesMasks[i]
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
                    ASSERT_TRUE(cube->isSolved(ruBaseCube::allCornersMask, edgesMasks[i]));
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


namespace {
    template <class T>
    class ruCubeAndLutCubeSolverCustomConfigurationSolveTests: public testing::Test {
        protected:
            ruCubeAndLutCubeSolverCustomConfigurationSolveTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeSolverCustomConfigurationSolveTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::tuple<std::vector<uint8_t>, solutionParameters, std::vector<std::vector<uint8_t>>>> testData = {
                {
                    { R2, U2, R2, U2, R2, U2 },
                    { 6, 6, 2 },
                    {
                        { R2, U2, R2, U2, R2, U2 },
                        { U2, R2, U2, R2, U2, R2 },
                    }
                },
                {
                    { R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U },
                    { 12, 14, 4 },
                    {
                        { R2, U2, R2, U2, R2, U, R2, U2, R2, U2, R2, Ui },
                        { R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U },
                        { U, R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2 },
                        { Ui, R2, U2, R2, U2, R2, U, R2, U2, R2, U2, R2 }
                    }
                },
                {
                    { R2, U2, R2, U2, R2, Ui, R2, U2, R2, U2, R2, U },
                    { 6, 10, 4 },
                    {

                    }
                },
                {
                    { R, U, Ri, U, R, U2, Ri },
                    { 6, 8, 1 },
                    {
                        { R, U2, Ri, Ui, R, Ui, Ri }
                    }
                },
                {
                    { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
                    { 12, 12, 2 },
                    {
                        { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
                        { U, R, Ui, Ri, U, R, Ui, Ri, U, R, Ui, Ri }
                    }
                },
                {
                    { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
                    { 12, 12, 200 },
                    {
                        { R, U, Ri, Ui, R, U, Ri, Ui, R, U, Ri, Ui },
                        { U, R, Ui, Ri, U, R, Ui, Ri, U, R, Ui, Ri }
                    }
                },
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeSolverCustomConfigurationSolveTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeSolverCustomConfigurationSolveTests, correctSolution) {
        for (const auto &data: this->testData) {
            const auto &[scr, params, expected] = data;
            const auto &[minLength, maxLength, maxNumOfSolutions] = params;

            std::stringstream ss;
            ss << "scr = " << ruCubeScrambleParser::vectorScrambleToStringScramble(scr) << ", params = { " << (int)minLength << ", " << (int)maxLength << ", " << (int)maxNumOfSolutions << "}" << std::endl;
            SCOPED_TRACE(ss.str());

            ruCubeSolver solver(params);
            this->cube->reset();
            this->cube->scramble(scr);
            solver.solve(this->cube.get());
            auto solutions = solver.getSolutionsAsVectors();
            ASSERT_EQ(expected, solutions);
        }
    }
}


namespace {
    template <class T>
    class ruCubeAndLutCubeSolverSingleMoveSolutionsTests: public testing::Test {
        protected:
            ruCubeAndLutCubeSolverSingleMoveSolutionsTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeSolverSingleMoveSolutionsTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>>> testData {
                { { Ui }, { U } },
                { { U2 }, { U2 } },
                { { U }, { Ui } },
                { { Ri }, { R } },
                { { R2 }, { R2 } },
                { { R }, { Ri } }
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeSolverSingleMoveSolutionsTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeSolverSingleMoveSolutionsTests, singleMoveSolutionsTest) {
        for (const auto &data: this->testData) {
            const auto &[scramble, expected] = data;

            std::stringstream ss;
            ss << "scr = " << ruCubeScrambleParser::vectorScrambleToStringScramble(scramble) << std::endl;
            SCOPED_TRACE(ss.str());

            ruCubeSolver solver;
            this->cube->reset();
            this->cube->scramble(scramble);
            solver.solve(this->cube.get());
            auto solutions = solver.getSolutionsAsVectors();

            ASSERT_EQ(expected, solutions[0]);
        }
    }
}
