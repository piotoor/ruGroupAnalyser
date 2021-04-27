#ifndef RUCUBEFACTORY_H
#define RUCUBEFACTORY_H

#include "ruCube.h"
#include <memory>

enum class ruCubeType {
    ruCube,
    ruLutCube
};

class ruCubeFactory {
    public:
        ruCubeFactory();
        virtual ~ruCubeFactory();
        virtual std::unique_ptr<ruBaseCube> createCube(ruCubeType cubeType) const;

};

#endif // RUCUBEFACTORY_H
