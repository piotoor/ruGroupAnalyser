#include "gtest/gtest.h"
#include <valgrind/callgrind.h>
#include "permutationGenerator.h"

#include <vector>

TEST(permutationGeneratorTest, generatePermutationsTest) {
    permutationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedPerms = {
        {{  }},


        {{ 0 }},


        {{ 0, 1 },
         { 1, 0 }},


        {{ 0, 1, 2 },
         { 0, 2, 1 },
         { 1, 0, 2 },
         { 1, 2, 0 },
         { 2, 0, 1 },
         { 2, 1, 0 }},


        {{ 0, 1, 2, 3 },
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
         { 3, 2, 1, 0 }},
    };

    const std::vector<uint8_t> permLengths { 0, 1, 2, 3, 4 };

    for (uint8_t test = 0; test < size(expectedPerms); ++test) {
        auto perms = gen.generatePermutations(permLengths[test]);
        ASSERT_EQ(expectedPerms[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedPerms[test].size(); ++i) {
            ASSERT_EQ(expectedPerms[test][i], perms[i]);
        }
    }
}

TEST(permutationGeneratorTest, generatePermutationsWithLockedPiecesTest) {
    permutationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedPerms = {
        {{ 0, 1, 2 },
         { 0, 2, 1 },
         { 1, 0, 2 },
         { 1, 2, 0 },
         { 2, 0, 1 },
         { 2, 1, 0 }},

        {{ 0, 1, 2, 3, 4, 5 },
         { 0, 2, 1, 3, 4, 5 },
         { 1, 0, 2, 3, 4, 5 },
         { 1, 2, 0, 3, 4, 5 },
         { 2, 0, 1, 3, 4, 5 },
         { 2, 1, 0, 3, 4, 5 }},

        {{ 0, 1, 2 },
         { 2, 1, 0 }},

        { { } },

        {{ 0, 1, 2, 3, 4, 5 },
         { 0, 1, 2, 3, 5, 4 },
         { 4, 1, 2, 3, 0, 5 },
         { 4, 1, 2, 3, 5, 0 },
         { 5, 1, 2, 3, 0, 4 },
         { 5, 1, 2, 3, 4, 0 }},

        {{ 0, 1, 2, 3 }},

        {{ 0, 1, 2, 3 }},
    };

    const std::vector<std::vector<int8_t>> lockedPieces = {
        { },
        { 3, 4, 5 },
        { 1 },
        {   },
        { 1, 2, 3 },
        { 1, 2, 3 },
        { 0, 1, 2, 3 },
    };

    const std::vector<uint8_t> permLengths { 3, 6, 3, 0, 6, 4, 4 };

    for (uint8_t test = 0; test < size(expectedPerms); ++test) {
        auto perms = gen.generatePermutations(permLengths[test], lockedPieces[test]);
        ASSERT_EQ(expectedPerms[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedPerms[test].size(); ++i) {
            ASSERT_EQ(expectedPerms[test][i], perms[i]);
        }
    }
}

TEST(permutationGeneratorTest, generatePermutationsWithIgnoredPiecesTest) {
    permutationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedPerms = {
        {{ 0, 1, 2, 3 },
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
         { 3, 2, 1, 0 }},


        {{ }},


        {{ 0 }},


        {{ -1 }},


        {{ -1, -1 }},


        {{ -1,  1 },
         {  1, -1 }},


        {{ -1,  1,  2 },
         { -1,  2,  1 },
         {  1, -1,  2 },
         {  1,  2, -1 },
         {  2, -1,  1 },
         {  2,  1, -1 }},


        {{ -1, -1,  1,  2 },
         { -1, -1,  2,  1 },
         { -1,  1, -1,  2 },
         { -1,  1,  2, -1 },
         { -1,  2, -1,  1 },
         { -1,  2,  1, -1 },

         {  1, -1, -1,  2 },
         {  1, -1,  2, -1 },
         {  1,  2, -1, -1 },

         {  2, -1, -1,  1 },
         {  2, -1,  1, -1 },
         {  2,  1, -1, -1 }}
    };

    const std::vector<std::vector<int8_t>> lockedPieces = {
        { },
        { },
        { },
        { },
        { },
        { },
        { },
        { },
    };

    const std::vector<std::vector<int8_t>> ignoredPieces = {
        { },
        { },
        { },
        { 0 },
        { 0, 1 },
        { 0 },
        { 0 },
        { 0, 3 },
    };

    const std::vector<uint8_t> permLengths { 4, 0, 1, 1, 2, 2, 3, 4 };

    for (uint8_t test = 0; test < size(expectedPerms); ++test) {
        auto perms = gen.generatePermutations(permLengths[test], lockedPieces[test], ignoredPieces[test]);
        ASSERT_EQ(expectedPerms[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedPerms[test].size(); ++i) {
            ASSERT_EQ(expectedPerms[test][i], perms[i]);
        }
    }
}

TEST(permutationGeneratorTest, generatePermutationsWithLockedAndIgnoredPiecesTest) {
    permutationGenerator gen;

    const std::vector<std::vector<std::vector<int8_t>>> expectedPerms = {
        {{  }},

        {{ 0, 1, 2 },
         { 0, 2, 1 },
         { 1, 0, 2 },
         { 1, 2, 0 },
         { 2, 0, 1 },
         { 2, 1, 0 }},

        {{ -1, -1, 2, 3 }},

        {{ -1, -1,  2,  3,  4 },
         { -1,  4,  2,  3, -1 },
         {  4, -1,  2,  3, -1 }},

        {{ -1, -1,  2,  3,  4,  5 },
         { -1, -1,  2,  3,  5,  4 },
         { -1,  4,  2,  3, -1,  5 },
         { -1,  4,  2,  3,  5, -1 },
         { -1,  5,  2,  3, -1,  4 },
         { -1,  5,  2,  3,  4, -1 },
         {  4, -1,  2,  3, -1,  5 },
         {  4, -1,  2,  3,  5, -1 },
         {  4,  5,  2,  3, -1, -1 },
         {  5, -1,  2,  3, -1,  4 },
         {  5, -1,  2,  3,  4, -1 },
         {  5,  4,  2,  3, -1, -1 }},

        {{ -1, -1, -1,  3,  4,  5 }}
    };

    const std::vector<std::vector<int8_t>> lockedPieces = {
        { },
        { },
        { 2, 3 },
        { 2, 3 },
        { 2, 3 },
        { 3, 4, 5 },
    };

    const std::vector<std::vector<int8_t>> ignoredPieces = {
        { },
        { },
        { 0, 1 },
        { 0, 1 },
        { 0, 1 },
        { 0, 1, 2 },
    };

    const std::vector<uint8_t> permLengths { 0, 3, 4, 5, 6, 6 };

    for (uint8_t test = 0; test < size(expectedPerms); ++test) {
        auto perms = gen.generatePermutations(permLengths[test], lockedPieces[test], ignoredPieces[test]);
        ASSERT_EQ(expectedPerms[test].size(), perms.size());
        for (uint8_t i = 0; i < expectedPerms[test].size(); ++i) {
            ASSERT_EQ(expectedPerms[test][i], perms[i]);
        }
    }
}
