#include "ruCubeMultiSolveHandler.h"
#include "ruCubeStateConverter.h"
#include <cmath>
#include <algorithm>

auto operator""_MB(long double x) -> uint64_t {
    return 1024ULL * 1024ULL * x;
}

auto operator""_GB(long double x) -> uint64_t {
    return 1024ULL * 1024ULL * 1024ULL * x;
}

ruCubeMultiSolveHandler::ruCubeMultiSolveHandler(   const generatorParameters &genParams,
                                                    const solutionParameters &solParams,
                                                    const solveReportFlags &flags)
                                                     :
                                                        solParams(solParams),
                                                        masks(masks),
                                                        flags(flags),
                                                        genParams(genParams) {

}

ruCubeMultiSolveHandler::~ruCubeMultiSolveHandler() {

}

void ruCubeMultiSolveHandler::generateAndSolve(std::string filename) {

}

void ruCubeMultiSolveHandler::disableHeadersAndFooters() {
    flags.headers = false;
}

void ruCubeMultiSolveHandler::disableLineNumbers() {
    flags.lineNumbers = false;
}

void ruCubeMultiSolveHandler::disableFixedWidthMoves() {
    flags.fixedWidthMoves = false;
}

void ruCubeMultiSolveHandler::dropMaxNumOfSolutionsToN(uint8_t n) {
    solParams.maxNumOfSolutions = std::min(solParams.maxNumOfSolutions, n);
}

uint64_t ruCubeMultiSolveHandler::estimateSingleSolveReportSize() {
    uint64_t ans = 0;
    ans += maxCubeStateStrSize;
    ans += solParams.maxNumOfSolutions * maxSolutionStrSize;

    if (flags.lineNumbers) {
        ans += solParams.maxNumOfSolutions * maxLineNumStrSize;
    }

    if (flags.headers) {
        ans += maxNumOfHeaders * maxHeaderStrSize + maxSummaryStrSize + maxNumOfBlankLines;
    }

    return ans;
}

uint32_t ruCubeMultiSolveHandler::calculateTotalNumberOfCubesToGenerate() {
    uint8_t numOfIgnoredEdges = size(genParams.ignoredEdges);
    uint8_t numOfLockedEdges = size(genParams.lockedEdges);
    uint32_t ans = ruCubeStateConverter::factLookup[ruBaseCube::noOfEdges - numOfLockedEdges] / ruCubeStateConverter::factLookup[numOfIgnoredEdges];

    if (numOfIgnoredEdges < 2 and (ruBaseCube::noOfEdges - numOfLockedEdges) >= 2) {
        ans /= 2;
    }
    //std::cout << "ans = " << ans << std::endl;
    uint8_t numOfIgnoredCorners = size(genParams.ignoredCornersPerm);
    uint8_t numOfLockedCorners = size(genParams.lockedCornersPerm);
    ans *= numOfCornerPerms[numOfIgnoredCorners][numOfLockedCorners];
    //std::cout << (int)numOfCornerPerms[numOfIgnoredCorners][numOfLockedCorners] << std::endl;
    uint8_t numOfIgnoredCornersOrient = std::count(begin(genParams.ignoredCornersOrient),
                                                   end(genParams.ignoredCornersOrient),
                                                   1);
    uint8_t numOfLockedCornersOrient = std::count_if(begin(genParams.lockedCornersOrient),
                                                     end(genParams.lockedCornersOrient),
                                                    [] (const auto &x) {
                                                        return x != -1;
                                                     });

    uint32_t numOfCornersOrients = 0;

    if (numOfLockedCornersOrient == ruBaseCube::noOfCorners) {
        numOfCornersOrients = 1;
    } else {
        numOfCornersOrients = static_cast<uint32_t>(pow(3.0, static_cast<double>(ruBaseCube::noOfCorners - numOfIgnoredCornersOrient - numOfLockedCornersOrient)));
        if (numOfIgnoredCornersOrient == 0) {
            numOfCornersOrients /= 3;
        }
    }

    ans *= numOfCornersOrients;

    return ans;
}

bool ruCubeMultiSolveHandler::optimizeReport() {

}
