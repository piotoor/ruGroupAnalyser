#include <iostream>
#include <string>
#include "stypox/argparser.hpp"
#include "ruCubeScrambleParser.h"
#include "ruCube.h"
#include "ruCubeSolver.h"
#include "ruCubeSingleSolveHandler.h"
#include "ruCubeSimpleBenchmarkTimer.h"
#include "ruCubeSingleSolveInputParser.h"
#include "ruException.h"
#include "ruCubeSolvedMaskParser.h"
#include "ruCubeMultiSolveHandler.h"
#include "ruCubeGeneratorParametersParser.h"
#include <cstdlib>

enum class solvingMode {
    SINGLE_SOLVE_STATE,
    SINGLE_SOLVE_SCRAMBLE,
    GENERATOR,
    ANALYSIS
};

int main(int argc, char const* argv[]) {
    std::ios::sync_with_stdio(false);
    bool help = false;
    bool usage = false;
    std::pair<solvingMode, std::string> mode;

    solutionParameters solParams;
    solvedMasks masks;
    solveReportFlags reportFlags;

    uint8_t minLength = 0;
    uint8_t maxLength = 20;
    uint8_t maxNumOfSolutions = 1;
    bool headers = false;
    bool lineNumbers = false;
    bool fixedWidthMoves = false;
    bool summary = false;
    std::pair<uint64_t, uint32_t> solvedMask = std::make_pair(ruBaseCube::allCornersMask, ruBaseCube::allEdgesMask);

    try {
        stypox::ArgParser p {
            std::make_tuple(
                stypox::HelpSection { "\nHelp options:" },
                stypox::SwitchOption { "help", help, stypox::args("-?", "-h", "--help"), "show help screen" },
                stypox::SwitchOption { "usage", usage, stypox::args("-u", "--usage"), "show usage screen" },

                stypox::HelpSection { "\nCube state definition options:" },
                stypox::ManualOption { "cubeDefinition", mode, stypox::args("-m=", "--mode="), "mode (cube state format: \"s;000102030405;0123456\", scramble format: \"S;R U2 R' U' R' U' R2\")",
                    [] (const std::string_view& str) {
                        try {
                            size_t semicolonIndex = str.find_first_of(";");
                            if (semicolonIndex == std::string::npos)
                                throw std::runtime_error{""};
                            solvingMode sm = solvingMode::SINGLE_SOLVE_SCRAMBLE;

                            std::string_view modeStr = str.substr(0, semicolonIndex);
                            std::string_view args = str.substr(semicolonIndex + 1);

                            if (modeStr == "s") {
                                sm = solvingMode::SINGLE_SOLVE_STATE;
                            } else if (modeStr == "g") {
                                sm = solvingMode::GENERATOR;
                            } else if (modeStr == "S") {
                                sm = solvingMode::SINGLE_SOLVE_SCRAMBLE;
                            } else {
                                throw std::runtime_error{""};
                            }

                            return std::pair<solvingMode, std::string>{sm, args};
                        } catch (...) {
                            throw std::runtime_error{"Invalid cube state format: " + std::string{str}};
                        }
                },
                true },

                stypox::HelpSection { "\nSolver options:" },
                stypox::Option { "numOfSolutions", maxNumOfSolutions, stypox::args("-n=", "--num-of-sols="), "number of solutions per cube (1-; default=1)",
                    false,
                    [] (int value){
                        return value >= 1 and value <= 255;
                    }},
                stypox::Option { "minLength", minLength, stypox::args("-l=", "--min-length="), "min solution length (0-20; default=0)",
                    false,
                    [] (int value){
                        return value >= 0 and value <= 20;
                    }},
                stypox::Option { "maxLength", maxLength, stypox::args("-h=", "--max-length="), "max solution length (0-20; default=20)",
                    false,
                    [] (int value){
                        return value >= 0 and value <= 20;
                    }},
                stypox::ManualOption { "solvedMask", solvedMask, stypox::args("-s=", "--solved-mask="), "solved mask (format: \"001101010101;1010011\")",
                    [] (const std::string_view& str) {
                        try {
                            return ruCubeSolvedMaskParser::stringSolvedMaskToIntSimple(std::string{str});
                        } catch (const ruCubeSolvedMaskException &e) {
                            throw std::runtime_error{std::string(e.what())};
                        }
                },
                false },

                stypox::HelpSection { "\nOutput options:" },
                stypox::SwitchOption { "headers", headers, stypox::args("-H", "--headers"), "headers" },
                stypox::SwitchOption { "lineNumbers", lineNumbers, stypox::args("-L", "--line-numbers"), "line numbers" },
                stypox::SwitchOption { "fixedWidthMoves", fixedWidthMoves, stypox::args("-F", "--fixed-width"), "fixed width moves" },
                stypox::SwitchOption { "summary", summary, stypox::args("-S", "--summary"), "solution summary" }
            ),
            "--------------- ruGroupAnalyser ---------------"
        };

        p.parse(argc, argv);


        if (help) {
            std::cout << p.help();
            return 0;
        }
        if (usage) {
            std::cout << p.usage();
            return 0;
        }

        p.validate();

    } catch (const std::runtime_error &e) {
        std::cout << std::string(e.what()) << std::endl;

        return EXIT_FAILURE;
    }

    if (mode.first == solvingMode::SINGLE_SOLVE_SCRAMBLE) {
        ruCubeSingleSolveInputParser parser;
        try {
            auto cube = parser.getCubeFromScramble(mode.second);
            auto [cornersMask, edgesMask] = solvedMask;
            masks.cornersMask = cornersMask;
            masks.edgesMask = edgesMask;
            solParams.maxLength = maxLength;
            solParams.minLength = minLength;
            solParams.maxNumOfSolutions = maxNumOfSolutions;
            reportFlags.fixedWidthMoves = fixedWidthMoves;
            reportFlags.headers = headers;
            reportFlags.lineNumbers = lineNumbers;
            reportFlags.summary = summary;

            ruCubeSingleSolveHandler solveHandler(solParams, masks, reportFlags);
            solveHandler.solve(cube);

            std::cout << solveHandler.getReport();
        } catch (const ruCubeScrambleException &e) {
            std::cout << std::string(e.what()) << std::endl;
            return EXIT_FAILURE;
        }

    } else if (mode.first == solvingMode::SINGLE_SOLVE_STATE) {
        ruCubeSingleSolveInputParser parser;
        try {
            auto cube = parser.getCubeFromState(mode.second);
            auto [cornersMask, edgesMask] = solvedMask;
            masks.cornersMask = cornersMask;
            masks.edgesMask = edgesMask;
            solParams.maxLength = maxLength;
            solParams.minLength = minLength;
            solParams.maxNumOfSolutions = maxNumOfSolutions;
            reportFlags.fixedWidthMoves = fixedWidthMoves;
            reportFlags.headers = headers;
            reportFlags.lineNumbers = lineNumbers;
            reportFlags.summary = summary;

            ruCubeSingleSolveHandler solveHandler(solParams, masks, reportFlags);
            solveHandler.solve(cube);

            std::cout << solveHandler.getReport();
        } catch (const ruCubeStateException& e) {
            std::cout << std::string(e.what()) << std::endl;
            return EXIT_FAILURE;
        }


    } else if (mode.first == solvingMode::GENERATOR ){
        try {
            auto genParams = ruCubeGeneratorParametersParser::strGeneratorParametersToStruct(mode.second);
            solParams.maxLength = maxLength;
            solParams.minLength = minLength;
            solParams.maxNumOfSolutions = maxNumOfSolutions;
            reportFlags.fixedWidthMoves = fixedWidthMoves;
            reportFlags.headers = headers;
            reportFlags.lineNumbers = lineNumbers;
            reportFlags.summary = summary;

            ruCubeMultiSolveHandler handler(genParams, solParams, reportFlags);
            try {
                handler.generateAndSolve("default.ruc");
            } catch (ruCubeMultiSolveHandlerException &e) {
                std::cout << std::string(e.what()) << std::endl;
                return EXIT_FAILURE;
            }
        } catch (ruCubeGeneratorParametersException &e) {
            std::cout << std::string(e.what()) << std::endl;
            return EXIT_FAILURE;
        }
    } else if (mode.first == solvingMode::ANALYSIS ){
        std::cout << "Mode currently unavailable." << std::endl;
    }


    return EXIT_SUCCESS;
}
