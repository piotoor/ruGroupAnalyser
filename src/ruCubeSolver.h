#ifndef RUCUBESOLVER_H
#define RUCUBESOLVER_H

#include "ruCube.h"
#include <vector>
#include <string>

class ruCubeSolver
{
    public:
        ruCubeSolver(uint8_t minLength = 0, uint8_t maxLength = 20, uint8_t maxNumOfSolutions = 1, uint32_t edgesMask = ruCube::allEdgesMask, uint64_t cornersMask = ruCube::allCornersMask);
        virtual ~ruCubeSolver();
        void configure(uint8_t minLength, uint8_t maxLength, uint8_t maxNumOfSolutions, uint32_t edgesMask, uint32_t cornersMask);
        void solve(ruCube *cube);
        std::vector<std::string> getSolutionsAsStrings() const;
        std::vector<std::vector<uint8_t>> getSolutionsAsVectors() const;

    private:
        bool dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove);

        uint8_t minLength;
        uint8_t maxLength;
        uint8_t maxNumOfSolutions;
        std::vector<std::vector<uint8_t>> solutions;
        std::vector<uint8_t> currSolution;
        uint32_t edgesMask;
        uint64_t cornersMask;
        ruCube *cube;
};

#endif // RUCUBESOLVER_H
