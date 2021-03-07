#include "gtest/gtest.h"
#include "permutationGenerator.h"

#include <vector>


TEST(permutationGeneratorTest, generatePermutationsTest) {
    permutationGenerator gen;
    auto perms = gen.generatePermutations(3);

    std::vector<std::vector<int8_t>> expectedPerms = {
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 }
    };

    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }

    perms = gen.generatePermutations(4);
    expectedPerms = {
        { 0, 1, 2, 3 },
        { 0, 1, 3, 2 },
        { 0, 2, 1, 3 },
        { 0, 2, 3, 1 },
        { 0, 3, 1, 2 },
        { 0, 3, 2, 1 },

        { 1, 0, 2, 3 },
        { 1, 0, 3, 2 },
        { 1, 2, 0, 3 },
        { 1, 2, 3, 0 },
        { 1, 3, 0, 2 },
        { 1, 3, 2, 0 },

        { 2, 0, 1, 3 },
        { 2, 0, 3, 1 },
        { 2, 1, 0, 3 },
        { 2, 1, 3, 0 },
        { 2, 3, 0, 1 },
        { 2, 3, 1, 0 },

        { 3, 0, 1, 2 },
        { 3, 0, 2, 1 },
        { 3, 1, 0, 2 },
        { 3, 1, 2, 0 },
        { 3, 2, 0, 1 },
        { 3, 2, 1, 0 },
    };

    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }
}


TEST(permutationGeneratorTest, generatePermutationsWithLockedPiecesTest) {
    permutationGenerator gen;
    std::vector<int8_t> lockedPieces = {3, 4, 5};
    auto perms = gen.generatePermutationsWithLockedPieces(6, lockedPieces);
    std::vector<std::vector<int8_t>> expectedPerms = {
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 }
    };

    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {1};
    perms = gen.generatePermutationsWithLockedPieces(3, lockedPieces);
    expectedPerms = {
        { 0, 2 },
        { 2, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {1, 2, 3};
    perms = gen.generatePermutationsWithLockedPieces(6, lockedPieces);
    expectedPerms = {
        { 0, 4, 5 },
        { 0, 5, 4 },
        { 4, 0, 5 },
        { 4, 5, 0 },
        { 5, 0, 4 },
        { 5, 4, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {1, 2, 3, 1, 2, 3};
    perms = gen.generatePermutationsWithLockedPieces(6, lockedPieces);
    expectedPerms = {
        { 0, 4, 5 },
        { 0, 5, 4 },
        { 4, 0, 5 },
        { 4, 5, 0 },
        { 5, 0, 4 },
        { 5, 4, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }




    lockedPieces = {1, 2, 3};
    perms = gen.generatePermutationsWithLockedPieces(4, lockedPieces);
    expectedPerms = {
        { 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {0, 1, 2, 3};
    perms = gen.generatePermutationsWithLockedPieces(4, lockedPieces);
    expectedPerms = {
        {  }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {1, 2, 3, 5, 9, 8, 11};
    perms = gen.generatePermutationsWithLockedPieces(4, lockedPieces);
    expectedPerms = {
        { 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (int i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }

}
