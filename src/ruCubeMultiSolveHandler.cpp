#include "ruCubeMultiSolveHandler.h"
#include "ruCubeStateConverter.h"
#include <cmath>
#include <algorithm>
#include <filesystem>

auto operator""_MB(long double x) -> uint64_t {
    return 1024ULL * 1024ULL * x;
}

auto operator""_GB(long double x) -> uint64_t {
    return 1024ULL * 1024ULL * 1024ULL * x;
}

ruCubeMultiSolveHandler::ruCubeMultiSolveHandler(   const generatorParameters &genParams,
                                                    const solutionParameters &solParams,
                                                    const solveReportFlags &flags):
                                                        solParams(solParams),
                                                        flags(flags),
                                                        genParams(genParams),
                                                        solParamsInitial(solParams),
                                                        flagsInitial(flags) {

}

ruCubeMultiSolveHandler::~ruCubeMultiSolveHandler() {

}

void ruCubeMultiSolveHandler::configure( const generatorParameters &genParams,
                                    const solutionParameters &solParams,
                                    const solveReportFlags &flags) {
    this->genParams = genParams;
    this->solParams = solParams;
    this->flags = flags;
    this->solParamsInitial = solParams;
    this->flagsInitial = flags;
}

void ruCubeMultiSolveHandler::generateAndSolve(std::string filename) {
    uint64_t singleReportSize = estimateSingleSolveReportSize();
    uint32_t numOfCubes = calculateTotalNumberOfCubesToGenerate();
    uint64_t availableDiskSpace = calculateAvailableDiskSpace();
    bool canBeOptimizedFurther = true;
    bool optimized = false;

    std::cout << "You are about to generate and solve " << numOfCubes << " cubes..." << std::endl;
    if (singleReportSize * numOfCubes > availableDiskSpace) {
        std::cout << "Not enough available disk space to save the output.\nTrying to optimize";
    }

    while (singleReportSize * numOfCubes > availableDiskSpace and canBeOptimizedFurther) {
        canBeOptimizedFurther = optimizeReport();
        singleReportSize = estimateSingleSolveReportSize();
        optimized = true;
        std::cout << ".";
    }

    if (not canBeOptimizedFurther) {
        throw 666; // notEnoughAvailableDiskSpace
    }

    if (optimized) {
        std::cout << std::endl;
        std::cout << "The following optimizations have been applied to reduce the output size:" << std::endl;
        if (solParams.maxNumOfSolutions) {

        }
    }

    std::cout << "\nWorking..." << std::endl;
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

void ruCubeMultiSolveHandler::disableSummary() {
    flags.summary = false;
}

void ruCubeMultiSolveHandler::compressSolutions() {
    flags.compressSolutions = true;
}

void ruCubeMultiSolveHandler::compressCubeState() {
    compressedCubeState = true;
}

uint64_t ruCubeMultiSolveHandler::estimateSingleSolveReportSize() {
    uint64_t ans = 0;

    if (compressedCubeState) {
        ans += maxCompressedCubeStateStrSize;
    } else {
        ans += maxCubeStateStrSize;
    }

    ans += solParams.maxNumOfSolutions * flags.compressSolutions ? maxCompressedSolutionStrSize : maxSolutionStrSize;

    if (flags.lineNumbers) {
        ans += solParams.maxNumOfSolutions * maxLineNumStrSize;
    }

    if (flags.headers) {
        ans += maxNumOfHeaders * maxHeaderStrSize + maxNumOfBlankLines;
    }

    if (flags.summary) {
        ans += maxSummaryStrSize;
    }

    ans += 1; // blank line after report

    return ans;
}

uint64_t ruCubeMultiSolveHandler::calculateAvailableDiskSpace() {
    std::error_code ec;
    const std::filesystem::space_info si = std::filesystem::space(".", ec);
    return si.available;
}

uint32_t ruCubeMultiSolveHandler::calculateTotalNumberOfCubesToGenerate() {
    uint8_t numOfIgnoredEdges = size(genParams.ignoredEdges);
    uint8_t numOfLockedEdges = size(genParams.lockedEdges);
    uint32_t ans = ruCubeStateConverter::factLookup[ruBaseCube::noOfEdges - numOfLockedEdges] / ruCubeStateConverter::factLookup[numOfIgnoredEdges];

    if (numOfIgnoredEdges < 2 and (ruBaseCube::noOfEdges - numOfLockedEdges) >= 2) {
        ans /= 2;
    }

    uint8_t numOfIgnoredCorners = size(genParams.ignoredCornersPerm);
    uint8_t numOfLockedCorners = size(genParams.lockedCornersPerm);
    ans *= numOfCornerPerms[numOfIgnoredCorners][numOfLockedCorners];

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
    if (solParams.maxNumOfSolutions > 0) {
        if (flags.lineNumbers) {
            disableLineNumbers();
            return true;
        } else if (flags.fixedWidthMoves) {
            disableFixedWidthMoves();
            return true;
        } else if (not compressedCubeState) {
            compressCubeState();
            return true;
        } else if (flags.summary) {
            disableSummary();
            return true;
        } else if (flags.compressSolutions) {
            compressSolutions();
            return true;
        } else if (flags.headers) {
            disableHeadersAndFooters();
            return true;
        } else {
            solParams.maxNumOfSolutions--;
            flags = flagsInitial;
            compressedCubeState = false;
            return solParams.maxNumOfSolutions > 0;
        }
    }
    return false;
}
