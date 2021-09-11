#include "ruLutCubeGenerator.h"
#include "ruCubeStateValidator.h"
#include <list>

ruLutCubeGenerator::ruLutCubeGenerator() {

}

ruLutCubeGenerator::~ruLutCubeGenerator() {

}

std::vector<ruLutCube> ruLutCubeGenerator::generateCubes(const std::vector<int8_t> &lockedEdges, const std::vector<int8_t> &ignoredEdges,
                                     const std::vector<int8_t> &lockedCornersPerm, const std::vector<int8_t> &ignoredCornersPerm,
                                     const std::vector<int8_t> &lockedCornersOrient, const std::vector<int8_t> &ignoredCornersOrient) {
    std::vector<ruLutCube> ans;
    std::list<ruLutCube> ans2;
    auto cornersOrientations =  orientGen.generateOrientations(6, lockedCornersOrient, ignoredCornersOrient);
    auto cornersPermutations =  permGen.generatePermutations(6, lockedCornersPerm, ignoredCornersPerm);
    auto edgesPermutations =    permGen.generatePermutations(7, lockedEdges, ignoredEdges);

    int k = 0;
    std::cout << "sizeof(lutCube) = " << sizeof(ruLutCube) << std::endl;
    for (auto &cp: cornersPermutations) {
        int w = 0;
        std::cin >> w;
        for (auto &ep: edgesPermutations) {
            filler.permutationIgnoredGapsFillInit(cp, ep);
            bool found = false;
            while (filler.permutationIgnoredGapsFillNext(cp, ep)) {
                if (validator.isVectCubePermSolveableQuick(cp, ep)) {
                    found = true;
                    break;
                }
            }

            if (found) {
                for (const auto &co: cornersOrientations) {
                    ans2.emplace_back(   converter.vectEdgesPermToLexIndexEdgesPerm(ep),
                                        converter.vectCornersPermToLexIndexCornersPerm(cp),
                                        converter.vectCornersOrientToLexIndexCornersOrient(co));
                    std::cout << "k = " << (int) ++k << std::endl;
                }
            }
        }
    }

    return ans;
}
