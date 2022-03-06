#include "ruCubeStateConverter.h"
#include <set>
#include <numeric>
#include <iterator>
#include <type_traits>
#include <string>

uint64_t ruCubeStateConverter::vectCornersToIntCorners(const cornersArray& orient, const cornersArray& perm) const {
    uint64_t ans = 0;

    std::set<int8_t> availPerm { 0, 1, 2, 3, 4, 5 };
    for (const auto &x: perm) {
        availPerm.erase(x);
    }
    auto permIt = availPerm.begin();

    uint8_t numOfNegativeOrients = 0;
    uint8_t sumOfPositiveOrients = std::accumulate(begin(orient),
                                                   end(orient),
                                                   0,
                                                   [&numOfNegativeOrients] (const auto &lhs, const auto &rhs) {
                                                        if (rhs >= 0) {
                                                            return lhs + rhs;
                                                        } else {
                                                            ++numOfNegativeOrients;
                                                            return lhs;
                                                        }
                                                   });

    constexpr uint8_t maxTotalOrient = 12;
    uint8_t orientReplacement = (maxTotalOrient - sumOfPositiveOrients) % 3;

    for (size_t i = 0; i < size(perm); ++i) {
        ans <<= 3;
        if (orient[i] != -1) {
            ans = ans | (01 << orient[i]);
        } else {
            ans = ans | (01 << orientReplacement);
            orientReplacement = 0;
        }
        ans <<= 3;
        if (perm[i] != -1) {
            ans = ans | perm[i];
        } else {
            ans = ans | *permIt++;
        }
    }

    return ans;
}

uint32_t ruCubeStateConverter::vectEdgesToIntEdges(const edgesArray& perm) const {
    uint32_t ans = 0;
    std::set<int8_t> availPerm { 0, 1, 2, 3, 4, 5, 6 };
    for (const auto &x: perm) {
        availPerm.erase(x);
    }
    auto permIt = availPerm.begin();

    for (size_t i = 0; i < size(perm); ++i) {
        ans <<= 3;
        if (perm[i] != -1) {
            ans = ans | perm[i];
        } else {
            ans = ans | *permIt++;
        }
    }

    return ans;
}

uint16_t ruCubeStateConverter::intEdgesToLexIndexEdges(const uint32_t edges) {
    return intPermToLexIndexPerm(edges, pieceSizeEdges, shiftBaseEdges, numOfEdges);
}

uint16_t ruCubeStateConverter::intPermToLexIndexPerm(const uint64_t perm, uint8_t pieceSize, uint8_t shiftBase, uint8_t numOfPieces) {
    visited.reset();
    uint16_t ans = 0;

    for (uint8_t i = 0; i < numOfPieces; ++i) {
        uint8_t shift = shiftBase - i * pieceSize;
        uint8_t curr = ((perm & (uint64_t(7) << shift)) >> shift);
        visited[curr] = 1;

        int lehmer = curr - (visited << (maxNumOfPieces - curr)).count();
        ans += lehmer * factLookup[numOfPieces - 1 - i];
    }

    return ans;
}

uint16_t ruCubeStateConverter::intCornersToLexIndexCornersPerm(const uint64_t corners) {
    return intPermToLexIndexPerm(corners, pieceSizeCorners, shiftBaseCorners, numOfCorners);
}

uint16_t ruCubeStateConverter::intCornersToLexIndexCornersOrient(const uint64_t corners) {
    uint16_t ans = 0;

    for (int8_t i = numOfCorners - 1; i >= 0; --i) {
        uint8_t shift = shiftBaseCornersOrient - i * pieceSizeCorners;
        uint8_t curr = ((corners & (uint64_t(7) << shift)) >> shift) / 2;
        ans += curr * powersOf3[numOfCorners - 1 - i];
    }

    return ans;
}

uint32_t ruCubeStateConverter::lexIndexEdgesToIntEdges(uint16_t lexIndexEdges) {
    uint32_t ans = 0;

    lexIndexPermToArrayPermIntermediate(lexIndexEdges, numOfEdges);

    for (int8_t i = 0; i < numOfEdges; ++i) {
        ans <<= pieceSizeEdges;
        ans |= perm[i];
    }

    return ans;
}

void ruCubeStateConverter::lexIndexPermToArrayPermIntermediate(uint16_t lexPerm, uint8_t numOfPieces) {
    perm.fill(0);

    for (uint8_t i = 0; i < numOfPieces; ++i) {
        perm[i] = lexPerm / factLookup[numOfPieces - 1 - i];
        lexPerm = lexPerm % factLookup[numOfPieces - 1 - i];
    }


    for (int8_t i = numOfPieces - 1; i > 0; --i) {
        for (int8_t j = i - 1; j >= 0; --j) {
            if (perm[j] <= perm[i]) {
                perm[i]++;
            }
        }
    }
}

