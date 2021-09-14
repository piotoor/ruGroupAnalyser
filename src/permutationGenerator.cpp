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

std::vector<std::vector<int8_t>> permutationGenerator::generatePermutations(int8_t n, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    cleanup(n);

    for (const auto &x: ignored) {
        if (size(pieces) > static_cast<uint8_t>(x)) {
            pieces.insert(-1);
            pieces.erase(x);
        }
    }

    if (!locked.empty()) {
        std::set_difference( begin(pieces),
                        end(pieces),
                        begin(locked),
                        end(locked),
                        inserter(permuteablePieces, permuteablePieces.end()));

    } else {
        permuteablePieces = pieces;
    }

    generateAns();
    mergeWithLocked(locked);
    return ans;
}

void permutationGenerator::cleanup(int8_t n) {
    pieces.clear();
    permuteablePieces.clear();
    ans.clear();

    for (int i = 0; i < n; ++i) {
        pieces.insert(i);
    }
}

void permutationGenerator::generateAns() {
    std::vector<int8_t> pieces (begin(permuteablePieces), end(permuteablePieces));
    do {
        ans.push_back(pieces);
    } while (next_permutation(begin(pieces),
                              end(pieces)));
}

void permutationGenerator::mergeWithLocked(const std::vector<int8_t> &locked) {
    for (const auto &x: locked) {
        for (auto &perm: ans) {
            perm.insert(perm.begin() + x, x);
        }
    }
}
