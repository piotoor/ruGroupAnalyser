#ifndef RUGROUPSINGLESOLVEHANDLER_H
#define RUGROUPSINGLESOLVEHANDLER_H

#include "ruCube.h"
#include "ruCubeSolver.h"
#include <sstream>
#include "ruCubeSimpleBenchmarkTimer.h"

class ruCubeSingleSolveHandler
{
    public:
        ruCubeSingleSolveHandler(  uint8_t minLength = 0,
                                    uint8_t maxLength = 20,
                                    uint8_t maxNumOfSolutions = 1,
                                    bool headers = false,
                                    bool lineNumbers = false,
                                    bool fixedWidthMoves = false,
                                    uint32_t edgesMask = ruBaseCube::allEdgesMask,
                                    uint64_t cornersMask = ruBaseCube::allCornersMask);
        virtual ~ruCubeSingleSolveHandler();
        void configure( uint8_t minLength,
                        uint8_t maxLength,
                        uint8_t maxNumOfSolutions,
                        bool headers,
                        bool lineNumbers,
                        bool fixedWidthMoves,
                        uint32_t edgesMask,
                        uint64_t cornersMask);

        void solve(ruLutCube cube);
        std::string getReport();

        std::vector<std::vector<uint8_t>> getSolutionsAsVectors();
        std::vector<std::string> getSolutionsAsStrings();

    private:
        ruCubeSolver solver;
        std::stringstream report;
        bool headers;
        bool lineNumbers;
        bool fixedWidthMoves;
        std::chrono::milliseconds elapsedTime;
        std::vector<std::vector<uint8_t>> solutionsVect;
        std::vector<std::string> solutionsStr;
};

#endif // RUGROUPSINGLESOLVEHANDLER_H
