#include "gtest/gtest.h"
#include "ruCubeFactory.h"
#include "ruException.h"


TEST(ruCubeFactoryTest, createCubeNegativeTest) {

    try {
        auto cube = ruCubeFactory::createCube(static_cast<ruCubeFactory::ruCubeType>(3));
    } catch (const ruCubeFactoryException &e) {
        ASSERT_EQ(std::string("ruCubeFactoryException: Invalid cube type"), e.what());
    }
}
