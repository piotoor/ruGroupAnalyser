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
        uint16_t intEdgesToEdgesLexIndex(const uint32_t edges) const;
        uint16_t intCornersToCornersPermLexIndex(const uint64_t corners) const;
        uint16_t intCornersToCornersOrientLexIndex(const uint64_t corners) const;

    protected:
//        static std::array<uint8_t, maxNumOfPieces> onesCountLookup;
//        static std::array<uint8_t, maxNumOfPieces> factorialLookup;

        static inline const uint8_t maxNumOfPieces = 7;
        static inline const uint8_t numOfEdges = 7;
    private:
};

#endif // RUCUBESTATECONVERTER_H
