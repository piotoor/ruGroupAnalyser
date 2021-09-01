#include "ruCubeFactory.h"
#include "lutGenerators.h"


namespace lutGenerators {
    std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> generateEdgesPermMoveMap () {
        std::cout << std::setw(48) << std::left << "Generating edges permutation move map..." << std::flush;

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

        std::cout << "DONE" << std::endl;
        return ans;
    }
    std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> generateCornersPermMoveMap () {
        std::cout << std::setw(48) << std::left << "Generating corners permutation move map..." << std::flush;

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

        std::cout << "DONE" << std::endl;
        return ans;
    }

    std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> generateCornersOrientMoveMap () {
        std::cout << std::setw(48) << std::left << "Generating corners orientation move map..." << std::flush;

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

        std::cout << "DONE" << std::endl;
        return ans;
    }

    std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> generateEdgesPermSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating edges permutation solved table..." << std::flush;

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

        std::cout << "DONE" << std::endl;
        return ans;
    }

    std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> generateCornersPermSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating corners permutation solved table..." << std::flush;

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

        std::cout << "DONE" << std::endl;
        return ans;
    }

    std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> generateCornersOrientSolvedTable () {
        std::cout << std::setw(48) << std::left << "Generating corners orientation solved table..." << std::flush;

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

        std::cout << "DONE" << std::endl;
        return ans;
    }


    void edgesPermPruningDfs(ruCube &cube, ruCubeStateConverter &conv, uint8_t depth, uint8_t maxDepth, int8_t prevMove, std::array<int8_t, noOfEdgesPermutations> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                auto lexIndexEdges = conv.intEdgesToLexIndexEdges(cube.getEdges());
                if (depth < pruningTable[lexIndexEdges] or pruningTable[lexIndexEdges] == -1) {
                    pruningTable[lexIndexEdges] = depth;
                }

                cube.turn(i);
                edgesPermPruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<int8_t, noOfEdgesPermutations> generateEdgesPermPruningTable() {
        std::cout << std::setw(48) << std::left << "Generating edges permutation pruning table..." << std::flush;

        std::array<int8_t, noOfEdgesPermutations> ans {};
        ans.fill(-1);
        ruCube cube;
        ruCubeStateConverter converter;

        edgesPermPruningDfs(cube, converter, 0, maxEdgesPermPruningDepth, -6, ans);

        std::cout << "DONE" << std::endl;
        return ans;
    }


    void cornersPruningDfs(ruCube &cube, ruCubeStateConverter &conv, uint8_t depth, uint8_t maxDepth, int8_t prevMove, std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                auto lexIndexCornersPerm = conv.intCornersToLexIndexCornersPerm(cube.getCorners());
                auto lexIndexCornersOrient = conv.intCornersToLexIndexCornersOrient(cube.getCorners());
                if (depth < pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] or pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] == -1) {
                    pruningTable[lexIndexCornersPerm][lexIndexCornersOrient] = depth;
                }

                cube.turn(i);
                cornersPruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> generateCornersPruningTable() {
        std::cout << std::setw(48) << std::left << "Generating corners pruning table..." << std::flush;

        std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, noOfCornersPermutations> ans {};
        for (auto &row: ans) {
            row.fill(-1);
        }
        ruCube cube;
        ruCubeStateConverter converter;

        cornersPruningDfs(cube, converter, 0, maxCornersPruningDepth, -6, ans);

        std::cout << "DONE" << std::endl;
        return ans;
    }


    void fullCubePruningDfs(ruCube &cube, ruCubeStateConverter &conv, uint8_t depth, uint8_t maxDepth, int8_t prevMove, std::vector<std::vector<std::vector<int8_t>>> &pruningTable) {
        if (depth <= maxDepth) {
            for (int8_t i = 0; i < 6; ++i) {
                if (i / 3 == prevMove / 3) {
                    continue;
                }

                auto lexIndexCornersPerm = conv.intCornersToLexIndexCornersPerm(cube.getCorners());
                auto lexIndexCornersOrient = conv.intCornersToLexIndexCornersOrient(cube.getCorners());
                auto lexIndexEdgesPerm = conv.intEdgesToLexIndexEdges(cube.getEdges());
                if (depth < pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] or pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] == -1) {
                    pruningTable[lexIndexCornersPerm][lexIndexCornersOrient][lexIndexEdgesPerm] = depth;
                }

                cube.turn(i);
                fullCubePruningDfs(cube, conv, depth + 1, maxDepth, i, pruningTable);
                cube.inverseTurn(i);
            }
        }
    }

    std::vector<std::vector<std::vector<int8_t>>> generateFullCubePruningTable() {
        std::cout << std::setw(48) << std::left << "Generating full cube pruning table..." << std::flush;

        std::vector<std::vector<std::vector<int8_t>>> ans (noOfCornersPermutations, std::vector(noOfCornersOrientations, std::vector<int8_t>(noOfEdgesPermutations, -1)));

        ruCube cube;
        ruCubeStateConverter converter;

        fullCubePruningDfs(cube, converter, 0, maxFullCubePruningDepth, -6, ans);

        std::cout << "DONE" << std::endl;
        return ans;
    }
}

