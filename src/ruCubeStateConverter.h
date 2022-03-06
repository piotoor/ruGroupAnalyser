#ifndef RUCUBESTATECONVERTER_H
#define RUCUBESTATECONVERTER_H

#include "ruCube.h"
#include <vector>
#include <array>
#include <bitset>


using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

class ruCubeStateConverter
{
    public:
        ruCubeStateConverter() = default;
        ruCubeStateConverter(const ruCubeStateConverter &other) = delete;
        ruCubeStateConverter& operator=(const ruCubeStateConverter &other) = delete;
        virtual ~ruCubeStateConverter() = default;
        uint64_t vectCornersToIntCorners(const cornersArray &orient, const cornersArray &perm) const;
        uint32_t vectEdgesToIntEdges(const edgesArray &perm) const;
        uint16_t intEdgesToLexIndexEdges(const uint32_t edges);
        uint16_t intCornersToLexIndexCornersPerm(const uint64_t corners);
        uint16_t intCornersToLexIndexCornersOrient(const uint64_t corners);

        uint32_t lexIndexEdgesToIntEdges(uint16_t lexIndexEdges);
        uint64_t lexIndexCornersToIntCorners(uint16_t lexIndexOrient, uint16_t lexIndexPerm);

        std::string lexIndexEdgesToIntEdgesAsStrWithIgnored(uint16_t lexIndexEdges, const std::bitset<7> &ignoredEdeges);
        std::string lexIndexCornersToIntCornersAsStrWithIgnored(uint16_t lexIndexOrient, uint16_t lexIndexPerm, const std::bitset<6> &ignoredCornersOrient, const std::bitset<6> &ignoredCornersPerm);

        uint16_t vectEdgesPermToLexIndexEdgesPerm(const edgesArray &perm);
        uint16_t vectCornersPermToLexIndexCornersPerm(const cornersArray &perm);
        uint16_t vectCornersOrientToLexIndexCornersOrient(const cornersArray &orient);

        template <typename T>
        std::string containerToString(const T &cont);

    private:
        uint16_t intPermToLexIndexPerm(const uint64_t perm, uint8_t pieceSize, uint8_t shiftBase, uint8_t numOfPieces);

        template <typename T>
        uint16_t vectPermToLexIndexPerm(const T &perm);
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
        std::array<uint8_t, maxNumOfPieces> perm;

    public:
        static constexpr std::array<uint16_t, maxNumOfPieces + 1> factLookup = {
            1, 1, 2, 6, 24, 120, 720, 5040
        };

        static constexpr std::array<uint16_t, maxNumOfPieces> powersOf3 = {
            1, 3, 9, 27, 81, 243, 729
        };

};

#endif // RUCUBESTATECONVERTER_H
