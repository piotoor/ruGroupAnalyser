#ifndef RUGROUPSINGLESOLVEHANDLER_H
#define RUGROUPSINGLESOLVEHANDLER_H

#include "ruCube.h"
#include "ruCubeSolver.h"
#include <sstream>

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

        void solve(std::vector<uint8_t> scramble);
        void solve(ruLutCube cube);
        std::string getReport();

    private:
        ruCubeSolver solver;
        std::stringstream report;
        bool headers;
        bool lineNumbers;
        bool fixedWidthMoves;
};

#endif // RUGROUPSINGLESOLVEHANDLER_H