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

bool ruCubeStateValidator::isVectCornersValid(const std::vector<int8_t>& orient, const std::vector<int8_t>& perm) {
    return size(orient) == 6 and isOrientationValid(orient) and size(perm) == 6 and isPermutationValid(perm);
}

bool ruCubeStateValidator::isVectEdgesValid(const std::vector<int8_t>& perm) {
    return size(perm) == 7 and isPermutationValid(perm);
}

bool ruCubeStateValidator::isVectCornersOrientValid(const std::vector<int8_t> &orient) {
    return size(orient) == 6 and isOrientationValid(orient);
}

bool ruCubeStateValidator::isVectCornersPermValid(const std::vector<int8_t> &perm) {
    return size(perm) == 6 and isPermutationValid(perm);
}

bool ruCubeStateValidator::isPermutationValid(const std::vector<int8_t>& perm) {
    if (size(perm) == 0) {
        return false;
    }

    const auto &[l, h] = std::minmax_element(begin(perm), end(perm));
    if (*l < -1 or static_cast<int8_t>(*h) >= (uint8_t)size(perm)) {
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

bool ruCubeStateValidator::isOrientationValid(const std::vector<int8_t>& orient) {
    const auto &[l, h] = std::minmax_element(begin(orient), end(orient));
    if (*l < -1 or static_cast<uint8_t>(*h) > 2) {
        return false;
    }

    if (none_of( begin(orient),
                end(orient),
                [] (const auto &x) {
                    return x == -1;
                })) {
        const int acc = std::accumulate(begin(orient),
                                    end(orient),
                                    0);
        if (acc % 3 != 0) {
            return false;
        }
    }

    return true;
}

bool ruCubeStateValidator::isVectCubeStateSolveable(const std::vector<int8_t>& cornersOrient, const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return isVectCornersValid(cornersOrient, cornersPerm) and isVectEdgesValid(edgesPerm) and isVectCornersInRU(cornersPerm);
}

bool ruCubeStateValidator::isVectCornersInRU(const std::vector<int8_t>& perm) {
    ruCube cube;
    ruCubeStateConverter converter;
    const uint64_t cornersInt = converter.vectCornersToIntCorners(perm, {0, 0, 0, 0, 0, 0});
    cube.setCorners(cornersInt);

    constexpr uint64_t dfrCornersMask = 0000000000007;
    constexpr uint64_t drbDfrCornersMask = 0000000000707;
    constexpr uint64_t ubrDrbDfrCornersMask = 0000000070707;
    return true;
}
