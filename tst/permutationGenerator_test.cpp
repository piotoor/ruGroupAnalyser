#include "gtest/gtest.h"
#include "permutationGenerator.h"

#include <vector>


TEST(permutationGeneratorTest, generatePermutationsTest) {
    permutationGenerator gen;


    auto perms = gen.generatePermutations(0);
    std::vector<std::vector<int8_t>> expectedPerms = {
        {  }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    perms = gen.generatePermutations(1);
    expectedPerms = {
        { 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    perms = gen.generatePermutations(2);
    expectedPerms = {
        { 0, 1 },
        { 1, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    perms = gen.generatePermutations(3);
    expectedPerms = {
        { 0, 1, 2 },
        { 0, 2, 1 },

        { 1, 0, 2 },
        { 1, 2, 0 },

        { 2, 0, 1 },
        { 2, 1, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
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
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }
}


TEST(permutationGeneratorTest, generatePermutationsWithLockedPiecesTest) {
    permutationGenerator gen;

    std::vector<int8_t> lockedPieces = {};
    auto perms = gen.generatePermutations(3, lockedPieces);
    std::vector<std::vector<int8_t>> expectedPerms = {
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {3, 4, 5};
    perms = gen.generatePermutations(6, lockedPieces);
    expectedPerms = {
        { 0, 1, 2, 3, 4, 5 },
        { 0, 2, 1, 3, 4, 5 },
        { 1, 0, 2, 3, 4, 5 },
        { 1, 2, 0, 3, 4, 5 },
        { 2, 0, 1, 3, 4, 5 },
        { 2, 1, 0, 3, 4, 5 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {1};
    perms = gen.generatePermutations(3, lockedPieces);
    expectedPerms = {
        { 0, 1, 2 },
        { 2, 1, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {};
    perms = gen.generatePermutations(0, lockedPieces);
    expectedPerms = {
        {  }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {1, 2, 3};
    perms = gen.generatePermutations(6, lockedPieces);
    expectedPerms = {
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 5, 4 },
        { 4, 1, 2, 3, 0, 5 },
        { 4, 1, 2, 3, 5, 0 },
        { 5, 1, 2, 3, 0, 4 },
        { 5, 1, 2, 3, 4, 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }


    lockedPieces = {1, 2, 3};
    perms = gen.generatePermutations(4, lockedPieces);
    expectedPerms = {
        { 0, 1, 2, 3 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    lockedPieces = {0, 1, 2, 3};
    perms = gen.generatePermutations(4, lockedPieces);
    expectedPerms = {
        { 0, 1, 2, 3 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }

}


TEST(permutationGeneratorTest, generatePermutationsWithIgnoredPiecesTest) {
    permutationGenerator gen;

    std::vector<int8_t> ignoredPieces = {};
    std::vector<int8_t> lockedPieces = {};
    auto perms = gen.generatePermutations(4, lockedPieces, ignoredPieces);
    std::vector<std::vector<int8_t>> expectedPerms = {
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
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {};
    perms = gen.generatePermutations(0, lockedPieces, ignoredPieces);
    expectedPerms = {
        { }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {};
    perms = gen.generatePermutations(1, lockedPieces, ignoredPieces);
    expectedPerms = {
        { 0 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = { 0 };
    perms = gen.generatePermutations(1, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = { 0, 1 };
    perms = gen.generatePermutations(2, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, -1 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = { 0 };
    perms = gen.generatePermutations(2, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, 1 },
        { 1, -1 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = { 0 };
    perms = gen.generatePermutations(3, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, 1, 2 },
        { -1, 2, 1 },

        { 1, -1, 2 },
        { 1, 2, -1 },

        { 2, -1, 1 },
        { 2, 1, -1 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {0, 3};
    perms = gen.generatePermutations(4, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, -1, 1, 2 },
        { -1, -1, 2, 1 },
        { -1, 1, -1, 2 },
        { -1, 1, 2, -1 },
        { -1, 2, -1, 1 },
        { -1, 2, 1, -1 },

        { 1, -1, -1, 2 },
        { 1, -1, 2, -1 },
        { 1, 2, -1, -1 },

        { 2, -1, -1, 1 },
        { 2, -1, 1, -1 },
        { 2, 1, -1, -1 },
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }
}



TEST(permutationGeneratorTest, generatePermutationsWithLockedAndIgnoredPiecesTest) {
    permutationGenerator gen;
    std::vector<int8_t> ignoredPieces = {};
    std::vector<int8_t> lockedPieces = {};
    auto perms = gen.generatePermutations(0, lockedPieces, ignoredPieces);
    std::vector<std::vector<int8_t>> expectedPerms = {
        { }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {};
    lockedPieces = {};
    perms = gen.generatePermutations(3, lockedPieces, ignoredPieces);
    expectedPerms = {
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 },
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {0, 1};
    lockedPieces = {2, 3};
    perms = gen.generatePermutations(4, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, -1, 2, 3 }
    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {0, 1};
    lockedPieces = {2, 3};
    perms = gen.generatePermutations(5, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, -1, 2, 3, 4 },
        { -1, 4, 2, 3, -1 },
        { 4, -1, 2, 3, -1 }

    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {0, 1};
    lockedPieces = {2, 3};
    perms = gen.generatePermutations(6, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, -1, 2, 3, 4, 5 },
        { -1, -1, 2, 3, 5, 4 },
        { -1, 4, 2, 3, -1, 5 },
        { -1, 4, 2, 3, 5, -1 },
        { -1, 5, 2, 3, -1, 4 },
        { -1, 5, 2, 3, 4, -1 },
        { 4, -1, 2, 3, -1, 5 },
        { 4, -1, 2, 3, 5, -1 },
        { 4, 5, 2, 3, -1, -1 },
        { 5, -1, 2, 3, -1, 4 },
        { 5, -1, 2, 3, 4, -1 },
        { 5, 4, 2, 3, -1, -1 },

    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }



    ignoredPieces = {0, 1, 2};
    lockedPieces = {3, 4, 5};
    perms = gen.generatePermutations(6, lockedPieces, ignoredPieces);
    expectedPerms = {
        { -1, -1, -1, 3, 4, 5 }

    };
    ASSERT_EQ(expectedPerms.size(), perms.size());
    for (uint8_t i = 0; i < expectedPerms.size(); ++i) {
        ASSERT_EQ(expectedPerms[i], perms[i]);
    }


}
