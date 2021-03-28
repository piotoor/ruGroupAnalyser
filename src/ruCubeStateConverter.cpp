#include "ruCubeStateConverter.h"

ruCubeStateConverter::ruCubeStateConverter() {
    //ctor
}

ruCubeStateConverter::~ruCubeStateConverter() {
    //dtor
}

uint64_t ruCubeStateConverter::vectCornersToInt(const std::vector<uint8_t>& perm, const std::vector<uint8_t>& orient) {
    uint64_t ans = 0;

    for (int i = 0; i < size(perm); ++i) {
        ans <<= 3;
        ans = ans | (01 << orient[i]);
        ans <<= 3;
        ans = ans | perm[i];
    }

    return ans;
}

uint32_t ruCubeStateConverter::vectEdgesToInt(const std::vector<uint8_t>& perm) {
    uint32_t ans = 0;

    for (int i = 0; i < size(perm); ++i) {
        ans <<= 3;
        ans = ans |= perm[i];
    }

    return ans;
}

