#include "ruCubeSolvedMaskParser.h"
#include <regex>
#include "ruException.h"
#include <string>
#include <iostream>

// co, cp, ep
using ruCubeSolvedMaskPair = std::pair<uint64_t, uint32_t>;
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

    ruCubeSolvedMaskPair stringSolvedMaskToIntSimple(std::string mask) {
        std::regex maskValidator("^[0-1]{12};[0-1]{7}$");
        if (not std::regex_match (mask, maskValidator)) {
            throw ruCubeSolvedMaskException("Parsing exception. Invalid cube solved mask definition.");
        }

        size_t semicolonIndex = mask.find_first_of(";");
        std::string corners = mask.substr(0, semicolonIndex);
        std::string edges = mask.substr(semicolonIndex + 1);

        std::reverse(begin(corners), end(corners));
        std::reverse(begin(edges), end(edges));

        std::bitset<64> cornersBits;
        std::bitset<32> edgesBits;

        for (size_t i = 0; i < size(corners); ++i) {
            if (i % 2 != 0) {
                cornersBits[32 + i / 2] = corners[i] - '0';
            } else {
                cornersBits[i / 2] = corners[i] - '0';
            }
        }

        for (size_t i = 0; i < size(edges); ++i) {
            edgesBits[i] = edges[i] - '0';
        }


        return std::make_pair(static_cast<uint64_t>(cornersBits.to_ullong()), static_cast<uint32_t>(edgesBits.to_ullong()));
    }
}