uint64_t ruCubeStateConverter::lexIndexCornersToIntCorners(uint16_t lexIndexOrient, uint16_t lexIndexPerm) {
    uint64_t ans = lexIndexCornersOrientToIntCornersOrient(lexIndexOrient);
    lexIndexPermToArrayPermIntermediate(lexIndexPerm, numOfCorners);

    uint8_t shift = 0;
    for (int8_t i = 0; i < numOfCorners; ++i) {
        ans |= static_cast<uint64_t>(perm[numOfCorners - 1 - i]) << shift;
        shift += pieceSizeCorners;
    }
    return ans;
}

uint64_t ruCubeStateConverter::lexIndexCornersOrientToIntCornersOrient(uint16_t lexIndexOrient) {
    uint64_t ans = 0;
    uint64_t shift = 3;

    for (int8_t i = 0; i < numOfCorners; ++i) {
        ans |= static_cast<uint64_t>(static_cast<uint64_t>(1) << (lexIndexOrient % 3)) << shift;
        shift += pieceSizeCorners;
        lexIndexOrient /= 3;
    }

    return ans;
}


template <typename T>
uint16_t ruCubeStateConverter::vectPermToLexIndexPerm(const T &perm) {
    static_assert(std::is_convertible_v<T, cornersArray> or std::is_convertible_v<T, edgesArray>,
                  "Only cornersArray and edgesArray are allowed.");

    visited.reset();
    uint16_t ans = 0;

    for (size_t i = 0; i < size(perm); ++i) {
        visited[perm[i]] = 1;

        int lehmer = perm[i] - (visited << (maxNumOfPieces - perm[i])).count();
        ans += lehmer * factLookup[size(perm) - 1 - i];
    }

    return ans;
}

template uint16_t ruCubeStateConverter::vectPermToLexIndexPerm<cornersArray>(const cornersArray &perm);
template uint16_t ruCubeStateConverter::vectPermToLexIndexPerm<edgesArray>(const edgesArray &perm);

uint16_t ruCubeStateConverter::vectEdgesPermToLexIndexEdgesPerm(const edgesArray &perm) {
    return vectPermToLexIndexPerm<edgesArray>(perm);
}

uint16_t ruCubeStateConverter::vectCornersPermToLexIndexCornersPerm(const cornersArray &perm) {
    return vectPermToLexIndexPerm<cornersArray>(perm);
}

uint16_t ruCubeStateConverter::vectCornersOrientToLexIndexCornersOrient(const cornersArray &orient) {
    uint16_t ans = 0;

    for (uint8_t i = 0; i < numOfCorners; ++i) {
        ans += orient[i] * powersOf3[numOfCorners - 1 - i];
    }

    return ans;
}

std::string ruCubeStateConverter::lexIndexEdgesToIntEdgesAsStrWithIgnored(uint16_t lexIndexEdges, const std::bitset<ruBaseCube::noOfEdges> &ignoredEdeges) {
    std::string ans = "-------";

    lexIndexPermToArrayPermIntermediate(lexIndexEdges, numOfEdges);

    for (int8_t i = 0; i < numOfEdges; ++i) {
        if (not ignoredEdeges[perm[i]]) {
            ans[i] = perm[i] + '0';
        }
    }

    return ans;
}

std::string ruCubeStateConverter::lexIndexCornersToIntCornersAsStrWithIgnored(uint16_t lexIndexPerm, uint16_t lexIndexOrient, const std::bitset<ruBaseCube::noOfCorners> &ignoredCornersPerm, const std::bitset<ruBaseCube::noOfCorners> &ignoredCornersOrient) {
    std::string ans = "------------";
    lexIndexPermToArrayPermIntermediate(lexIndexPerm, numOfCorners);


    for (int8_t i = 0; i < numOfCorners; ++i) {
        if (not ignoredCornersOrient[perm[numOfCorners - 1 - i]]) {
            ans[numOfCorners * 2 - 2 - i * 2] = ((0x1 << (lexIndexOrient % 3)) >> 1) + '0';
        }
        if (not ignoredCornersPerm[perm[i]]) {
            ans[i * 2 + 1] = perm[i] + '0';
        }
        lexIndexOrient /= 3;
    }
    return ans;
}

template <typename T>
std::string ruCubeStateConverter::containerToString(const T &cont) {
    static_assert(std::is_convertible_v<T, cornersArray> or std::is_convertible_v<T, edgesArray> or std::is_convertible_v<T, std::set<int8_t>>, "Only cornersArray and edgesArray are allowed.");
    return std::accumulate(   begin(cont),
                              end(cont),
                              std::string(),
                              [] (const auto &lhs, const auto &rhs) {
                                    if (rhs < 0) {
                                        return lhs + "x";
                                    } else {
                                        return lhs + std::to_string(rhs);
                                    }
                              });
}

template std::string ruCubeStateConverter::containerToString<cornersArray>(const cornersArray &cont);
template std::string ruCubeStateConverter::containerToString<edgesArray>(const edgesArray &cont);
template std::string ruCubeStateConverter::containerToString<std::set<int8_t>>(const std::set<int8_t> &cont);
