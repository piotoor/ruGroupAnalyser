#include "ruCubeFactory.h"
#include "ruException.h"

//return std::make_unique<StandardGameStyleAgent>();


ruCubeFactory::ruCubeFactory() {

}

ruCubeFactory::~ruCubeFactory() {

}


std::unique_ptr<ruBaseCube> ruCubeFactory::createCube(ruCubeType cubeType) const {
    switch (cubeType) {
    case ruCubeType::ruCube:
            return std::make_unique<ruCube>();
        case ruCubeType::ruLutCube:
            // generate lut table first time it gets there
            // inject the dependency to lut cube
            //return std::make_unique<ruLutCube>();
        default:
            throw ruCubeFactoryException();
    }

}
