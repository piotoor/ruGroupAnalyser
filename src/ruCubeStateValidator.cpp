#include "ruCubeStateValidator.h"

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
    if (size(orient) == 0) {
        return false;
    }

    const auto &[l, h] = std::minmax_element(begin(orient), end(orient));
    if (*l < -1 or static_cast<int8_t>(*h) > 2) {
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

bool ruCubeStateValidator::isVectCubePermSolveable(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return  isVectCornersPermValid(cornersPerm) and
            isVectEdgesValid(edgesPerm) and
            cube.isPermutationSolveable(converter.vectCornersPermToLexIndexCornersPerm(cornersPerm), converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm));
}

bool ruCubeStateValidator::isVectCubeStateSolveable(const std::vector<int8_t>& cornersOrient, const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return isVectCubePermSolveable(cornersPerm, edgesPerm) and isVectCornersOrientValid(cornersOrient);
}

bool ruCubeStateValidator::isVectCubePermSolveableLutBased(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return cube.isPermutationSolveable(converter.vectCornersPermToLexIndexCornersPerm(cornersPerm), converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm));
}

bool ruCubeStateValidator::isVectCubeStateSolveableLutBased(const std::vector<int8_t>& cornersOrient, const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return cube.isCubeSolveable(converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm),
                                converter.vectCornersPermToLexIndexCornersPerm(cornersPerm),
                                converter.vectCornersOrientToLexIndexCornersOrient(cornersOrient));
}
