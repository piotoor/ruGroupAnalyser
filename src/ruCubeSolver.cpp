#include "ruCubeSolver.h"
#include <iterator>
#include <algorithm>
#include "ruCubeScrambleParser.h"

ruCubeSolver::ruCubeSolver(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint64_t cornersMask): cube(nullptr) {
    configure(minLength, maxLength, maxNumOfSolutions, edgesMask, cornersMask);
}

ruCubeSolver::~ruCubeSolver() {

}


void ruCubeSolver::configure(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint64_t cornersMask) {
    this->minLength = minLength;
    this->maxLength = maxLength;
    this->maxNumOfSolutions = maxNumOfSolutions;
    this->edgesMask = edgesMask;
    this->cornersMask = cornersMask;
}

void ruCubeSolver::solve(ruBaseCube *cube) {
    solutions.clear();
    currSolution.clear();
    this->cube = cube;

    if (maxNumOfSolutions > 0) {
        for (uint8_t length = minLength; length <= maxLength and solutions.size() < maxNumOfSolutions; ++length) {
            currSolution.resize(length);
            dfs(0, length, -6);
        }
    }
}

std::vector<std::string> ruCubeSolver::getSolutionsAsStrings() const {
    std::vector<std::string> solutionsStr;

    std::transform(begin(solutions),
                   end(solutions),
                   std::back_inserter(solutionsStr),
                   [] (const auto &x) {
                        return ruCubeScrambleParser::vectorScrambleToStringScramble(x);
                   });

    return solutionsStr;
}

std::vector<std::vector<uint8_t>> ruCubeSolver::getSolutionsAsVectors() const {
    return this->solutions;
}

void ruCubeSolver::dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove) {
    if (solutions.size() < maxNumOfSolutions) {
        if (depth == maxDepth) {
            if (cube->isSolved(edgesMask, cornersMask)) {
                solutions.push_back(currSolution);
            }
        } else {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3 or cube->isPruningPossible(maxDepth - depth)) {
                    continue;
                }

                cube->turn(i);
                currSolution[depth] = i;
                dfs(depth + 1, maxDepth, i);
                cube->inverseTurn(i);
            }
        }
    }
}

