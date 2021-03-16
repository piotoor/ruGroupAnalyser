#include "permutationGenerator.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>
permutationGenerator::permutationGenerator() {
    //ctor
}

permutationGenerator::~permutationGenerator() {
    //dtor
}

std::vector<std::vector<int8_t>> permutationGenerator::generatePermutations(int8_t n) {
    initializePermutation(n);
    generateAns();
    return ans;
}

std::vector<std::vector<int8_t>> permutationGenerator::generatePermutationsWithLockedPieces(int8_t n, const std::vector<int8_t>& locked) {
    initializePermutation(n);
    std::vector<int8_t> piecesAfterLocking;

    set_difference( begin(pieces),
                    end(pieces),
                    begin(locked),
                    end(locked),
                    back_inserter(piecesAfterLocking));

    pieces = std::move(piecesAfterLocking);

    generateAns();
    return ans;
}

std::vector<std::vector<int8_t>> permutationGenerator::generatePermutationsWithIgnoredPieces(int8_t n, const std::vector<int8_t>& ignored) {
    initializePermutation(n);

    for (const auto &x: ignored) {
        if (size(pieces) > x) {
            pieces[x] = -1;
        }
    }

    sort(   begin(pieces),
            end(pieces));

    generateAns();
    return ans;
}

void permutationGenerator::initializePermutation(int8_t n) {
    pieces.clear();
    pieces.resize(n);
    ans.clear();
    std::iota(begin(pieces), end(pieces), 0);
}

void permutationGenerator::generateAns() {
    do {
        ans.push_back(pieces);
    } while (next_permutation(begin(pieces),
                              end(pieces)));
}
