#include "gtest/gtest.h"
#include "ruLutCubeGenerator.h"
#include "ruCubeSolver.h"
#include <vector>
#include <set>

using cornersArray = std::array<int8_t, 6>;

TEST(generatorParametersTest, toSolvedMasksTest) {
    std::vector<generatorParameters> params = {
        {   // LL
            { 4, 5, 6 },                // lockedEdges
            { },                        // ignoredEdges
            { 4, 5 },                   // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { -1, -1, -1, -1, 0, 0 },   // lockedCornersOrient
            { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
        },
        {   // PLL
            { 4, 5, 6 },                // lockedEdges
            { },                        // ignoredEdges
            { 4, 5 },                   // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { 0, 0, 0, 0, 0, 0 },       // lockedCornersOrient
            { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
        },
        {   // Sune no AUF
            { 4, 5, 6 },                // lockedEdges
            { },                        // ignoredEdges
            { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { 1, 0, 1, 1, 0, 0 },       // lockedCornersOrient
            { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
        },
        {   // H no AUF
            { 4, 5, 6 },                // lockedEdges
            { },                        // ignoredEdges
            { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { 1, 2, 1, 2, 0, 0 },       // lockedCornersOrient
            { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
        },
        {   // corners flip
            { 0, 1, 2, 3, 4, 5, 6 },    // lockedEdges
            { },                        // ignoredEdges
            { 0, 1, 2, 3, 4, 5 },       // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 0, 0, 0, 0, 0, 0 },       // ignoredCornersOrient
        },
        {   // permutation only
            { },                        // lockedEdges
            { },                        // ignoredEdges
            { },                        // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 1, 1, 1, 1, 1, 1 },       // ignoredCornersOrient
        },
        {   // permutation only, 2 edges ignored
            { },                        // lockedEdges
            { 3, 5 },                   // ignoredEdges
            { },                        // lockedCornersPerm
            { },                        // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 1, 1, 1, 1, 1, 1 },       // ignoredCornersOrient
        },
        {   // last F2L slot
            { 4, 5 },                   // lockedEdges
            { 0, 1, 2, 3 },             // ignoredEdges
            { 4 },                      // lockedCornersPerm
            { 0, 1, 2, 3 },             // ignoredCornersPerm
            { -1, -1, -1, -1, 0, -1 },  // lockedCornersOrient
            { 1, 1, 1, 1, 0, 0 },       // ignoredCornersOrient
        },
        {   // last two F2L slots
            { 5 },                      // lockedEdges
            { 0, 1, 2, 3 },             // ignoredEdges
            { },                        // lockedCornersPerm
            { 0, 1, 2, 3 },             // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 1, 1, 1, 1, 0, 0 },       // ignoredCornersOrient
        },
        {   // all pieces but two edges and two corners are locked. The rest is ignored.
            { 0, 1, 3, 4, 6 },          // lockedEdges
            { 2, 5 },                   // ignoredEdges
            { 0, 1, 3, 4 },             // lockedCornersPerm
            { 2, 5 },                   // ignoredCornersPerm
            { 0, 0, -1, 0, -1, 0 },     // lockedCornersOrient
            { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
        },
        {   // all pieces but three edges and two corners are locked. The rest is ignored.
            { 0, 1, 3, 6 },             // lockedEdges
            { 2, 4, 5 },                // ignoredEdges
            { 0, 1, 3, 4 },             // lockedCornersPerm
            { 2, 5 },                   // ignoredCornersPerm
            { 0, 0, -1, 0, -1, 0 },     // lockedCornersOrient
            { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
        },
        {   // two edges and two corners ignored
            { },                        // lockedEdges
            { 2, 4 },                   // ignoredEdges
            {  },                       // lockedCornersPerm
            { 2, 4 },                   // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
        },
        {   // one edge and two corners ignored
            { },                        // lockedEdges
            { 2 },                      // ignoredEdges
            {  },                       // lockedCornersPerm
            { 2, 4 },                   // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 0, 0, 1, 0, 1, 0 },       // ignoredCornersOrient
        },
        {   // one edge and one corner ignored
            { },                        // lockedEdges
            { 2 },                      // ignoredEdges
            {  },                       // lockedCornersPerm
            { 4 },                      // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            { 0, 0, 1, 0, 0, 0 },       // ignoredCornersOrient
        },
    };

    std::vector<solvedMasks> expectedSolvedMasks = {
        {
            UINT64_C(0x0000003F0000003F),
            UINT32_C(0x7F),
        },
        {
            UINT64_C(0x0000003F0000003F),
            UINT32_C(0x7F),
        },
        {
            UINT64_C(0x0000003F0000003F),
            UINT32_C(0x7F),
        },
        {
            UINT64_C(0x0000003F0000003F),
            UINT32_C(0x7F),
        },
        {
            UINT64_C(0x0000003F0000003F),
            UINT32_C(0x7F),
        },
        {
            UINT64_C(0x3F),
            UINT32_C(0x7F),
        },
        {
            UINT64_C(0x3F),
            UINT32_C(0x75),
        },
        {
            UINT64_C(0x0000000300000003),
            UINT32_C(0x07),
        },
        {
            UINT64_C(0x0000000300000003),
            UINT32_C(0x07),
        },
        {
            UINT64_C(0x0000003500000036),
            UINT32_C(0x6D),
        },
        {
            UINT64_C(0x0000003500000036),
            UINT32_C(0x69),
        },
        {
            UINT64_C(0x0000003500000035),
            UINT32_C(0x6B),
        },
        {
            UINT64_C(0x0000003500000035),
            UINT32_C(0x6F),
        },
        {
            UINT64_C(0x000000370000003D),
            UINT32_C(0x6F),
        },
    };


    for (size_t i = 0; i < size(expectedSolvedMasks); ++i) {
        ASSERT_EQ(expectedSolvedMasks[i].edgesMask, params[i].toSolvedMasks().edgesMask);
        ASSERT_EQ(expectedSolvedMasks[i].cornersMask, params[i].toSolvedMasks().cornersMask);
    }
}
