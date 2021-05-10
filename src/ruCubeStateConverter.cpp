#include "ruCubeStateConverter.h"

#include <set>
#include <numeric>
#include <cmath>

ruCubeStateConverter::ruCubeStateConverter() {

}

ruCubeStateConverter::~ruCubeStateConverter() {

}

uint64_t ruCubeStateConverter::vectCornersToInt(const std::vector<int8_t>& perm, const std::vector<int8_t>& orient) const {
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

    for (uint8_t i = 0; i < size(perm); ++i) {
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

#include <iostream>
uint32_t ruCubeStateConverter::vectEdgesToInt(const std::vector<int8_t>& perm) const {
    uint32_t ans = 0;
    std::set<int8_t> availPerm { 0, 1, 2, 3, 4, 5, 6 };
    for (const auto &x: perm) {
        availPerm.erase(x);
    }
    auto permIt = availPerm.begin();

    for (uint8_t i = 0; i < size(perm); ++i) {
        ans <<= 3;
        if (perm[i] != -1) {
            ans = ans | perm[i];
        } else {
            ans = ans | *permIt++;
        }
    }

    return ans;
}

uint16_t ruCubeStateConverter::intEdgesToEdgesLexIndex(const uint32_t edges) {
    return intPermToPermLexIndex(edges, pieceSizeEdges, shiftBaseEdges, numOfEdges);
}

uint16_t ruCubeStateConverter::intPermToPermLexIndex(const uint64_t perm, uint8_t pieceSize, uint8_t shiftBase, uint8_t numOfPieces) {
    lehmer.fill(0);
    visited.reset();
    for (uint8_t i = 0; i < numOfPieces; ++i) {
        uint8_t shift = shiftBase - i * pieceSize;
        uint8_t curr = ((perm & (7UL << shift)) >> shift);
        visited[curr] = 1;

        lehmer[i] = curr - (visited << (numOfPieces - curr + (maxNumOfPieces - numOfPieces))).count();
    }

    uint16_t ans = 0;
    for (uint8_t i = 0; i < numOfPieces; ++i) {
        ans += lehmer[i] * factLookup[numOfPieces - 1 - i];
    }

    return ans;
}

uint16_t ruCubeStateConverter::intCornersToCornersPermLexIndex(const uint64_t corners) {
    return intPermToPermLexIndex(corners, pieceSizeCorners, shiftBaseCorners, numOfCorners);
}

uint16_t ruCubeStateConverter::intCornersToCornersOrientLexIndex(const uint64_t corners) {
    uint16_t ans = 0;

    for (int8_t i = numOfCorners - 1; i >= 0; --i) {
        uint8_t shift = shiftBaseCornersOrient - i * pieceSizeCorners;
        uint8_t curr = ((corners & (7UL << shift)) >> shift) / 2;
        ans += curr * static_cast<uint16_t>(pow(3.0, static_cast<double>(numOfCorners - 1 - i)));
    }

    return ans;
}
