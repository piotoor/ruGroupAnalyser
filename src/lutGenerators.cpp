#include "ruCube.h"
#include "ruCubeStateConverter.h"
#include "ruCubeFactory.h"
#include "lutGenerators.h"
#include <array>


namespace lutGenerators {
    std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> generateEdgesPermMoveMap () {
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

        return ans;
    }

    std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> generateCornersPermMoveMap () {
        std::array<std::array<uint16_t, noOfTurns>, noOfCornersPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cornersPerm = 0; cornersPerm < noOfCornersPermutations; ++cornersPerm) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(cornersPerm, ruCube::solvedLexIndexCornersOrient));

            for (uint8_t t = R; t <= Ui; ++t) {
                cube->turn(t);
                ans[cornersPerm][t] = converter.intCornersToLexIndexCornersPerm(cube->getCorners());
                cube->inverseTurn(t);
            }
        }

        return ans;
    }

    std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> generateCornersOrientMoveMap () {
        std::array<std::array<uint16_t, noOfTurns>, noOfCornersOrientations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cornersOrient = 0; cornersOrient < noOfCornersOrientations; ++cornersOrient) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(ruCube::solvedLexIndexCornersPerm, cornersOrient));

            for (uint8_t t = R; t <= Ui; ++t) {
                cube->turn(t);
                ans[cornersOrient][t] = converter.intCornersToLexIndexCornersOrient(cube->getCorners());
                cube->inverseTurn(t);
            }
        }

        return ans;
    }

    std::array<std::bitset<noOfEdgesPermSolvedStates>, noOfEdgesPermutations> generateEdgesPermSolvedTable () {
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

        return ans;
    }

    std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> generateCornersPermSolvedTable () {
        std::array<std::bitset<noOfCornersPermSolvedStates>, noOfCornersPermutations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t cp = 0; cp < noOfCornersPermutations; ++cp) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(cp, ruCube::solvedLexIndexCornersOrient));
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

            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::llCornersInRSolved)] =         ans[cp][static_cast<uint8_t>(cornersPermSolvedState::allCorners)] and
                                                                                            not ans[cp][static_cast<uint8_t>(cornersPermSolvedState::f2lCornersInUSolved)];
            ans[cp][static_cast<uint8_t>(cornersPermSolvedState::llCornersInUSolved)] =         ans[cp][static_cast<uint8_t>(cornersPermSolvedState::allCorners)] and
                                                                                            not ans[cp][static_cast<uint8_t>(cornersPermSolvedState::f2lCornersInRSolved)];
        }

        return ans;
    }

    std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> generateCornersOrientSolvedTable () {
        std::array<std::bitset<noOfCornersOrientSolvedStates>, noOfCornersOrientations> ans {};
        auto cube = ruCubeFactory::createCube(ruCubeFactory::ruCubeType::ruCube);
        ruCubeStateConverter converter;

        for (uint16_t co = 0; co < noOfCornersOrientations; ++co) {
            cube->setCorners(converter.lexIndexCornersToIntCorners(ruCube::solvedLexIndexCornersPerm, co));

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

            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::llCornersInROriented)] =         ans[co][static_cast<uint8_t>(cornersOrientSolvedState::allCorners)] and
                                                                                                not ans[co][static_cast<uint8_t>(cornersOrientSolvedState::f2lCornersInUOriented)];
            ans[co][static_cast<uint8_t>(cornersOrientSolvedState::llCornersInUOriented)] =         ans[co][static_cast<uint8_t>(cornersOrientSolvedState::allCorners)] and
                                                                                                not ans[co][static_cast<uint8_t>(cornersOrientSolvedState::f2lCornersInROriented)];
        }

        return ans;
    }
}

