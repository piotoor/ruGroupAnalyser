#include "ruCubeSingleSolveHandler.h"
#include <iomanip>
#include <cmath>

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

void ruCubeSingleSolveHandler::solve(ruLutCube cube) {
    ruCubeSimpleBenchmarkTimer bt(false, false);
    solver.solve(&cube);
    elapsedTime = bt.getElapsedTime();
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
            report << std::setw(log(size(solutionsVect)) + 1) << std::left << std::to_string(i + 1) + "." << " ";
        }


        if (fixedWidthMoves) {
            std::string solution;
            for (const auto &x: solutionsStr[i]) {

                if (!solution.empty() and x == ' ' and isalpha(solution.back())) {
                    solution += ' ';
                }
                solution += x;
            }
            report << solution << std::endl;
        } else {
            report << solutionsStr[i] << std::endl;
        }
    }
    if (headers) {
        report << "\nSolutions found: " << std::to_string(size(solutionsVect)) << std::endl;
        report << "Solving time: " << elapsedTime.count() << "ms" << std::endl;
    }

    return report.str();
}
