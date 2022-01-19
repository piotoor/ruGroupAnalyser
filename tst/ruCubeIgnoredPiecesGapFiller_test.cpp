#include "gtest/gtest.h"
#include "ruCubeIgnoredPiecesGapFiller.h"
#include "testCustomDefinitions.h"
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
                    const auto &[cornersOrientation, expected] = testData.param;
                    std::string cornersOrientationStr = std::accumulate(begin(cornersOrientation),
                                                                        end(cornersOrientation),
                                                                        std::string(),
                                                                        [] (std::string a, int8_t b) {
                                                                            if (b < 0) {
                                                                                return a + "_";
                                                                            }
                                                                            return a + std::to_string(b);
                                                                        });
                    return cornersOrientationStr;
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

TEST(ruCubeIgnoredPiecesGapFiller, permutationIgnoredGapsFillNextTest) {
    ruCubeIgnoredPiecesGapFiller filler;

    std::vector<std::tuple<cornersArray, edgesArray>> permutations {
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
    };

    const std::vector<std::vector<std::tuple<cornersArray, edgesArray>>> expectedPermutations {
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
        },
    };

    for (size_t i = 0; i < size(permutations); ++i) {
        auto& [cp, ep] = permutations[i];
        filler.permutationIgnoredGapsFillInit(cp, ep);

        uint16_t j = 0;
        while (filler.permutationIgnoredGapsFillNext(cp, ep)) {
            const auto& [ecp, eep] = expectedPermutations[i][j];
            ASSERT_EQ(ecp, cp);
            ASSERT_EQ(eep, ep);
            ++j;
        }

    }
}

