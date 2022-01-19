#include "ruCubeIgnoredPiecesGapFiller.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
#include <set>
#include <bitset>

ruCubeIgnoredPiecesGapFiller::ruCubeIgnoredPiecesGapFiller() {
    permutationIgnoredGapsFillCleanup();
}

ruCubeIgnoredPiecesGapFiller::~ruCubeIgnoredPiecesGapFiller() {
    //dtor
}

bool ruCubeIgnoredPiecesGapFiller::cornersOrientationIgnoredGapsFill(cornersArray& cornersOrient) {
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
        replaceNegativeOrients(cornersOrient, orientReplacement);
    }

    return true;
}

void ruCubeIgnoredPiecesGapFiller::permutationIgnoredGapsFillInit(const cornersArray& cornersPerm, const edgesArray& edgesPerm) {
    permutationIgnoredGapsFillCleanup();
    findMissingCorners(cornersPerm);
    findMissingEdges(edgesPerm);
}

bool ruCubeIgnoredPiecesGapFiller::permutationIgnoredGapsFillNext(cornersArray& cornersPerm, edgesArray& edgesPerm) {
    int validOutput = false;
    if (hasNextEdgesPerm) {
        for (size_t i = 0; i < size(missingCorners); ++i) {
            cornersPerm[cornersPermIgnoredIndices[i]] = missingCorners[i];
        }

        for (size_t i = 0; i < size(missingEdges); ++i) {
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

void ruCubeIgnoredPiecesGapFiller::replaceNegativeOrients(cornersArray& cornersOrient, uint8_t orientReplacement) {
    for (size_t i = 0; i < size(cornersOrient); ++i) {
        if (cornersOrient[i] == -1) {
            cornersOrient[i] = orientReplacement;
            orientReplacement = 0;
        }
    }
}

void ruCubeIgnoredPiecesGapFiller::permutationIgnoredGapsFillCleanup() {
    missingEdges.clear();
    missingCorners.clear();
    hasNextEdgesPerm = true;
    hasNextCornersPerm = true;
    cornersPermIgnoredIndices.clear();
    edgesPermIgnoredIndices.clear();
    missingCornersBits.reset();
    missingEdgesBits.reset();
}

void ruCubeIgnoredPiecesGapFiller::findMissingCorners(const cornersArray &cornersPerm) {
    for (uint8_t i = 0; i < ruBaseCube::noOfCorners; ++i) {
        if (cornersPerm[i] == -1) {
            cornersPermIgnoredIndices.push_back(i);
        } else {
            missingCornersBits.flip(cornersPerm[i]);
        }
    }

    for (uint8_t i = 0; i < ruBaseCube::noOfCorners; ++i) {
        if (!missingCornersBits[i]) {
            missingCorners.push_back(i);
        }
    }
}

void ruCubeIgnoredPiecesGapFiller::findMissingEdges(const edgesArray &edgesPerm) {
    for (uint8_t i = 0; i < ruBaseCube::noOfEdges; ++i) {
        if (edgesPerm[i] == -1) {
            edgesPermIgnoredIndices.push_back(i);
        } else {
            missingEdgesBits.flip(edgesPerm[i]);
        }
    }

    for (uint8_t i = 0; i < ruBaseCube::noOfEdges; ++i) {
        if (!missingEdgesBits[i]) {
            missingEdges.push_back(i);
        }
    }
}
