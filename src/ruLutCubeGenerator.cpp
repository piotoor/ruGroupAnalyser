#include "ruLutCubeGenerator.h"
#include "ruCubeStateValidator.h"
#include <algorithm>

ruLutCubeGenerator::ruLutCubeGenerator() {

}

ruLutCubeGenerator::~ruLutCubeGenerator() {

}

void ruLutCubeGenerator::saveCompressedGeneratorIgnoredParams(const generatorParameters &params) {
    for (int8_t i = 0; i < ruCube::noOfEdges; ++i) {
        if (params.ignoredEdges.find(i) != params.ignoredEdges.end()) {
            ignoredEdgesBits.set(i);
        }
    }

    for (int8_t i = 0; i < ruCube::noOfCorners; ++i) {
        if (params.ignoredCornersPerm.find(i) != params.ignoredCornersPerm.end()) {
            ignoredCornersPermBits.set(i);
        }
        if (params.ignoredCornersOrient[i] == 1) {
            ignoredCornersOrientBits.set(i);
        }
    }
}

void ruLutCubeGenerator::init(const generatorParameters &params) {
    cornersOrientations =  orientGen.generateOrientations(params.lockedCornersOrient, params.ignoredCornersOrient);
    cornersPermutations =  cornersPermGen.generatePermutations(params.lockedCornersPerm, params.ignoredCornersPerm);
    edgesPermutations =    edgesPermGen.generatePermutations(params.lockedEdges, params.ignoredEdges);

    std::transform(begin(cornersOrientations),
                   end(cornersOrientations),
                   begin(cornersOrientations),
                   [this] (auto &co) {
                        filler.cornersOrientationIgnoredGapsFill(co);
                        return co;
                   });

    saveCompressedGeneratorIgnoredParams(params);
    lexIndexCornersPerm = 0;
    lexIndexEdgesPerm = 0;
    lexIndexCornersOrient = 0;
    hasNextCube = false;
    cpIndex = 0;
    coIndex = 0;
    epIndex = 0;
    generateNextCube();
}

void ruLutCubeGenerator::generateNextCube() {
    bool found = false;
    hasNextCube = false;

    while (not found and cpIndex < cornersPermutations.size()) {
        auto currCornersPerm = cornersPermutations[cpIndex];
        auto currEdgesPerm = edgesPermutations[epIndex];
        filler.permutationIgnoredGapsFillInit(currCornersPerm, currEdgesPerm);

        while (not found and filler.permutationIgnoredGapsFillNext(currCornersPerm, currEdgesPerm)) {
            lexIndexCornersPerm = converter.vectCornersPermToLexIndexCornersPerm(currCornersPerm);
            lexIndexEdgesPerm = converter.vectEdgesPermToLexIndexEdgesPerm(currEdgesPerm);
            if (ruLutCube::isPermutationSolveable(lexIndexCornersPerm, lexIndexEdgesPerm)) {
                found = true;
            }
        }

        if (found) {
            hasNextCube = true;

            cornersArray cornersOrientationPermuted;
            for (size_t i = 0; i < size(cornersOrientationPermuted); ++i) {
                cornersOrientationPermuted[i] = cornersOrientations[coIndex][currCornersPerm[i]];
            }
            lexIndexCornersOrient = converter.vectCornersOrientToLexIndexCornersOrient(cornersOrientationPermuted);

            coIndex++;
            if (coIndex == cornersOrientations.size()) {
                coIndex = 0;
                epIndex++;
                if (epIndex >= edgesPermutations.size()) {
                    epIndex = 0;
                    cpIndex++;
                }
            }
        } else {
            coIndex = 0;
            epIndex++;
            if (epIndex >= edgesPermutations.size()) {
                epIndex = 0;
                cpIndex++;
            }
        }
    }
}

ruLutCube ruLutCubeGenerator::next() {
    ruLutCube ans(lexIndexCornersOrient,
                  lexIndexCornersPerm,
                  lexIndexEdgesPerm,
                  { ignoredCornersOrientBits, ignoredCornersPermBits, ignoredEdgesBits });
    generateNextCube();
    return ans;
}

bool ruLutCubeGenerator::hasNext() {
    return hasNextCube;
}

solvedMasks generatorParameters::toSolvedMasks () const {
        solvedMasks ans { 0, 0 };

        std::bitset<32> edgesBits;
        for (int8_t i = 0; i < ruCube::noOfEdges; ++i) {
            if (ignoredEdges.find(i) == ignoredEdges.end()) {
                edgesBits.set(ruCube::noOfEdges - 1 - i);
            }
        }
        ans.edgesMask = static_cast<uint32_t>(edgesBits.to_ulong());

        std::bitset<32> cornersPermBits;
        std::bitset<32> cornersOrientBits;
        for (int8_t i = 0; i < ruCube::noOfCorners; ++i) {
            if (ignoredCornersPerm.find(i) == ignoredCornersPerm.end()) {
                cornersPermBits.set(ruCube::noOfCorners - 1 - i);
            }
            if (ignoredCornersOrient[i] == 0) {
                cornersOrientBits.set(ruCube::noOfCorners - 1 - i);
            }
        }

        ans.cornersMask =   (static_cast<uint64_t>(cornersOrientBits.to_ulong()) << (sizeof(uint32_t) * 8)) |
                            static_cast<uint64_t>(cornersPermBits.to_ulong());
        return ans;
    }
