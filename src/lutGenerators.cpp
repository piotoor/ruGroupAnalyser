#include "ruCube.h"
#include "ruCubeStateConverter.h"
#include "ruCubeFactory.h"
#include "lutGenerators.h"
#include <array>


namespace lutGenerators {
    constexpr uint8_t noOfTurns = 6;
    constexpr uint16_t noOfEdgesPermutations = 5040;

    auto generateEdgesPermMoveMap () {
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
}
