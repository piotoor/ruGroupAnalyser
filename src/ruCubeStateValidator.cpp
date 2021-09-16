#include "ruCubeStateValidator.h"

#include <algorithm>
#include <numeric>
#include <iterator>


ruCubeStateValidator::ruCubeStateValidator() {
}

ruCubeStateValidator::~ruCubeStateValidator() {
}

bool ruCubeStateValidator::isVectCornersValid(const cornersArray& orient, const std::vector<int8_t>& perm) {
    return isVectCornersOrientValid(orient) and size(perm) == 6 and isPermutationValid(perm);
}

bool ruCubeStateValidator::isVectEdgesValid(const std::vector<int8_t>& perm) {
    return size(perm) == 7 and isPermutationValid(perm);
}

bool ruCubeStateValidator::isVectCornersOrientValid(const cornersArray &orient) {
    const auto &[l, h] = std::minmax_element(begin(orient), end(orient));
    if (*l < -1 or static_cast<int8_t>(*h) > 2) {
        return false;
    }

    if (std::none_of( begin(orient),
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

bool ruCubeStateValidator::isVectCornersOrientSolveableQuick(const cornersArray& cornersOrient) {
    return cube.isCornersOrientationSolveable(converter.vectCornersOrientToLexIndexCornersOrient(cornersOrient));
}

bool ruCubeStateValidator::isVectCubePermSolveableQuick(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return cube.isPermutationSolveable(converter.vectCornersPermToLexIndexCornersPerm(cornersPerm),
                                       converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm));
}

bool ruCubeStateValidator::isVectCubeStateSolveableQuick(   const cornersArray&cornersOrient,
                                                            const std::vector<int8_t> &cornersPerm,
                                                            const std::vector<int8_t> &edgesPerm) {
    return cube.isCubeSolveable(converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm),
                                converter.vectCornersPermToLexIndexCornersPerm(cornersPerm),
                                converter.vectCornersOrientToLexIndexCornersOrient(cornersOrient));
}


bool ruCubeStateValidator::isVectCornersOrientSolveableFull(const cornersArray& cornersOrient) {
    return isVectCornersOrientValid(cornersOrient) and isVectCornersOrientSolveableQuick(cornersOrient);
}

bool ruCubeStateValidator::isVectCubePermSolveableFull(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm) {
    return isVectCornersPermValid(cornersPerm) and isVectEdgesValid(edgesPerm) and isVectCubePermSolveableQuick(cornersPerm, edgesPerm);
}

bool ruCubeStateValidator::isVectCubeStateSolveableFull(const cornersArray &cornersOrient,
                                                        const std::vector<int8_t> &cornersPerm,
                                                        const std::vector<int8_t> &edgesPerm) {
    return isVectCornersOrientSolveableFull(cornersOrient) and isVectCubePermSolveableFull(cornersPerm, edgesPerm);
}
