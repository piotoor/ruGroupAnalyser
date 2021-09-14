#include "ruCubeIgnoredPiecesGapFiller.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
#include <set>

ruCubeIgnoredPiecesGapFiller::ruCubeIgnoredPiecesGapFiller() {
    permutationIgnoredGapsFillCleanup();
}

ruCubeIgnoredPiecesGapFiller::~ruCubeIgnoredPiecesGapFiller() {
    //dtor
}

bool ruCubeIgnoredPiecesGapFiller::cornersOrientationIgnoredGapsFill(std::vector<int8_t>& cornersOrient) {
    if (size(cornersOrient) != 6) {
        return false;
    }

    uint8_t numOfNegativeOrients = 0;
    uint8_t sumOfPositiveOrients = std::accumulate(begin(cornersOrient),
                                                   end(cornersOrient),
                                                   0,
                                                   [&numOfNegativeOrients] (const auto &lhs, const auto &rhs) {
                                                        if (rhs >= 0) {
                                                            return lhs + rhs;
                                                        } else {
                                                            ++numOfNegativeOrients;
                                                            return lhs;
                                                        }
                                                   });

    if (numOfNegativeOrients != 0) {
        constexpr uint8_t maxTotalOrient = 12;
        uint8_t orientReplacement = (maxTotalOrient - sumOfPositiveOrients) % 3;

        for (uint8_t i = 0; i < size(cornersOrient); ++i) {
            if (cornersOrient[i] == -1) {
                cornersOrient[i] = orientReplacement;
                orientReplacement = 0;
            }
        }
    }

    return true;
}

void ruCubeIgnoredPiecesGapFiller::permutationIgnoredGapsFillCleanup() {
    missingEdges.clear();
    missingCorners.clear();
    hasNextEdgesPerm = true;
    hasNextCornersPerm = true;
    cornersPermIgnoredIndices.clear();
    edgesPermIgnoredIndices.clear();
}

void ruCubeIgnoredPiecesGapFiller::permutationIgnoredGapsFillInit(std::vector<int8_t> cornersPerm, std::vector<int8_t> edgesPerm) {
    permutationIgnoredGapsFillCleanup();

    std::set<uint8_t> tmpEdges { 0, 1, 2, 3, 4, 5, 6 };
    std::set<uint8_t> tmpCorners { 0, 1, 2, 3, 4, 5 };

    for (uint8_t i = 0; i < size(cornersPerm); ++i) {
        if (cornersPerm[i] == -1) {
            cornersPermIgnoredIndices.push_back(i);
        }
    }

    for (uint8_t i = 0; i < size(edgesPerm); ++i) {
        if (edgesPerm[i] == -1) {
            edgesPermIgnoredIndices.push_back(i);
        }
    }

    std::sort(begin(edgesPerm),
              end(edgesPerm));

    std::sort(begin(cornersPerm),
              end(cornersPerm));

    std::set_difference(begin(tmpEdges),
                        end(tmpEdges),
                        begin(edgesPerm),
                        end(edgesPerm),
                        std::back_inserter(missingEdges));

    std::set_difference(begin(tmpCorners),
                        end(tmpCorners),
                        begin(cornersPerm),
                        end(cornersPerm),
                        std::back_inserter(missingCorners));
}

bool ruCubeIgnoredPiecesGapFiller::permutationIgnoredGapsFillNext(std::vector<int8_t>& cornersPerm, std::vector<int8_t>& edgesPerm) {
    int validOutput = false;
    if (hasNextEdgesPerm) {
        for (uint8_t i = 0; i < size(missingCorners); ++i) {
            cornersPerm[cornersPermIgnoredIndices[i]] = missingCorners[i];
        }

        for (uint8_t i = 0; i < size(missingEdges); ++i) {
            edgesPerm[edgesPermIgnoredIndices[i]] = missingEdges[i];
        }
        validOutput = true;
    }

    hasNextEdgesPerm = std::next_permutation(begin(missingEdges),
                                             end(missingEdges));

    if (not hasNextEdgesPerm) {
        hasNextCornersPerm = std::next_permutation(begin(missingCorners),
                                                   end(missingCorners));

        if (hasNextCornersPerm) {
            hasNextEdgesPerm = true;
        }
    }

    return validOutput;
}

