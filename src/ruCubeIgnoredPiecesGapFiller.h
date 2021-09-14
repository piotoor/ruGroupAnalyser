#ifndef RUCUBEIGNOREDPIECESGAPFILLER_H
#define RUCUBEIGNOREDPIECESGAPFILLER_H

#include "ruCube.h"
#include "ruCubeStateValidator.h"

#include <vector>

class ruCubeIgnoredPiecesGapFiller
{
    public:
        ruCubeIgnoredPiecesGapFiller();
        virtual ~ruCubeIgnoredPiecesGapFiller();
        bool cornersOrientationIgnoredGapsFill(std::vector<int8_t> &cornersOrient);
        bool permutationIgnoredGapsFillNext(std::vector<int8_t>& cornersPerm, std::vector<int8_t>& edgesPerm);
        void permutationIgnoredGapsFillInit(std::vector<int8_t> cornersPerm, std::vector<int8_t> edgesPerm);

    private:
        void permutationIgnoredGapsFillCleanup();


        std::vector<uint8_t> missingEdges;
        std::vector<uint8_t> missingCorners;
        std::vector<uint8_t> cornersPermIgnoredIndices;
        std::vector<uint8_t> edgesPermIgnoredIndices;
        bool hasNextEdgesPerm = true;
        bool hasNextCornersPerm = true;
};

#endif // RUCUBEIGNOREDPIECESGAPFILLER_H