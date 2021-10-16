#ifndef RULUTCUBEGENERATOR_H
#define RULUTCUBEGENERATOR_H
#include "ruCubeStateConverter.h"
#include "orientationGenerator.h"
#include "permutationGenerator.h"
#include "ruCube.h"
#include "ruCubeIgnoredPiecesGapFiller.h"

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

struct generatorParameters {
    std::vector<int8_t> lockedEdges = {};
    std::vector<int8_t> ignoredEdges = {};
    std::vector<int8_t> lockedCornersPerm = {};
    std::vector<int8_t> ignoredCornersPerm = {};
    cornersArray lockedCornersOrient = { -1, -1, -1, -1, -1, -1 };
    cornersArray ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };
};

class ruLutCubeGenerator
{
    public:
        ruLutCubeGenerator();
        virtual ~ruLutCubeGenerator();
        void init(const generatorParameters &params = generatorParameters());

        ruLutCube next();
        bool hasNext();

    private:
        void generateNextCube();


        permutationGenerator<edgesArray> edgesPermGen;
        permutationGenerator<cornersArray> cornersPermGen;
        orientationGenerator orientGen;
        ruCubeStateConverter converter;
        ruCubeStateValidator validator;
        ruCubeIgnoredPiecesGapFiller filler;

        std::vector<cornersArray> cornersOrientations;
        std::vector<cornersArray> cornersPermutations;
        std::vector<edgesArray> edgesPermutations;
        uint16_t lexIndexCornersPerm ;
        uint16_t lexIndexEdgesPerm;
        uint16_t lexIndexCornersOrient;

        bool hasNextCube;

        uint16_t cpIndex;
        uint16_t coIndex;
        uint16_t epIndex;

};

#endif // RULUTCUBEGENERATOR_H
