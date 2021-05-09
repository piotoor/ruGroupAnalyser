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
        uint64_t vectCornersToInt(const std::vector<int8_t> &perm, const std::vector<int8_t> &orient) const;
        uint32_t vectEdgesToInt(const std::vector<int8_t> &perm) const;
        uint16_t intEdgesToEdgesLexIndex(const uint32_t edges);
        uint16_t intCornersToCornersPermLexIndex(const uint64_t corners);
        uint16_t intCornersToCornersOrientLexIndex(const uint64_t corners);

    private:
    uint16_t intPermToPermLexIndex(const uint64_t perm, uint8_t pieceSize, uint8_t shiftBase, uint8_t numOfPieces);

        static inline constexpr uint8_t maxNumOfPieces = 7;
        static inline const uint8_t numOfEdges = 7;
        static inline const uint8_t numOfCorners = 6;

        static inline const uint8_t pieceSizeEdges = 3;
        static inline const uint8_t shiftBaseEdges = 18;
        static inline const uint8_t pieceSizeCorners = 6;
        static inline const uint8_t shiftBaseCorners = 30;

        std::bitset<maxNumOfPieces> visited;
        std::array<uint8_t, maxNumOfPieces> lehmer;

        static constexpr std::array<uint16_t, maxNumOfPieces> factLookup = {
            0, 1, 2, 6, 24, 120, 720
        };

};

#endif // RUCUBESTATECONVERTER_H
