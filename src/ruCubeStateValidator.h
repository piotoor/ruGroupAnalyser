#ifndef RUCUBESTATEVALIDATOR_H
#define RUCUBESTATEVALIDATOR_H

#include <vector>
#include <cstdint>

class ruCubeStateValidator
{
    public:
        ruCubeStateValidator();
        virtual ~ruCubeStateValidator();
        bool isVectCubeStateSolveable(const std::vector<uint8_t> &cornersOrient,
                                      const std::vector<uint8_t> &cornersPerm,
                                      const std::vector<uint8_t> &edgesPerm);
        bool isVectCornersValid(const std::vector<uint8_t> &orient, const std::vector<uint8_t> &perm);
        bool isVectEdgesValid(const std::vector<uint8_t> &perm);

    private:
        bool isPermutationValid(const std::vector<uint8_t> &perm);
        bool isOrientationValid(const std::vector<uint8_t> &orient);
        bool isVectCornersInRU(const std::vector<uint8_t> &perm);
};

#endif // RUCUBESTATEVALIDATOR_H
