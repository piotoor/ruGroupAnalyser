#include "ruCubeSingleSolveHandler.h"
#include <iomanip>

ruCubeSingleSolveHandler::ruCubeSingleSolveHandler(   uint8_t minLength,
                                                        uint8_t maxLength,
                                                        uint8_t maxNumOfSolutions,
                                                        bool headers,
                                                        bool lineNumbers,
                                                        bool fixedWidthMoves,
                                                        uint32_t edgesMask,
                                                        uint64_t cornersMask): solver(minLength, maxLength, maxNumOfSolutions, edgesMask, cornersMask), headers(headers), lineNumbers(lineNumbers), fixedWidthMoves(fixedWidthMoves) {

}

ruCubeSingleSolveHandler::~ruCubeSingleSolveHandler() {
}


void ruCubeSingleSolveHandler::configure(  uint8_t minLength,
                                            uint8_t maxLength,
                                            uint8_t maxNumOfSolutions,
                                            bool headers,
                                            bool lineNumbers,
                                            bool fixedWidthMoves,
                                            uint32_t edgesMask,
                                            uint64_t cornersMask) {
    solver.configure(minLength, maxLength, maxNumOfSolutions, edgesMask, cornersMask);
    this->headers = headers;
    this->lineNumbers = lineNumbers;
    this->fixedWidthMoves = fixedWidthMoves;
}

void ruCubeSingleSolveHandler::solve(std::vector<uint8_t> scramble) {
    ruLutCube cube;
    cube.scramble(scramble);
    solver.solve(&cube);
}
void ruCubeSingleSolveHandler::solve(ruLutCube cube) {
    solver.solve(&cube);
}

std::string ruCubeSingleSolveHandler::getReport() {
    report.clear();
    auto solutionsVect = solver.getSolutionsAsVectors();
    auto solutionsStr = solver.getSolutionsAsStrings();

    int currLength = -1;
    for (size_t i = 0; i < size(solutionsVect); ++i) {
        if (size(solutionsVect[i]) != currLength) {
            currLength = size(solutionsVect[i]);
            if (headers) {
                report << "\nSolutions of length " << std::setw(2) << std::to_string(currLength) << "..." << std::endl;
            }
        }
        if (lineNumbers) {
            report << std::setw(4) << i + 1;
        }
        report << solutionsStr[i] << std::endl;
    }
    if (headers) {
        report << "\nSolutions found: " << std::to_string(size(solutionsVect)) << std::endl;
    }

    return report.str();
}
