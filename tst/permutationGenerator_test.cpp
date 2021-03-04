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
