#include "ruCubeStateConverter.h"

#include <set>
#include <numeric>

ruCubeStateConverter::ruCubeStateConverter() {

}

ruCubeStateConverter::~ruCubeStateConverter() {

}

uint64_t ruCubeStateConverter::vectCornersToInt(const std::vector<int8_t>& perm, const std::vector<int8_t>& orient) {
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

uint32_t ruCubeStateConverter::vectEdgesToInt(const std::vector<int8_t>& perm) {
    uint32_t ans = 0;

    for (int i = 0; i < size(perm); ++i) {
        ans <<= 3;
        ans = ans |= perm[i];
    }

    return ans;
}

