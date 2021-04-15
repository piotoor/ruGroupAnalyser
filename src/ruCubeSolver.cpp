#include "ruCubeSolver.h"

ruCubeSolver::ruCubeSolver(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint64_t cornersMask) {
    configure(minLength, maxLength, maxNumOfSolutions, edgesMask, cornersMask);
}

ruCubeSolver::~ruCubeSolver() {
    //dtor
}


void ruCubeSolver::configure(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint32_t cornersMask) {
    this->minLength = minLength;
    this->maxLength = maxLength;
    this->maxNumOfSolutions = maxNumOfSolutions;
    this->edgesMask = edgesMask;
    this->cornersMask = cornersMask;
}

void ruCubeSolver::solve(ruCube *cube) {
    solutions.clear();
    currSolution.clear();

    if (maxNumOfSolutions > 0) {
        this->cube = cube;
        bool reachedMaxNumberOfSolutions = false;

        for (int length = minLength; length <= maxLength and not reachedMaxNumberOfSolutions; ++length) {
            reachedMaxNumberOfSolutions = dfs(0, length, -1);
        }
    }
}

std::vector<std::string> ruCubeSolver::getSolutionsAsStrings() const {
    std::vector<std::string> solutionsStr;

    return solutionsStr;
}

std::vector<std::vector<uint8_t>> ruCubeSolver::getSolutionsAsVectors() const {
    return this->solutions;
}
#include <iostream>
bool ruCubeSolver::dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove) {
    std::cout << "depth = " << (int)depth << std::endl;
    if (depth == maxDepth) {
        if (cube->isSolved(edgesMask, cornersMask)) {
            solutions.push_back(currSolution);
            if (solutions.size() >= maxNumOfSolutions) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    for (uint8_t i = 0; i < 6; ++i) {
        if (i / 3 == prevMove / 3) {
            continue;
        }

        cube->turn(i);
        currSolution.push_back(i);
        if (dfs(depth + 1, maxDepth, i) ) {
            return true;
        }
        currSolution.pop_back();
        cube->inverseTurn(i);
    }
    return false;
}
