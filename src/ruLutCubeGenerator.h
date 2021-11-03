#ifndef RULUTCUBEGENERATOR_H
#define RULUTCUBEGENERATOR_H
#include "ruCubeStateConverter.h"
#include "orientationGenerator.h"
#include "permutationGenerator.h"
#include "ruCube.h"
#include "ruCubeIgnoredPiecesGapFiller.h"
#include "ruCubeSolver.h"

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

    solvedMasks toSolvedMasks () const {
        solvedMasks ans { 0, 0 };

        std::bitset<32> edgesBits;
        for (int8_t i = 0; i < ruCube::noOfEdges; ++i) {
            if (ignoredEdges.find(i) == ignoredEdges.end()) {
                edgesBits.set(ruCube::noOfEdges - 1 - i);
            }
        }
        ans.edgesMask = static_cast<uint32_t>(edgesBits.to_ulong());

        std::bitset<32> cornersPermBits;
        std::bitset<32> cornersOrientBits;
        for (int8_t i = 0; i < ruCube::noOfCorners; ++i) {
            if (ignoredCornersPerm.find(i) == ignoredCornersPerm.end()) {
                cornersPermBits.set(ruCube::noOfCorners - 1 - i);
            }
            if (ignoredCornersOrient[i] == 0) {
                cornersOrientBits.set(ruCube::noOfCorners - 1 - i);
            }
        }

        ans.cornersMask =   (static_cast<uint64_t>(cornersOrientBits.to_ulong()) << (sizeof(uint32_t) * 8)) |
                            static_cast<uint64_t>(cornersPermBits.to_ulong());
        return ans;
    }


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
