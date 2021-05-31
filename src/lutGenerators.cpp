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
}
