#ifndef RULUTCUBEGENERATOR_H
#define RULUTCUBEGENERATOR_H
#include "ruCubeStateConverter.h"
#include "orientationGenerator.h"
#include "permutationGenerator.h"
#include "ruCube.h"
#include "ruCubeIgnoredPiecesGapFiller.h"

class ruLutCubeGenerator
{
    public:
        ruLutCubeGenerator();
        virtual ~ruLutCubeGenerator();
        std::vector<ruLutCube> generateCubes(const std::vector<int8_t> &lockedEdges = {}, const std::vector<int8_t> &ignoredEdges = {},
                                             const std::vector<int8_t> &lockedCornersPerm = {}, const std::vector<int8_t> &ignoredCornersPerm = {},
                                             const std::vector<int8_t> &lockedCornersOrient = {}, const std::vector<int8_t> &ignoredCornersOrient = {});

    private:
        permutationGenerator permGen;
        orientationGenerator orientGen;
        ruCubeStateConverter converter;
        ruCubeStateValidator validator;
        ruCubeIgnoredPiecesGapFiller filler;

};

#endif // RULUTCUBEGENERATOR_H
