#ifndef RUCUBESOLVEDMASKPARSER_H
#define RUCUBESOLVEDMASKPARSER_H
#include <utility>
#include <cstdint>
#include <string>

using ruCubeSolvedMaskPair = std::pair<uint64_t, uint32_t>;

namespace ruCubeSolvedMaskParser {
    ruCubeSolvedMaskPair stringSolvedMaskToInt(std::string mask);
    ruCubeSolvedMaskPair stringSolvedMaskToIntSimple(std::string mask);
};

#endif // RUCUBESOLVEDMASKPARSER_H
