#include "orientationGenerator.h"
#include <iostream>
#include <iterator>
#include <algorithm>

orientationGenerator::orientationGenerator() {
    //ctor
}

orientationGenerator::~orientationGenerator() {
    //dtor
}

std::vector<std::vector<int8_t>> orientationGenerator::generateOrientations(int8_t n, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    cleanup(n);
    hasIgnoredPiece = !ignored.empty() and std::any_of(begin(ignored), end(ignored), [] (const auto &x) { return x == 1; });
    dfs(0, n, locked, ignored);
    return ans;
}

void orientationGenerator::dfs(uint8_t depth, uint8_t maxDepth, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    if (depth == maxDepth) {
        if (hasIgnoredPiece or currSum % 3 == 0) {
            ans.push_back(curr);
        }
    } else {
        if (!locked.empty() and depth < size(locked) and locked[depth] != -1) {
            curr[depth] = locked[depth];
            currSum += locked[depth];

            dfs(depth + 1, maxDepth, locked, ignored);

            currSum -= locked[depth];
        } else if (!ignored.empty() and ignored[depth] == 1) {
            curr[depth] = -1;
            dfs(depth + 1, maxDepth, locked, ignored);

        } else {
            for (int i = 0; i < 3; ++i) {
                curr[depth] = i;
                currSum += i;

                dfs(depth + 1, maxDepth, locked, ignored);

                currSum -= i;
            }
        }
    }
}

void orientationGenerator::cleanup(uint8_t n) {
    ans.clear();
    curr = std::vector<int8_t>(n);
    currSum = 0;
    hasIgnoredPiece = false;
}
