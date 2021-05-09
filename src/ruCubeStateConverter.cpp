#include "ruCubeStateConverter.h"

#include <set>
#include <numeric>

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

    for (int i = 0; i < size(perm); ++i) {
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

    for (int i = 0; i < size(perm); ++i) {
        ans <<= 3;
        if (perm[i] != -1) {
            ans = ans | perm[i];
        } else {
            ans = ans | *permIt++;
        }
    }

    return ans;
}

uint16_t ruCubeStateConverter::intEdgesToEdgesLexIndex(const uint32_t edges) const {
    std::bitset<numOfEdges> visited;
    std::array<uint8_t, numOfEdges> lehmer;

    std::array<uint16_t, numOfEdges> fact {
        720, 120, 24, 6, 2, 1, 0
    };

//    std::cout << std::endl << "-----------------------\n";
//    std::cout << std::oct << "edges = " << edges << std::dec << std::endl;
    uint8_t shift = 18;
    uint8_t curr = ((edges & (7 << shift)) >> shift);
    visited[curr] = 1;
//    std::cout << "curr = " << (int)curr << std::endl;
//    std::cout << 0 << ") visited = " << visited << std::endl;
    lehmer[0] = curr;

    for (uint8_t i = 1; i < numOfEdges; ++i) {
        shift = 18 - i * 3;
        curr = ((edges & (7 << shift)) >> shift);
        visited[curr] = 1;
//        std::cout << "curr = " << (int)curr << std::endl;
//        std::cout << (int)i << ") visited = " << visited << std::endl;
//        std::cout << "shifted = " << (visited << (numOfEdges - curr)) << std::endl;


        lehmer[i] = curr - (visited << (numOfEdges - curr)).count();
    }

    uint16_t ans = 0;
    for (uint8_t i = 0; i < numOfEdges; ++i) {
        //std::cout << (int)lehmer[i] << " ";
        ans += lehmer[i] * fact[i];
    }
    //std::cout << std::endl;

    return ans;
}

uint16_t ruCubeStateConverter::intCornersToCornersPermLexIndex(const uint64_t corners) const {
    return 0;
}

uint16_t ruCubeStateConverter::intCornersToCornersOrientLexIndex(const uint64_t corners) const {
    return 0;
}
