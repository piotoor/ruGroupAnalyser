#ifndef RUCUBEFACTORY_H
#define RUCUBEFACTORY_H

#include "ruCube.h"
#include <memory>

namespace ruCubeFactory {
    enum class ruCubeType {
        ruCube,
        ruLutCube
    };

    std::unique_ptr<ruBaseCube> createCube(ruCubeType cubeType);
}





#endif // RUCUBEFACTORY_H
