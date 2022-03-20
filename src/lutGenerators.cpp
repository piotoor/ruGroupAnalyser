#include "lutGenerators.h"
#include "ruCubeFactory.h"
#include "ruCubeSimpleBenchmarkTimer.h"
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

namespace lutGenerators {
    std::array<std::bitset<ruBaseCube::noOfEdgesPermSolvedStates>, ruBaseCube::noOfEdgesPermutations> generateEdgesPermSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating edges permutation solved table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::bitset<ruBaseCube::noOfEdgesPermSolvedStates>, ruBaseCube::noOfEdgesPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t ep = 0; ep < ruBaseCube::noOfEdgesPermutations; ++ep) {
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

    std::array<std::bitset<ruBaseCube::noOfCornersPermSolvedStates>, ruBaseCube::noOfCornersPermutations> generateCornersPermSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating corners permutation solved table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::bitset<ruBaseCube::noOfCornersPermSolvedStates>, ruBaseCube::noOfCornersPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cp = 0; cp < ruBaseCube::noOfCornersPermutations; ++cp) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(ruLutCube::solvedLexIndexCornersOrient, cp));
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::allCorners)] = cube->isSolvedCorners(ruCube::allCornersPermMask);

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

    std::array<std::bitset<ruBaseCube::noOfCornersOrientSolvedStates>, ruBaseCube::noOfCornersOrientations> generateCornersOrientSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating corners orientation solved table..." << std::flush;
        ruCubeSimpleBenchmarkTimer bt;

        std::array<std::bitset<ruBaseCube::noOfCornersOrientSolvedStates>, ruBaseCube::noOfCornersOrientations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t co = 0; co < ruBaseCube::noOfCornersOrientations; ++co) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(co, ruLutCube::solvedLexIndexCornersPerm));

            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::allCorners)] = cube->isSolvedCorners(ruCube::allCornersOrientMask);

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
                                    int depth,
                                    int maxDepth,
                                    int prevMove,
                                    uint8_t partInd,
                                    std::unordered_map<uint32_t, uint8_t> &pruningTable,
                                    std::unordered_map<uint32_t, std::unordered_set<uint32_t>> &partialPermOwners) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                uint32_t partialPerm = cube.getPartialEdges(partInd);

                partialPermOwners[partialPerm].insert(conv.intEdgesToLexIndexEdges(cube.getEdges()));
                if (pruningTable.find(partialPerm) == pruningTable.end()) {
                    pruningTable[partialPerm] = static_cast<uint8_t>(depth);

                } else {
                    if (depth < pruningTable[partialPerm]) {
                        pruningTable[partialPerm] = static_cast<uint8_t>(depth);
                    }
                }

                edgesPartialPermPruningDfs(cube, conv, depth + 1, maxDepth, i, partInd, pruningTable, partialPermOwners);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::array<int8_t, ruBaseCube::noOfPartialEdgesPermCases>, ruBaseCube::noOfEdgesPermutations> generateEdgesPermPruningTable() {
        std::ifstream inFile("edgesPruningTable.pru");
        std::array<std::array<int8_t, ruBaseCube::noOfPartialEdgesPermCases>, ruBaseCube::noOfEdgesPermutations>  ans {};
        if (inFile.good()) {
            std::cout << std::setw(48) << std::left << "Loading edges pruning table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;

            for (uint16_t i = 0; i < ruBaseCube::noOfEdgesPermutations; ++i) {
                inFile.read((char*)ans[i].data(), ruBaseCube::noOfPartialEdgesPermCases);
            }

            std::cout << "DONE ";
        } else {
            inFile.close();
            {
                std::cout << std::setw(48) << std::left << "Generating edges pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;

                for (auto &r: ans) {
                    r.fill(-1);
                }
                ruCube cube;
                ruCubeStateConverter converter;
                ans[0].fill(0);

                std::unordered_map<uint32_t, uint8_t> edgesPartialPermPruningTable;
                std::unordered_map<uint32_t, std::unordered_set<uint32_t>> partialPermOwners;

                for (uint8_t partInd = 0; partInd < ruBaseCube::noOfPartialEdgesPermCases; ++partInd) {
                    partialPermOwners.clear();
                    edgesPartialPermPruningDfs(cube, converter, 1, maxEdgesPermPruningDepth, -6, partInd, edgesPartialPermPruningTable, partialPermOwners);
                    for (const auto &[partial, perms]: partialPermOwners) {
                        for (const auto &perm: perms) {
                            ans[perm][partInd] = edgesPartialPermPruningTable[partial];
                        }
                    }
                }

                std::cout << "DONE ";
            }
            {
                std::cout << std::setw(48) << std::left << "Saving edges pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream outFile("edgesPruningTable.pru");

                if (outFile.good()) {
                    for (uint16_t i = 0; i < ruBaseCube::noOfEdgesPermutations; ++i) {
                        outFile.write((char*)ans[i].data(), ruBaseCube::noOfPartialEdgesPermCases);
                    }
                }

                outFile.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }


    void cornersPruningDfs(ruCube &cube, ruCubeStateConverter &conv, int depth, int maxDepth, int prevMove, std::array<std::array<int8_t, ruBaseCube::noOfCornersOrientations>, ruBaseCube::noOfCornersPermutations> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                auto lexIndexCornersPerm = conv.intCornersToLexIndexCornersPerm(cube.getCorners());
                auto lexIndexCornersOrient = conv.intCornersToLexIndexCornersOrient(cube.getCorners());
                if (depth < pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] or pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] == -1) {
                    pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] = static_cast<uint8_t>(depth);
                }

                cornersPruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::array<int8_t, ruBaseCube::noOfCornersOrientations>, ruBaseCube::noOfCornersPermutations> generateCornersPruningTable() {
        std::ifstream inFile("cornersPruningTable.pru");
        std::array<std::array<int8_t, ruBaseCube::noOfCornersOrientations>, ruBaseCube::noOfCornersPermutations> ans {};
        if (inFile.good()) {
            std::cout << std::setw(48) << std::left << "Loading corners pruning table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;

            if (inFile.good()) {
                for (uint16_t i = 0; i < ruBaseCube::noOfCornersPermutations; ++i) {
                    inFile.read((char*)ans[i].data(), ruBaseCube::noOfCornersOrientations);
                }
            }
            std::cout << "DONE ";
        } else {
            inFile.close();
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
                std::ofstream outFile("cornersPruningTable.pru");
                if (outFile.good()) {
                    for (uint16_t i = 0; i < ruBaseCube::noOfCornersPermutations; ++i) {
                        outFile.write((char*)ans[i].data(), ruBaseCube::noOfCornersOrientations);
                    }
                }
                outFile.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }


    void fullCubePruningDfs(ruCube &cube, ruCubeStateConverter &conv, int depth, int maxDepth, int prevMove, std::vector<std::vector<std::vector<int8_t>>> &pruningTable) {
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
                    pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] = static_cast<uint8_t>(depth);
                }

                fullCubePruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::vector<std::vector<std::vector<int8_t>>> generateFullCubePruningTable() {
        std::vector<std::vector<std::vector<int8_t>>> ans (ruBaseCube::noOfCornersPermutations, std::vector(ruBaseCube::noOfCornersOrientations, std::vector<int8_t>(ruBaseCube::noOfEdgesPermutations, -1)));
        std::ifstream inFile;

        #ifndef DEBUG
            inFile.open("fullCubePruningTable.pru");
        #endif

        if (inFile.good()) {
            std::cout << std::setw(48) << std::left << std::string("Loading full cube pruning table (") + std::to_string((int)maxFullCubePruningDepth) + ")..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;
            for (uint16_t cp = 0; cp < ruBaseCube::noOfCornersPermutations; ++cp) {
                for (uint16_t co = 0; co < ruBaseCube::noOfCornersOrientations; ++co ) {
                    inFile.read((char*)(ans[cp][co].data()), ruBaseCube::noOfEdgesPermutations);
                }
            }
            inFile.close();
            std::cout << "DONE ";
        } else {
            inFile.close();
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
                std::ofstream outFile("fullCubePruningTable.pru");
                if (outFile.good()) {
                    for (uint16_t cp = 0; cp < ruBaseCube::noOfCornersPermutations; ++cp) {
                        for (uint16_t co = 0; co < ruBaseCube::noOfCornersOrientations; ++co) {
                            outFile.write(reinterpret_cast<char*>(ans[cp][co].data()), ruBaseCube::noOfEdgesPermutations);
                        }
                    }
                }
                outFile.close();
                std::cout << "DONE ";
            }
            #endif
        }
        return ans;
    }


    void permutationValidityDfs(ruCube &cube, ruCubeStateConverter &conv, int depth, int maxDepth, int prevMove, std::array<std::bitset<ruBaseCube::noOfEdgesPermutations>, ruBaseCube::noOfCornersPermutations> &pruningTable) {
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

    std::array<std::bitset<ruBaseCube::noOfEdgesPermutations>, ruBaseCube::noOfCornersPermutations> generatePermutationValidityTable() {
        std::array<std::bitset<ruBaseCube::noOfEdgesPermutations>, ruBaseCube::noOfCornersPermutations> ans {};
        std::ifstream inFile("permutationValidityTable.pru");

        if (inFile.good()) {
            std::cout << std::setw(48) << std::left << "Loading permutation validity table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;
            char buff[ruBaseCube::noOfEdgesPermutations];

            for (uint16_t i = 0; i < ruBaseCube::noOfCornersPermutations; ++i) {

                inFile.read(buff, ruBaseCube::noOfEdgesPermutations);
                ans[i] = std::bitset<ruBaseCube::noOfEdgesPermutations>(std::string(buff));
            }

            std::cout << "DONE ";
        } else {
            inFile.close();
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
                std::ofstream outFile("permutationValidityTable.pru");
                if (outFile.good()) {
                    for (uint16_t i = 0; i < ruBaseCube::noOfCornersPermutations; ++i) {
                        outFile.write(ans[i].to_string().c_str(), ruBaseCube::noOfEdgesPermutations);
                    }
                }
                outFile.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }

    void cornersPartialPermPruningDfs(  ruCube &cube,
                                        ruCubeStateConverter &conv,
                                        int depth,
                                        int maxDepth,
                                        int prevMove,
                                        uint8_t partInd,
                                        std::unordered_map<uint32_t, uint8_t> &pruningTable,
                                        std::unordered_map<uint32_t, std::unordered_set<uint32_t>> &partialPermOwners) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                uint32_t partialPerm = cube.getPartialCornersPerm(partInd);

                partialPermOwners[partialPerm].insert(conv.intCornersToLexIndexCornersPerm(cube.getCorners()));
                if (pruningTable.find(partialPerm) == pruningTable.end()) {
                    pruningTable[partialPerm] = static_cast<uint8_t>(depth);

                } else {
                    if (depth < pruningTable[partialPerm]) {
                        pruningTable[partialPerm] = static_cast<uint8_t>(depth);
                    }
                }

                cornersPartialPermPruningDfs(cube, conv, depth + 1, maxDepth, i, partInd, pruningTable, partialPermOwners);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::array<int8_t, ruBaseCube::noOfPartialCornersPermCases>, ruBaseCube::noOfCornersPermutations> generateCornersPermPruningTable() {
        std::ifstream inFile("cornersPermPruningTable.pru");
        std::array<std::array<int8_t, ruBaseCube::ruBaseCube::noOfPartialCornersPermCases>, ruBaseCube::noOfCornersPermutations>  ans {};
        if (inFile.good()) {
            std::cout << std::setw(48) << std::left << "Loading corners perm pruning table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;

            for (uint16_t i = 0; i < ruBaseCube::noOfCornersPermutations; ++i) {
                inFile.read((char*)ans[i].data(), ruBaseCube::ruBaseCube::noOfPartialCornersPermCases);
            }

            std::cout << "DONE ";
        } else {
            inFile.close();
            {
                std::cout << std::setw(48) << std::left << "Generating corners perm pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;

                for (auto &r: ans) {
                    r.fill(-1);
                }
                ruCube cube;
                ruCubeStateConverter converter;


                std::unordered_map<uint32_t, uint8_t> cornersPermPartialPermPruningTable;
                std::unordered_map<uint32_t, std::unordered_set<uint32_t>> partialPermOwners;

                for (uint8_t partInd = 0; partInd < ruBaseCube::ruBaseCube::noOfPartialCornersPermCases; ++partInd) {
                    partialPermOwners.clear();
                    cornersPartialPermPruningDfs(cube, converter, 1, maxCornersPermPruningDepth, -6, partInd, cornersPermPartialPermPruningTable, partialPermOwners);
                    for (const auto &[partial, perms]: partialPermOwners) {
                        for (const auto &perm: perms) {
                            if (ans[perm][partInd] == -1 or cornersPermPartialPermPruningTable[partial] < ans[perm][partInd]) {
                                ans[perm][partInd] = cornersPermPartialPermPruningTable[partial];
                            }

                        }
                    }
                }
                ans[0].fill(0);
                std::cout << "DONE ";
            }
            {
                std::cout << std::setw(48) << std::left << "Saving corners perm pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream outFile("cornersPermPruningTable.pru");

                if (outFile.good()) {
                    for (uint16_t i = 0; i < ruBaseCube::noOfCornersPermutations; ++i) {
                        outFile.write((char*)ans[i].data(), ruBaseCube::ruBaseCube::noOfPartialCornersPermCases);
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
                                        std::unordered_map<uint32_t, std::unordered_set<uint32_t>> &partialOrientOwners) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                cube.turn(i);
                uint32_t partialOrient = cube.getPartialCornersOrient(partInd);

                partialOrientOwners[partialOrient].insert(conv.intCornersToLexIndexCornersOrient(cube.getCorners()));
                if (pruningTable.find(partialOrient) == pruningTable.end()) {
                    pruningTable[partialOrient] = static_cast<uint8_t>(depth);

                } else {
                    if (depth < pruningTable[partialOrient]) {
                        pruningTable[partialOrient] = static_cast<uint8_t>(depth);
                    }
                }

                cornersPartialOrientPruningDfs(cube, conv, depth + 1, maxDepth, i, partInd, pruningTable, partialOrientOwners);
                cube.inverseTurn(i);
            }
        }
    }



    std::array<std::array<int8_t, ruBaseCube::noOfPartialCornersOrientCases>, ruBaseCube::noOfCornersOrientations> generateCornersOrientPruningTable() {
        std::ifstream inFile("cornersOrientPruningTable.pru");
        std::array<std::array<int8_t, ruBaseCube::ruBaseCube::noOfPartialCornersOrientCases>, ruBaseCube::noOfCornersOrientations>  ans {};

        if (inFile.good()) {
            std::cout << std::setw(48) << std::left << "Loading corners orient pruning table..." << std::flush;
            ruCubeSimpleBenchmarkTimer bt;

            for (uint16_t i = 0; i < ruBaseCube::noOfCornersOrientations; ++i) {
                inFile.read((char*)ans[i].data(), ruBaseCube::ruBaseCube::noOfPartialCornersOrientCases);
            }

            std::cout << "DONE ";
        } else {
            inFile.close();
            {
                std::cout << std::setw(48) << std::left << "Generating corners orient pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;

                for (auto &r: ans) {
                    r.fill(-1);
                }
                ruCube cube;
                ruCubeStateConverter converter;


                std::unordered_map<uint32_t, uint8_t> cornersOrientPartialOrientPruningTable;
                std::unordered_map<uint32_t, std::unordered_set<uint32_t>> partialOrientOwners;

                for (uint8_t partInd = 0; partInd < ruBaseCube::ruBaseCube::noOfPartialCornersOrientCases; ++partInd) {
                    partialOrientOwners.clear();
                    cornersPartialOrientPruningDfs(cube, converter, 1, maxCornersOrientPruningDepth, -6, partInd, cornersOrientPartialOrientPruningTable, partialOrientOwners);
                    for (const auto &[partial, orients]: partialOrientOwners) {
                        for (const auto &orient: orients) {
                            if (ans[orient][partInd] == -1 or cornersOrientPartialOrientPruningTable[partial] < ans[orient][partInd]) {
                                ans[orient][partInd] = cornersOrientPartialOrientPruningTable[partial];
                            }

                        }
                    }
                }
                ans[0].fill(0);
                std::cout << "DONE ";
            }
            {
                std::cout << std::setw(48) << std::left << "Saving corners orient pruning table..." << std::flush;
                ruCubeSimpleBenchmarkTimer bt;
                std::ofstream outFile("cornersOrientPruningTable.pru");

                if (outFile.good()) {
                    for (uint16_t i = 0; i < ruBaseCube::noOfCornersOrientations; ++i) {
                        outFile.write((char*)ans[i].data(), ruBaseCube::ruBaseCube::noOfPartialCornersOrientCases);
                    }
                }

                outFile.close();
                std::cout << "DONE ";
            }
        }

        return ans;
    }

}


