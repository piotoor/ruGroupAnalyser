#ifndef RUCUBESTATEVALIDATOR_H
#define RUCUBESTATEVALIDATOR_H

#include <vector>
#include <cstdint>

class ruCubeStateValidator
{
    public:
        ruCubeStateValidator();
        virtual ~ruCubeStateValidator();

        bool isVectCornersValid(const std::vector<uint8_t> &orient, const std::vector<uint8_t> &perm);
        bool isVectEdgesValid(const std::vector<uint8_t> &perm);

    protected:

    private:
};

#endif // RUCUBESTATEVALIDATOR_H
