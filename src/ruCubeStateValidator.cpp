#include "ruCubeStateValidator.h"

#include <algorithm>
#include <numeric>
#include <iterator>


ruCubeStateValidator::ruCubeStateValidator() {
}

ruCubeStateValidator::~ruCubeStateValidator() {
}

bool ruCubeStateValidator::isVectCornersValid(const cornersArray& orient, const cornersArray& perm) {
    return isVectCornersOrientValid(orient) and size(perm) == 6 and isPermutationValid(perm);
}

bool ruCubeStateValidator::isVectEdgesValid(const edgesArray& perm) {
    return isPermutationValid(perm);
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

bool ruCubeStateValidator::isVectCornersPermValid(const cornersArray &perm) {
    return isPermutationValid(perm);
}

template <typename T>
bool ruCubeStateValidator::isPermutationValid(const T &perm) {
//    static_assert(!(std::is_convertible_v<T, cornersArray> or std::is_convertible_v<T, edgesArray>),
//                  "Only cornersArray and edgesArray are allowed.");

    const auto &[l, h] = std::minmax_element(begin(perm), end(perm));
    if (*l < -1 or static_cast<int8_t>(*h) >= (uint8_t)size(perm)) {
        return false;
    }

    auto copyPerm = perm;
    std::sort(begin(copyPerm), end(copyPerm));
    auto adj = std::adjacent_find(begin(copyPerm), end(copyPerm));
    if (adj != end(copyPerm) and *adj != -1) {
        return false;
    }

    return true;
}

template bool ruCubeStateValidator::isPermutationValid<cornersArray>(const cornersArray &perm);
template bool ruCubeStateValidator::isPermutationValid<edgesArray>(const edgesArray &perm);

bool ruCubeStateValidator::isVectCornersOrientSolveableQuick(const cornersArray& cornersOrient) {
    return cube.isCornersOrientationSolveable(converter.vectCornersOrientToLexIndexCornersOrient(cornersOrient));
}

bool ruCubeStateValidator::isVectCubePermSolveableQuick(const cornersArray& cornersPerm, const edgesArray& edgesPerm) {
    return cube.isPermutationSolveable(converter.vectCornersPermToLexIndexCornersPerm(cornersPerm),
                                       converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm));
}

bool ruCubeStateValidator::isVectCubeStateSolveableQuick(   const cornersArray&cornersOrient,
                                                            const cornersArray &cornersPerm,
                                                            const edgesArray &edgesPerm) {
    return cube.isCubeSolveable(converter.vectEdgesPermToLexIndexEdgesPerm(edgesPerm),
                                converter.vectCornersPermToLexIndexCornersPerm(cornersPerm),
                                converter.vectCornersOrientToLexIndexCornersOrient(cornersOrient));
}


bool ruCubeStateValidator::isVectCornersOrientSolveableFull(const cornersArray& cornersOrient) {
    return isVectCornersOrientValid(cornersOrient) and isVectCornersOrientSolveableQuick(cornersOrient);
}

bool ruCubeStateValidator::isVectCubePermSolveableFull(const cornersArray& cornersPerm, const edgesArray& edgesPerm) {
    return isVectCornersPermValid(cornersPerm) and isVectEdgesValid(edgesPerm) and isVectCubePermSolveableQuick(cornersPerm, edgesPerm);
}

bool ruCubeStateValidator::isVectCubeStateSolveableFull(const cornersArray &cornersOrient,
                                                        const cornersArray &cornersPerm,
                                                        const edgesArray &edgesPerm) {
    return isVectCornersOrientSolveableFull(cornersOrient) and isVectCubePermSolveableFull(cornersPerm, edgesPerm);
}
