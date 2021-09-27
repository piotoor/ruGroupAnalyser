#include <iostream>
#include <string>
#include "stypox/argparser.hpp"
#include "ruCubeScrambleParser.h"
#include "ruCube.h"
#include "ruCubeSolver.h"
#include "ruCubeSingleSolveHandler.h"
#include "ruCubeSimpleBenchmarkTimer.h"

enum class solvingMode {
    SINGLE_SOLVE_STATE,
    SINGLE_SOLVE_SCRAMBLE,
    GENERATOR,
    ANALYSIS
};

int main(int argc, char const* argv[]) {
    bool help = false;
    bool usage = false;
    std::pair<solvingMode, std::string> mode;
    uint8_t minLength = 0;
    uint8_t maxLength = 20;
    int maxNumOfSolutions = 1;
    bool headers = false;
    bool lineNumbers = false;
    bool fixedWidthMoves = false;

    stypox::ArgParser p {
        std::make_tuple(
            stypox::HelpSection { "\nHelp options:" },
            stypox::SwitchOption { "help", help, stypox::args("-?", "-h", "--help"), "show help screen" },
            stypox::SwitchOption { "usage", usage, stypox::args("-u", "--usage"), "show usage screen" },

            stypox::HelpSection { "\nCube state definition options:" },
            stypox::ManualOption { "cubeDefinition", mode, stypox::args("-m=", "--mode="), "solving mode (format: 's;cp-co-ep'|'g;cpf-cpi-cof-coi-epf-epi'|'S;<scramble>')",
                [] (const std::string_view& str) {
                    try {
                        size_t semicolonIndex = str.find_first_of(";");
                        if (semicolonIndex == std::string::npos)
                            throw std::runtime_error{""};
                        solvingMode mode = solvingMode::SINGLE_SOLVE_SCRAMBLE;

                        std::string_view modeStr = str.substr(0, semicolonIndex);
                        std::string_view args = str.substr(semicolonIndex + 1);

                        if (modeStr == "s") {
                            mode = solvingMode::SINGLE_SOLVE_STATE;
                        } else if (modeStr == "g") {
                            mode = solvingMode::GENERATOR;
                        } else if (modeStr == "S") {
                            mode = solvingMode::SINGLE_SOLVE_SCRAMBLE;
                        } else {
                            throw std::runtime_error{std::string("Invalid solving mode ") + std::string(modeStr)};
                        }

                        return std::pair<solvingMode, std::string>{mode, args};
                    } catch (...) {
                        throw std::runtime_error{"Invalid solving mode " + std::string{str}};
                    }
            },
            true },

            stypox::HelpSection { "\nSolver options:" },
            stypox::Option { "numOfSolutions", maxNumOfSolutions, stypox::args("-n=", "--num-of-sols="), "number of solutions per cube (1-; default=1)",
                false,
                [] (int value){
                    return value >= 1;
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

            stypox::HelpSection { "\nOutput options:" },
            stypox::SwitchOption { "headers", headers, stypox::args("-H", "--headers"), "headers in solve report" },
            stypox::SwitchOption { "lineNumbers", lineNumbers, stypox::args("-L", "--line-numbers"), "line numbers in solve report" },
            stypox::SwitchOption { "fixedWidthMoves", fixedWidthMoves, stypox::args("-F", "--fixed-width"), "fixed width moves in solve report" }
        ),
        "ruGroupAnalyser"
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

    if (mode.first == solvingMode::SINGLE_SOLVE_SCRAMBLE) {
        auto scramble = ruCubeScrambleParser::stringScrambleToVectorScramble(mode.second);
        ruCubeSingleSolveHandler solveHandler(minLength, maxLength, maxNumOfSolutions, headers, lineNumbers, fixedWidthMoves);
        ruCubeSimpleBenchmarkTimer bt;
        solveHandler.solve(scramble);

        std::cout << solveHandler.getReport();
        std::cout << "Total time: ";

    } else if (mode.first == solvingMode::SINGLE_SOLVE_STATE) {
        std::cout << "Mode currently unavailable." << std::endl;
    } else if (mode.first == solvingMode::GENERATOR ){
        std::cout << "Mode currently unavailable." << std::endl;
    } else if (mode.first == solvingMode::ANALYSIS ){
        std::cout << "Mode currently unavailable." << std::endl;
    }


    return 0;
}
