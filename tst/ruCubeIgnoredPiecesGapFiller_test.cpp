#include "gtest/gtest.h"
#include "ruCubeIgnoredPiecesGapFiller.h"
#include <vector>
#include <iostream>
#include <iterator>

using cornersArray = std::array<int8_t, 6>;

TEST(ruCubeIgnoredPiecesGapFiller, cornersOrientationIgnoredGapsFillNoGapsTest) {
    ruCubeIgnoredPiecesGapFiller filler;

    const std::vector<cornersArray> cornersOrient = {
        { 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1 },
        { 0, 1, 0, 1, 0, 1 },
        { 2, 2, 2, 2, 2, 2 },
        { 2, 0, 2, 0, 2, 0 },
        { 2, 1, 2, 1, 2, 1 },
        { 2, 1, 2, 1, 2, 1 },
        { 2, 0, 2, 0, 2, 0 },
        { 2, 1, 2, 1, 0, 0 },
        { 2, 1, 2, 1, 0, 0 },
        { 2, 1, 1, 0, 1, 1 },
    };

    const std::vector<cornersArray> expectedCornersOrient = cornersOrient;

    for (uint8_t i = 0; i < size(cornersOrient); ++i) {
        auto orient = cornersOrient[i];
        ASSERT_TRUE(filler.cornersOrientationIgnoredGapsFill(orient));
        ASSERT_EQ(expectedCornersOrient[i], orient);
    }
}

TEST(ruCubeIgnoredPiecesGapFiller, cornersOrientationIgnoredGapsFillWithGapsTest) {
    ruCubeIgnoredPiecesGapFiller filler;

    std::vector<cornersArray> cornersOrient = {
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
    };

    const std::vector<cornersArray> expectedCornersOrient = {
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
    };

    for (uint8_t i = 0; i < size(cornersOrient); ++i) {
        ASSERT_TRUE(filler.cornersOrientationIgnoredGapsFill(cornersOrient[i]));
        ASSERT_EQ(expectedCornersOrient[i], cornersOrient[i]);
    }
}

TEST(ruCubeIgnoredPiecesGapFiller, permutationIgnoredGapsFillNextTest) {
    ruCubeIgnoredPiecesGapFiller filler;

    std::vector<std::tuple<std::vector<int8_t>, std::vector<int8_t>>> permutations {
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

    const std::vector<std::vector<std::tuple<std::vector<int8_t>, std::vector<int8_t>>>> expectedPermutations {
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

    for (uint8_t i = 0; i < size(permutations); ++i) {
        auto& [cp, ep] = permutations[i];
        filler.permutationIgnoredGapsFillInit(cp, ep);

        uint j = 0;
        while (filler.permutationIgnoredGapsFillNext(cp, ep)) {
            const auto& [ecp, eep] = expectedPermutations[i][j];
//            std::cout << "---------------i = " << (int) i << ": " << (int)j << std::endl;
//            std::cout << "cp and ecp" << std::endl;
//            std::copy(begin(cp), end(cp), std::ostream_iterator<int>(std::cout, " "));
//            std::cout << std::endl;
//            std::copy(begin(ecp), end(ecp), std::ostream_iterator<int>(std::cout, " "));
//            std::cout << std::endl;
//            std::cout << "ep and eep" << std::endl;
//            std::copy(begin(ep), end(ep), std::ostream_iterator<int>(std::cout, " "));
//            std::cout << std::endl;
//            std::copy(begin(eep), end(eep), std::ostream_iterator<int>(std::cout, " "));
//            std::cout << std::endl;
            ASSERT_EQ(ecp, cp);
            ASSERT_EQ(eep, ep);
            ++j;
        }

    }
}

