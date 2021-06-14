#ifndef LUTGENERATORS_H
#define LUTGENERATORS_H
#include <bitset>

namespace lutGenerators {
    inline static const uint8_t noOfTurns = 6;
    inline static const uint16_t noOfEdgesPermutations = 5040;
    inline static const uint16_t noOfCornersPermutations = 720;
    inline static const uint16_t noOfCornersOrientations = 729;

    std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> generateEdgesPermMoveMap ();
    std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> generateCornersPermMoveMap ();
    std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> generateCornersOrientMoveMap ();

    inline static const uint16_t noOfEdgesPermSolvedStates = 15;

    enum class edgesPermSolvedState {
        allEdges,
        f2lEdgesInRSolved,
        f2lEdgesInUSolved,
        llEdgesInR,
        llEdgesInU,
        mEdgesInM,
        eEdgesInE,
        sEdgesInS,

        UF,
        UL,
        UB,
        UR,
        BR,
        DR,
        FR
    };

    std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> generateEdgesPermSolvedTable ();
}


#endif // LUTGENERATORS_H
