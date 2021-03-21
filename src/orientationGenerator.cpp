#include "orientationGenerator.h"
#include <iostream>

orientationGenerator::orientationGenerator():currSum(0) {
    //ctor
}

orientationGenerator::~orientationGenerator() {
    //dtor
}

std::vector<std::vector<int8_t>> orientationGenerator::generateOrientations(int8_t n, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    cleanup();
    dfs(0, n);
    return ans;
}

void orientationGenerator::dfs(uint8_t depth, uint8_t maxDepth) {
    if (depth == maxDepth) {
        if (currSum % 3 == 0) {
            ans.push_back(curr);
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            curr.push_back(i);
            currSum += i;

            dfs(depth + 1, maxDepth);

            currSum -= i;
            curr.pop_back();
        }
    }
}

void orientationGenerator::cleanup() {
    ans.clear();
    curr.clear();
    currSum = 0;
}
