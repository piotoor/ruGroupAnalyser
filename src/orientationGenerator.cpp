#include "orientationGenerator.h"
#include <iostream>
#include <iterator>

orientationGenerator::orientationGenerator() {
    //ctor
}

orientationGenerator::~orientationGenerator() {
    //dtor
}

std::vector<std::vector<int8_t>> orientationGenerator::generateOrientations(int8_t n, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    cleanup();
    hasIgnoredPiece = !ignored.empty();
    dfs(0, n, locked, ignored);
    return ans;
}

void orientationGenerator::dfs(uint8_t depth, uint8_t maxDepth, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    if (depth == maxDepth) {
        if (hasIgnoredPiece or currSum % 3 == 0) {
            ans.push_back(curr);
        }
    } else {
        if (!locked.empty() and locked[depth] != -1) {
            curr.push_back(locked[depth]);
            currSum += locked[depth];

            dfs(depth + 1, maxDepth, locked, ignored);

            currSum -= locked[depth];
            curr.pop_back();
        } else if (!ignored.empty() and ignored[depth] == 1) {
            curr.push_back(-1);
            dfs(depth + 1, maxDepth, locked, ignored);

            curr.pop_back();
        } else {
            for (int i = 0; i < 3; ++i) {
                curr.push_back(i);
                currSum += i;

                dfs(depth + 1, maxDepth, locked, ignored);

                currSum -= i;
                curr.pop_back();
            }
        }
    }
}

void orientationGenerator::cleanup() {
    ans.clear();
    curr.clear();
    currSum = 0;
    hasIgnoredPiece = false;
}
