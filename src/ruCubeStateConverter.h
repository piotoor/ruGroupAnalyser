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
        uint64_t vectCornersToInt(const std::vector<uint8_t> &perm, const std::vector<uint8_t> &orient);
        uint32_t vectEdgesToInt(const std::vector<uint8_t> &perm);
    protected:

    private:
};

#endif // RUCUBESTATECONVERTER_H
