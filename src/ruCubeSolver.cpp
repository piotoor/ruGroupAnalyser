#include "ruCubeSolver.h"
#include <iterator>
#include <algorithm>
#include "ruCubeScrambleParser.h"

ruCubeSolver::ruCubeSolver(const solutionParameters &solParams, const solvedMasks &masks): cube(nullptr) {
    configure(solParams, masks);
}

ruCubeSolver::~ruCubeSolver() {

}


void ruCubeSolver::configure(const solutionParameters &solParams, const solvedMasks &masks) {
    this->minLength = solParams.minLength;
    this->maxLength = solParams.maxLength;
    this->maxNumOfSolutions = solParams.maxNumOfSolutions;
    this->edgesMask = masks.edgesMask;
    this->cornersMask = masks.cornersMask;
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

std::vector<std::string> ruCubeSolver::getSolutionsAsStrings(bool compressSolutions) const {
    std::vector<std::string> solutionsStr;

    std::transform(begin(solutions),
                   end(solutions),
                   std::back_inserter(solutionsStr),
                   [compressSolutions] (const auto &x) {
                        return ruCubeScrambleParser::vectorScrambleToStringScramble(x, compressSolutions);
                   });

    return solutionsStr;
}

std::vector<std::vector<uint8_t>> ruCubeSolver::getSolutionsAsVectors() const {
    return this->solutions;
}

void ruCubeSolver::dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove) {
    if (solutions.size() < maxNumOfSolutions) {
        if (depth == maxDepth) {
            if (cube->isSolved(cornersMask, edgesMask)) {
                solutions.push_back(currSolution);
            }
        } else {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3 or cube->isPruningPossible(maxDepth - depth, this->cornersMask, this->edgesMask)) {
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

