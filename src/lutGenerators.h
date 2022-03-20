#ifndef LUTGENERATORS_H
#define LUTGENERATORS_H
#include "ruCube.h"
#include "ruCubeStateConverter.h"
#include "ruCubeSimpleBenchmarkTimer.h"
#include "ruCubeFactory.h"
#include <bitset>
#include <iostream>
#include <iterator>
#include <array>
#include <iomanip>
#include <vector>
#include <functional>

namespace lutGenerators {
    template <int N>
    std::array<std::array<uint16_t, ruBaseCube::noOfTurns>, N> generateMoveMap (std::function <void(std::unique_ptr<ruBaseCube>::pointer, ruCubeStateConverter&, uint16_t)> setter,
                                                                                std::function <uint16_t(std::unique_ptr<ruBaseCube>::pointer, ruCubeStateConverter&)> getter,
                                                                                std::string mapName) {
        std::string message = "Generating " + mapName + " move map...";
        std::cout << std::setw(48) << std::left << message << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::array<uint16_t, ruBaseCube::noOfTurns>, N> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t lexIndex = 0; lexIndex < N; ++lexIndex) {
            for (uint8_t t = R; t <= Ui; ++t) {
                setter(cube.get(), converter, lexIndex);
                cube->turn(t);
                ans[lexIndex][t] = getter(cube.get(), converter);
            }
        }

        std::cout << "DONE ";
        return ans;
    }

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
    std::array<std::bitset<ruBaseCube::noOfEdgesPermSolvedStates>, ruBaseCube::noOfEdgesPermutations> generateEdgesPermSolvedTable ();

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
    std::array<std::bitset<ruBaseCube::noOfCornersPermSolvedStates>, ruBaseCube::noOfCornersPermutations> generateCornersPermSolvedTable ();

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
    std::array<std::bitset<ruBaseCube::noOfCornersOrientSolvedStates>, ruBaseCube::noOfCornersOrientations> generateCornersOrientSolvedTable ();

    inline static const uint8_t maxEdgesPermPruningDepth = 11;
    std::array<std::array<int8_t, ruBaseCube::noOfPartialEdgesPermCases>, ruBaseCube::noOfEdgesPermutations> generateEdgesPermPruningTable();

    inline static const uint8_t maxCornersPermPruningDepth = 6;
    std::array<std::array<int8_t, ruBaseCube::noOfPartialCornersPermCases>, ruBaseCube::noOfCornersPermutations> generateCornersPermPruningTable();

    inline static const uint8_t maxCornersOrientPruningDepth = 11;
    std::array<std::array<int8_t, ruBaseCube::noOfPartialCornersOrientCases>, ruBaseCube::noOfCornersOrientations> generateCornersOrientPruningTable();


    inline static const uint8_t maxCornersPruningDepth = 14;
    std::array<std::array<int8_t, ruBaseCube::noOfCornersOrientations>, ruBaseCube::noOfCornersPermutations> generateCornersPruningTable();

    #ifdef DEBUG
        inline static const uint8_t maxFullCubePruningDepth = 14;
    #else
        inline static const uint8_t maxFullCubePruningDepth = 17;
    #endif

    std::vector<std::vector<std::vector<int8_t>>> generateFullCubePruningTable();

    inline static const uint8_t maxPermutationValidityDepth = 15;
    std::array<std::bitset<ruBaseCube::noOfEdgesPermutations>, ruBaseCube::noOfCornersPermutations> generatePermutationValidityTable();
}


#endif // LUTGENERATORS_H
