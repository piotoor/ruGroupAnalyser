#ifndef RUCUBESTATEPARSER_H
#define RUCUBESTATEPARSER_H
#include "ruCube.h"
#include <string>

using ruCubeStateVect = std::tuple<cornersArray, cornersArray, edgesArray>;

namespace ruCubeStateParser {
     ruCubeStateVect stringStateToVect(std::string state);
};

#endif // RUCUBESTATEPARSER_H
