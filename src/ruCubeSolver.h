#ifndef RUCUBESOLVER_H
#define RUCUBESOLVER_H

#include "ruCube.h"
#include <vector>
#include <string>

struct solutionParameters {
    uint8_t minLength = 0;
    uint8_t maxLength = 20;
    uint8_t maxNumOfSolutions = 1;
};

struct solvedMasks {
    uint32_t edgesMask = ruBaseCube::allEdgesMask;
    uint64_t cornersMask = ruBaseCube::allCornersMask;
};

class ruCubeSolver
{
    public:
        ruCubeSolver(const solutionParameters &solParams = solutionParameters(), const solvedMasks &masks = solvedMasks());
        ruCubeSolver(const ruCubeSolver &other) = default;
        ruCubeSolver& operator=(const ruCubeSolver &other) = default;
        virtual ~ruCubeSolver();

        void configure(const solutionParameters &solParams = solutionParameters(), const solvedMasks &masks = solvedMasks());
        void solve(ruBaseCube *cube);
        std::vector<std::string> getSolutionsAsStrings(bool compressSolutions = false) const;
        std::vector<std::vector<uint8_t>> getSolutionsAsVectors() const;

    private:
        void dfs(uint8_t depth, uint8_t maxDepth, int8_t prevMove);

        uint8_t minLength;
        uint8_t maxLength;
        uint8_t maxNumOfSolutions;
        std::vector<std::vector<uint8_t>> solutions;
        std::vector<uint8_t> currSolution;
        uint32_t edgesMask;
        uint64_t cornersMask;
        ruBaseCube *cube;

};

#endif // RUCUBESOLVER_H
