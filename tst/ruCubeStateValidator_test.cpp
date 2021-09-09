#include "gtest/gtest.h"
#include "ruCubeStateValidator.h"


TEST(ruCubeStateValidatorTest, isVectEdgesValidTest) {
    ruCubeStateValidator validator;

    const std::vector<std::vector<int8_t>> permutations {
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
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(permutations), true);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        ASSERT_EQ(expectedValidities[i], validator.isVectEdgesValid(permutations[i]));
    }
}

TEST(ruCubeStateValidatorTest, isVectEdgesValidNegativeTest) {
    ruCubeStateValidator validator;

    const std::vector<std::vector<int8_t>> permutations {
        { },
        { -1 },
        { 0 },
        { 0, 1 },
        { 0, 1, 2 },
        { 0, 1, 2, 3 },
        { 0, 1, 2, 3, 4 },
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5, 6, 7 },
        { 0, 1, 2, 3, 4, 4, 5 },
        { 0, 1, 2, 3, 4, 5, 7 },
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(permutations), false);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        ASSERT_EQ(expectedValidities[i], validator.isVectEdgesValid(permutations[i]));
    }
}

TEST(ruCubeStateValidatorTest, isVectCornersPermValidTest) {
    ruCubeStateValidator validator;

    const std::vector<std::vector<int8_t>> permutations {
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
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(permutations), true);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        ASSERT_EQ(expectedValidities[i], validator.isVectCornersPermValid(permutations[i]));
    }
}

TEST(ruCubeStateValidatorTest, isVectCornersPermValidNegativeTest) {
    ruCubeStateValidator validator;

    const std::vector<std::vector<int8_t>> permutations {
        { },
        { -1 },
        { 0 },
        { 0, 1 },
        { 0, 1, 2 },
        { 0, 1, 2, 3 },
        { 0, 1, 2, 3, 4 },
        { 0, 1, 2, 3, 4, 5, 6 },
        { 0, 1, 2, 3, 4, 5, 6, 7 },
        { 0, 1, 2, 3, 4, 4, 5 },
        { 0, 1, 2, 3, 4, 7 },
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(permutations), false);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        ASSERT_EQ(expectedValidities[i], validator.isVectCornersPermValid(permutations[i]));
    }
}

TEST(ruCubeStateValidatorTest, isVectCornersOrientValidTest) {
    ruCubeStateValidator validator;

    const std::vector<std::vector<int8_t>> orientations {
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
        { 1, 2, 1, 2, 1, 2 },
        { 2, 0, 2, 0, 2, 0 },
        { 1, 0, 1, 0, 1, 0 },
        { 2, 1, 2, 0, 2, 2 },
        { 0, 0, 1, 0, 1, 1 },
        { 2, 1, 1, 0, 1, 1 },
        { 0, 1, 1, 2, 1, 1 },
        { 0, 1, 1, 2, 1, 1 },


        { -1,  1,  1,  2,  1,  1 },
        {  0,  1, -1, -1,  1,  1 },
        { -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1,  0 },
        { -1, -1,  2, -1, -1, -1 },
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(orientations), true);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        ASSERT_EQ(expectedValidities[i], validator.isVectCornersOrientValid(orientations[i]));
    }
}

TEST(ruCubeStateValidatorTest, isVectCornersOrientValidNegativeTest) {
    ruCubeStateValidator validator;

    const std::vector<std::vector<int8_t>> orientations {
        { 1, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0 },
        { 1, 2, 0, 0, 0, 2 },
        { 0, 0, 0, 4, 0, 0 },
        { 0, 0, 0, 3, 0, 0 },
        {  },
        { 3 },
        { 1, 2 },
        { 1, 2, 1, 2, 1, 2, 1, 2 },
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(orientations), false);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        ASSERT_EQ(expectedValidities[i], validator.isVectCornersOrientValid(orientations[i]));
    }
}

TEST(ruCubeStateValidatorTest, isVectCubeStateSolveableTest) {
    ruCubeStateValidator validator;

    const std::vector<std::tuple<std::vector<int8_t>, std::vector<int8_t>, std::vector<int8_t>>> cubeStates {
        { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 1, 2, 0, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 1, 2, 1, 2, 1, 2 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 1, 2, 1, 2, 1, 2 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },
        { { 1, 1, 1, 2, 2, 2 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5, 6 } },

        { { 1, 1, 1, 0, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 5, 6, 4 } },
        { { 1, 2, 1, 0, 0, 2 }, { 0, 1, 2, 3, 4, 5 }, { 2, 0, 1, 3, 5, 6, 4 } },
        { { 1, 2, 1, 2, 0, 0 }, { 0, 1, 2, 3, 4, 5 }, { 1, 2, 0, 3, 5, 6, 4 } },
        { { 1, 1, 1, 0, 1, 2 }, { 3, 2, 0, 4, 1, 5 }, { 0, 2, 5, 3, 1, 6, 4 } },
        { { 1, 2, 2, 1, 1, 2 }, { 3, 1, 4, 0, 2, 5 }, { 2, 0, 1, 3, 5, 6, 4 } },
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(cubeStates), true);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        const auto &[co, cp, ep] = cubeStates[i];
        ASSERT_EQ(expectedValidities[i], validator.isVectCubeStateSolveableQuick(co, cp, ep));
        ASSERT_EQ(expectedValidities[i], validator.isVectCubeStateSolveableFull(co, cp, ep));
    }
}

TEST(ruCubeStateValidatorTest, isVectCubeStateSolveableNegativeTest) {
    ruCubeStateValidator validator;

    const std::vector<std::tuple<std::vector<int8_t>, std::vector<int8_t>, std::vector<int8_t>>> cubeStates {
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
    };

    const std::vector<bool> expectedValidities = std::vector<bool> (size(cubeStates), false);

    for (uint8_t i = 0; i < size(expectedValidities); ++i) {
        const auto &[co, cp, ep] = cubeStates[i];
        ASSERT_EQ(expectedValidities[i], validator.isVectCubeStateSolveableQuick(co, cp, ep));
        ASSERT_EQ(expectedValidities[i], validator.isVectCubeStateSolveableFull(co, cp, ep));
    }
}
