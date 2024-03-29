#include "gtest/gtest.h"
#include "ruCubeStateValidator.h"
#include "testCustomDefinitions.h"

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

namespace {
    class ruCubeStateValidatorIsVectEdgesValidTestTestFixture: public testing::TestWithParam<std::tuple<edgesArray, bool>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    ruCubeStateConverter conv;
                    const auto &[edgesPerm, expected] = testData.param;


                    return conv.containerToString(edgesPerm);
                }
            };

        protected:
            ruCubeStateValidator validator;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeStateValidatorTests,
        ruCubeStateValidatorIsVectEdgesValidTestTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<edgesArray, bool> (
            {
                { 0, 1, 2, 3, 4, 5, 6, },
                { 0, 1, 2, 3, 4, 6, 5, },
                { 0, 1, 2, 3, 5, 4, 6, },
                { 0, 1, 2, 3, 5, 6, 4, },
                { 0, 1, 2, 3, 6, 4, 5, },
                { 0, 1, 2, 3, 6, 5, 4, },
                { 0, 1, 2, 4, 3, 5, 6, },
                { 0, 1, 2, 4, 3, 6, 5, },
                { 0, 1, 2, 4, 5, 3, 6, },
                { 0, 1, 2, 4, 5, 6, 3, },
                { 0, 1, 2, 4, 6, 3, 5, },
                { 0, 1, 2, 4, 6, 5, 3, },
                { 0, 1, 2, 5, 3, 4, 6, },
                { 0, 1, 2, 5, 3, 6, 4, },
                { 0, 1, 2, 5, 4, 3, 6, },
                { 0, 1, 2, 5, 4, 6, 3, },
                { 0, 1, 2, 5, 6, 3, 4, },
                { 0, 1, 2, 5, 6, 4, 3, },
                { 0, 1, 2, 6, 3, 4, 5, },
                { 0, 1, 2, 6, 3, 5, 4, },
                { 0, 1, 2, 6, 4, 3, 5, },
                { 0, 1, 2, 6, 4, 5, 3, },
                { 0, 1, 2, 6, 5, 3, 4, },
                { 0, 1, 2, 6, 5, 4, 3, },
                { 0, 1, 3, 2, 4, 5, 6, },
                { 0, 1, 3, 2, 4, 6, 5, },
                { 0, 1, 3, 2, 5, 4, 6, },
                { 0, 1, 3, 2, 5, 6, 4, },
                { 0, 1, 3, 2, 6, 4, 5, },
                { 0, 1, 3, 2, 6, 5, 4, },
                { 0, 1, 3, 4, 2, 5, 6, },
                { 0, 1, 3, 4, 2, 6, 5, },
                { 0, 1, 3, 4, 5, 2, 6, },
                { 0, 1, 3, 4, 5, 6, 2, },
                { 0, 1, 3, 4, 6, 2, 5, },
                { 0, 1, 3, 4, 6, 5, 2, },
                { 0, 1, 3, 5, 2, 4, 6, },
                { 0, 1, 3, 5, 2, 6, 4, },
                { 0, 1, 3, 5, 4, 2, 6, },
                { 0, 1, 3, 5, 4, 6, 2, },
                { 0, 1, 3, 5, 6, 2, 4, },
                { 0, 1, 3, 5, 6, 4, 2, },
                { 0, 1, 3, 6, 2, 4, 5, },
                { 0, 1, 3, 6, 2, 5, 4, },
                { 0, 1, 3, 6, 4, 2, 5, },
                { 0, 1, 3, 6, 4, 5, 2, },
                { 0, 1, 3, 6, 5, 2, 4, },
                { 0, 1, 3, 6, 5, 4, 2, },
                { 0, 1, 4, 2, 3, 5, 6, },
                { 0, 1, 4, 2, 3, 6, 5, },
                { 0, 1, 4, 2, 5, 3, 6, },
                { 0, 1, 4, 2, 5, 6, 3, },
                { 0, 1, 4, 2, 6, 3, 5, },
                { 0, 1, 4, 2, 6, 5, 3, },
                { 0, 1, 4, 3, 2, 5, 6, },
                { 0, 1, 4, 3, 2, 6, 5, },
                { 0, 1, 4, 3, 5, 2, 6, },
                { 0, 1, 4, 3, 5, 6, 2, },
                { 0, 1, 4, 3, 6, 2, 5, },
                { 0, 1, 4, 3, 6, 5, 2, },
                { 0, 1, 4, 5, 2, 3, 6, },
                { 0, 1, 4, 5, 2, 6, 3, },
                { 0, 1, 4, 5, 3, 2, 6, },
                { 0, 1, 4, 5, 3, 6, 2, },
                { 0, 1, 4, 5, 6, 2, 3, },
                { 0, 1, 4, 5, 6, 3, 2, },
                { 0, 1, 4, 6, 2, 3, 5, },
                { 0, 1, 4, 6, 2, 5, 3, },
                { 0, 1, 4, 6, 3, 2, 5, },
                { 0, 1, 4, 6, 3, 5, 2, },
                { 0, 1, 4, 6, 5, 2, 3, },
                { 0, 1, 4, 6, 5, 3, 2, },
                { 0, 1, 5, 2, 3, 4, 6, },
                { 0, 1, 5, 2, 3, 6, 4, },
                { 0, 1, 5, 2, 4, 3, 6, },
                { 0, 1, 5, 2, 4, 6, 3, },
                { 0, 1, 5, 2, 6, 3, 4, },
                { 0, 1, 5, 2, 6, 4, 3, },
                { 0, 1, 5, 3, 2, 4, 6, },
                { 0, 1, 5, 3, 2, 6, 4, },
                { 0, 1, 5, 3, 4, 2, 6, },
                { 0, 1, 5, 3, 4, 6, 2, },
                { 0, 1, 5, 3, 6, 2, 4, },
                { 0, 1, 5, 3, 6, 4, 2, },
                { 0, 1, 5, 4, 2, 3, 6, },
                { 0, 1, 5, 4, 2, 6, 3, },
                { 0, 1, 5, 4, 3, 2, 6, },
                { 0, 1, 5, 4, 3, 6, 2, },
                { 0, 1, 5, 4, 6, 2, 3, },
                { 0, 1, 5, 4, 6, 3, 2, },
                { 0, 1, 5, 6, 2, 3, 4, },
                { 0, 1, 5, 6, 2, 4, 3, },
                { 0, 1, 5, 6, 3, 2, 4, },
                { 0, 1, 5, 6, 3, 4, 2, },
                { 0, 1, 5, 6, 4, 2, 3, },
                { 0, 1, 5, 6, 4, 3, 2, },
                { 0, 1, 6, 2, 3, 4, 5, },
                { 0, 1, 6, 2, 3, 5, 4, },
                { 0, 1, 6, 2, 4, 3, 5, },
                { 0, 1, 6, 2, 4, 5, 3, },
                { 0, 1, 6, 2, 5, 3, 4, },
                { -1,  1,  6,  2,  5, -1,  4 },
                { -1, -1, -1, -1, -1, -1, -1 },

                { 0, 1, 2, 3, 4, 4, 5 },
                { 0, 1, 2, 3, 4, 5, 7 },
                { 0, 3, 2, 3, 4, 5, 7 },
            },
            testDataGenerators::vectorsConcat(std::vector<bool>(103, true), std::vector<bool>(3, false))
        )),
        ruCubeStateValidatorIsVectEdgesValidTestTestFixture::toString()
    );

    TEST_P(ruCubeStateValidatorIsVectEdgesValidTestTestFixture, isVectEdgesValidTest) {
        const auto &[edgesPerm, expected] = GetParam();

        ASSERT_EQ(expected, validator.isVectEdgesValid(edgesPerm));
    }
}

