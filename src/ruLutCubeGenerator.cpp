#include "ruLutCubeGenerator.h"
#include "ruCubeStateValidator.h"
#include <algorithm>

ruLutCubeGenerator::ruLutCubeGenerator() {

}

ruLutCubeGenerator::~ruLutCubeGenerator() {

}

void ruLutCubeGenerator::init(  const std::vector<int8_t> &lockedEdges, const std::vector<int8_t> &ignoredEdges,
                                const std::vector<int8_t> &lockedCornersPerm, const std::vector<int8_t> &ignoredCornersPerm,
                                const cornersArray &lockedCornersOrient, const cornersArray &ignoredCornersOrient) {
    cornersOrientations =  orientGen.generateOrientations(lockedCornersOrient, ignoredCornersOrient);
    cornersPermutations =  cornersPermGen.generatePermutations(lockedCornersPerm, ignoredCornersPerm);
    edgesPermutations =    edgesPermGen.generatePermutations(lockedEdges, ignoredEdges);

    std::transform(begin(cornersOrientations),
                   end(cornersOrientations),
                   begin(cornersOrientations),
                   [this] (auto &co) {
                        filler.cornersOrientationIgnoredGapsFill(co);
                        return co;
                   });

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
        filler.permutationIgnoredGapsFillInit(cornersPermutations[cpIndex], edgesPermutations[epIndex]);

        while (not found and filler.permutationIgnoredGapsFillNext(cornersPermutations[cpIndex], edgesPermutations[epIndex])) {
            lexIndexCornersPerm = converter.vectCornersPermToLexIndexCornersPerm(cornersPermutations[cpIndex]);
            lexIndexEdgesPerm = converter.vectEdgesPermToLexIndexEdgesPerm(edgesPermutations[epIndex]);
            if (ruLutCube::isPermutationSolveable(lexIndexCornersPerm, lexIndexEdgesPerm)) {
                found = true;
            }
        }

        if (found) {
            hasNextCube = true;

            cornersArray cornersOrientationPermuted;
            for (uint8_t i = 0; i < size(cornersOrientationPermuted); ++i) {
                cornersOrientationPermuted[i] = cornersOrientations[coIndex][cornersPermutations[cpIndex][i]];
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
    ruLutCube ans(lexIndexEdgesPerm, lexIndexCornersPerm, lexIndexCornersOrient);
    generateNextCube();
    return ans;
}

bool ruLutCubeGenerator::hasNext() {
    return hasNextCube;
}
