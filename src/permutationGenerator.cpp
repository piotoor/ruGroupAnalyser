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
    std::vector<std::vector<int8_t>> ans;

    do {
        ans.push_back(pieces);
    } while (next_permutation(begin(pieces),
                              end(pieces)));

    return ans;
}

std::vector<std::vector<int8_t>> permutationGenerator::generatePermutationsWithLockedPieces(int8_t n, const std::vector<int8_t>& locked) {
    initializePermutation(n);
    std::vector<int8_t> piecesAfterLocking;
    std::vector<std::vector<int8_t>> ans;

    set_difference( begin(pieces),
                    end(pieces),
                    begin(locked),
                    end(locked),
                    back_inserter(piecesAfterLocking));

    do {
        ans.push_back(piecesAfterLocking);
    } while (next_permutation(begin(piecesAfterLocking),
                              end(piecesAfterLocking)));

    return ans;
}

std::vector<std::vector<int8_t>> permutationGenerator::generatePermutationsWithIgnoredPieces(int8_t n, const std::vector<int8_t>& ignored) {
    initializePermutation(n);

    std::vector<int8_t> piecesAfterIgnoring;
    std::vector<std::vector<int8_t>> ans;

    for (const auto &x: ignored) {
        piecesAfterIgnoring[x] = -1;
    }

    sort(   begin(piecesAfterIgnoring),
            end(piecesAfterIgnoring));

    do {
        ans.push_back(piecesAfterIgnoring);
    } while (next_permutation(begin(piecesAfterIgnoring),
                              end(piecesAfterIgnoring)));

    return ans;
}

void permutationGenerator::initializePermutation(int8_t n) {
    pieces.clear();
    pieces.resize(n);
    std::iota(begin(pieces), end(pieces), 0);
}