namespace {
    class ruCubeStateValidatorIsVectCornersPermValidTestTestFixture: public testing::TestWithParam<std::tuple<cornersArray, bool>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    ruCubeStateConverter conv;
                    const auto &[cornersPerm, expected] = testData.param;


                    return conv.containerToString(cornersPerm);
                }
            };

        protected:
            ruCubeStateValidator validator;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeStateValidatorTests,
        ruCubeStateValidatorIsVectCornersPermValidTestTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<cornersArray, bool> (
            {
                { 0, 1, 2, 3, 4, 5, },
                { 0, 1, 2, 3, 5, 4, },
                { 0, 1, 2, 4, 3, 5, },
                { 0, 1, 2, 4, 5, 3, },
                { 0, 1, 2, 5, 3, 4, },
                { 0, 1, 2, 5, 4, 3, },
                { 0, 1, 3, 2, 4, 5, },
                { 0, 1, 3, 2, 5, 4, },
                { 0, 1, 3, 4, 2, 5, },
                { 0, 1, 3, 4, 5, 2, },
                { 0, 1, 3, 5, 2, 4, },
                { 0, 1, 3, 5, 4, 2, },
                { 0, 1, 4, 2, 3, 5, },
                { 0, 1, 4, 2, 5, 3, },
                { 0, 1, 4, 3, 2, 5, },
                { 0, 1, 4, 3, 5, 2, },
                { 0, 1, 4, 5, 2, 3, },
                { 0, 1, 4, 5, 3, 2, },
                { 0, 1, 5, 2, 3, 4, },
                { 0, 1, 5, 2, 4, 3, },
                { 0, 1, 5, 3, 2, 4, },
                { 0, 1, 5, 3, 4, 2, },
                { 0, 1, 5, 4, 2, 3, },
                { 0, 1, 5, 4, 3, 2, },
                { 0, 2, 1, 3, 4, 5, },
                { 0, 2, 1, 3, 5, 4, },
                { 0, 2, 1, 4, 3, 5, },
                { 0, 2, 1, 4, 5, 3, },
                { 0, 2, 1, 5, 3, 4, },
                { 0, 2, 1, 5, 4, 3, },
                { 0, 2, 3, 1, 4, 5, },
                { 0, 2, 3, 1, 5, 4, },
                { 0, 2, 3, 4, 1, 5, },
                { 0, 2, 3, 4, 5, 1, },
                { 0, 2, 3, 5, 1, 4, },
                { 0, 2, 3, 5, 4, 1, },
                { 0, 2, 4, 1, 3, 5, },
                { 0, 2, 4, 1, 5, 3, },
                { 0, 2, 4, 3, 1, 5, },
                { 0, 2, 4, 3, 5, 1, },
                { 0, 2, 4, 5, 1, 3, },
                { 0, 2, 4, 5, 3, 1, },
                { 0, 2, 5, 1, 3, 4, },
                { 0, 2, 5, 1, 4, 3, },
                { 0, 2, 5, 3, 1, 4, },
                { 0, 2, 5, 3, 4, 1, },
                { 0, 2, 5, 4, 1, 3, },
                { 0, 2, 5, 4, 3, 1, },
                { 0, 3, 1, 2, 4, 5, },
                { 0, 3, 1, 2, 5, 4, },
                { 0, 3, 1, 4, 2, 5, },
                { 0, 3, 1, 4, 5, 2, },
                { 0, 3, 1, 5, 2, 4, },
                { 0, 3, 1, 5, 4, 2, },
                { 0, 3, 2, 1, 4, 5, },
                { 0, 3, 2, 1, 5, 4, },
                { 0, 3, 2, 4, 1, 5, },
                { 0, 3, 2, 4, 5, 1, },
                { 0, 3, 2, 5, 1, 4, },
                { 0, 3, 2, 5, 4, 1, },
                { 0, 3, 4, 1, 2, 5, },
                { 0, 3, 4, 1, 5, 2, },
                { 0, 3, 4, 2, 1, 5, },
                { 0, 3, 4, 2, 5, 1, },
                { 0, 3, 4, 5, 1, 2, },
                { 0, 3, 4, 5, 2, 1, },
                { 0, 3, 5, 1, 2, 4, },
                { 0, 3, 5, 1, 4, 2, },
                { 0, 3, 5, 2, 1, 4, },
                { 0, 3, 5, 2, 4, 1, },
                { 0, 3, 5, 4, 1, 2, },
                { 0, 3, 5, 4, 2, 1, },
                { 0, 4, 1, 2, 3, 5, },
                { 0, 4, 1, 2, 5, 3, },
                { 0, 4, 1, 3, 2, 5, },
                { 0, 4, 1, 3, 5, 2, },
                { 0, 4, 1, 5, 2, 3, },
                { 0, 4, 1, 5, 3, 2, },
                { 0, 4, 2, 1, 3, 5, },
                { 0, 4, 2, 1, 5, 3, },
                { 0, 4, 2, 3, 1, 5, },
                { 0, 4, 2, 3, 5, 1, },
                { 0, 4, 2, 5, 1, 3, },
                { 0, 4, 2, 5, 3, 1, },
                { 0, 4, 3, 1, 2, 5, },
                { 0, 4, 3, 1, 5, 2, },
                { 0, 4, 3, 2, 1, 5, },
                { 0, 4, 3, 2, 5, 1, },
                { 0, 4, 3, 5, 1, 2, },
                { 0, 4, 3, 5, 2, 1, },
                { 0, 4, 5, 1, 2, 3, },
                { 0, 4, 5, 1, 3, 2, },
                { 0, 4, 5, 2, 1, 3, },
                { 0, 4, 5, 2, 3, 1, },
                { 0, 4, 5, 3, 1, 2, },
                { 0, 4, 5, 3, 2, 1, },
                { 0, 5, 1, 2, 3, 4, },
                { 0, 5, 1, 2, 4, 3, },
                { 0, 5, 1, 3, 2, 4, },
                { 0, 5, 1, 3, 4, 2, },
                { 0, 5, 1, 4, 2, 3, },
                {  0,  5,  1,  4,  2, -1, },
                {  0, -1,  1,  4,  2,  3, },
                { -1, -1, -1, -1, -1, -1, },

                { 0, 1, 2, 3, 4, 7 },
                { 0, 1, 4, 3, 4, 7 },
                { 7, 1, 2, 3, 4, 7 },
                { 1, 1, 1, 1, 1, 1 },
            },
            testDataGenerators::vectorsConcat(std::vector<bool>(104, true), std::vector<bool>(4, false))
        )),
        ruCubeStateValidatorIsVectCornersPermValidTestTestFixture::toString()
    );

    TEST_P(ruCubeStateValidatorIsVectCornersPermValidTestTestFixture, isVectCornersPermValidTest) {
        const auto &[cornersPerm, expected] = GetParam();

        ASSERT_EQ(expected, validator.isVectCornersPermValid(cornersPerm));
    }
}

