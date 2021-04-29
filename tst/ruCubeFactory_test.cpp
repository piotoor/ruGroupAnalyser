#include "gtest/gtest.h"
#include "ruCubeFactory.h"
#include "ruException.h"


TEST(ruCubeFactoryTest, createCubeNegativeTest) {
    ruCubeFactory factory;

    try {
        auto cube = factory.createCube(static_cast<ruCubeType>(3));
    } catch (const ruCubeFactoryException &e) {
        ASSERT_EQ(std::string("ruCubeFactoryException: Invalid cube type"), e.what());
    }
}
