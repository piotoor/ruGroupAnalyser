#include "ruCubeStateValidator.h"

ruCubeStateValidator::ruCubeStateValidator() {
    //ctor
}

ruCubeStateValidator::~ruCubeStateValidator() {
    //dtor
}

bool ruCubeStateValidator::isVectCornersValid(const std::vector<uint8_t>& orient, const std::vector<uint8_t>& perm) {
    return isOrientationValid(orient) and size(orient) == 6 and isPermutationValid(perm) and size(perm) == 6;
}

bool ruCubeStateValidator::isVectEdgesValid(const std::vector<uint8_t>& perm) {
    return isPermutationValid(perm) and size(perm) == 7;
}

bool ruCubeStateValidator::isPermutationValid(const std::vector<uint8_t>& perm) {
    auto &[l, h] = std::minmax(begin(perm), end(perm));
    if (l < -1 or h >= size(perm)) {
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
    auto &[l, h] = std::minmax(begin(perm), end(perm));
    if (l < -1 or h > 2) {
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
    bool valid = isVectCornersValid(cornersOrient, cornersPerm) and isVectEdgesValid(edgesPerm);
    // todo solveability check

    return valid;
}


