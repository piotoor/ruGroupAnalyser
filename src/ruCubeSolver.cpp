#include "ruCubeSolver.h"
#include <iterator>

ruCubeSolver::ruCubeSolver(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint64_t cornersMask) {
    configure(minLength, maxLength, maxNumOfSolutions, edgesMask, cornersMask);
}

ruCubeSolver::~ruCubeSolver() {
    //dtor
}


void ruCubeSolver::configure(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint64_t cornersMask) {
    this->minLength = minLength;
    this->maxLength = maxLength;
    this->maxNumOfSolutions = maxNumOfSolutions;
    this->edgesMask = edgesMask;
    this->cornersMask = cornersMask;
}
#include <iostream>

void ruCubeSolver::solve(ruCube *cube, bool multiThreading, uint8_t multiThreadingThreshold) {
    solutions.clear();
    currSolution.clear();
    this->cube = cube;

    if (maxNumOfSolutions > 0) {
        if (multiThreading) {
            currSolutions.clear();
            currSolutions.resize(numOfThreads);
            //cubes.clear();
            cubes.resize(numOfThreads);
            threads.clear();
            std::fill(begin(cubes), end(cubes), ruCube(*cube));
            //currSolution.clear();

            for (int i = 0; i < numOfThreads; ++i) {
                currSolutions[i].push_back(i);
                cubes[i].turn(i);
            }
            for (uint8_t length = minLength; length <= maxLength and solutions.size() < maxNumOfSolutions; ++length) {
                if (length >= multiThreadingThreshold) {
                    for (uint8_t t = 0; t < numOfThreads; ++t) {
                        //threads.push_back(std::thread(&ruCubeSolver::multiThreadingDfs, this, 0, length - 1, t, t));
                        currSolutions[t].resize(length);
                        threads.emplace_back(&ruCubeSolver::multiThreadingDfs, this, 1, length, t, t);
                    }

                    for (auto &thread: threads) {
                        if (thread.joinable()) {
                            thread.join();
                        }
                    }
                } else {
                    currSolution.resize(length);
                    dfs(0, length, -6);
                }
            }

        } else {
//            currSolution.clear();
//            this->cube = cube;
            for (uint8_t length = minLength; length <= maxLength and solutions.size() < maxNumOfSolutions; ++length) {
                currSolution.resize(length);
                dfs(0, length, -6);
            }
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

void ruCubeSolver::dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove) {
    if (solutions.size() < maxNumOfSolutions) {
        if (depth == maxDepth) {
            if (cube->isSolved(edgesMask, cornersMask)) {
                solutions.push_back(currSolution);
            }
        } else {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
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


void ruCubeSolver::multiThreadingDfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove, uint8_t id) {
    if (solutions.size() < maxNumOfSolutions) {
        if (depth == maxDepth) {

            if (cubes[id].isSolved(edgesMask, cornersMask)) {
                std::lock_guard<std::mutex> guard(solutionsMutex);
                if (solutions.size() < maxNumOfSolutions) {
                    solutions.push_back(currSolutions[id]);
                }
            }
        } else {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cubes[id].turn(i);
                currSolutions[id][depth] = i;
                multiThreadingDfs(depth + 1, maxDepth, i, id);
                cubes[id].inverseTurn(i);
            }
        }
    }
}