namespace {
    class ruCubeStateValidatorIsVectCornersOrientValidTestTestFixture: public testing::TestWithParam<std::tuple<cornersArray, bool>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    ruCubeStateConverter conv;
                    const auto &[cornersOrient, expected] = testData.param;


                    return conv.containerToString(cornersOrient);
                }
            };

        protected:
            ruCubeStateValidator validator;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeStateValidatorTests,
        ruCubeStateValidatorIsVectCornersOrientValidTestTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<cornersArray, bool> (
            {
                { 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 1, 2 },
                { 0, 0, 1, 2, 1, 2 },
                { 1, 2, 1, 2, 1, 2 },
                { 1, 2, 1, 2, 0, 0 },
                { 1, 2, 0, 0, 0, 0 },
                { 2, 1, 1, 2, 0, 0 },
                { 2, 2, 2, 2, 2, 2 },
                { 1, 1, 1, 1, 1, 1 },
                { 2, 1, 2, 1, 2, 1 },
                { 2, 0, 2, 0, 2, 0 },
                { 1, 0, 1, 0, 1, 0 },
                { 2, 1, 2, 0, 2, 2 },
                { 0, 0, 1, 0, 1, 1 },
                { 2, 1, 1, 0, 1, 1 },
                { 0, 1, 1, 2, 1, 1 },
                { -1,  1,  1,  2,  1,  1 },
                {  0,  1, -1, -1,  1,  1 },
                { -1, -1, -1, -1, -1, -1 },
                { -1, -1, -1, -1, -1,  0 },
                { -1, -1,  2, -1, -1, -1 },

                { 1, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 1, 0, 0 },
                { 1, 2, 0, 0, 0, 2 },
                { 0, 0, 0, 4, 0, 0 },
                { 0, 0, 0, 3, 0, 0 },
                { 0, 0, 0, 3, 1, 0 },
                { 9, 0, 0, 3, 0, 0 },
            },
            testDataGenerators::vectorsConcat(std::vector<bool>(21, true), std::vector<bool>(7, false))
        )),
        ruCubeStateValidatorIsVectCornersOrientValidTestTestFixture::toString()
    );

    TEST_P(ruCubeStateValidatorIsVectCornersOrientValidTestTestFixture, isVectCornersOrientValidTest) {
        const auto &[cornersOrient, expected] = GetParam();

        ASSERT_EQ(expected, validator.isVectCornersOrientValid(cornersOrient));
    }
}

