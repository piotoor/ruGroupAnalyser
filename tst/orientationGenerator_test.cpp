#include "gtest/gtest.h"
#include "orientationGenerator.h"
#include "ruCubeStateConverter.h"
#include <vector>
#include <iostream>


namespace {
    class orientationGeneratorTestFixture: public testing::TestWithParam<std::tuple<cornersArray, cornersArray, std::vector<cornersArray>>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto& [locked, ignored, expected] = testData.param;

                    ruCubeStateConverter conv;
                    std::string lockedStr = conv.vectToString(locked);
                    std::string ignoredStr = conv.vectToString(ignored);

                    return lockedStr + "_" + ignoredStr;
                }
            };

        protected:
            orientationGenerator generator;

    };

    INSTANTIATE_TEST_SUITE_P (
        orientationGeneratorTest,
        orientationGeneratorTestFixture,
        ::testing::Values(std::tuple<cornersArray, cornersArray, std::vector<cornersArray>> {
            { -1, -1, -1, -1, -1, -1 },
            { 0, 0, 0, 0, 0, 0 },
            {
                { 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 1, 2 },
                { 0, 0, 0, 0, 2, 1 },
                { 0, 0, 0, 1, 0, 2 },
                { 0, 0, 0, 1, 1, 1 },
                { 0, 0, 0, 1, 2, 0 },
                { 0, 0, 0, 2, 0, 1 },
                { 0, 0, 0, 2, 1, 0 },
                { 0, 0, 0, 2, 2, 2 },
                { 0, 0, 1, 0, 0, 2 },
                { 0, 0, 1, 0, 1, 1 },
                { 0, 0, 1, 0, 2, 0 },
                { 0, 0, 1, 1, 0, 1 },
                { 0, 0, 1, 1, 1, 0 },
                { 0, 0, 1, 1, 2, 2 },
                { 0, 0, 1, 2, 0, 0 },
                { 0, 0, 1, 2, 1, 2 },
                { 0, 0, 1, 2, 2, 1 },
                { 0, 0, 2, 0, 0, 1 },
                { 0, 0, 2, 0, 1, 0 },
                { 0, 0, 2, 0, 2, 2 },
                { 0, 0, 2, 1, 0, 0 },
                { 0, 0, 2, 1, 1, 2 },
                { 0, 0, 2, 1, 2, 1 },
                { 0, 0, 2, 2, 0, 2 },
                { 0, 0, 2, 2, 1, 1 },
                { 0, 0, 2, 2, 2, 0 },
                { 0, 1, 0, 0, 0, 2 },
                { 0, 1, 0, 0, 1, 1 },
                { 0, 1, 0, 0, 2, 0 },
                { 0, 1, 0, 1, 0, 1 },
                { 0, 1, 0, 1, 1, 0 },
                { 0, 1, 0, 1, 2, 2 },
                { 0, 1, 0, 2, 0, 0 },
                { 0, 1, 0, 2, 1, 2 },
                { 0, 1, 0, 2, 2, 1 },
                { 0, 1, 1, 0, 0, 1 },
                { 0, 1, 1, 0, 1, 0 },
                { 0, 1, 1, 0, 2, 2 },
                { 0, 1, 1, 1, 0, 0 },
                { 0, 1, 1, 1, 1, 2 },
                { 0, 1, 1, 1, 2, 1 },
                { 0, 1, 1, 2, 0, 2 },
                { 0, 1, 1, 2, 1, 1 },
                { 0, 1, 1, 2, 2, 0 },
                { 0, 1, 2, 0, 0, 0 },
                { 0, 1, 2, 0, 1, 2 },
                { 0, 1, 2, 0, 2, 1 },
                { 0, 1, 2, 1, 0, 2 },
                { 0, 1, 2, 1, 1, 1 },
                { 0, 1, 2, 1, 2, 0 },
                { 0, 1, 2, 2, 0, 1 },
                { 0, 1, 2, 2, 1, 0 },
                { 0, 1, 2, 2, 2, 2 },
                { 0, 2, 0, 0, 0, 1 },
                { 0, 2, 0, 0, 1, 0 },
                { 0, 2, 0, 0, 2, 2 },
                { 0, 2, 0, 1, 0, 0 },
                { 0, 2, 0, 1, 1, 2 },
                { 0, 2, 0, 1, 2, 1 },
                { 0, 2, 0, 2, 0, 2 },
                { 0, 2, 0, 2, 1, 1 },
                { 0, 2, 0, 2, 2, 0 },
                { 0, 2, 1, 0, 0, 0 },
                { 0, 2, 1, 0, 1, 2 },
                { 0, 2, 1, 0, 2, 1 },
                { 0, 2, 1, 1, 0, 2 },
                { 0, 2, 1, 1, 1, 1 },
                { 0, 2, 1, 1, 2, 0 },
                { 0, 2, 1, 2, 0, 1 },
                { 0, 2, 1, 2, 1, 0 },
                { 0, 2, 1, 2, 2, 2 },
                { 0, 2, 2, 0, 0, 2 },
                { 0, 2, 2, 0, 1, 1 },
                { 0, 2, 2, 0, 2, 0 },
                { 0, 2, 2, 1, 0, 1 },
                { 0, 2, 2, 1, 1, 0 },
                { 0, 2, 2, 1, 2, 2 },
                { 0, 2, 2, 2, 0, 0 },
                { 0, 2, 2, 2, 1, 2 },
                { 0, 2, 2, 2, 2, 1 }
            }
        }),
        orientationGeneratorTestFixture::toString()
    );

    INSTANTIATE_TEST_SUITE_P (
        orientationGeneratorWithLockedPiecesTest,
        orientationGeneratorTestFixture,
        ::testing::ValuesIn(std::vector<std::tuple<cornersArray, cornersArray, std::vector<cornersArray>>> {
            {
                {  1,  0,  2, -1, -1, -1 },
                { 0, 0, 0, 0, 0, 0 },
                {
                    { 1, 0, 2, 0, 0, 0 },
                    { 1, 0, 2, 0, 1, 2 },
                    { 1, 0, 2, 0, 2, 1 },
                    { 1, 0, 2, 1, 0, 2 },
                    { 1, 0, 2, 1, 1, 1 },
                    { 1, 0, 2, 1, 2, 0 },
                    { 1, 0, 2, 2, 0, 1 },
                    { 1, 0, 2, 2, 1, 0 },
                    { 1, 0, 2, 2, 2, 2 }
                }
            },
            {
                { -1,  1,  0,  2, -1, -1 },
                { 0, 0, 0, 0, 0, 0 },
                {
                    { 0, 1, 0, 2, 0, 0 },
                    { 0, 1, 0, 2, 1, 2 },
                    { 0, 1, 0, 2, 2, 1 },
                    { 1, 1, 0, 2, 0, 2 },
                    { 1, 1, 0, 2, 1, 1 },
                    { 1, 1, 0, 2, 2, 0 },
                    { 2, 1, 0, 2, 0, 1 },
                    { 2, 1, 0, 2, 1, 0 },
                    { 2, 1, 0, 2, 2, 2 }
                },
            },
        }),
        orientationGeneratorTestFixture::toString()
    );

    INSTANTIATE_TEST_SUITE_P (
        orientationGeneratorWithIgnoredPiecesTest,
        orientationGeneratorTestFixture,
        ::testing::ValuesIn(std::vector<std::tuple<cornersArray, cornersArray, std::vector<cornersArray>>> {
            {
                { -1, -1, -1, -1, -1, -1 },
                { 1, 1, 1, 1, 1, 1 },
                {
                    { -1, -1, -1, -1, -1, -1 }
                }
            },
            {
                { -1, -1, -1, -1, -1, -1 },
                { 0, 0, 0, 0, 0, 0 },
                {
                    { 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 1, 2 },
                    { 0, 0, 0, 0, 2, 1 },
                    { 0, 0, 0, 1, 0, 2 },
                    { 0, 0, 0, 1, 1, 1 },
                    { 0, 0, 0, 1, 2, 0 },
                    { 0, 0, 0, 2, 0, 1 },
                    { 0, 0, 0, 2, 1, 0 },
                    { 0, 0, 0, 2, 2, 2 },
                    { 0, 0, 1, 0, 0, 2 },
                    { 0, 0, 1, 0, 1, 1 },
                    { 0, 0, 1, 0, 2, 0 },
                    { 0, 0, 1, 1, 0, 1 },
                    { 0, 0, 1, 1, 1, 0 },
                    { 0, 0, 1, 1, 2, 2 },
                    { 0, 0, 1, 2, 0, 0 },
                    { 0, 0, 1, 2, 1, 2 },
                    { 0, 0, 1, 2, 2, 1 },
                    { 0, 0, 2, 0, 0, 1 },
                    { 0, 0, 2, 0, 1, 0 },
                    { 0, 0, 2, 0, 2, 2 },
                    { 0, 0, 2, 1, 0, 0 },
                    { 0, 0, 2, 1, 1, 2 },
                    { 0, 0, 2, 1, 2, 1 },
                    { 0, 0, 2, 2, 0, 2 },
                    { 0, 0, 2, 2, 1, 1 },
                    { 0, 0, 2, 2, 2, 0 },
                    { 0, 1, 0, 0, 0, 2 },
                    { 0, 1, 0, 0, 1, 1 },
                    { 0, 1, 0, 0, 2, 0 },
                    { 0, 1, 0, 1, 0, 1 },
                    { 0, 1, 0, 1, 1, 0 },
                    { 0, 1, 0, 1, 2, 2 },
                    { 0, 1, 0, 2, 0, 0 },
                    { 0, 1, 0, 2, 1, 2 },
                    { 0, 1, 0, 2, 2, 1 },
                    { 0, 1, 1, 0, 0, 1 },
                    { 0, 1, 1, 0, 1, 0 },
                    { 0, 1, 1, 0, 2, 2 },
                    { 0, 1, 1, 1, 0, 0 },
                    { 0, 1, 1, 1, 1, 2 },
                    { 0, 1, 1, 1, 2, 1 },
                    { 0, 1, 1, 2, 0, 2 },
                    { 0, 1, 1, 2, 1, 1 },
                    { 0, 1, 1, 2, 2, 0 },
                    { 0, 1, 2, 0, 0, 0 },
                    { 0, 1, 2, 0, 1, 2 },
                    { 0, 1, 2, 0, 2, 1 },
                    { 0, 1, 2, 1, 0, 2 },
                    { 0, 1, 2, 1, 1, 1 },
                    { 0, 1, 2, 1, 2, 0 },
                    { 0, 1, 2, 2, 0, 1 },
                    { 0, 1, 2, 2, 1, 0 },
                    { 0, 1, 2, 2, 2, 2 },
                    { 0, 2, 0, 0, 0, 1 },
                    { 0, 2, 0, 0, 1, 0 },
                    { 0, 2, 0, 0, 2, 2 },
                    { 0, 2, 0, 1, 0, 0 },
                    { 0, 2, 0, 1, 1, 2 },
                    { 0, 2, 0, 1, 2, 1 },
                    { 0, 2, 0, 2, 0, 2 },
                    { 0, 2, 0, 2, 1, 1 },
                    { 0, 2, 0, 2, 2, 0 },
                    { 0, 2, 1, 0, 0, 0 },
                    { 0, 2, 1, 0, 1, 2 },
                    { 0, 2, 1, 0, 2, 1 },
                    { 0, 2, 1, 1, 0, 2 },
                    { 0, 2, 1, 1, 1, 1 },
                    { 0, 2, 1, 1, 2, 0 },
                    { 0, 2, 1, 2, 0, 1 },
                    { 0, 2, 1, 2, 1, 0 },
                    { 0, 2, 1, 2, 2, 2 },
                    { 0, 2, 2, 0, 0, 2 },
                    { 0, 2, 2, 0, 1, 1 },
                    { 0, 2, 2, 0, 2, 0 },
                    { 0, 2, 2, 1, 0, 1 },
                    { 0, 2, 2, 1, 1, 0 },
                    { 0, 2, 2, 1, 2, 2 },
                    { 0, 2, 2, 2, 0, 0 },
                    { 0, 2, 2, 2, 1, 2 },
                    { 0, 2, 2, 2, 2, 1 }
                },
            },
            {
                { -1, -1, -1, -1, -1, -1 },
                { 1, 1, 0, 0, 1, 1 },
                {
                    { -1, -1,  0,  0, -1, -1 },
                    { -1, -1,  0,  1, -1, -1 },
                    { -1, -1,  0,  2, -1, -1 },
                    { -1, -1,  1,  0, -1, -1 },
                    { -1, -1,  1,  1, -1, -1 },
                    { -1, -1,  1,  2, -1, -1 },
                    { -1, -1,  2,  0, -1, -1 },
                    { -1, -1,  2,  1, -1, -1 },
                    { -1, -1,  2,  2, -1, -1 }
                },
            },
        }),
        orientationGeneratorTestFixture::toString()
    );

    INSTANTIATE_TEST_SUITE_P (
        orientationGeneratorWithLockedAndIgnoredPiecesTest,
        orientationGeneratorTestFixture,
        ::testing::ValuesIn(std::vector<std::tuple<cornersArray, cornersArray, std::vector<cornersArray>>> {
            {
                {  1,  1,  1, -1, -1, -1 },
                { 0, 0, 0, 1, 1, 1 },
                {
                    {  1,  1,  1, -1, -1, -1 }
                }
            },
            {
                {  1,  2,  1,  2, -1, -1 },
                { 0, 0, 0, 0, 1, 0 },
                {
                    {  1,  2,  1,  2, -1,  0 }
                },
            },
            {
                { -1,  2,  1,  2,  2,  1 },
                { 1, 0, 0, 0, 0, 0 },
                {
                    { -1,  2,  1,  2,  2,  1 }
                },
            },
        }),
        orientationGeneratorTestFixture::toString()
    );

    TEST_P(orientationGeneratorTestFixture, generateOrientationtTest) {
        const auto &[locked, ignored, expected] = GetParam();
        auto orients = generator.generateOrientations(locked, ignored);
        orients.erase(begin(orients) + size(expected), end(orients));
        ASSERT_EQ(expected, orients);
    }
}
