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
            pieces[x] = -1;
        }
    }

    std::sort(begin(pieces), end(pieces));
    if (!locked.empty()) {
        std::set_difference( begin(pieces),
                        end(pieces),
                        begin(locked),
                        end(locked),
                        back_inserter(lockedPieces));

    } else {
        lockedPieces = pieces;
    }

    generateAns();
    mergeWithLocked(locked);
    return ans;
}

void permutationGenerator::cleanup(int8_t n) {
    pieces.clear();
    lockedPieces.clear();
    pieces.resize(n);
    ans.clear();
    std::iota(begin(pieces), end(pieces), 0);
}

void permutationGenerator::generateAns() {
    do {
        ans.push_back(lockedPieces);
    } while (next_permutation(begin(lockedPieces),
                              end(lockedPieces)));
}

void permutationGenerator::mergeWithLocked(const std::vector<int8_t> &locked) {
    for (const auto &x: locked) {
        for (auto &perm: ans) {
            perm.insert(perm.begin() + x, x);
        }
    }
}