namespace {
    class ruCubeStateValidatorIsCubeStateSolveableTestFixture: public testing::TestWithParam<std::tuple<std::tuple<cornersArray, cornersArray, edgesArray>, bool>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    ruCubeStateConverter conv;
                    const auto &[cubeState, expected] = testData.param;
                    const auto &[co, cp, ep] = cubeState;

                    return conv.containerToString(co) + "_" + conv.containerToString(cp) + "_" + conv.containerToString(ep);
                }
            };

        protected:
            ruCubeStateValidator validator;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeStateValidatorTests,
        ruCubeStateValidatorIsCubeStateSolveableTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::tuple<cornersArray, cornersArray, edgesArray>, bool> (
            {
                { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 2, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 2, 1, 2, 1, 2 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 2, 1, 2, 2, 1 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 1, 1, 2, 2, 2 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 1, 1, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 5, 6, 4 } },
                { { 1, 2, 1, 0, 0, 2 }, { 0, 1, 2, 3, 4, 5 }, { 2, 0, 1, 3, 5, 6, 4 } },
                { { 1, 2, 1, 2, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 1, 2, 0, 3, 5, 6, 4 } },
                { { 1, 1, 1, 0, 1, 2 }, { 3, 2, 0, 4, 1, 5 }, { 0, 2, 5, 3, 1, 6, 4 } },
                { { 1, 2, 2, 1, 1, 2 }, { 3, 1, 4, 0, 2, 5 }, { 2, 0, 1, 3, 5, 6, 4 } },

                { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 5, 4 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 1, 0, 2, 3, 4, 5, 6 } },
                { { 1, 1, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 2, 1, 2, 1, 2 }, { 5, 1, 2, 3, 4, 0 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 1, 1, 2, 2, 2 }, { 2, 1, 0, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
                { { 1, 1, 1, 0, 0, 0 }, { 0, 1, 3, 2, 4, 5 }, { 0, 1, 2, 3, 5, 6, 4 } },
                { { 1, 2, 1, 0, 0, 2 }, { 0, 1, 2, 3, 4, 5 }, { 2, 0, 1, 5, 3, 6, 4 } },
                { { 1, 2, 1, 2, 0, 0 }, { 0, 1, 2, 4, 5, 3 }, { 1, 2, 0, 3, 5, 6, 4 } },
                { { 1, 1, 1, 0, 1, 2 }, { 3, 0, 2, 4, 1, 5 }, { 1, 2, 5, 3, 0, 6, 4 } },
                { { 1, 2, 2, 1, 1, 2 }, { 3, 1, 0, 2, 4, 5 }, { 2, 0, 1, 3, 5, 6, 4 } },
            },
            testDataGenerators::vectorsConcat(std::vector<bool>(10, true), std::vector<bool>(10, false))
        )),
        ruCubeStateValidatorIsCubeStateSolveableTestFixture::toString()
    );

    TEST_P(ruCubeStateValidatorIsCubeStateSolveableTestFixture, isVectCubeStateSolveableFullTest) {
        const auto &[cubeState, expected] = GetParam();
        const auto &[co, cp, ep] = cubeState;
        ASSERT_EQ(expected, validator.isVectCubeStateSolveableQuick(co, cp, ep));
    }

    TEST_P(ruCubeStateValidatorIsCubeStateSolveableTestFixture, isVectCubeStateSolveableQuickTest) {
        const auto &[cubeState, expected] = GetParam();
        const auto &[co, cp, ep] = cubeState;
        ASSERT_EQ(expected, validator.isVectCubeStateSolveableFull(co, cp, ep));
    }
}
