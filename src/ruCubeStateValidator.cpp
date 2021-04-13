#include "ruCubeStateValidator.h"
#include "ruCubeStateConverter.h"
#include "ruCube.h"

#include <algorithm>
#include <numeric>
#include <iterator>


ruCubeStateValidator::ruCubeStateValidator() {
}

ruCubeStateValidator::~ruCubeStateValidator() {
}

bool ruCubeStateValidator::isVectCornersValid(const std::vector<uint8_t>& orient, const std::vector<uint8_t>& perm) {
    return isOrientationValid(orient) and size(orient) == 6 and isPermutationValid(perm) and size(perm) == 6;
}

bool ruCubeStateValidator::isVectEdgesValid(const std::vector<uint8_t>& perm) {
    return isPermutationValid(perm) and size(perm) == 7;
}

bool ruCubeStateValidator::isPermutationValid(const std::vector<uint8_t>& perm) {
    const auto &[l, h] = std::minmax(begin(perm), end(perm));
    if (*l < -1 or *h >= size(perm)) {
        return false;
    }

    auto copyPerm = perm;
    sort(begin(copyPerm), end(copyPerm));
    auto adj = adjacent_find(begin(copyPerm), end(copyPerm));
    if (adj != end(copyPerm) and *adj != -1) {
        return false;
    }

    return true;
}

bool ruCubeStateValidator::isOrientationValid(const std::vector<uint8_t>& orient) {
    const auto &[l, h] = std::minmax(begin(orient), end(orient));
    if (*l < -1 or *h > 2) {
        return false;
    }

    if (none_of( begin(orient),
                end(orient),
                [] (const auto &x) {
                    return x == -1;
                })) {
        int acc = std::accumulate(begin(orient),
                                    end(orient),
                                    0);
        if (acc % 3 != 0) {
            return false;
        }
    }

    return true;
}

bool ruCubeStateValidator::isVectCubeStateSolveable(const std::vector<uint8_t>& cornersOrient, const std::vector<uint8_t>& cornersPerm, const std::vector<uint8_t>& edgesPerm) {
    return isVectCornersValid(cornersOrient, cornersPerm) and isVectEdgesValid(edgesPerm) and isVectCornersInRU(cornersPerm);
}

bool ruCubeStateValidator::isVectCornersInRU(const std::vector<uint8_t>& perm) {
    ruCube cube;
    ruCubeStateConverter converter;
    const uint64_t cornersInt = converter.vectCornersToInt(perm, {0, 0, 0, 0, 0, 0});
    cube.setCorners(cornersInt);

    constexpr uint64_t dfrCornersMask = 0000000000007;
    constexpr uint64_t drbDfrCornersMask = 0000000000707;
    constexpr uint64_t ubrDrbDfrCornersMask = 0000000070707;
    return true;
}



