#include "ruCubeSolvedMaskParser.h"
#include <regex>
#include "ruException.h"
#include <string>
#include <iostream>

// co, cp, ep
namespace ruCubeSolvedMaskParser {
    ruCubeSolvedMaskPair stringSolvedMaskToInt(std::string mask) {
        std::regex maskValidator("^[0-9A-F]{8};[0-9A-F]{8};[0-9A-F]{8}$");
        if (not std::regex_match (mask, maskValidator)) {
            throw ruCubeSolvedMaskException("Parsing exception. Invalid cube solved mask definition.");
        }

        std::string cornersOrient = mask.substr(0, 8);
        std::string cornersPerm = mask.substr(9, 8);
        std::string edgesPerm = mask.substr(18);

        uint64_t corners = static_cast<uint64_t>(std::stoull(cornersOrient, nullptr, 16)) << (8 * sizeof(uint32_t));
        corners |= static_cast<uint64_t>(std::stoull(cornersPerm, nullptr, 16));
        uint32_t edges = static_cast<uint32_t>(std::stoull(edgesPerm, nullptr, 16));

        return std::make_pair(corners, edges);
    }

    ruCubeSolvedMaskPair stringSolvedMaskToVectSimple(std::string mask) {

    }
}
