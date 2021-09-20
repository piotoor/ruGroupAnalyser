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

std::vector<cornersArray> orientationGenerator::generateOrientations(const cornersArray &locked, const cornersArray &ignored) {
    cleanup();
    hasIgnoredPiece = !ignored.empty() and std::any_of(begin(ignored), end(ignored), [] (const auto &x) { return x == 1; });
    dfs(0, ruBaseCube::noOfCorners, locked, ignored);
    return ans;
}

void orientationGenerator::dfs(uint8_t depth, uint8_t maxDepth, const cornersArray &locked, const cornersArray &ignored) {
    if (depth == maxDepth) {
        if (hasIgnoredPiece or currSum % 3 == 0) {
            ans.push_back(curr);
        }
    } else {
        if (locked[depth] != -1) {
            curr[depth] = locked[depth];
            currSum += locked[depth];

            dfs(depth + 1, maxDepth, locked, ignored);

            currSum -= locked[depth];
        } else if (ignored[depth] == 1) {
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

void orientationGenerator::cleanup() {
    ans.clear();
    curr.fill(0);
    currSum = 0;
    hasIgnoredPiece = false;
}
