#ifndef RUGROUPSINGLESOLVEHANDLER_H
#define RUGROUPSINGLESOLVEHANDLER_H

#include "ruCube.h"
#include "ruCubeSolver.h"
#include <sstream>
#include "ruCubeSimpleBenchmarkTimer.h"

struct solveReportFlags {
    bool headers = false;
    bool lineNumbers = false;
    bool fixedWidthMoves = false;
    bool compressSolutions = false;
    bool compressCubeState = false;
    bool summary = false;
};

class ruCubeSingleSolveHandler
{
    public:
        ruCubeSingleSolveHandler(const solutionParameters &solParams = solutionParameters(),
                                 const solvedMasks &masks = solvedMasks(),
                                 const solveReportFlags &flags = solveReportFlags());

        virtual ~ruCubeSingleSolveHandler();

        ruCubeSingleSolveHandler(const ruCubeSingleSolveHandler&);

        void configure( const solutionParameters &solParams = solutionParameters(),
                        const solvedMasks &masks = solvedMasks(),
                        const solveReportFlags &flags = solveReportFlags());

        void solve(ruLutCube cube);
        std::string getReport();

        std::vector<std::vector<uint8_t>> getSolutionsAsVectors();
        std::vector<std::string> getSolutionsAsStrings();

    private:
        ruCubeSolver solver;
        std::stringstream report;
        solveReportFlags flags;

        std::chrono::milliseconds elapsedTime;
        std::vector<std::vector<uint8_t>> solutionsVect;
        std::vector<std::string> solutionsStr;

        ruLutCube currCube;
};

#endif // RUGROUPSINGLESOLVEHANDLER_H
