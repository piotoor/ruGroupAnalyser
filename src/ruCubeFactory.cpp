#include "ruCubeFactory.h"
#include "ruException.h"

namespace ruCubeFactory {
    std::unique_ptr<ruBaseCube> createCube(ruCubeType cubeType) {
        switch (cubeType) {
        case ruCubeType::ruCube:
                return std::make_unique<ruCube>();
            case ruCubeType::ruLutCube:
                return std::make_unique<ruLutCube>();
            default:
                throw ruCubeFactoryException();
        }
    }
}
