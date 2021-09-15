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
        void init( const std::vector<int8_t> &lockedEdges = {}, const std::vector<int8_t> &ignoredEdges = {},
                                const std::vector<int8_t> &lockedCornersPerm = {}, const std::vector<int8_t> &ignoredCornersPerm = {},
                                const std::vector<int8_t> &lockedCornersOrient = {}, const std::vector<int8_t> &ignoredCornersOrient = {});

        ruLutCube next();
        bool hasNext();

    private:
        void generateNextCube();


        permutationGenerator permGen;
        orientationGenerator orientGen;
        ruCubeStateConverter converter;
        ruCubeStateValidator validator;
        ruCubeIgnoredPiecesGapFiller filler;

        std::vector<std::vector<int8_t>> cornersOrientations;
        std::vector<std::vector<int8_t>> cornersPermutations;
        std::vector<std::vector<int8_t>> edgesPermutations;
        uint16_t lexIndexCornersPerm ;
        uint16_t lexIndexEdgesPerm;
        uint16_t lexIndexCornersOrient;

        bool hasNextCube;

        uint16_t cpIndex;
        uint16_t coIndex;
        uint16_t epIndex;

};

#endif // RULUTCUBEGENERATOR_H
