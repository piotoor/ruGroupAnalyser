#ifndef LUTGENERATORS_H
#define LUTGENERATORS_H
#include "ruCube.h"
#include "ruCubeStateConverter.h"

#include <bitset>
#include <iostream>
#include <iterator>
#include <array>
#include <iomanip>

namespace lutGenerators {
    inline static const uint8_t noOfTurns = 6;
    inline static const uint16_t noOfEdgesPermutations = 5040;
    inline static const uint16_t noOfCornersPermutations = 720;
    inline static const uint16_t noOfCornersOrientations = 729;

    std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> generateEdgesPermMoveMap ();
    std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> generateCornersPermMoveMap ();
    std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> generateCornersOrientMoveMap ();

    inline static const uint16_t noOfEdgesPermSolvedStates = 15;
    inline static const uint32_t edgesSolvedBitmask = 0x7FFF;
    enum class edgesPermSolvedState {
        FR,
        DR,
        BR,
        UR,
        UB,
        UL,
        UF,
        allEdges,
        f2lEdgesInRSolved,
        f2lEdgesInUSolved,
        llEdgesInRSolved,
        llEdgesInUSolved,
        mEdgesInM,
        eEdgesInE,
        sEdgesInS,
    };
    std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> generateEdgesPermSolvedTable ();

    inline static const uint16_t noOfCornersPermSolvedStates = 11;
    inline static const uint64_t cornersPermSolvedBitMask = 0x7FF;
    enum class cornersPermSolvedState {
        DFR,
        DRB,
        UBR,
        ULB,
        UFL,
        URF,
        allCorners,
        f2lCornersInRSolved,
        f2lCornersInUSolved,
        llCornersInRSolved,
        llCornersInUSolved,
    };
    std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> generateCornersPermSolvedTable ();

    inline static const uint16_t noOfCornersOrientSolvedStates = 11;
    inline static const uint64_t cornersOrientSolvedBitMask = 0x7FF;
    enum class cornersOrientSolvedState {
        DFR,
        DRB,
        UBR,
        ULB,
        UFL,
        URF,
        allCorners,
        f2lCornersInROriented,
        f2lCornersInUOriented,
        llCornersInROriented,
        llCornersInUOriented,
    };
    std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> generateCornersOrientSolvedTable ();

    inline static const uint8_t maxEdgesPermPruningDepth = 11;
    inline static const uint8_t noOfPartialEdgesPermCases = 128;
    std::array<std::array<int8_t, noOfPartialEdgesPermCases>, noOfEdgesPermutations> generateEdgesPermPruningTable();

    inline static const uint8_t maxCornersPermPruningDepth = 11;
    inline static const uint8_t noOfPartialCornersPermCases = 64;
    std::array<std::array<int8_t, noOfPartialCornersPermCases>, noOfCornersPermutations> generateCornersPermPruningTable();

    inline static const uint8_t maxCornersPruningDepth = 14;
    std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> generateCornersPruningTable();

    #ifdef DEBUG
        inline static const uint8_t maxFullCubePruningDepth = 14;
    #else
        inline static const uint8_t maxFullCubePruningDepth = 17;
    #endif

    inline static const uint8_t maxRealFullCubePruningDepth = 20;
    std::vector<std::vector<std::vector<int8_t>>> generateFullCubePruningTable();

    inline static const uint8_t maxPermutationValidityDepth = 15;
    std::array<std::bitset<lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations> generatePermutationValidityTable();
}


#endif // LUTGENERATORS_H
