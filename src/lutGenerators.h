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

    inline static const uint16_t noOfEdgesPermSolvedStates = 16;
    enum class edgesPermSolvedState {
        allEdges,
        f2lEdgesInRSolved,
        f2lEdgesInUSolved,
        llEdgesInRSolved,
        llEdgesInUSolved,
        mEdgesInM,
        eEdgesInE,
        sEdgesInS,

        UF,
        UL,
        UB,
        UR,
        BR,
        DR,
        FR,

        noEdges
    };
    std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> generateEdgesPermSolvedTable ();

    inline static const uint16_t noOfCornersPermSolvedStates = 12;
    enum class cornersPermSolvedState {
        allCorners,
        f2lCornersInRSolved,
        f2lCornersInUSolved,
        llCornersInRSolved,
        llCornersInUSolved,

        URF,
        UFL,
        ULB,
        UBR,
        DRB,
        DFR,

        noCorners
    };
    std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> generateCornersPermSolvedTable ();

    inline static const uint16_t noOfCornersOrientSolvedStates = 12;
    enum class cornersOrientSolvedState {
        allCorners,
        f2lCornersInROriented,
        f2lCornersInUOriented,
        llCornersInROriented,
        llCornersInUOriented,

        URF,
        UFL,
        ULB,
        UBR,
        DRB,
        DFR,

        noCorners
    };
    std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> generateCornersOrientSolvedTable ();
}


#endif // LUTGENERATORS_H
