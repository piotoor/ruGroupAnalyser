#include "ruCubeMultiSolveHandler.h"
#include "ruCubeStateConverter.h"
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <thread>
#include "ruException.h"
#include "ruCubeSingleSolveHandlerPool.h"
#include "ruCubeFileWriter.h"

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
                                                        flagsInitial(flags),
                                                        numOfThreads (calculateNumOfAvailableThreads()) {

}

ruCubeMultiSolveHandler::~ruCubeMultiSolveHandler() {
}

uint8_t ruCubeMultiSolveHandler::calculateNumOfAvailableThreads() {
    uint8_t cores = std::thread::hardware_concurrency();
    return fmaxf ( cores, UINT8_C(1) );
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

void ruCubeMultiSolveHandler::prepare() {
    uint64_t singleReportSize = estimateSingleSolveReportSize();
    uint32_t numOfCubes = calculateTotalNumberOfCubesToGenerate();
    uint64_t availableDiskSpace = calculateAvailableDiskSpace();
    bool canBeOptimizedFurther = true;
    bool optimized = false;


    std::cout << "You are about to generate and solve " << numOfCubes << " cubes..." << std::endl;
    if (singleReportSize * numOfCubes > availableDiskSpace) {
        std::cout << "Not enough available disk space to save the output." << std::endl;
        std::cout << "Trying to optimize..." << std::flush;
    }

    while (singleReportSize * numOfCubes > availableDiskSpace and canBeOptimizedFurther) {
        canBeOptimizedFurther = optimizeReport();
        singleReportSize = estimateSingleSolveReportSize();
        optimized = true;
    }

    if (not canBeOptimizedFurther) {
        std::cout << std::endl;
        throw ruCubeMultiSolveHandlerException("Not enough available disk space. Exiting...");
    }

    // number of threads
    std::cout << "DONE" << std::endl;
    printOptimizations();
}

void ruCubeMultiSolveHandler::generateAndSolve(std::string filename) {
    prepare();
    std::cout << "\nGenerating..." << std::endl;
    ruCubeSimpleBenchmarkTimer bt;

    auto writer = std::make_shared<ruCubeFileWriter>(filename);
    generator.init(genParams);
    ruCubeSingleSolveHandlerPool pool(writer, numOfThreads, solParams, genParams.toSolvedMasks(), flags);
    while (generator.hasNext()) {
        pool.enqueueCube(generator.next());
    }

    std::cout << "DONE ";
}

void ruCubeMultiSolveHandler::printOptimizations() {
    std::cout << std::endl;
    std::cout << "The following optimizations have been applied to reduce the output size:" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "+--------------------------+-------+-------+" << std::endl;
    std::cout << "|" << std::setw(26) << " parameters" << "|" << " old   " << "|" << " new   |" << std::endl;
    std::cout << "+--------------------------+-------+-------+" << std::endl;
    std::cout << "|" << std::setw(26) << " maxNumOfSolutions" << "| " << std::setw(6) << (int)solParamsInitial.maxNumOfSolutions << "| " << std::setw(6) << (int)solParams.maxNumOfSolutions << "|"
              <<  (solParamsInitial.maxNumOfSolutions > solParams.maxNumOfSolutions ? " *" : "") << std::endl;
    std::cout << "|" << std::setw(26) << " headers" << "| " << std::setw(6) << flagsInitial.headers << "| " << std::setw(6) << flags.headers << "|"
              <<  (flagsInitial.headers != flags.headers ? " *" : "") << std::endl;
    std::cout << "|" << std::setw(26) << " line numbers" << "| " << std::setw(6) << flagsInitial.lineNumbers << "| " << std::setw(6) << flags.lineNumbers << "|"
              <<  (flagsInitial.lineNumbers != flags.lineNumbers ? " *" : "") << std::endl;
    std::cout << "|" << std::setw(26) << " fixed width font" << "| " << std::setw(6) << flagsInitial.fixedWidthMoves << "| " << std::setw(6) << flags.fixedWidthMoves << "|"
              <<  (flagsInitial.fixedWidthMoves != flags.fixedWidthMoves ? " *" : "") << std::endl;
    std::cout << "|" << std::setw(26) << " summary" << "| " << std::setw(6) << flagsInitial.summary << "| " << std::setw(6) << flags.summary << "|"
              <<  (flagsInitial.summary != flags.summary ? " *" : "") << std::endl;
    std::cout << "|" << std::setw(26) << " compressed solution" << "| " << std::setw(6) << flagsInitial.compressSolutions << "| " << std::setw(6) << flags.compressSolutions << "|"
              <<  (flagsInitial.compressSolutions != flags.compressSolutions ? " *" : "") << std::endl;
    std::cout << "|" << std::setw(26) << " compressed cube state" << "| " << std::setw(6) << compressedCubeStateInitial << "| " << std::setw(6) << compressedCubeState << "|"
              <<  (compressedCubeStateInitial != compressedCubeState ? " *" : "") << std::endl;
    std::cout << "+--------------------------+-------+-------+" << std::endl;
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

    ans += solParams.maxNumOfSolutions * (flags.compressSolutions ? maxCompressedSolutionStrSize : maxSolutionStrSize);

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


// K - non locked
// k - permutable

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
        } else if (not flags.compressSolutions) {
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