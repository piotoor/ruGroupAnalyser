#include "gtest/gtest.h"
#include "ruCubeIgnoredPiecesGapFiller.h"
#include "testCustomDefinitions.h"
#include "ruCubeStateConverter.h"
#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;


namespace {
    class ruCubeIgnoredOrientationGapFillerTestFixture: public testing::TestWithParam<std::tuple<cornersArray, cornersArray>>{
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[co, expected] = testData.param;

                    ruCubeStateConverter conv;
                    std::string cornersOrientStr = conv.vectToString(co);
                    return cornersOrientStr;
                }
            };

        protected:
            ruCubeIgnoredPiecesGapFiller filler;
    };

    INSTANTIATE_TEST_SUITE_P (
        cornersOrientationIgnoredGapsFillNoGapsTests,
        ruCubeIgnoredOrientationGapFillerTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<cornersArray, cornersArray> (
            {
                { 0, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 1, 1, 1 },
                { 0, 1, 0, 1, 0, 1 },
                { 2, 2, 2, 2, 2, 2 },
                { 2, 0, 2, 0, 2, 0 },
                { 2, 1, 2, 1, 2, 1 },
                { 2, 1, 2, 1, 0, 0 },
                { 2, 1, 1, 0, 1, 1 },
            },
            {
                { 0, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 1, 1, 1 },
                { 0, 1, 0, 1, 0, 1 },
                { 2, 2, 2, 2, 2, 2 },
                { 2, 0, 2, 0, 2, 0 },
                { 2, 1, 2, 1, 2, 1 },
                { 2, 1, 2, 1, 0, 0 },
                { 2, 1, 1, 0, 1, 1 },
            }
        )),
        ruCubeIgnoredOrientationGapFillerTestFixture::toString()
    );

    INSTANTIATE_TEST_SUITE_P (
        cornersOrientationIgnoredGapsFillWithGapsTests,
        ruCubeIgnoredOrientationGapFillerTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<cornersArray, cornersArray> (
            {
                {  0,  0, -1,  0,  0,  0 },
                { -1, -1,  1,  1,  1,  1 },
                {  0, -1,  0, -1,  0, -1 },
                { -1, -1,  2, -1, -1,  2 },
                {  2,  0,  2,  0,  2, -1 },
                {  2,  1, -1, -1, -1, -1 },
                { -1, -1,  2,  1, -1,  1 },
                { -1,  1, -1,  1, -1,  1 },
                {  2, -1,  2, -1,  0,  0 },
                {  2,  1,  2,  1, -1, -1 },
                {  2,  1,  1,  0, -1,  1 },
                { -1, -1, -1, -1, -1, -1 },
            },
            {
                {  0,  0,  0,  0,  0,  0 },
                {  2,  0,  1,  1,  1,  1 },
                {  0,  0,  0,  0,  0,  0 },
                {  2,  0,  2,  0,  0,  2 },
                {  2,  0,  2,  0,  2,  0 },
                {  2,  1,  0,  0,  0,  0 },
                {  2,  0,  2,  1,  0,  1 },
                {  0,  1,  0,  1,  0,  1 },
                {  2,  2,  2,  0,  0,  0 },
                {  2,  1,  2,  1,  0,  0 },
                {  2,  1,  1,  0,  1,  1 },
                {  0,  0,  0,  0,  0,  0 },
            }
        )),
        ruCubeIgnoredOrientationGapFillerTestFixture::toString()
    );

    TEST_P(ruCubeIgnoredOrientationGapFillerTestFixture, cornersOrientationIgnoredGapsFill) {
        auto [cornersOrientation, expected] = GetParam();
        ASSERT_TRUE(filler.cornersOrientationIgnoredGapsFill(cornersOrientation));
        ASSERT_EQ(expected, cornersOrientation);
    }
}


namespace {
    class ruCubeIgnoredPermutationGapFillerTestFixture: public testing::TestWithParam<std::tuple<std::tuple<cornersArray, edgesArray>, std::vector<std::tuple<cornersArray, edgesArray>>>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[permutation, expected] = testData.param;
                    const auto &[cp, ep] = permutation;

                    ruCubeStateConverter conv;
                    std::string cornersPermStr = conv.vectToString(cp);
                    std::string edgesPermStr = conv.vectToString(ep);

