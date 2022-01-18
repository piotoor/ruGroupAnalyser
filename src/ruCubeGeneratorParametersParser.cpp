#include "ruCubeGeneratorParametersParser.h"
#include <regex>
#include "ruException.h"

namespace ruCubeGeneratorParametersParser {
    generatorParameters strGeneratorParametersToStruct(std::string strGenParams) {
        std::regex genParamsValidator("^([GI012][GIL]){6};[GIL]{7}$");
        if (not std::regex_match (strGenParams, genParamsValidator)) {
            throw ruCubeGeneratorParametersException("Parsing exception. Invalid cube generator parameters.");
        }

        generatorParameters ans;
        size_t semicolonIndex = strGenParams.find_first_of(";");
        std::string corners = strGenParams.substr(0, semicolonIndex);
        std::string edges = strGenParams.substr(semicolonIndex + 1);

        for (size_t i = 0; i < size(corners); ++i) {
            if (i % 2 == 0) {
                if (corners[i] == 'I' or corners[i] == 'i') {
                    ans.ignoredCornersOrient[i / 2] = 1;
                } else if (isdigit(corners[i])) {
                    ans.lockedCornersOrient[i / 2] = corners[i] - '0';
                }

            } else {
                if (corners[i] == 'I' or corners[i] == 'i') {
                    ans.ignoredCornersPerm.insert(i / 2);
                } else if (corners[i] == 'L' or corners[i] == 'l') {
                    ans.lockedCornersPerm.insert(i / 2);
                }
            }
        }

        for (size_t i = 0; i < size(edges); ++i) {
            if (edges[i] == 'I' or edges[i] == 'i') {
                ans.ignoredEdges.insert(i);
            } else if (edges[i] == 'L' or edges[i] == 'l') {
                ans.lockedEdges.insert(i);
            }
        }

        return ans;
    }
}
