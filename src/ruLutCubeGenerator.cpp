#include "ruLutCubeGenerator.h"
#include "ruCubeStateValidator.h"
#include <algorithm>

ruLutCubeGenerator::ruLutCubeGenerator() {

}

ruLutCubeGenerator::~ruLutCubeGenerator() {

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
        //filler.permutationIgnoredGapsFillInit(cornersPermutations[cpIndex], edgesPermutations[epIndex]);
        filler.permutationIgnoredGapsFillInit(currCornersPerm, currEdgesPerm);

        while (not found and filler.permutationIgnoredGapsFillNext(currCornersPerm, currEdgesPerm)) {
        //while (not found and filler.permutationIgnoredGapsFillNext(cornersPermutations[cpIndex], edgesPermutations[epIndex])) {
            //lexIndexCornersPerm = converter.vectCornersPermToLexIndexCornersPerm(cornersPermutations[cpIndex]);
            lexIndexCornersPerm = converter.vectCornersPermToLexIndexCornersPerm(currCornersPerm);
            //lexIndexEdgesPerm = converter.vectEdgesPermToLexIndexEdgesPerm(edgesPermutations[epIndex]);
            lexIndexEdgesPerm = converter.vectEdgesPermToLexIndexEdgesPerm(currEdgesPerm);
            if (ruLutCube::isPermutationSolveable(lexIndexCornersPerm, lexIndexEdgesPerm)) {
//                std::cout << std::oct << converter.vectCornersToIntCorners(currCornersPerm, {0,0,0,0,0,0}) << " ";
//                std::cout << std::oct << converter.vectEdgesToIntEdges(currEdgesPerm) << std::endl;
                found = true;
            }
        }

        if (found) {
            hasNextCube = true;

            cornersArray cornersOrientationPermuted;
            for (uint8_t i = 0; i < size(cornersOrientationPermuted); ++i) {
                //cornersOrientationPermuted[i] = cornersOrientations[coIndex][cornersPermutations[cpIndex][i]];
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
    ruLutCube ans(lexIndexEdgesPerm, lexIndexCornersPerm, lexIndexCornersOrient);
    generateNextCube();
    return ans;
}

bool ruLutCubeGenerator::hasNext() {
    return hasNextCube;
}

