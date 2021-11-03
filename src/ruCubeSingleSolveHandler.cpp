#include "ruCubeSingleSolveHandler.h"
#include <iomanip>
#include <cmath>

ruCubeSingleSolveHandler::ruCubeSingleSolveHandler( const solutionParameters &solParams,
                                                    const solvedMasks &masks,
                                                    const solveReportFlags &flags):
                                                        solver(solParams,
                                                               masks),
                                                        flags(flags){

}

ruCubeSingleSolveHandler::~ruCubeSingleSolveHandler() {
}

ruCubeSingleSolveHandler::ruCubeSingleSolveHandler(const ruCubeSingleSolveHandler &other) {
    solver = other.solver;
    report.str( std::string() );
    report.clear();
    report << other.report.rdbuf();

    flags = other.flags;

    elapsedTime = other.elapsedTime;
    solutionsVect = other.solutionsVect;
    solutionsStr = other.solutionsStr;
};

void ruCubeSingleSolveHandler::configure(   const solutionParameters &solParams,
                                            const solvedMasks &masks,
                                            const solveReportFlags &flags) {
    solver.configure(solParams, masks);
    this->flags = flags;
}

void ruCubeSingleSolveHandler::solve(ruLutCube cube) {
    solutionsStr.clear();
    solutionsVect.clear();
    ruCubeSimpleBenchmarkTimer bt(false, false);
    currCube = cube;
    solver.solve(&cube);
    elapsedTime = bt.getElapsedTime();
    solutionsVect = solver.getSolutionsAsVectors();
    solutionsStr = solver.getSolutionsAsStrings(flags.compressSolutions);
}

std::string ruCubeSingleSolveHandler::getReport() {
    report.str( std::string() );
    report.clear();

    if (flags.compressCubeState) {
        report << currCube.toString() << std::endl;
    } else {
        report << "+------------+-------+" << std::endl;
        report << "|" << currCube.toString() << "|" << std::endl;
        report << "+------------+-------+" << std::endl;
    }
    int currLength = -1;
    for (size_t i = 0; i < size(solutionsVect); ++i) {
        if (size(solutionsVect[i]) != currLength) {
            if (currLength != -1 and flags.headers) {
                    report << "\n";
            }
            currLength = size(solutionsVect[i]);
            if (flags.headers) {

                report << "Solutions of length " << std::setw(2) << std::to_string(currLength) << "..." << std::endl;
            }
        }
        if (flags.lineNumbers) {
            report << std::setw(log(size(solutionsVect)) + 1) << std::left << std::to_string(i + 1) + "." << " ";
        }


        if (flags.fixedWidthMoves and not flags.compressSolutions) {
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

    if (flags.summary) {
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
