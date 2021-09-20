#ifndef RUCUBEIGNOREDPIECESGAPFILLER_H
#define RUCUBEIGNOREDPIECESGAPFILLER_H

#include "ruCube.h"
#include "ruCubeStateValidator.h"

#include <vector>

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

class ruCubeIgnoredPiecesGapFiller
{
    public:
        ruCubeIgnoredPiecesGapFiller();
        virtual ~ruCubeIgnoredPiecesGapFiller();
        bool cornersOrientationIgnoredGapsFill(cornersArray &cornersOrient);
        bool permutationIgnoredGapsFillNext(cornersArray& cornersPerm, edgesArray& edgesPerm);
        void permutationIgnoredGapsFillInit(const cornersArray& cornersPerm, const edgesArray& edgesPerm);

    private:
        void permutationIgnoredGapsFillCleanup();


        std::vector<uint8_t> missingEdges;
        std::vector<uint8_t> missingCorners;
        std::vector<uint8_t> cornersPermIgnoredIndices;
        std::vector<uint8_t> edgesPermIgnoredIndices;
        bool hasNextEdgesPerm = true;
        bool hasNextCornersPerm = true;

        std::bitset<ruBaseCube::noOfCorners> missingCornersBits;
        std::bitset<ruBaseCube::noOfEdges> missingEdgesBits;
};

#endif // RUCUBEIGNOREDPIECESGAPFILLER_H
