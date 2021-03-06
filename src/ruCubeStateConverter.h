#ifndef RUCUBESTATECONVERTER_H
#define RUCUBESTATECONVERTER_H

#include <cstdint>
#include <vector>
#include <array>
#include <bitset>

class ruCubeStateConverter
{
    public:
        ruCubeStateConverter();
        explicit ruCubeStateConverter(const ruCubeStateConverter &other) = delete;
        ruCubeStateConverter& operator=(const ruCubeStateConverter &other) = delete;
        virtual ~ruCubeStateConverter();
        uint64_t vectCornersToIntCorners(const std::vector<int8_t> &perm, const std::vector<int8_t> &orient) const;
        uint32_t vectEdgesToIntEdges(const std::vector<int8_t> &perm) const;
        uint16_t intEdgesToLexIndexEdges(const uint32_t edges);
        uint16_t intCornersToLexIndexCornersPerm(const uint64_t corners);
        uint16_t intCornersToLexIndexCornersOrient(const uint64_t corners);

        uint32_t lexIndexEdgesToIntEdges(uint16_t lexIndexEdges);
        uint64_t lexIndexCornersToIntCorners(uint16_t lexIndexPerm, uint16_t lexIndexOrient);

        uint16_t vectEdgesPermToLexIndexEdgesPerm(const std::vector<int8_t> &perm);
        uint16_t vectCornersPermToLexIndexCornersPerm(const std::vector<int8_t> &perm);
        uint16_t vectCornersOrientToLexIndexCornersOrient(const std::vector<int8_t> &orient);

    private:
        uint16_t intPermToLexIndexPerm(const uint64_t perm, uint8_t pieceSize, uint8_t shiftBase, uint8_t numOfPieces);
        uint16_t vectPermToLexIndexPerm(const std::vector<int8_t> &perm);
        void lexIndexPermToArrayPermIntermediate(uint16_t lexPerm, uint8_t numOfPieces);
        uint64_t lexIndexCornersOrientToIntCornersOrient(uint16_t lexIndexOrient);

        static inline constexpr uint8_t maxNumOfPieces = 7;
        static inline const uint8_t numOfEdges = 7;
        static inline const uint8_t numOfCorners = 6;

        static inline const uint8_t pieceSizeEdges = 3;
        static inline const uint8_t shiftBaseEdges = 18;
        static inline const uint8_t pieceSizeCorners = 6;
        static inline const uint8_t shiftBaseCorners = 30;
        static inline const uint8_t shiftBaseCornersOrient = 33;

        std::bitset<maxNumOfPieces> visited;
        std::array<uint8_t, maxNumOfPieces> lehmer;
        std::array<uint8_t, maxNumOfPieces> perm;

        static constexpr std::array<uint16_t, maxNumOfPieces> factLookup = {
            1, 1, 2, 6, 24, 120, 720
        };

};

#endif // RUCUBESTATECONVERTER_H
