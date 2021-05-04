#ifndef RUCUBESTATECONVERTER_H
#define RUCUBESTATECONVERTER_H

#include <cstdint>
#include <vector>

class ruCubeStateConverter
{
    public:
        ruCubeStateConverter();
        explicit ruCubeStateConverter(const ruCubeStateConverter &other) = delete;
        ruCubeStateConverter& operator=(const ruCubeStateConverter &other) = delete;
        virtual ~ruCubeStateConverter();
        uint64_t vectCornersToInt(const std::vector<int8_t> &perm, const std::vector<int8_t> &orient) const;
        uint32_t vectEdgesToInt(const std::vector<int8_t> &perm) const;
        uint16_t intEdgesToEdgesLexIndex(const uint32_t) const;
        uint16_t intCornersToCornersPermLexIndex(const uint64_t) const;
        uint16_t intCornersToCornersOrientLexIndex(const uint64_t) const;

    protected:

    private:
};

#endif // RUCUBESTATECONVERTER_H
