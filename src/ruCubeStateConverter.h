#ifndef RUCUBESTATECONVERTER_H
#define RUCUBESTATECONVERTER_H

#include <cstdint>
#include <vector>

class ruCubeStateConverter
{
    public:
        ruCubeStateConverter();
        virtual ~ruCubeStateConverter();
        uint64_t vectCornersToInt(const std::vector<uint8_t> &perm, const std::vector<uint8_t> &orient);
        uint32_t vectEdgesToInt(const std::vector<uint8_t> &perm);
    protected:

    private:
};

#endif // RUCUBESTATECONVERTER_H