                    return cornersPermStr + "__" + edgesPermStr;
                }
            };

        protected:
            ruCubeIgnoredPiecesGapFiller filler;
    };

    INSTANTIATE_TEST_SUITE_P (
        permutationIgnoredGapsFillWithGapsTests,
        ruCubeIgnoredPermutationGapFillerTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::tuple<cornersArray, edgesArray>, std::vector<std::tuple<cornersArray, edgesArray>>> (
            {
                { { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 5, 4, 3, 2, 1, 0 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 0, 1, 2, 3, 4, 5 }, { 6, 5, 4, 3, 2, 1, 0 } },
                { { 5, 4, 3, 2, 1, 0 }, { 6, 5, 4, 3, 2, 1, 0 } },

                { { -1,  1,  2,  3,  4,  5 }, { -1,  1,  2,  3,  4,  5,  6 } },
                { { -1,  1,  2,  3,  4,  5 }, {  0,  1,  2,  3,  4,  5,  6 } },
                { {  0,  1,  2,  3,  4,  5 }, { -1,  1,  2,  3,  4,  5,  6 } },

                { { -1,  1,  2,  3,  4, -1 }, { -1,  1,  2,  3,  4,  5, -1 } },

                { { -1,  1,  2,  3,  4, -1 }, { -1, -1,  2,  3,  4,  5, -1 } },

                { { -1, -1,  2,  3,  4, -1 }, { -1, -1,  2,  3,  4,  5, -1 } },
            },
            {
                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }}
                },
                {
                    {{ 5, 4, 3, 2, 1, 0 }, { 0, 1, 2, 3, 4, 5, 6 }}
                },
                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 6, 5, 4, 3, 2, 1, 0 }}
                },
                {
                    {{ 5, 4, 3, 2, 1, 0 }, { 6, 5, 4, 3, 2, 1, 0 }}
                },


                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }}
                },
                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }}
                },
                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }}
                },


                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 6, 1, 2, 3, 4, 5, 0 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 6, 1, 2, 3, 4, 5, 0 }}
                },


                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 6, 1, 2, 3, 4, 5, 0 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 6, 1, 2, 3, 4, 5, 0 }},
                },


                {
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 0, 1, 2, 3, 4, 5 }, { 6, 1, 2, 3, 4, 5, 0 }},

                    {{ 0, 5, 2, 3, 4, 1 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 0, 5, 2, 3, 4, 1 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 0, 5, 2, 3, 4, 1 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 0, 5, 2, 3, 4, 1 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 0, 5, 2, 3, 4, 1 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 0, 5, 2, 3, 4, 1 }, { 6, 1, 2, 3, 4, 5, 0 }},

                    {{ 1, 0, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 1, 0, 2, 3, 4, 5 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 1, 0, 2, 3, 4, 5 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 1, 0, 2, 3, 4, 5 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 1, 0, 2, 3, 4, 5 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 1, 0, 2, 3, 4, 5 }, { 6, 1, 2, 3, 4, 5, 0 }},

                    {{ 1, 5, 2, 3, 4, 0 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 1, 5, 2, 3, 4, 0 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 1, 5, 2, 3, 4, 0 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 1, 5, 2, 3, 4, 0 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 1, 5, 2, 3, 4, 0 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 1, 5, 2, 3, 4, 0 }, { 6, 1, 2, 3, 4, 5, 0 }},

                    {{ 5, 0, 2, 3, 4, 1 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 5, 0, 2, 3, 4, 1 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 5, 0, 2, 3, 4, 1 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 5, 0, 2, 3, 4, 1 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 5, 0, 2, 3, 4, 1 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 5, 0, 2, 3, 4, 1 }, { 6, 1, 2, 3, 4, 5, 0 }},

                    {{ 5, 1, 2, 3, 4, 0 }, { 0, 1, 2, 3, 4, 5, 6 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 0, 6, 2, 3, 4, 5, 1 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 1, 0, 2, 3, 4, 5, 6 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 1, 6, 2, 3, 4, 5, 0 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 6, 0, 2, 3, 4, 5, 1 }},
                    {{ 5, 1, 2, 3, 4, 0 }, { 6, 1, 2, 3, 4, 5, 0 }},
                }
            }
        )),
        ruCubeIgnoredPermutationGapFillerTestFixture::toString()
    );

    TEST_P(ruCubeIgnoredPermutationGapFillerTestFixture, permutationIgnoredGapsFill) {
        auto [permutation, expected] = GetParam();
        auto [cp, ep] = permutation;

        size_t j = 0;
        filler.permutationIgnoredGapsFillInit(cp, ep);
        while (filler.permutationIgnoredGapsFillNext(cp, ep)) {
            const auto &[ecp, eep] = expected[j];
            ASSERT_EQ(ecp, cp);
            ASSERT_EQ(eep, ep);
            ++j;
        }
    }
}
