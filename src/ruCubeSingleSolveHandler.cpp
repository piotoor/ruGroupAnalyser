#include "ruCubeSingleSolveHandler.h"
#include <iomanip>
#include <cmath>

ruCubeSingleSolveHandler::ruCubeSingleSolveHandler( const solutionParameters &solParams,
                                                    const solvedMasks &masks,
                                                    const solveReportFlags &flags):
                                                        solver(solParams,
                                                               masks),
                                                        headers(flags.headers),
                                                        lineNumbers(flags.lineNumbers),
                                                        fixedWidthMoves(flags.fixedWidthMoves) {

}

ruCubeSingleSolveHandler::~ruCubeSingleSolveHandler() {
}


void ruCubeSingleSolveHandler::configure(   const solutionParameters &solParams,
                                            const solvedMasks &masks,
                                            const solveReportFlags &flags) {
    solver.configure(solParams, masks);
    this->headers = flags.headers;
    this->lineNumbers = flags.lineNumbers;
    this->fixedWidthMoves = flags.fixedWidthMoves;
}

void ruCubeSingleSolveHandler::solve(ruLutCube cube) {
    solutionsStr.clear();
    solutionsVect.clear();
    ruCubeSimpleBenchmarkTimer bt(false, false);
    solver.solve(&cube);
    elapsedTime = bt.getElapsedTime();
    solutionsVect = solver.getSolutionsAsVectors();
    solutionsStr = solver.getSolutionsAsStrings();
}

std::string ruCubeSingleSolveHandler::getReport() {
    report.str( std::string() );
    report.clear();

    int currLength = -1;
    for (size_t i = 0; i < size(solutionsVect); ++i) {
        if (size(solutionsVect[i]) != currLength) {
            if (currLength != -1 and headers) {
                    report << "\n";
            }
            currLength = size(solutionsVect[i]);
            if (headers) {

                report << "Solutions of length " << std::setw(2) << std::to_string(currLength) << "..." << std::endl;
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

std::vector<std::vector<uint8_t>> ruCubeSingleSolveHandler::getSolutionsAsVectors() {
    return solutionsVect;
}
std::vector<std::string> ruCubeSingleSolveHandler::getSolutionsAsStrings() {
    return solutionsStr;
}
