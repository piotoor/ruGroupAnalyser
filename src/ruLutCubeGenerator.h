#ifndef RULUTCUBEGENERATOR_H
#define RULUTCUBEGENERATOR_H
#include "ruCubeStateConverter.h"
#include "orientationGenerator.h"
#include "permutationGenerator.h"
#include "ruCube.h"
#include "ruCubeIgnoredPiecesGapFiller.h"
#include "ruCubeSolver.h"

#include <bitset>

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

struct generatorParameters {
    std::set<int8_t> lockedEdges = {};
    std::set<int8_t> ignoredEdges = {};
    std::set<int8_t> lockedCornersPerm = {};
    std::set<int8_t> ignoredCornersPerm = {};
    cornersArray lockedCornersOrient = { -1, -1, -1, -1, -1, -1 };
    cornersArray ignoredCornersOrient = { 0, 0, 0, 0, 0, 0 };

    bool operator == (const generatorParameters &other) const {
        return  lockedEdges == other.lockedEdges and
                ignoredEdges == other.ignoredEdges and
                lockedCornersPerm == other.lockedCornersPerm and
                ignoredCornersPerm == other.ignoredCornersPerm and
                lockedCornersOrient == other.lockedCornersOrient and
                ignoredCornersOrient == other.ignoredCornersOrient;
    }

    solvedMasks toSolvedMasks () const;
};

class ruLutCubeGenerator
{
    public:
        ruLutCubeGenerator() = default;
        virtual ~ruLutCubeGenerator() = default;
        void init(const generatorParameters &params = generatorParameters());

        ruLutCube next();
        bool hasNext();

    private:
        void generateNextCube();
        void saveCompressedGeneratorIgnoredParams(const generatorParameters &params);

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

        std::bitset<ruCube::noOfEdges> ignoredEdgesBits;
        std::bitset<ruCube::noOfCorners> ignoredCornersPermBits;
        std::bitset<ruCube::noOfCorners> ignoredCornersOrientBits;
};

#endif // RULUTCUBEGENERATOR_H
