#include "orientationGenerator.h"
#include <iostream>
#include <iterator>

orientationGenerator::orientationGenerator():currSum(0) {
    //ctor
}

orientationGenerator::~orientationGenerator() {
    //dtor
}

std::vector<std::vector<int8_t>> orientationGenerator::generateOrientations(int8_t n, const std::vector<int8_t> &locked, const std::vector<int8_t> &ignored) {
    cleanup();
    dfs(0, n, locked);
    return ans;
}

void orientationGenerator::dfs(uint8_t depth, uint8_t maxDepth, const std::vector<int8_t> &locked) {
    if (depth == maxDepth) {
        if (currSum % 3 == 0) {
            ans.push_back(curr);
//            std::copy(begin(curr), end(curr), std::ostream_iterator<int>(std::cout, " "));
//            std::cout << std::endl;
        }
    } else {
        if (locked.empty() or locked[depth] == -1) {
            for (int i = 0; i < 3; ++i) {
                curr.push_back(i);
                currSum += i;

                dfs(depth + 1, maxDepth, locked);

                currSum -= i;
                curr.pop_back();
            }
        } else {
            curr.push_back(locked[depth]);
            currSum += locked[depth];

            dfs(depth + 1, maxDepth, locked);

            currSum -= locked[depth];
            curr.pop_back();
        }
    }
}

void orientationGenerator::cleanup() {
    ans.clear();
    curr.clear();
    currSum = 0;
}
