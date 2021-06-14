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
        }

        return ans;
    }
}

