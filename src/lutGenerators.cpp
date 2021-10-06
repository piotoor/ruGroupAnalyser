#include "ruCubeFactory.h"
#include "lutGenerators.h"

#include "ruCubeSimpleBenchmarkTimer.h"
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

namespace lutGenerators {
    std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> generateEdgesPermMoveMap () {
        std::cout << std::setw(48) << std::left << "Generating edges permutation move map..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t edgesPerm = 0; edgesPerm < noOfEdgesPermutations; ++edgesPerm) {
            cube->setEdges(converter.lexIndexEdgesToIntEdges(edgesPerm));

            for (uint8_t t = R; t <= Ui; ++t) {
                cube->turn(t);
                ans[edgesPerm][t] = converter.intEdgesToLexIndexEdges(cube->getEdges());
                cube->inverseTurn(t);
            }
        }

        std::cout << "DONE ";
        return ans;
    }
    std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> generateCornersPermMoveMap () {
        std::cout << std::setw(48) << std::left << "Generating corners permutation move map..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cornersPerm = 0; cornersPerm < noOfCornersPermutations; ++cornersPerm) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(cornersPerm, ruLutCube::solvedLexIndexCornersOrient));
            for (uint8_t t = R; t <= Ui; ++t) {
                cube->turn(t);
                ans[cornersPerm][t] = converter.intCornersToLexIndexCornersPerm(cube->getCorners());
                cube->inverseTurn(t);
            }
        }

        std::cout << "DONE ";
        return ans;
    }

    std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> generateCornersOrientMoveMap () {
        std::cout << std::setw(48) << std::left << "Generating corners orientation move map..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cornersOrient = 0; cornersOrient < noOfCornersOrientations; ++cornersOrient) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(ruLutCube::solvedLexIndexCornersPerm, cornersOrient));

            for (uint8_t t = R; t <= Ui; ++t) {
                cube->turn(t);
                ans[cornersOrient][t] = converter.intCornersToLexIndexCornersOrient(cube->getCorners());
                cube->inverseTurn(t);
            }
        }

        std::cout << "DONE ";
        return ans;
    }

    std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> generateEdgesPermSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating edges permutation solved table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t ep = 0; ep < noOfEdgesPermutations; ++ep) {
            cube->setEdges(converter.lexIndexEdgesToIntEdges(ep));
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::allEdges)] = cube->isSolvedEdges(ruCube::allEdgesMask);

            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::mEdgesInM)] = cube->isSolvedMEinM();
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::eEdgesInE)] = cube->isSolvedEEinE();
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::sEdgesInS)] = cube->isSolvedSEinS();

            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UF)] = cube->isSolvedEdges(ruCube::UFMask);
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UL)] = cube->isSolvedEdges(ruCube::ULMask);
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UB)] = cube->isSolvedEdges(ruCube::UBMask);
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UR)] = cube->isSolvedEdges(ruCube::URMask);
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::BR)] = cube->isSolvedEdges(ruCube::BRMask);
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::DR)] = cube->isSolvedEdges(ruCube::DRMask);
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::FR)] = cube->isSolvedEdges(ruCube::FRMask);

            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::f2lEdgesInRSolved)] =    ans[ep][static_cast<uint8_t>(edgesPermSolvedState::BR)] and
                                                                                        ans[ep][static_cast<uint8_t>(edgesPermSolvedState::DR)] and
                                                                                        ans[ep][static_cast<uint8_t>(edgesPermSolvedState::FR)];
            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::f2lEdgesInUSolved)] =    ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UF)] and
                                                                                        ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UL)] and
                                                                                        ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UB)];

            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::llEdgesInRSolved)] =     ans[ep][static_cast<uint8_t>(edgesPermSolvedState::f2lEdgesInRSolved)] and
                                                                                        ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UR)];

            ans[ep][static_cast<uint8_t>(edgesPermSolvedState::llEdgesInUSolved)] =     ans[ep][static_cast<uint8_t>(edgesPermSolvedState::f2lEdgesInUSolved)] and
                                                                                        ans[ep][static_cast<uint8_t>(edgesPermSolvedState::UR)];
        }

        std::cout << "DONE ";
        return ans;
    }

    std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> generateCornersPermSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating corners permutation solved table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cp = 0; cp < noOfCornersPermutations; ++cp) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(cp, ruLutCube::solvedLexIndexCornersOrient));
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::allCorners)] = cube->isSolvedCorners(ruCube::cornersPermutationMask);

            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::URF)] = cube->isSolvedCorners(ruCube::URFPermMask);
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::UFL)] = cube->isSolvedCorners(ruCube::UFLPermMask);
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::ULB)] = cube->isSolvedCorners(ruCube::ULBPermMask);
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::UBR)] = cube->isSolvedCorners(ruCube::UBRPermMask);
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::DRB)] = cube->isSolvedCorners(ruCube::DRBPermMask);
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::DFR)] = cube->isSolvedCorners(ruCube::DFRPermMask);

            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::f2lCornersInRSolved)] =    ans[cp][static_cast<uint8_t>(cornersPermSolvedState::DRB)]  and
                                                                                            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::DFR)];
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::f2lCornersInUSolved)] =    ans[cp][static_cast<uint8_t>(cornersPermSolvedState::UFL)]  and
                                                                                            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::ULB)];

            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::llCornersInRSolved)] =     ans[cp][static_cast<uint8_t>(cornersPermSolvedState::f2lCornersInRSolved)]  and
                                                                                            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::URF)]  and
                                                                                            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::UBR)];
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::llCornersInUSolved)] =     ans[cp][static_cast<uint8_t>(cornersPermSolvedState::f2lCornersInUSolved)]  and
                                                                                            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::URF)]  and
                                                                                            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::UBR)];
        }

        std::cout << "DONE ";
        return ans;
    }

    std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> generateCornersOrientSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating corners orientation solved table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t co = 0; co < noOfCornersOrientations; ++co) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(ruLutCube::solvedLexIndexCornersPerm, co));

            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::allCorners)] = cube->isSolvedCorners(ruCube::cornersOrientationMask);

            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::URF)] = cube->isSolvedCorners(ruCube::URFOrientMask);
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::UFL)] = cube->isSolvedCorners(ruCube::UFLOrientMask);
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::ULB)] = cube->isSolvedCorners(ruCube::ULBOrientMask);
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::UBR)] = cube->isSolvedCorners(ruCube::UBROrientMask);
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::DRB)] = cube->isSolvedCorners(ruCube::DRBOrientMask);
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::DFR)] = cube->isSolvedCorners(ruCube::DFROrientMask);

            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::f2lCornersInROriented)] =    ans[co][static_cast<uint8_t>(cornersOrientSolvedState::DRB)]  and
                                                                                                ans[co][static_cast<uint8_t>(cornersOrientSolvedState::DFR)];
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::f2lCornersInUOriented)] =    ans[co][static_cast<uint8_t>(cornersOrientSolvedState::UFL)]  and
                                                                                                ans[co][static_cast<uint8_t>(cornersOrientSolvedState::ULB)];

            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::llCornersInROriented)] =     ans[co][static_cast<uint8_t>(cornersOrientSolvedState::f2lCornersInROriented)]  and
                                                                                                ans[co][static_cast<uint8_t>(cornersOrientSolvedState::URF)]  and
                                                                                                ans[co][static_cast<uint8_t>(cornersOrientSolvedState::UBR)];
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::llCornersInUOriented)] =     ans[co][static_cast<uint8_t>(cornersOrientSolvedState::f2lCornersInUOriented)]  and
                                                                                                ans[co][static_cast<uint8_t>(cornersOrientSolvedState::URF)]  and
                                                                                                ans[co][static_cast<uint8_t>(cornersOrientSolvedState::UBR)];
        }

        std::cout << "DONE ";
        return ans;
    }


    void edgesPartialPermPruningDfs(ruCube &cube,
                                    ruCubeStateConverter &conv,
                                    uint8_t depth,
                                    uint8_t maxDepth,
                                    int8_t prevMove,
                                    uint8_t partInd,
                                    std::array<std::unordered_map<uint32_t, uint8_t>, noOfPartialEdgesPermCases> &pruningTable,
                                    std::array<std::unordered_set<uint32_t>, noOfPartialEdgesPermCases> &partialPermOwners) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                uint32_t partialPerm = cube.getEdges();
                for (uint8_t i = 0; i < ruCube::noOfEdges; ++i) {
                    int curr = ((07 << i * 3) & partialPerm) >> i * 3;
                    if ((partInd & (1 << (7 - curr - 1))) == 0) {
                        partialPerm |= (07 << i * 3);
                    }
                }

                partialPermOwners[partInd].insert(conv.intEdgesToLexIndexEdges(cube.getEdges()));
                if (pruningTable[partInd].find(partialPerm) == pruningTable[partInd].end()) {
                    pruningTable[partInd][partialPerm] = depth;

                } else {
                    if (depth < pruningTable[partInd][partialPerm]) {
                        pruningTable[partInd][partialPerm] = depth;
                    }
                }

                edgesPartialPermPruningDfs(cube, conv, depth + 1, maxDepth, i, partInd, pruningTable, partialPermOwners);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::array<uint8_t, noOfPartialEdgesPermCases>, noOfEdgesPermutations> generateEdgesPermPruningTable() {
        std::cout << std::setw(48) << std::left << "Generating edges permutation pruning table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::array<uint8_t, noOfPartialEdgesPermCases>, noOfEdgesPermutations>  ans {};
        for (auto &r: ans) {
            r.fill(-1);
        }
        ruCube cube;
        ruCubeStateConverter converter;
        ans[0].fill(0);

        std::array<std::unordered_map<uint32_t, uint8_t>, noOfPartialEdgesPermCases> edgesPartialPermPruningTable;
        std::array<std::unordered_set<uint32_t>, noOfPartialEdgesPermCases> partialPermOwners;

        for (uint8_t partInd = 0; partInd < noOfPartialEdgesPermCases; ++partInd) {
            edgesPartialPermPruningDfs(cube, converter, 1, maxEdgesPermPruningDepth, -6, partInd, edgesPartialPermPruningTable, partialPermOwners);
            for (const auto &x: partialPermOwners[partInd]) {
                ans[x][partInd] = edgesPartialPermPruningTable[partInd][x];
            }
        }


        std::cout << "DONE ";
        return ans;
    }


    void cornersPruningDfs(ruCube &cube, ruCubeStateConverter &conv, uint8_t depth, uint8_t maxDepth, int8_t prevMove, std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                auto lexIndexCornersPerm = conv.intCornersToLexIndexCornersPerm(cube.getCorners());
                auto lexIndexCornersOrient = conv.intCornersToLexIndexCornersOrient(cube.getCorners());
                if (depth < pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] or pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] == -1) {
                    pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] = depth;
                }

                cornersPruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> generateCornersPruningTable() {
        std::ifstream f("cornersPruningTable.pru");
        std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> ans {};
        if (f.good()) {
            std::cout << std::setw(48) << std::left << "Loading corners pruning table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;

            if (f.good()) {
                for (uint16_t i = 0; i < lutGenerators::noOfCornersPermutations; ++i) {
                    f.read((char*)ans[i].data(), lutGenerators::noOfCornersOrientations);
                }
            }
            std::cout << "DONE ";
        } else {
            f.close();
            {
                std::cout << std::setw(48) << std::left << "Generating corners pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                for (auto &row: ans) {
                    row.fill(-1);
                }

                ruCube cube;
                ruCubeStateConverter converter;
                ans[0][0] = 0;
                cornersPruningDfs(cube, converter, 1, maxCornersPruningDepth, -6, ans);

                std::cout << "DONE ";
            }
            {
                std::cout << std::setw(48) << std::left << "Saving corners pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream f("cornersPruningTable.pru");
                if (f.good()) {
                    for (uint16_t i = 0; i < lutGenerators::noOfCornersPermutations; ++i) {
                        f.write((char*)ans[i].data(), lutGenerators::noOfCornersOrientations);
                    }
                }
                f.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }


    void fullCubePruningDfs(ruCube &cube, ruCubeStateConverter &conv, uint8_t depth, uint8_t maxDepth, int8_t prevMove, std::vector<std::vector<std::vector<int8_t>>> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                auto lexIndexCornersPerm = conv.intCornersToLexIndexCornersPerm(cube.getCorners());
                auto lexIndexCornersOrient = conv.intCornersToLexIndexCornersOrient(cube.getCorners());
                auto lexIndexEdgesPerm = conv.intEdgesToLexIndexEdges(cube.getEdges());
                if (depth < pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] or pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] == -1) {
                    pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] = depth;
                }

                fullCubePruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::vector<std::vector<std::vector<int8_t>>> generateFullCubePruningTable() {
        std::vector<std::vector<std::vector<int8_t>>> ans (noOfCornersPermutations, std::vector(noOfCornersOrientations, std::vector<int8_t>(noOfEdgesPermutations, -1)));
        std::ifstream f;

        #ifndef DEBUG
            f.open("fullCubePruningTable.pru");
        #endif

        if (f.good()) {
            std::cout << std::setw(48) << std::left << std::string("Loading full cube pruning table (") + std::to_string((int)maxFullCubePruningDepth) + ")..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;
            for (uint16_t cp = 0; cp < lutGenerators::noOfCornersPermutations; ++cp) {
                for (uint16_t co = 0; co < lutGenerators::noOfCornersOrientations; ++co ) {
                    f.read((char*)(ans[cp][co].data()), lutGenerators::noOfEdgesPermutations);
                }
            }
            f.close();
            std::cout << "DONE ";
        } else {
            f.close();
            {
                std::cout << std::setw(48) << std::left << std::string("Generating full cube pruning table (") + std::to_string((int)maxFullCubePruningDepth) + ")..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;

                ruCube cube;
                ruCubeStateConverter converter;
                ans[0][0][0] = 0;
                fullCubePruningDfs(cube, converter, 1, maxFullCubePruningDepth, -6, ans);

                std::cout << "DONE ";
            }
            #ifndef DEBUG
            {
                std::cout << std::setw(48) << std::left << std::string("Saving full cube pruning table (") + std::to_string((int)maxFullCubePruningDepth) + ")..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream f("fullCubePruningTable.pru");
                if (f.good()) {
                    for (uint16_t cp = 0; cp < lutGenerators::noOfCornersPermutations; ++cp) {
                        for (uint16_t co = 0; co < lutGenerators::noOfCornersOrientations; ++co) {
                            f.write(reinterpret_cast<char*>(ans[cp][co].data()), lutGenerators::noOfEdgesPermutations);
                        }
                    }
                }
                f.close();
                std::cout << "DONE ";
            }
            #endif
        }
        return ans;
    }


    void permutationValidityDfs(ruCube &cube, ruCubeStateConverter &conv, uint8_t depth, uint8_t maxDepth, int8_t prevMove, std::array<std::bitset<lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                auto lexIndexCornersPerm = conv.intCornersToLexIndexCornersPerm(cube.getCorners());
                auto lexIndexEdgesPerm = conv.intEdgesToLexIndexEdges(cube.getEdges());
                pruningTable[lexIndexCornersPerm][lexIndexEdgesPerm] = true;

                permutationValidityDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::bitset<lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations> generatePermutationValidityTable() {
        std::array<std::bitset<lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations> ans {};
        std::ifstream f("permutationValidityTable.pru");

        if (f.good()) {
            std::cout << std::setw(48) << std::left << "Loading permutation validity table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;
            char buff[lutGenerators::noOfEdgesPermutations];

            for (uint16_t i = 0; i < lutGenerators::noOfCornersPermutations; ++i) {

                f.read(buff, lutGenerators::noOfEdgesPermutations);
                ans[i] = std::bitset<lutGenerators::noOfEdgesPermutations>(std::string(buff));
            }

            std::cout << "DONE ";
        } else {
            f.close();
            {
                std::cout << std::setw(48) << std::left << "Generating permutation validity table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                for (auto &row: ans) {
                    row.reset();
                }

                ruCube cube;
                ruCubeStateConverter converter;
                ans[0][0] = true;
                permutationValidityDfs(cube, converter, 1, maxPermutationValidityDepth, -6, ans);

                std::cout << "DONE ";
            }
            {
                std::cout << std::setw(48) << std::left << "Saving permutation validity table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream f("permutationValidityTable.pru");
                if (f.good()) {
                    for (uint16_t i = 0; i < lutGenerators::noOfCornersPermutations; ++i) {
                        f.write(ans[i].to_string().c_str(), lutGenerators::noOfEdgesPermutations);
                    }
                }
                f.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }
}

