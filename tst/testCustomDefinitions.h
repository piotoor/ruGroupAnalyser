#ifndef TESTCUSTOMDEFINITIONS_H
#define TESTCUSTOMDEFINITIONS_H
#include "gtest/gtest.h"
#include "ruCubeScrambleParser.h"
#include <vector>

namespace testDataGenerators {
    template<class T1, class T2>
    std::vector<std::tuple<T1, T2>> combine2VectorsCartesian(std::vector<T1> v1, std::vector<T2> v2) {
        std::vector<std::tuple<T1, T2>> ans;

        for (const auto &x: v1) {
            for (const auto &y: v2) {
                ans.emplace_back(x, y);
            }
        }

        return ans;
    }

    template<class T1, class T2>
    std::vector<std::tuple<T1, T2>> combine2VectorsLinear(std::vector<T1> v1, std::vector<T2> v2) {
        std::vector<std::tuple<T1, T2>> ans;

        for (size_t i = 0; i < std::min({v1.size(), v2.size()}); ++i) {
            ans.emplace_back(v1[i], v2[i]);
        }

        return ans;
    }

    template<class T1, class T2, class T3>
    std::vector<std::tuple<T1, T2, T3>> combineTwoVectorsCartesianCombineThirdLinear(std::vector<T1> v1, std::vector<T2> v2, std::vector<T3> v3) {
        std::vector<std::tuple<T1, T2, T3>> ans;

        size_t v3_ind = 0;
        for (const auto &x: v1) {
            for (const auto &y: v2) {
                ans.emplace_back(x, y, v3[v3_ind++]);
            }
        }

        return ans;
    }
}

namespace testCustomAsserts {
    template <class T1, class T2>
    testing::AssertionResult AssertEqOct(const char* a_expr,
                                         const char* b_expr,
                                         T1 a,
                                         T2 b) {
        if (a == b) {
            return testing::AssertionSuccess();
        }
        std::stringstream ss;
        ss  << "Expected equality of these values:\n"
            << "\t" << a_expr << "\n"
            << "\t\t" << "Which is: " << std::oct << a << "\n"
            << "\t" << b_expr << "\n"
            << "\t\t" << "Which is: " << std::oct << b;

        return testing::AssertionFailure() << ss.str();
    }
}

namespace templateFixtureClasses {
    template <class T, int N>
    class ruCubePartialStateBaseParameterizedTestFixture: public testing::TestWithParam<std::tuple<T, uint32_t, uint32_t>> {
        public:
           struct toString {
              template <class ParamType>
              std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                 const auto& [intPieces, piecesMask, expected] = testData.param;

                 std::stringstream ss;
                 ss << std::oct << "pieces_" << std::setw(N) << std::setfill('0') << intPieces << "_mask_" << std::bitset<8>(piecesMask);
                 return ss.str();
              }
           };

        protected:
            ruCube cube;
    };

    template <class T>
    class ruCubeIsSolvedBaseParameterizedTestFixture: public testing::TestWithParam<std::tuple<std::vector<uint8_t>, std::tuple<uint64_t, uint32_t>, bool>> {
        public:
            struct toString {
                template <class ParamType>
                    std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto& [scramble, masks, expected] = testData.param;
                    const auto& [cornersMask, edgesMask] = masks;

                    std::stringstream ss;
                    bool compressSolution = true;
                    bool alnumMoves = true;
                    ss  << std::oct << "masks_" << std::setw(12) << std::setfill('0') << cornersMask << "_"
                        << std::setw(7) << edgesMask << "_"
                        << ruCubeScrambleParser::vectorScrambleToStringScramble(scramble, compressSolution, alnumMoves);
                    return ss.str();
                }
           };

        protected:
            T cube;
    };
}

#endif
