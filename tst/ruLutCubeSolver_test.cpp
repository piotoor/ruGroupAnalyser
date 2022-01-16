#include "gtest/gtest.h"
#include "ruCubeSolver.h"
#include "ruCubeFactory.h"
#include "ruCubeSolver.h"
#include "ruCubeScrambleParser.h"
#include "testCustomDefinitions.h"
#include <chrono>
#include <vector>
#include <sstream>


namespace {
    class ruCubeSolverCustomRuLutCubeMaskTestFixture: public testing::TestWithParam<std::tuple<solvedMasks, std::vector<uint8_t>, std::string>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto& [masks, scramble, expected] = testData.param;

                    std::stringstream ss;
                    bool compressSolution = true;
                    bool alnumMoves = true;
                    ss  << ruCubeScrambleParser::vectorScrambleToStringScramble(scramble, compressSolution, alnumMoves) << "_"
                        << std::oct << std::setw(12) << std::setfill('0') << masks.cornersMask << "_"
                        << std::oct << std::setw(7)  << std::setfill('0') << masks.edgesMask;
                    return ss.str();
                }
            };

        protected:
            ruLutCube cube;
            ruCubeSolver solver;
            ruCubeStateConverter conv;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSolverTests,
        ruCubeSolverCustomRuLutCubeMaskTestFixture,
        ::testing::ValuesIn(testDataGenerators::combineTwoVectorsCartesianCombineThirdLinear<solvedMasks, std::vector<uint8_t>, std::string> (
            {
                { ruLutCube::noCornersMask, 0b0000001 },
                { ruLutCube::noCornersMask, 0b0000010 },
                { ruLutCube::noCornersMask, 0b0000100 },
                { ruLutCube::noCornersMask, 0b0001000 },
                { ruLutCube::noCornersMask, 0b0010000 },
                { ruLutCube::noCornersMask, 0b0100000 },
                { ruLutCube::noCornersMask, 0b1000000 },
                { ruLutCube::noCornersMask, 0b1111111 },
                { ruLutCube::noCornersMask, 0b0000111 },
                { ruLutCube::noCornersMask, 0b0001111 },
                { ruLutCube::noCornersMask, 0b1111000 },
            },
            {
                {  },
                { R },
                { R2 },
                { Ri },
                { R2, U },
                { R2, U2 },
                { R2, Ui },
                { R2, U2, R, U, Ri, Ui },
                { R2, U, R, Ui, Ri, Ui },
            },
            {
                "",
                "R'",
                "R2",
                "R",
                "R2",
                "R2",
                "R2",
                "R2",
                "R2",

                "",
                "R'",
                "R2",
                "R",
                "U' R2",
                "U2 R2",
                "U R2",
                "U2 R2",
                "R'",

                "",
                "R'",
                "R2",
                "R",
                "R2",
                "R2",
                "R2",
                "R",
                "U2 R",

                "",
                "R'",
                "R2",
                "R",
                "R2",
                "R2",
                "R2",
                "R2",
                "R2",

                "",
                "",
                "",
                "",
                "U'",
                "U2",
                "U",
                "U2",
                "",

                "",
                "",
                "",
                "",
                "U'",
                "U2",
                "U",
                "U'",
                "U",

                "",
                "",
                "",
                "",
                "U'",
                "U2",
                "U",
                "R U",
                "U",

                "",
                "R'",
                "R2",
                "R",
                "U' R2",
                "U2 R2",
                "U R2",
                "U R U' R' U2 R2",
                "U R U R' U' R2",

                "",
                "R'",
                "R2",
                "R",
                "U' R2",
                "U2 R2",
                "U R2",
                "U2 R U2 R",
                "R U2 R' U2 R2",

                "",
                "R'",
                "R2",
                "R",
                "U' R2",
                "U2 R2",
                "U R2",
                "U2 R U2 R",
                "R U2 R' U2 R2",

                "",
                "R'",
                "R2",
                "R",
                "U' R2",
                "U2 R2",
                "U R2",
                "U R U' R' U2 R2",
                "U R2 U R2 U'"
            }
        )),
        ruCubeSolverCustomRuLutCubeMaskTestFixture::toString()
    );

    TEST_P(ruCubeSolverCustomRuLutCubeMaskTestFixture, customIsSolvedFiltersTest) {
        const auto &[masks, scramble, expected] = GetParam();
        const uint8_t minLength = 0;
        const uint8_t maxLength = 20;
        const uint8_t maxNoOfSols = 1;
        solutionParameters params = { minLength, maxLength, maxNoOfSols };

        this->cube.reset();
        this->cube.scramble(scramble);
        this->solver.configure(params, masks);
        this->solver.solve(&this->cube);
        solver.solve(&cube);
        auto solution = solver.getSolutionsAsStrings()[0];
        ASSERT_EQ(expected, solution);
    }
}
