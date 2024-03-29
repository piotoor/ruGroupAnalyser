#include "ruCubeSingleSolveInputParser.h"
#include "ruException.h"

ruLutCube ruCubeSingleSolveInputParser::getCubeFromScramble(std::string scramble) {
    auto scr = ruCubeScrambleParser::stringScrambleToVectorScramble(scramble);
    ruLutCube cube;
    cube.scramble(scr);
    return cube;
}

ruLutCube ruCubeSingleSolveInputParser::getCubeFromState(std::string state) {
    auto [co, cp, ep] = ruCubeStateParser::stringStateToVect(state);
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

    ruLutCube cube(converter.vectCornersOrientToLexIndexCornersOrient(co),
                   converter.vectCornersPermToLexIndexCornersPerm(cp),
                   converter.vectEdgesPermToLexIndexEdgesPerm(ep));

    return cube;
}
