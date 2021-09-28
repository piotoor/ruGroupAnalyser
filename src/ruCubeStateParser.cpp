#include "ruCubeStateParser.h"
#include <regex>
#include "ruException.h"
#include <algorithm>

namespace ruCubeStateParser {
    ruCubeStateVect stringStateToVect(std::string state) {

        size_t noOfSemicolons = std::count (begin(state), end(state), ';');
        if (noOfSemicolons != 1) {
            throw ruCubeStateException("Parsing exception. Invalid cube state definition. Wrong number of sections.");
        }
        size_t semicolonIndex = state.find_first_of(";");
        std::string corners = state.substr(0, semicolonIndex);
        std::string edges = state.substr(semicolonIndex + 1);

        cornersArray cornersPerm;
        cornersArray cornersOrient;
        std::regex cornersValidator("^([0-2][0-5]){6}$");

        if (not std::regex_match (corners, cornersValidator)) {
            throw ruCubeStateException("Parsing exception. Invalid cube state definition. Wrong corners format.");
        }

        for (uint8_t i = 0; i < size(corners); ++i) {
            if (i % 2 == 0) {
                cornersOrient[i / 2] = corners[i] - '0';
            } else {
                cornersPerm[i / 2] = corners[i] - '0';
            }
        }

        edgesArray edgesPerm;
        std::regex edgesValidator("^[0-6]{7}$");

        if (not std::regex_match (edges, edgesValidator)) {
            throw ruCubeStateException("Parsing exception. Invalid cube state definition. Wrong edges format.");
        }

        for (uint8_t i = 0; i < size(edges); ++i) {
            edgesPerm[i] = edges[i] - '0';
        }

        return std::make_tuple(cornersPerm, cornersOrient, edgesPerm);
    }

}
