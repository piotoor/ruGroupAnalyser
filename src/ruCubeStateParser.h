#ifndef RUCUBESTATEPARSER_H
#define RUCUBESTATEPARSER_H
#include "ruCube.h"
#include <string>


using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;
using ruCubeStateVect = std::tuple<cornersArray, cornersArray, edgesArray>;

namespace ruCubeStateParser {
     ruCubeStateVect stringStateToVect(std::string state);
}

#endif // RUCUBESTATEPARSER_H
