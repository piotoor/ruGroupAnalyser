#ifndef RUCUBESOLVER_H
#define RUCUBESOLVER_H

#include "ruCube.h"
#include <vector>
#include <string>
#include <thread>
#include <mutex>

class ruCubeSolver
{
    public:
        ruCubeSolver(uint8_t minLength = 0, uint8_t maxLength = 20, uint8_t maxNumOfSolutions = 1, uint32_t edgesMask = ruCube::allEdgesMask, uint64_t cornersMask = ruCube::allCornersMask);
        virtual ~ruCubeSolver();
        void configure(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask = ruCube::allEdgesMask, uint64_t cornersMask = ruCube::allCornersMask);
        void solve(ruCube *cube, bool multiThreading = false, uint8_t multiThreadingThreshold = 8);
        std::vector<std::string> getSolutionsAsStrings() const;
        std::vector<std::vector<uint8_t>> getSolutionsAsVectors() const;

    private:
        void dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove);
        void multiThreadingDfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove, uint8_t id);

        uint8_t minLength;
        uint8_t maxLength;
        uint8_t maxNumOfSolutions;
        std::vector<std::vector<uint8_t>> solutions;
        std::vector<uint8_t> currSolution;
        uint32_t edgesMask;
        uint64_t cornersMask;
        ruCube *cube;

        std::vector<std::vector<uint8_t>> currSolutions;
        std::vector<ruCube> cubes;
        std::mutex solutionsMutex;
        std::vector<std::thread> threads;
        static inline const uint8_t numOfThreads = 6;
};

#endif // RUCUBESOLVER_H
