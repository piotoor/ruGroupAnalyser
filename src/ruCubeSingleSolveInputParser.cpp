#include "ruCubeSingleSolveInputParser.h"
#include "ruException.h"

ruCubeSingleSolveInputParser::ruCubeSingleSolveInputParser() {
    //ctor
}

ruCubeSingleSolveInputParser::~ruCubeSingleSolveInputParser() {
    //dtor
}

ruLutCube ruCubeSingleSolveInputParser::getCubeFromScramble(std::string scramble) {
    auto scr = ruCubeScrambleParser::stringScrambleToVectorScramble(scramble);
    ruLutCube cube;
    cube.scramble(scr);
    return cube;
}

// cp, co, ep
using ruCubeStateVect = std::tuple<cornersArray, cornersArray, edgesArray>;

ruLutCube ruCubeSingleSolveInputParser::getCubeFromState(std::string state) {
    auto [cp, co, ep] = ruCubeStateParser::stringStateToVect(state);
    if (!validator.isVectCornersPermValid(cp)) {
        throw ruCubeStateException("Validation exception. Invalid corners permutation.");
    } else if (!validator.isVectCornersOrientValid(co)) {
        throw ruCubeStateException("Validation exception. Invalid corners orientation.");
    } else if (!validator.isVectEdgesValid(ep)) {
        throw ruCubeStateException("Validation exception. Invalid edges permutation.");
    }

    if (!validator.isVectCubeStateSolveableQuick(co, cp, ep)) {
        throw ruCubeStateException("Validation exception. Unsolvable state.");
    }

    ruLutCube cube(converter.vectEdgesPermToLexIndexEdgesPerm(ep),
                   converter.vectCornersPermToLexIndexCornersPerm(cp),
                   converter.vectCornersOrientToLexIndexCornersOrient(co));

    return cube;
}
