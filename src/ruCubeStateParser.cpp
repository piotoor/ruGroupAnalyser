#include "ruCubeStateParser.h"
#include <regex>
#include "ruException.h"
#include <algorithm>

namespace ruCubeStateParser {
    ruCubeStateVect stringStateToVect(std::string state) {

        std::regex stateValidator("^([0-2][0-5]){6};[0-6]{7}$");
        if (not std::regex_match (state, stateValidator)) {
            throw ruCubeStateException("Parsing exception. Invalid cube state definition.");
        }

        size_t semicolonIndex = state.find_first_of(";");
        std::string corners = state.substr(0, semicolonIndex);
        std::string edges = state.substr(semicolonIndex + 1);

        cornersArray cornersPerm;
        cornersArray cornersOrient;
        for (size_t i = 0; i < size(corners); ++i) {
            if (i % 2 == 0) {
                cornersOrient[i / 2] = corners[i] - '0';
            } else {
                cornersPerm[i / 2] = corners[i] - '0';
            }
        }

        edgesArray edgesPerm;
        for (size_t i = 0; i < size(edges); ++i) {
            edgesPerm[i] = edges[i] - '0';
        }

        return std::make_tuple(cornersOrient, cornersPerm, edgesPerm);
    }

}
