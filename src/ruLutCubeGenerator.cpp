#include "ruLutCubeGenerator.h"
#include "ruCubeStateValidator.h"
#include <algorithm>

ruLutCubeGenerator::ruLutCubeGenerator() {

}

ruLutCubeGenerator::~ruLutCubeGenerator() {

}

void ruLutCubeGenerator::init(  const std::vector<int8_t> &lockedEdges, const std::vector<int8_t> &ignoredEdges,
                                const std::vector<int8_t> &lockedCornersPerm, const std::vector<int8_t> &ignoredCornersPerm,
                                const std::vector<int8_t> &lockedCornersOrient, const std::vector<int8_t> &ignoredCornersOrient) {
    cornersOrientations =  orientGen.generateOrientations(6, lockedCornersOrient, ignoredCornersOrient);
    cornersPermutations =  permGen.generatePermutations(6, lockedCornersPerm, ignoredCornersPerm);
    edgesPermutations =    permGen.generatePermutations(7, lockedEdges, ignoredEdges);

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
            lexIndexCornersOrient = converter.vectCornersOrientToLexIndexCornersOrient(cornersOrientations[coIndex]);

            coIndex++;
            if (coIndex == cornersOrientations.size()) {
                coIndex = 0;
                epIndex++;
                if (epIndex >= edgesPermutations.size()) {
                    epIndex = 0;
                    cpIndex++;
                    if (cpIndex >= cornersPermutations.size()) {

                        return;
                    }
                }
            }
        } else {
            coIndex = 0;
            epIndex++;
            if (epIndex >= edgesPermutations.size()) {
                epIndex = 0;
                cpIndex++;
                if (cpIndex >= cornersPermutations.size()) {

                    hasNextCube = false;
                    return;
                }
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
