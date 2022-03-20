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
#include <unordered_map>
#include <unordered_set>
#include <fstream>

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

    template <int N, int P, int MaxDepth>
    std::array<std::array<int8_t, P>, N> generatePruningTable(std::string tableName, std::function<void(ruCube&, ruCubeStateConverter&, int, int, int, uint8_t, std::unordered_map<uint32_t, uint8_t>&, std::unordered_map<uint32_t, std::unordered_set<uint32_t>>&)> dfs) {
        std::ifstream inFile(tableName + "PruningTable.pru");
        std::array<std::array<int8_t, P>, N>  ans {};
        if (inFile.good()) {
            std::string message = "Loading " + tableName + " pruning table...";
            std::cout << std::setw(48) << std::left << message << std::flush;

            ruCubeSimpleBenchmarkTimer bt;

            for (uint16_t i = 0; i < N; ++i) {
                inFile.read((char*)ans[i].data(), P);
            }

            std::cout << "DONE ";
        } else {
            inFile.close();
            {
                std::string message = "Generating " + tableName + " pruning table...";
                std::cout << std::setw(48) << std::left << message << std::flush;

                ruCubeSimpleBenchmarkTimer bt;

                for (auto &r: ans) {
                    r.fill(-1);
                }
                ruCube cube;
                ruCubeStateConverter converter;

                std::unordered_map<uint32_t, uint8_t> partialPruningTable;
                std::unordered_map<uint32_t, std::unordered_set<uint32_t>> partialOwners;

                for (uint8_t partInd = 0; partInd < P; ++partInd) {
                    partialOwners.clear();
                    dfs(cube, converter, 1, MaxDepth, -6, partInd, partialPruningTable, partialOwners);
                    for (const auto &[partial, fullCases]: partialOwners) {
                        for (const auto &fullCase: fullCases) {
                            if (ans[fullCase][partInd] == -1 or partialPruningTable[partial] < ans[fullCase][partInd]) {
                                ans[fullCase][partInd] = partialPruningTable[partial];
                            }

                        }
                    }
                }
                ans[0].fill(0);
                std::cout << "DONE ";
            }
            {
                std::string message = "Saving " + tableName + " pruning table...";
                std::cout << std::setw(48) << std::left << message << std::flush;

                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream outFile(tableName + "PruningTable.pru");

                if (outFile.good()) {
                    for (uint16_t i = 0; i < N; ++i) {
                        outFile.write((char*)ans[i].data(), P);
                    }
                }

                outFile.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }

    void cornersPartialOrientPruningDfs(ruCube &cube,
                                        ruCubeStateConverter &conv,
                                        int depth,
                                        int maxDepth,
                                        int prevMove,
                                        uint8_t partInd,
                                        std::unordered_map<uint32_t, uint8_t> &pruningTable,
                                        std::unordered_map<uint32_t, std::unordered_set<uint32_t>> &partialOrientOwners);

    void cornersPartialPermPruningDfs(  ruCube &cube,
                                        ruCubeStateConverter &conv,
                                        int depth,
                                        int maxDepth,
                                        int prevMove,
                                        uint8_t partInd,
                                        std::unordered_map<uint32_t, uint8_t> &pruningTable,
                                        std::unordered_map<uint32_t, std::unordered_set<uint32_t>> &partialPermOwners);

    void edgesPartialPermPruningDfs(ruCube &cube,
                                ruCubeStateConverter &conv,
                                int depth,
                                int maxDepth,
                                int prevMove,
                                uint8_t partInd,
                                std::unordered_map<uint32_t, uint8_t> &pruningTable,
                                std::unordered_map<uint32_t, std::unordered_set<uint32_t>> &partialPermOwners);




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
    inline static const uint8_t maxCornersPermPruningDepth = 6;
    inline static const uint8_t maxCornersOrientPruningDepth = 11;

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
